/*(GPLv2)
------------------------------------------------------------
   Kobo Deluxe - An enhanced SDL port of XKobo
------------------------------------------------------------
 * Copyright 1995, 1996 Akira Higuchi
 * Copyright 2001-2003, 2007, 2009 David Olofson
 * Copyright 2015-2017 David Olofson (Kobo Redux)
 * 
 * This program  is free software; you can redistribute it and/or modify it
 * under the terms  of  the GNU General Public License  as published by the
 * Free Software Foundation;  either version 2 of the License,  or (at your
 * option) any later version.
 *
 * This program is  distributed  in  the hope that  it will be useful,  but
 * WITHOUT   ANY   WARRANTY;   without   even   the   implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received  a copy of the GNU General Public License along
 * with this program; if not,  write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "screen.h"
#include "manage.h"
#include "enemies.h"
#include "myship.h"
#include "random.h"
#include "kobolog.h"
#include "mathutil.h"
#include <math.h>


/*
 * ===========================================================================
 *                                (template)
 * ===========================================================================
 */

inline void KOBO_enemy::move_enemy_m(int quick, int maxspeed)
{
	if(diffx > 0)
	{
		if(h > -maxspeed)
			h -= quick;
	}
	else if(diffx < 0)
	{
		if(h < maxspeed)
			h += quick;
	}
	if(diffy > 0)
	{
		if(v > -maxspeed)
			v -= quick;
	}
	else if(diffy < 0)
	{
		if(v < maxspeed)
			v += quick;
	}
}

inline void KOBO_enemy::move_enemy_template(int quick, int maxspeed)
{
	if(diffx > 0)
	{
		if(h > -maxspeed)
			h -= quick;
	}
	else if(diffx < 0)
	{
		if(h < maxspeed)
			h += quick;
	}
	if(diffy > 0)
	{
		if(v > -maxspeed)
			v -= quick;
	}
	else if(diffy < 0)
	{
		if(v < maxspeed)
			v += quick;
	}
	int ndi = speed2dir(h, v, frames);
	if(ndi > 0)
		di = ndi;
}

inline void KOBO_enemy::move_enemy_template_2(int quick, int maxspeed)
{
	h = -PIXEL2CS(diffy) >> quick;
	v = PIXEL2CS(diffx) >> quick;

	if(diffx > 0)
	{
		if(h > -maxspeed)
			h -= quick;
	}
	else if(diffx < 0)
	{
		if(h < maxspeed)
			h += quick;
	}
	if(diffy > 0)
	{
		if(v > -maxspeed)
			v -= quick;
	}
	else if(diffy < 0)
	{
		if(v < maxspeed)
			v += quick;
	}
	int ndi = speed2dir(h, v, frames);
	if(ndi > 0)
		di = ndi;
}

inline void KOBO_enemy::move_enemy_template_3(int quick, int maxspeed)
{
	h = PIXEL2CS(diffy) >> quick;
	v = -PIXEL2CS(diffx) >> quick;

	if(diffx > 0)
	{
		if(h > -maxspeed)
			h -= quick;
	}
	else if(diffx < 0)
	{
		if(h < maxspeed)
			h += quick;
	}
	if(diffy > 0)
	{
		if(v > -maxspeed)
			v -= quick;
	}
	else if(diffy < 0)
	{
		if(v < maxspeed)
			v += quick;
	}
	int ndi = speed2dir(h, v, frames);
	if(ndi > 0)
		di = ndi;
}

inline void KOBO_enemy::launch(const KOBO_enemy_kind *ekp)
{
	if(prefs->cheat_ceasefire || enemies.is_intro || !myship.alive())
		return;

	int v0 = ekp->launchspeed ? ekp->launchspeed : DEFAULT_LAUNCH_SPEED;
	if(ekp->is_bullet())
		v0 *= game.bullet_speed;
	else
		v0 *= game.launch_speed;
	int norm = (int)sqrt(diffx * diffx + diffy * diffy);
	if(!norm)
		return;

	int vx = v0 * -diffx / norm;
	int vy = v0 * -diffy / norm;
	enemies.make(ekp, x + vx, y + vy, vx, vy);
	playsound(ekp->launchsound);
}

void KOBO_enemy::shot_template_8_dir(const KOBO_enemy_kind *ekp)
{
	if(prefs->cheat_ceasefire || enemies.is_intro || !myship.alive())
		return;

	static int vx[] = { 0, 200, 300, 200, 0, -200, -300, -200 };
	static int vy[] = { -300, -200, 0, 200, 300, 200, 0, -200 };
	int vsc = ekp->is_bullet() ? game.bullet_speed : game.launch_speed;
	int i;
	for(i = 0; i < 8; i++)
		enemies.make(ekp, x, y, vx[i] * vsc >> 8, vy[i] * vsc >> 8);
	playsound(ekp->launchsound);
}

void KOBO_enemy::explode()
{
	KOBO_ParticleFXDef *pfxd = themedata.pfxdef(ek->deathpfx);
	if(pfxd)
		wfire->Spawn(x + h, y + v, h, v, pfxd);
}

void KOBO_enemy::kill_default()
{
	explode();
	die();
}

void KOBO_enemy::kill_silent()
{
	release();
}

void KOBO_enemy::kill_unused()
{
	log_printf(WLOG, "KOBO_enemy::kill_unused() called by '%s'!\n",
			enemies.enemy_name(ek->eki));
	release();
}

void KOBO_enemy::player_collision(int dx, int dy)
{
	if(!physics)
	{
		if(detonate_on_contact)
			detonate();		// Object detonates!
		else
			hit(game.ram_damage);	// Ship damages object
		myship.hit(damage);		// Object damages ship
		return;
	}

	// "Physics enabled" objects have bounding circles!
	int d = sqrt(dx * dx + dy * dy);
	contact = PIXEL2CS(hitsize + myship.get_hitsize()) - d;
	if(contact <= 0)
	{
		contact = 0;
		return;		// No intersection!
	}

	// Detonate-on-contact needs no physics. (Unless we knock things around
	// when dealing splash damage, but that doesn't belong here anyway.)
	if(detonate_on_contact)
	{
		detonate();		// Object detonates!
		myship.hit(damage);	// Object delivers full damage to ship
		return;
	}

	// Relative velocity
	int dvx = h - myship.get_velx();
	int dvy = v - myship.get_vely();

	// Only apply impulses if the objects are moving towards each other!
	if(dvx * dx + dvy * dy < 0)
	{
		// Calculate impulse based on contact point and velocity
		//
		// TODO:
		//	Do away with some trig functions - not because it's
		//	likely worth the effort performance wise, but because
		//	it would be nice to keep the game logic all integer and
		//	fully deterministic!
		//
		float da = atan2f(dy, dx);
		float dva = atan2f(dvy, dvx);
		float ra = da - dva;
		float cosra = cos(ra);
		float sinra = sin(ra);
		int ix = (dvx * cosra - dvy * sinra) * cosra;
		int iy = (dvx * sinra + dvy * cosra) * cosra;

		// Velocity dependent damage!
		int vel = sqrt(ix * ix + iy * iy);
		hit(game.scale_vel_damage(vel, game.ram_damage));
		myship.hit(game.scale_vel_damage(vel, damage));

		// Scale impulse for desired bounciness
		ix = (256 + (KOBO_ENEMY_BOUNCE)) * ix >> 9;
		iy = (256 + (KOBO_ENEMY_BOUNCE)) * iy >> 9;

		// Apply impulse! (All objects have identical mass...)
		h -= ix;
		v -= iy;
		myship.impulse(ix, iy);
	}

	// Since initial intersection and impulse rounding errors can allow
	// objects to creep into each other, we nudge them back to right at the
	// point of contact here.
	x += contact * dx / d;
	y += contact * dy / d;
}

void KOBO_enemy::render_hit_zone()
{
	if(!object)
		return;
	int r = PIXEL2CS(hitsize);
	if(physics)
	{
		if(contact)
			woverlay->foreground(woverlay->map_rgb(255, 128, 0));
		else
			woverlay->foreground(woverlay->map_rgb(128, 0, 128));
		woverlay->circle_fxp(object->point.gx, object->point.gy, r);
	}
	else
	{
		woverlay->foreground(woverlay->map_rgb(128, 0, 128));
		woverlay->hairrect_fxp(object->point.gx - r,
				object->point.gy - r, 2 * r, 2 * r);
	}
}


/*
 * ===========================================================================
 *                                bullets
 * ===========================================================================
 */

void KOBO_enemy::make_bullet1()
{
	if(frames)
		di = 1 + pubrand.get(8) % frames;
	else
		di = 1;
	health = 1;
	shootable = false;
	physics = false;
	damage = 10;
	takes_splash_damage = false;
	detonate_on_contact = true;
}

void KOBO_enemy::make_bullet2()
{
	make_bullet1();
	damage = 20;
}

void KOBO_enemy::make_bullet3()
{
	make_bullet1();
	damage = 40;
}

void KOBO_enemy::move_bullet()
{
	if(mindiff >= ((VIEWLIMIT >> 1) + 32))
		release();
	++di;
	if(di > frames)
		di = 1;
}

void KOBO_enemy::kill_bullet1()
{
	enemies.make(&bluebltexpl, x, y);
	release();
}

void KOBO_enemy::kill_bullet2()
{
	enemies.make(&greenbltexpl, x, y);
	release();
}

void KOBO_enemy::kill_bullet3()
{
	enemies.make(&redbltexpl, x, y);
	release();
}

const KOBO_enemy_kind bullet1 = {
	KOBO_EK_BULLET1,
	0,
	&KOBO_enemy::make_bullet1,
	&KOBO_enemy::move_bullet,
	&KOBO_enemy::kill_bullet1,
	2,
	B_BLT_BLUE, 0,
	LAYER_BULLETS,
	5,
	KOBO_EK_FX(BULLET1)
};

const KOBO_enemy_kind bullet2 = {
	KOBO_EK_BULLET2,
	0,
	&KOBO_enemy::make_bullet2,
	&KOBO_enemy::move_bullet,
	&KOBO_enemy::kill_bullet2,
	2,
	B_BLT_GREEN, 0,
	LAYER_BULLETS,
	3,
	KOBO_EK_FX(BULLET2)
};

const KOBO_enemy_kind bullet3 = {
	KOBO_EK_BULLET3,
	0,
	&KOBO_enemy::make_bullet3,
	&KOBO_enemy::move_bullet,
	&KOBO_enemy::kill_bullet3,
	2,
	B_BLT_RED, 0,
	LAYER_BULLETS,
	2,
	KOBO_EK_FX(BULLET3)
};


/*
 * ===========================================================================
 *                                rock
 * ===========================================================================
 */

void KOBO_enemy::make_rock()
{
	health = game.rock_health;
	damage = game.rock_damage;
	di = gamerand.get(5);
	a = gamerand.get(1) ? 1 : -1;
	switch(gamerand.get() % 3)
	{
	  case 0:
		set_bank(B_ROCK1);
		break;
	  case 1:
		set_bank(B_ROCK2);
		break;
	  case 2:
		set_bank(B_ROCK3);
		break;
	}
}

void KOBO_enemy::move_rock()
{
	di = ((di + a - 1) & 31) + 1;
}

void KOBO_enemy::kill_rock()
{
	enemies.make(&rockexpl, x, y, h >> 1, v >> 1);
	die();
}

const KOBO_enemy_kind rock = {
	KOBO_EK_ROCK,
	10,
	&KOBO_enemy::make_rock,
	&KOBO_enemy::move_rock,
	&KOBO_enemy::kill_rock,
	12,
	B_ROCK1, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ROCK)
};


/*
 * ===========================================================================
 *                                ring
 * ===========================================================================
 */

void KOBO_enemy::make_ring()
{
	physics = false;
	detonate_on_contact = true;
	health = 20;
	damage = 30;
	di = 0;
}

void KOBO_enemy::move_ring()
{
	di += 1 + pubrand.get(1);
	if(di > frames)
		di = 1;
}

void KOBO_enemy::kill_ring()
{
	enemies.make(&ringexpl, x, y, h >> 1, v >> 1);
	die();
}

const KOBO_enemy_kind ring = {
	KOBO_EK_RING,
	1,
	&KOBO_enemy::make_ring,
	&KOBO_enemy::move_ring,
	&KOBO_enemy::kill_ring,
	4,
	B_RING, 0,
	LAYER_BULLETS,
	0,
	KOBO_EK_FX(RING)
};


/*
 * ===========================================================================
 *                                bomb
 * ===========================================================================
 */

void KOBO_enemy::make_bomb()
{
	physics = false;
	health = 20;
	damage = 70;
	di = 0;
	c = 0;		// Trigger-to-detonation timer
}

void KOBO_enemy::move_bomb1()
{
	if(c)
	{
		frame = 32;
		di = 1 + di % 6;
	}
	else
	{
		frame = 0;
		di = 1 + di % 16;
	}

	int h1 = labs(diffx);
	int v1 = labs(diffy);
	if(((h1 < 100) && (v1 < 30)) || ((h1 < 30) && (v1 < 100)))
	{
		if(!c)
			startsound(S_BOMB1_TRIG);
		++c;
	}
	else
	{
		stopsound();
		c = 0;
	}
	if((c < game.bomb_delay) || prefs->cheat_brokentrigger ||
			prefs->cheat_ceasefire || enemies.is_intro ||
			!myship.alive())
		return;

	// Detonate!
	int vx1 = PIXEL2CS(-diffx) / (3*8);
	int vy1 = PIXEL2CS(-diffy) / (3*8);
	int vx2 = vx1, vx3 = vx1;
	int vy2 = vy1, vy3 = vy1;
	int i;
	for(i = 0; i < 4; i++)
	{
		int tmp = vx2;
		vx2 += (vy2 >> 4);
		vy2 -= (tmp >> 4);
		tmp = vx3;
		vx3 -= (vy3 >> 4);
		vy3 += (tmp >> 4);
	}
	enemies.make(&bullet3, x, y, vx2, vy2);
	enemies.make(&bullet3, x, y, vx3, vy3);
	KOBO_ParticleFXDef *pfxd = themedata.pfxdef(KOBO_PFX_BOMB1DETO);
	if(pfxd)
		wfire->Spawn(x + h, y + v, vx1, vy1, pfxd);
	playsound(S_BOMB1_DETONATE);
	release();
}

const KOBO_enemy_kind bomb1 = {
	KOBO_EK_BOMB1,
	5,
	&KOBO_enemy::make_bomb,
	&KOBO_enemy::move_bomb1,
	&KOBO_enemy::kill_default,
	5,
	B_BOMB, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(BOMB1)
};


/*
 * ===========================================================================
 *                                bomb2
 * ===========================================================================
 */

void KOBO_enemy::move_bomb2()
{
	if(c)
	{
		frame = 32;
		di = 1 + di % 6;
	}
	else
	{
		frame = 16;
		di = 1 + (di + 14) % 16;
	}

	int h1 = labs(diffx);
	int v1 = labs(diffy);
	if(((h1 < 100) && (v1 < 20)) || ((h1 < 20) && (v1 < 100)))
	{
		if(!c)
			startsound(S_BOMB2_TRIG);
		++c;
	}
	else
	{
		stopsound();
		c = 0;
	}
	if((c < game.bomb_delay) || prefs->cheat_brokentrigger ||
			prefs->cheat_ceasefire || enemies.is_intro ||
			!myship.alive())
		return;

	// Detonate!
	int vx1 = PIXEL2CS(-diffx) / (3*8);
	int vy1 = PIXEL2CS(-diffy) / (3*8);
	int vx2 = vx1, vx3 = vx1;
	int vy2 = vy1, vy3 = vy1;
	int i;
	for(i = 0; i < 6; i++)
	{
		int tmp = vx2;
		vx2 += (vy2 >> 4);
		vy2 -= (tmp >> 4);
		tmp = vx3;
		vx3 -= (vy3 >> 4);
		vy3 += (tmp >> 4);
	}
	int vx4 = vx2, vx5 = vx3;
	int vy4 = vy2, vy5 = vy3;
	for(i = 0; i < 6; i++)
	{
		int tmp = vx2;
		vx2 += (vy2 >> 4);
		vy2 -= (tmp >> 4);
		tmp = vx3;
		vx3 -= (vy3 >> 4);
		vy3 += (tmp >> 4);
	}
	enemies.make(&bullet3, x, y, vx1, vy1);
	enemies.make(&bullet3, x, y, vx2, vy2);
	enemies.make(&bullet3, x, y, vx3, vy3);
	enemies.make(&bullet3, x, y, vx4, vy4);
	enemies.make(&bullet3, x, y, vx5, vy5);
	KOBO_ParticleFXDef *pfxd = themedata.pfxdef(KOBO_PFX_BOMB2DETO);
	if(pfxd)
		wfire->Spawn(x + h, y + v, vx1, vy1, pfxd);
	playsound(S_BOMB2_DETONATE);
	release();
}

const KOBO_enemy_kind bomb2 = {
	KOBO_EK_BOMB2,
	20,
	&KOBO_enemy::make_bomb,
	&KOBO_enemy::move_bomb2,
	&KOBO_enemy::kill_default,
	5,
	B_BOMB, 16,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(BOMB2)
};


/*
 * ===========================================================================
 *                                explosionX
 *                            Various explosions
 * ===========================================================================
 */

void KOBO_enemy::make_expl()
{
	health = 1;
	damage = 0;
	shootable = false;
	physics = false;
	di = -1;	// ::move_expl() skips the first frame otherwise...
	a = frames;	// Use all loaded frames, unless overridden below!
	switch(logical_bank)
	{
	  case B_RINGEXPL:
		a = -8;
		break;
	  case B_BLTX_GREEN:
	  case B_BLTX_RED:
	  case B_BLTX_BLUE:
		a = -6;
		break;
	  case B_BOLT:
		frame = 80 + 4 * pubrand.get(2);
		di = pubrand.get(2);
		a = 8;
		break;
	  case B_BOMBDETO:
	  case B_ROCKEXPL:
		break;
	}
	if(a < 0)
	{
		a = -a;
		if(frames >= a * 2)
			frame = pubrand.get() % (frames / a) * a;
	}
}

void KOBO_enemy::move_expl()
{
	if(++di > a)
		release();
}


/*
 * ===========================================================================
 *                                 ringexpl
 *                           Ring dies in a flash
 * ===========================================================================
 */

const KOBO_enemy_kind ringexpl = {
	KOBO_EK_RINGEXPL,
	0,
	&KOBO_enemy::make_expl,
	&KOBO_enemy::move_expl,
	&KOBO_enemy::kill_unused,
	-1,
	B_RINGEXPL, 0,
	LAYER_FX,
	0,
	KOBO_EK_FX(RINGEXPL)
};


/*
 * ===========================================================================
 *                                 bltexpl
 *                         Enemy "bullet" discharges
 * ===========================================================================
 */

const KOBO_enemy_kind greenbltexpl = {
	KOBO_EK_GREENBLTEXPL,
	0,
	&KOBO_enemy::make_expl,
	&KOBO_enemy::move_expl,
	&KOBO_enemy::kill_unused,
	-1,
	B_BLTX_GREEN, 0,
	LAYER_FX,
	0,
	KOBO_EK_FX(BLTX_GREEN)
};

const KOBO_enemy_kind redbltexpl = {
	KOBO_EK_REDBLTEXPL,
	0,
	&KOBO_enemy::make_expl,
	&KOBO_enemy::move_expl,
	&KOBO_enemy::kill_unused,
	-1,
	B_BLTX_RED, 0,
	LAYER_FX,
	0,
	KOBO_EK_FX(BLTX_RED)
};

const KOBO_enemy_kind bluebltexpl = {
	KOBO_EK_BLUEBLTEXPL,
	0,
	&KOBO_enemy::make_expl,
	&KOBO_enemy::move_expl,
	&KOBO_enemy::kill_unused,
	-1,
	B_BLTX_BLUE, 0,
	LAYER_FX,
	0,
	KOBO_EK_FX(BLTX_BLUE)
};


/*
 * ===========================================================================
 *                                 boltexpl
 *                         Player bolt discharges
 * ===========================================================================
 */

const KOBO_enemy_kind boltexpl = {
	KOBO_EK_BOLTEXPL,
	0,
	&KOBO_enemy::make_expl,
	&KOBO_enemy::move_expl,
	&KOBO_enemy::kill_unused,
	-1,
	B_BOLT, 0,
	LAYER_FX,
	0,
	KOBO_EK_FX(BOLTEXPL)
};


/*
 * ===========================================================================
 *                                 rockexpl
 *                          Rock *finally* explodes
 * ===========================================================================
 */

const KOBO_enemy_kind rockexpl = {
	KOBO_EK_ROCKEXPL,
	0,
	&KOBO_enemy::make_expl,
	&KOBO_enemy::move_expl,
	&KOBO_enemy::kill_unused,
	-1,
	B_ROCKEXPL, 0,
	LAYER_FX,
	0,
	KOBO_EK_FX(ROCKEXPL)
};


/*
 * ===========================================================================
 *                                cannon
 * ===========================================================================
 */

void KOBO_enemy::make_cannon()
{
	physics = false;
	mapcollide = true;
	c = 0;
	health = game.node_health;
	damage = 0;
	splash_damage = 25;
	b = enemies.eint1() - 1;
	a = gamerand.get() & b;
}

void KOBO_enemy::move_cannon()
{
	c++;
	c &= b;
	if(c == a && mindiff < ((VIEWLIMIT >> 1) + 8))
		this->launch(enemies.ek1());
}

// For destruction via core chain reaction (don't spawn a pipein!)
void KOBO_enemy::destroy_cannon()
{
	explode();
	die();
}

// For destruction via normal damage
void KOBO_enemy::kill_cannon()
{
	explode();
	enemies.make(&pipein, x, y);
	die();
}

const KOBO_enemy_kind cannon = {
	KOBO_EK_CANNON,
	10,
	&KOBO_enemy::make_cannon,
	&KOBO_enemy::move_cannon,
	&KOBO_enemy::kill_cannon,
	4,
	-1, 0,
	LAYER_BASES,
	0,
	KOBO_EK_FX(CANNON)
};


/*
 * ===========================================================================
 *                                core
 * ===========================================================================
 */

void KOBO_enemy::make_core()
{
	physics = false;
	mapcollide = true;
	c = 0;
	health = game.core_health;
	damage = 0;
	splash_damage = 50;
	b = enemies.eint2() - 1;
	a = gamerand.get() & b;
}

void KOBO_enemy::move_core()
{
	c++;
	c &= b;
	if(c == a && mindiff < ((VIEWLIMIT >> 1) + 8))
		this->launch(enemies.ek2());
	unsigned hf = (health << 4) / game.core_health;
	if((hf < 16) && (pubrand.get(5) > 15 + hf))
	{
		int xo = pubrand.get(12) - (1 << 11);
		int yo = pubrand.get(12) - (1 << 11);
		KOBO_ParticleFXDef *pfxd = themedata.pfxdef(
				KOBO_PFX_CORE_FIRE);
		if(pfxd)
			wfire->Spawn(x + xo, y + yo, xo >> 4, yo >> 4, pfxd);
		controlsound(2, 0.1f);
	}
}

void KOBO_enemy::kill_core()
{
	enemies.make(&pipeout, x, y, 0, 0, 3);
	enemies.make(&pipeout, x, y, 0, 0, 7);
	enemies.make(&pipeout, x, y, 0, 0, 1);
	enemies.make(&pipeout, x, y, 0, 0, 5);
	explode();
	die();
	manage.destroyed_a_core();
}

const KOBO_enemy_kind core = {
	KOBO_EK_CORE,
	200,
	&KOBO_enemy::make_core,
	&KOBO_enemy::move_core,
	&KOBO_enemy::kill_core,
	4,
	-1, 0,
	LAYER_BASES,
	0,
	KOBO_EK_FX(CORE)
};


/*
 * ===========================================================================
 *                                pipein
 *                    Exploding pipe from leaf nodes
 * ===========================================================================
 */

void KOBO_enemy::make_pipein()
{
	health = 2;
	damage = 0;
	shootable = false;
	physics = false;
	c = 0;
	a = 0;
}

void KOBO_enemy::move_pipein()
{
	if(--c > 0)
		return;
	c = 2 + gamerand.get(2);

	int x1 = (CS2PIXEL(x) & (WORLD_SIZEX - 1)) >> 4;
	int y1 = (CS2PIXEL(y) & (WORLD_SIZEY - 1)) >> 4;
	int a_next = 0;
	int x_next = 0;
	int y_next = 0;
	int m = screen.get_map(x1, y1);
	int p = MAP_BITS(m);
	if(IS_SPACE(p))
	{
		// Clean scrap here too, in case we were set off by a core
		// detonation chain reaction!
		screen.clean_scrap(x1, y1);
		release();
		return;
	}

	int scraptube = 48 + pubrand.get(1);
	switch(p ^ a)
	{
	  case U_MASK:
		a_next = D_MASK;
		y_next = -PIXEL2CS(16);
		break;
	  case R_MASK:
		a_next = L_MASK;
		x_next = PIXEL2CS(16);
		scraptube += 2;
		break;
	  case D_MASK:
		a_next = U_MASK;
		y_next = PIXEL2CS(16);
		scraptube += 4;
		break;
	  case L_MASK:
		a_next = R_MASK;
		x_next = -PIXEL2CS(16);
		scraptube += 6;
		break;
	  default:
		if(!(p & CORE))
			screen.set_map(x1, y1, m ^ a);
		release();
		return;
	}
	if(health == 1)	// Skip the starting point! Cannon nodes handle that.
	{
		if(mindiff < ((VIEWLIMIT >> 1) + 32))
		{
			controlsound(2, pubrand.get(16) * (1.0f / 65536.0f));
			explode();
		}
	}
	else
		health = 1;
	screen.clean_scrap(x1, y1);
	screen.set_map(x1, y1, (scraptube << 8) | SPACE);
	x += x_next;
	y += y_next;
	a = a_next;
}

const KOBO_enemy_kind pipein = {
	KOBO_EK_PIPEIN,
	0,
	&KOBO_enemy::make_pipein,
	&KOBO_enemy::move_pipein,
	&KOBO_enemy::kill_unused,
	-1,
	-1, 0,
	LAYER_BASES,
	0,
	KOBO_EK_FX(PIPEIN)
};


/*
 * ===========================================================================
 *                                pipeout
 *      Exploding pipes from core, recursively following branches
 * ===========================================================================
 */

void KOBO_enemy::make_pipeout()
{
	int x1 = (CS2PIXEL(x) & (WORLD_SIZEX - 1)) >> 4;
	int y1 = (CS2PIXEL(y) & (WORLD_SIZEY - 1)) >> 4;
	screen.clean_scrap(x1, y1);
	screen.set_map(x1, y1, SPACE);
	health = 1;
	damage = 0;
	shootable = false;
	physics = false;
	c = 0;
	switch (di)
	{
	  case 1:
		a = D_MASK;
		y -= PIXEL2CS(16);
		break;
	  case 3:
		a = L_MASK;
		x += PIXEL2CS(16);
		break;
	  case 5:
		a = U_MASK;
		y += PIXEL2CS(16);
		break;
	  case 7:
		a = R_MASK;
		x -= PIXEL2CS(16);
		break;
	}
}

void KOBO_enemy::move_pipeout()
{
	if(--c > 0)
		return;

	c = 2 + gamerand.get(2);

	int x1 = (CS2PIXEL(x) & (WORLD_SIZEX - 1)) >> 4;
	int y1 = (CS2PIXEL(y) & (WORLD_SIZEY - 1)) >> 4;
	int a_next = 0;
	int x_next = 0;
	int y_next = 0;
	int p = MAP_BITS(screen.get_map(x1, y1));

	screen.clean_scrap(x1, y1);

	if(IS_SPACE(p))
	{
		release();
		return;
	}

	if((p ^ a) == 0)
	{
		manage.add_score(30);
		release();
		enemies.erase_cannon(x1, y1);
		screen.set_map(x1, y1, SPACE);
		return;
	}

	if((p ^ a) == HARD)
	{
		screen.set_map(x1, y1, SPACE);
		controlsound(2, pubrand.get(16) * (1.0f / 65536.0f));
		if(mindiff < ((VIEWLIMIT >> 1) + 32))
			explode();
		release();
		return;
	}

	int scraptube = 48 + pubrand.get(1);
	switch(p ^ a)
	{
	  case U_MASK:
		a_next = D_MASK;
		y_next = -PIXEL2CS(16);
		break;
	  case R_MASK:
		a_next = L_MASK;
		x_next = PIXEL2CS(16);
		scraptube += 2;
		break;
	  case D_MASK:
		a_next = U_MASK;
		y_next = PIXEL2CS(16);
		scraptube += 4;
		break;
	  case L_MASK:
		a_next = R_MASK;
		x_next = -PIXEL2CS(16);
		scraptube += 6;
		break;
	  default:
		p ^= a;
		if(p & U_MASK)
			enemies.make(&pipeout, x, y, 0, 0, 1);
		if(p & R_MASK)
			enemies.make(&pipeout, x, y, 0, 0, 3);
		if(p & D_MASK)
			enemies.make(&pipeout, x, y, 0, 0, 5);
		if(p & L_MASK)
			enemies.make(&pipeout, x, y, 0, 0, 7);
		manage.add_score(10);
		release();
		return;
	}
	screen.set_map(x1, y1, (scraptube << 8) | SPACE);
	controlsound(2, pubrand.get(16) * (1.0f / 65536.0f));
	if(mindiff < ((VIEWLIMIT >> 1) + 32))
		explode();
	x += x_next;
	y += y_next;
	a = a_next;
}

const KOBO_enemy_kind pipeout = {
	KOBO_EK_PIPEOUT,
	0,
	&KOBO_enemy::make_pipeout,
	&KOBO_enemy::move_pipeout,
	&KOBO_enemy::kill_unused,
	-1,
	-1, 0,
	LAYER_BASES,
	0,
	KOBO_EK_FX(PIPEOUT)
};


/*
 * ===========================================================================
 *                                enemy1
 *                           Gray Dumb Missile
 * ===========================================================================
 */

void KOBO_enemy::make_enemy1()
{
	physics = false;
	detonate_on_contact = true;
	di = 1;
	health = 20;
}

void KOBO_enemy::move_enemy1()
{
	this->move_enemy_template(2, 256);
}

const KOBO_enemy_kind enemy1 = {
	KOBO_EK_ENEMY1,
	2,
	&KOBO_enemy::make_enemy1,
	&KOBO_enemy::move_enemy1,
	&KOBO_enemy::kill_default,
	6,
	B_MISSILE1, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY1)
};


/*
 * ===========================================================================
 *                                enemy2
 *                          Teal Firing Fighter
 * ===========================================================================
 */

void KOBO_enemy::make_enemy2()
{
	di = 1;
	health = 80;
	c = gamerand.get() & 63;
}

void KOBO_enemy::move_enemy2()
{
	this->move_enemy_template(4, 192);
	if(--c <= 0)
	{
		if(mindiff < ((VIEWLIMIT >> 1) + 8))
			this->launch(&bullet3);
		c = 32;
	}
}

const KOBO_enemy_kind enemy2 = {
	KOBO_EK_ENEMY2,
	10,
	&KOBO_enemy::make_enemy2,
	&KOBO_enemy::move_enemy2,
	&KOBO_enemy::kill_default,
	6,
	B_FIGHTER, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY2)
};


/*
 * ===========================================================================
 *                                enemy3
 *                         Maroon Homing Missile
 * ===========================================================================
 */

void KOBO_enemy::make_enemy3()
{
	physics = false;
	detonate_on_contact = true;
	di = 1;
	health = 40;
}

void KOBO_enemy::move_enemy3()
{
	this->move_enemy_template(32, 96);
}

const KOBO_enemy_kind enemy3 = {
	KOBO_EK_ENEMY3,
	1,
	&KOBO_enemy::make_enemy3,
	&KOBO_enemy::move_enemy3,
	&KOBO_enemy::kill_default,
	6,
	B_MISSILE2, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY3)
};


/*
 * ===========================================================================
 *                                enemy4
 *                          Blue Homing Missile
 * ===========================================================================
 */

void KOBO_enemy::make_enemy4()
{
	physics = false;
	detonate_on_contact = true;
	di = 1;
	health = 40;
}

void KOBO_enemy::move_enemy4()
{
	this->move_enemy_template(4, 96);
}

const KOBO_enemy_kind enemy4 = {
	KOBO_EK_ENEMY4,
	1,
	&KOBO_enemy::make_enemy4,
	&KOBO_enemy::move_enemy4,
	&KOBO_enemy::kill_default,
	6,
	B_MISSILE3, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY4)
};


/*
 * ===========================================================================
 *                                enemy5
 *                        Green Boomerang Fighter
 * ===========================================================================
 */

void KOBO_enemy::make_enemy()
{
	c = gamerand.get() & 127;
	di = 1;
	health = 60;
	a = 0;
}

void KOBO_enemy::move_enemy5()
{
	if(a == 0)
	{
		if(mindiff > ((VIEWLIMIT >> 1) - 32))
			this->move_enemy_template(6, 192);
		else
			a = 1;
	}
	else
	{
		if(mindiff < VIEWLIMIT)
			this->move_enemy_template_2(4, 192);
		else
			a = 0;
	}
	if(--c <= 0)
	{
		c = 8;
		if(mindiff > ((VIEWLIMIT >> 1) - 32))
			this->launch(&bullet2);
	}
}

const KOBO_enemy_kind enemy5 = {
	KOBO_EK_ENEMY5,
	5,
	&KOBO_enemy::make_enemy,
	&KOBO_enemy::move_enemy5,
	&KOBO_enemy::kill_default,
	6,
	B_BMR_GREEN, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY5)
};


/*
 * ===========================================================================
 *                                enemy6
 *                         Purple Boomerang Fighter
 * ===========================================================================
 */

void KOBO_enemy::move_enemy6()
{
	if(a == 0)
	{
		if(mindiff > ((VIEWLIMIT >> 1) - 0))
			this->move_enemy_template(6, 192);
		else
			a = 1;
	}
	else
	{
		if(mindiff < VIEWLIMIT)
			this->move_enemy_template_2(5, 192);
		else
			a = 0;
	}
	if(--c <= 0)
	{
		c = 128;
		if(mindiff > ((VIEWLIMIT >> 1) - 32))
			this->launch(&bullet3);
	}
}

const KOBO_enemy_kind enemy6 = {
	KOBO_EK_ENEMY6,
	2,
	&KOBO_enemy::make_enemy,
	&KOBO_enemy::move_enemy6,
	&KOBO_enemy::kill_default,
	10,
	B_BMR_PURPLE, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY6)
};


/*
 * ===========================================================================
 *                                enemy7
 *                        Pink Boomerang Fighter
 * ===========================================================================
 */

void KOBO_enemy::move_enemy7()
{
	if(a == 0)
	{
		if(mindiff > ((VIEWLIMIT >> 1) - 32))
			this->move_enemy_template(6, 192);
		else
			a = 1;
	}
	else
	{
		if(mindiff < VIEWLIMIT)
			this->move_enemy_template_3(4, 192);
		else
			a = 0;
	}
	if(--c <= 0)
	{
		c = 4;
		if(mindiff > ((VIEWLIMIT >> 1) - 32))
			this->launch(&bullet1);
	}
}

const KOBO_enemy_kind enemy7 = {
	KOBO_EK_ENEMY7,
	5,
	&KOBO_enemy::make_enemy,
	&KOBO_enemy::move_enemy7,
	&KOBO_enemy::kill_default,
	6,
	B_BMR_PINK, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY7)
};


/*
 * ===========================================================================
 *                                enemy_m1
 * ===========================================================================
 */

void KOBO_enemy::make_enemy_m1()
{
	di = 1;
	health = game.enemy_m_health;	// Originally 26 hits
	c = gamerand.get() & 15;
}

void KOBO_enemy::move_enemy_m1()
{
	this->move_enemy_m(3, 128);
	if(++di > frames)
		di = 1;
	if(c-- <= 0)
	{
		c = 4;
		if(mindiff < ((VIEWLIMIT >> 1) - 16))
		{
			this->launch(&enemy1);
		}
	}
	if(health < 200)
	{
		playsound(S_ENEMY_M1_BAILOUT);
		this->shot_template_8_dir(&enemy2);
		die();
	}
}

const KOBO_enemy_kind enemy_m1 = {
	KOBO_EK_ENEMY_M1,
	50,
	&KOBO_enemy::make_enemy_m1,
	&KOBO_enemy::move_enemy_m1,
	&KOBO_enemy::kill_default,
	20,
	B_BIGSHIP, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY_M1)
};


/*
 * ===========================================================================
 *                                enemy_m2
 * ===========================================================================
 */

void KOBO_enemy::make_enemy_m2()
{
	di = 1;
	health = game.enemy_m_health;
	c = gamerand.get() & 15;
}

void KOBO_enemy::move_enemy_m2()
{
	this->move_enemy_m(3, 128);
	if(++di > frames)
		di = 1;
	if(c-- <= 0)
	{
		c = 8;
		if(mindiff < ((VIEWLIMIT >> 1) + 8))
			this->launch(&enemy2);
	}
	if(health < 200)
	{
		playsound(S_ENEMY_M2_BAILOUT);
		this->shot_template_8_dir(&bomb2);
		die();
	}
}

const KOBO_enemy_kind enemy_m2 = {
	KOBO_EK_ENEMY_M2,
	50,
	&KOBO_enemy::make_enemy_m2,
	&KOBO_enemy::move_enemy_m2,
	&KOBO_enemy::kill_default,
	20,
	B_BIGSHIP, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY_M2)
};


/*
 * ===========================================================================
 *                                enemy_m3
 * ===========================================================================
 */

void KOBO_enemy::make_enemy_m3()
{
	di = 1;
	health = game.enemy_m_health;
	c = gamerand.get() & 15;
}

void KOBO_enemy::move_enemy_m3()
{
	this->move_enemy_m(3, 128);
	if(--di < 1)
		di = frames;
	if(c-- <= 0)
	{
		c = 64;
		if(mindiff < ((VIEWLIMIT >> 1) + 8))
			this->shot_template_8_dir(&bomb2);
	}
	if(health < 200)
	{
		playsound(S_ENEMY_M3_BAILOUT);
		this->shot_template_8_dir(&rock);
		die();
	}
}

const KOBO_enemy_kind enemy_m3 = {
	KOBO_EK_ENEMY_M3,
	50,
	&KOBO_enemy::make_enemy_m3,
	&KOBO_enemy::move_enemy_m3,
	&KOBO_enemy::kill_default,
	20,
	B_BIGSHIP, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY_M3)
};


/*
 * ===========================================================================
 *                                enemy_m4
 * ===========================================================================
 */

void KOBO_enemy::make_enemy_m4()
{
	di = 1;
	health = game.enemy_m_health;
	c = gamerand.get() & 15;
}

void KOBO_enemy::move_enemy_m4()
{
	this->move_enemy_m(2, 96);
	if(--di < 1)
		di = frames;
	static const KOBO_enemy_kind *shot[8] = {
		&enemy1, &enemy2, &bomb2, &ring, &enemy1, &enemy2, &ring,
		&enemy1
	};
	if(c-- <= 0)
	{
		c = 64;
		if(mindiff < ((VIEWLIMIT >> 1) + 8))
			this->shot_template_8_dir(shot[gamerand.get() & 7]);
	}
	if(health < 200)
	{
		playsound(S_ENEMY_M4_BAILOUT);
		this->shot_template_8_dir(&rock);
		die();
	}
}

const KOBO_enemy_kind enemy_m4 = {
	KOBO_EK_ENEMY_M4,
	100,
	&KOBO_enemy::make_enemy_m4,
	&KOBO_enemy::move_enemy_m4,
	&KOBO_enemy::kill_default,
	20,
	B_BIGSHIP, 0,
	LAYER_ENEMIES,
	0,
	KOBO_EK_FX(ENEMY_M4)
};
