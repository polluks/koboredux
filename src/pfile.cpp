/*(LGPLv2.1)
---------------------------------------------------------------------------
	pfile.cpp - Portable File Access Toolkit
---------------------------------------------------------------------------
 * Copyright 2002, 2003, 2009, 2017 David Olofson
 *
 * This library is free software;  you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation;  either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library  is  distributed  in  the hope that it will be useful,  but
 * WITHOUT   ANY   WARRANTY;   without   even   the   implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library;  if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#define	DBG(x)
#define	LOGLEVEL	ULOG	/* LOGLEVEL */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kobo.h"
#include "kobolog.h"
#include "pfile.h"


#ifdef WIN32
time_t timegm(struct tm *brokentime)
{
	time_t t;
	char *tz = getenv("TZ");
	if(tz)
	{
		tz = strdup(tz);
		_putenv_s("TZ", "UTC");
	}
	tzset();
	t = mktime(brokentime);
	if(tz)
	{
		_putenv_s("TZ", tz);
		free(tz);
	}
	else
		putenv("TZ=");
	tzset();
	return t;
}
#endif


/*----------------------------------------------------------
	Constructor/Destructor
----------------------------------------------------------*/

pfile_t::pfile_t(FILE *file)
{
	f = file;
	_status = 0;
	bufsize = bufused = bufpos = 0;
	buffer = NULL;
	chunk_id = 0;
	chunk_ver = 0;
	chunk_writing = false;
}


pfile_t::~pfile_t()
{
	buffer_close();
}


/*----------------------------------------------------------
	Internal buffer control
----------------------------------------------------------*/

int pfile_t::buffer_init()
{
	buffer_close();

	bufsize = 1024;
	buffer = (char *)malloc(bufsize);
	if(!buffer)
		return status(-1);

	bufused = bufpos = 0;
	return _status;
}


int pfile_t::buffer_write()
{
	DBG(log_printf(LOGLEVEL, "pfile_t::buffer_write() %d bytes\n",
			bufused);)
	if(fwrite(buffer, bufused, 1, f) != 1)
		return status(-1);

	bufused = bufpos = 0;
	return _status;
}


int pfile_t::buffer_read(int len)
{
	DBG(log_printf(LOGLEVEL, "pfile_t::buffer_read() %d bytes\n", len);)

	buffer_close();

	bufsize = len;
	buffer = (char *)malloc(bufsize);
	if(!buffer)
		return status(-1);

	if(fread(buffer, bufsize, 1, f) != 1)
	{
		buffer_close();
		return status(-1);
	}

	bufused = bufsize;
	bufpos = 0;
	return _status;
}


void pfile_t::buffer_close()
{
	free(buffer);
	buffer = NULL;
	bufsize = bufused = bufpos = 0;
}


int pfile_t::read(void *data, int len)
{
	if(_status < 0)
		return _status;

	if(buffer)
	{
		if(bufpos + len > bufused)
			return -1;
		memcpy(data, buffer + bufpos, len);
		bufpos += len;
		return len;
	}
	else
	{
		if(fread(data, len, 1, f) != 1)
			return status(-1);
		return len;
	}
}


int pfile_t::write(const void *data, int len)
{
	if(_status < 0)
		return _status;

	if(bufused + len > bufsize)
	{
		int nbs = (bufused + len) * 3 / 2;
		char *nb = (char *)realloc(buffer, nbs);
		if(!nb)
			return -1;
		buffer = nb;
		bufsize = nbs;
	}
	memcpy(buffer + bufused, data, len);
	bufused += len;
	return len;
}



/*----------------------------------------------------------
	Status
----------------------------------------------------------*/

int pfile_t::status()
{
	int os = _status;
	_status = 0;
	return os;
}


int pfile_t::status(int new_status)
{
	if(_status >= 0)
		_status = new_status;
	return _status;
}


/*----------------------------------------------------------
	Little endian read/write API
----------------------------------------------------------*/

int pfile_t::read(uint32_t &x)
{
	unsigned char b[4];
	int result = read(&b, 4);
	if(4 == result)
		x = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
	DBG(log_printf(LOGLEVEL, "    read uint32 %u/0x%x\n", x, x);)
	return result;
}


int pfile_t::read(int32_t &x)
{
	unsigned char b[4];
	int result = read(&b, 4);
	if(4 == result)
		x = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
	DBG(log_printf(LOGLEVEL, "    read int32 %d/0x%x\n", x, x);)
	return result;
}


int pfile_t::read(int16_t &x)
{
	unsigned char b[2];
	int result = read(&b, 2);
	if(2 == result)
		x = b[0] | (b[1] << 8);
	DBG(log_printf(LOGLEVEL, "    read int16 %d/0x%x\n", x, x);)
	return result;
}


int pfile_t::read(int8_t &x)
{
	int result = read(&x, 1);
	DBG(log_printf(LOGLEVEL, "    read int8 %d/0x%x\n", x, x);)
	return result;
}


int pfile_t::write(uint32_t x)
{
	DBG(log_printf(LOGLEVEL, "    write uint32 %u/0x%x\n", x, x);)
	unsigned char b[4];
	b[0] = x & 0xff;
	b[1] = (x >> 8) & 0xff;
	b[2] = (x >> 16) & 0xff;
	b[3] = (x >> 24) & 0xff;
	return status(write(&b, 4));
}


int pfile_t::write(int32_t x)
{
	DBG(log_printf(LOGLEVEL, "    write int32 %d/0x%x\n", x, x);)
	unsigned char b[4];
	b[0] = x & 0xff;
	b[1] = (x >> 8) & 0xff;
	b[2] = (x >> 16) & 0xff;
	b[3] = (x >> 24) & 0xff;
	return status(write(&b, 4));
}


int pfile_t::write(int16_t x)
{
	DBG(log_printf(LOGLEVEL, "    write int16 %d/0x%x\n", x, x);)
	unsigned char b[2];
	b[0] = x & 0xff;
	b[1] = (x >> 8) & 0xff;
	return status(write(&b, 2));
}


int pfile_t::write(int8_t x)
{
	DBG(log_printf(LOGLEVEL, "    write int8 %d/0x%x\n", x, x);)
	return status(write(&x, 1));
}


/*----------------------------------------------------------
	Unbuffered Write API
----------------------------------------------------------*/
int pfile_t::write_ub(const void *data, int len)
{
	if(fwrite(data, len, 1, f) != 1)
		return status(-1);

	return _status;
}


int pfile_t::write_ub(uint32_t x)
{
	unsigned char b[4];
	b[0] = x & 0xff;
	b[1] = (x >> 8) & 0xff;
	b[2] = (x >> 16) & 0xff;
	b[3] = (x >> 24) & 0xff;
	return status(write_ub(&b, 4));
}


int pfile_t::write_ub(int32_t x)
{
	return status(write_ub((uint32_t)x));
}


int pfile_t::write_ub_align(int alignment)
{
	if(alignment <= 1)
		return 0;

	int a = ftell(f);
	if(a < 0)
		return status(a);

	a = alignment - a % alignment;
	if(a != alignment)
	{
		if(prefs->debug)
			log_printf(LOGLEVEL, "pfile_t::write_ub_align(): "
					"%d pad byte%s\n",
					a, a > 1 ? "s" : "");
		while(a--)
			if(putc(0, f) < 0)
				return status(-1);
	}
	return _status;
}


/*----------------------------------------------------------
	RIFF style chunk API
----------------------------------------------------------*/

const char *pfile_t::fourcc2string(unsigned int c)
{
	fourccbuf[0] = c & 0xff;;
	fourccbuf[1] = (c >> 8) & 0xff;;
	fourccbuf[2] = (c >> 16) & 0xff;;
	fourccbuf[3] = (c >> 24) & 0xff;;
	fourccbuf[4] = 0;
	return fourccbuf;
}


int pfile_t::chunk_read()
{
	chunk_writing = false;

	// Read FourCC, skipping any leading zero pad bytes
	int8_t buf[4];
	buf[0] = 0;
	while(!buf[0])
		if(read(buf[0]) != 1)
			return _status;
	for(int i = 1; i < 4; ++i)
		if(read(buf[i]) != 1)
			return _status;
	chunk_id = MAKE_4CC(buf[0], buf[1], buf[2], buf[3]);

	if(read(chunk_ver) != 4)
		return _status;

	uint32_t size;
	if(read(size) != 4)
		return _status;

	DBG(log_printf(LOGLEVEL, "  reading %sv%d chunk, %d bytes\n",
			fourcc2string(chunk_id), chunk_ver, size));
	return buffer_read(size);
}


int pfile_t::chunk_write(uint32_t id, int32_t version)
{
	DBG(log_printf(LOGLEVEL, "  writing %sv%d chunk\n",
			fourcc2string(id), version));
	if(!(id & 0xff))
	{
		log_printf(ELOG, "Illegal FourCC; must not start with 0!\n");
		return status(-1);
	}
	chunk_writing = true;
	chunk_id = id;
	chunk_ver = version;
	buffer_init();
	return _status;
}


int pfile_t::chunk_end()
{
	if(!buffer)
	{
		log_printf(ELOG, "pfile_t::chunk_end() with no chunk!\n");
		return status(-1);
	}
	if(chunk_writing)
	{
		write_ub_align(PFILE_ALIGN);
		write_ub(chunk_id);
		write_ub(chunk_ver);
		write_ub(bufused);
		buffer_write();
		chunk_writing = false;
		DBG(log_printf(LOGLEVEL, "  wrote %s chunk, %d bytes\n",
				fourcc2string(chunk_id), bufused));
	}
	buffer_close();
	return _status;
}


/*----------------------------------------------------------
	read()/write() for additional data types
----------------------------------------------------------*/

typedef struct {
	int16_t	year;
	int16_t	yday;
	int8_t	sec;
	int8_t	min;
	int8_t	hour;
	int8_t	mday;
	int8_t	mon;
	int8_t	wday;
	int8_t	isdst;
	int8_t	pad;
} pfile_tm_t;


int pfile_t::read(struct tm &t)
{
	int len = 0;
	pfile_tm_t pftm;
	DBG(log_printf(LOGLEVEL, "   time {\n");)
	len += read(pftm.year);
	len += read(pftm.yday);
	len += read(pftm.sec);
	len += read(pftm.min);
	len += read(pftm.hour);
	len += read(pftm.mday);
	len += read(pftm.mon);
	len += read(pftm.wday);
	len += read(pftm.isdst);
	len += read(pftm.pad);
	if(_status)
		return _status;

	t.tm_year = pftm.year;
	t.tm_yday = pftm.yday;
	t.tm_sec = pftm.sec;
	t.tm_min = pftm.min;
	t.tm_hour = pftm.hour;
	t.tm_mday = pftm.mday;
	t.tm_mon = pftm.mon;
	t.tm_wday = pftm.wday;
	t.tm_isdst = pftm.isdst;
	DBG(time_t tt = mktime(&t);)
	DBG(log_printf(LOGLEVEL, "   } // %s", ctime(&tt));)
	return len;
}


int pfile_t::write(const struct tm *t)
{
	int len = 0;
	pfile_tm_t pftm;
	memset(&pftm, 0, sizeof(pftm));
	if(t)
	{
		pftm.year = t->tm_year;
		pftm.yday = t->tm_yday;
		pftm.sec = t->tm_sec;
		pftm.min = t->tm_min;
		pftm.hour = t->tm_hour;
		pftm.mday = t->tm_mday;
		pftm.mon = t->tm_mon;
		pftm.wday = t->tm_wday;
		pftm.isdst = t->tm_isdst;
	}
	DBG(if(t)
	{
		struct tm t2 = *t;
		time_t tt = mktime(&t2);
		log_printf(LOGLEVEL, "   time { // %s", ctime(&tt));
	}
	else
		log_printf(LOGLEVEL, "   time {\n");)
	len += write(pftm.year);
	len += write(pftm.yday);
	len += write(pftm.sec);
	len += write(pftm.min);
	len += write(pftm.hour);
	len += write(pftm.mday);
	len += write(pftm.mon);
	len += write(pftm.wday);
	len += write(pftm.isdst);
	len += write(pftm.pad);
	DBG(log_printf(LOGLEVEL, "   }\n"));
	if(_status)
		return _status;
	else
		return len;
}
