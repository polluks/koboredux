/*(GPLv2)
------------------------------------------------------------
   Kobo Deluxe - An enhanced SDL port of XKobo
------------------------------------------------------------
 * Copyright 1995, 1996 Akira Higuchi
 * Copyright 2001-2003, 2005, 2007, 2009 David Olofson
 * Copyright 2008 Robert Schuster
 * Copyright 2015 David Olofson (Kobo Redux)
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

#ifndef _KOBO_H_
#define _KOBO_H_

#include "config.h"

#include "gfxengine.h"
#include "window.h"
#include "filemap.h"
#include "prefs.h"
#include "radar.h"
#include "dashboard.h"
#include "sound.h"

/*----------------------------------------------------------
	Singletons
----------------------------------------------------------*/
extern KOBO_sound	sound;


/*----------------------------------------------------------
	Globals
----------------------------------------------------------*/

class kobo_gfxengine_t : public gfxengine_t
{
#ifdef ENABLE_TOUCHSCREEN
	bool pointer_margin_used;
	int pointer_margin_width_min;
	int pointer_margin_width_max;
	int pointer_margin_height_min;
	int pointer_margin_height_max;
#endif
	void frame();
	void pre_render();
	void post_render();
  public:
#ifdef ENABLE_TOUCHSCREEN
	void setup_pointer_margin(int, int);
#endif
};

extern kobo_gfxengine_t		*gengine;
extern filemapper_t		*fmap;
extern prefs_t			*prefs;

extern screen_window_t		*wscreen;
extern dashboard_window_t	*wdash;
extern bargraph_t		*whealth;
extern bargraph_t		*wtemp;
extern bargraph_t		*wttemp;
extern radar_map_t		*wmap;
extern radar_window_t		*wradar;
extern engine_window_t		*wmain;
extern window_t			*woverlay;
extern display_t		*dhigh;
extern display_t		*dscore;
extern display_t		*dstage;
extern display_t		*dregion;
extern display_t		*dlevel;
extern display_t		*dships;
extern hledbar_t		*pxtop;
extern hledbar_t		*pxbottom;
extern vledbar_t		*pxleft;
extern vledbar_t		*pxright;

extern int mouse_x, mouse_y;
extern int mouse_left, mouse_middle, mouse_right;

extern int exit_game;


/* Sprite priority levels */
#define	LAYER_OVERLAY	0	// Mouse crosshair
#define	LAYER_BULLETS	1	// Bullets - most important!
#define	LAYER_FX	2	// Explosions and similar effects
#define	LAYER_PLAYER	3	// Player and fire bolts
#define	LAYER_ENEMIES	4	// Enemies
#define	LAYER_BASES	5	// Bases and stationary enemies

/* Graphics banks */
typedef enum
{
	B_R1_TILES =	0,
	B_R2_TILES,
	B_R3_TILES,
	B_R4_TILES,
	B_R5_TILES,

	B_R1L3_PLANET,
	B_R2L3_PLANET,
	B_R3L3_PLANET,
	B_R4L3_PLANET,
	B_R5L3_PLANET,

	B_R1L4_PLANET,
	B_R2L4_PLANET,
	B_R3L4_PLANET,
	B_R4L4_PLANET,
	B_R5L4_PLANET,

	B_R1L5_PLANET,
	B_R2L5_PLANET,
	B_R3L5_PLANET,
	B_R4L5_PLANET,
	B_R5L5_PLANET,

	B_R1L6_PLANET,
	B_R2L6_PLANET,
	B_R3L6_PLANET,
	B_R4L6_PLANET,
	B_R5L6_PLANET,

	B_R1L7_PLANET,
	B_R2L7_PLANET,
	B_R3L7_PLANET,
	B_R4L7_PLANET,
	B_R5L7_PLANET,

	B_R1_CLOUDS,
	B_R2_CLOUDS,
	B_R3_CLOUDS,
	B_R4_CLOUDS,
	B_R5_CLOUDS,

	B_R1L8_GROUND,
	B_R2L8_GROUND,
	B_R3L8_GROUND,
	B_R4L8_GROUND,
	B_R5L8_GROUND,

	B_R1L9_GROUND,
	B_R2L9_GROUND,
	B_R3L9_GROUND,
	B_R4L9_GROUND,
	B_R5L9_GROUND,

	B_R1L10_GROUND,
	B_R2L10_GROUND,
	B_R3L10_GROUND,
	B_R4L10_GROUND,
	B_R5L10_GROUND,

	B_CROSSHAIR,
	B_PLAYER,
	B_BLT_GREEN,
	B_BLT_RED,
	B_BLTX_GREEN,
	B_BLTX_RED,
	B_RING,
	B_RINGEXPL,
	B_BOMB,
	B_BOMBDETO,
	B_BOLT,
	B_EXPLO1,
	B_EXPLO3,
	B_EXPLO4,
	B_EXPLO5,
	B_ROCK1,
	B_ROCK2,
	B_ROCK3,
	B_ROCKEXPL,
	B_BMR_GREEN,
	B_BMR_PURPLE,
	B_BMR_PINK,
	B_FIGHTER,
	B_MISSILE1,
	B_MISSILE2,
	B_MISSILE3,
	B_BIGSHIP,

	B_NOISE,
	B_HITNOISE,
	B_FOCUSFX,

	B_SCREEN,
	B_HLEDS,
	B_VLEDS,

	B_LOGO,

	B_HIGH_BACK,
	B_SCORE_BACK,
	B_RADAR_BACK,
	B_SHIPS_BACK,
	B_STAGE_BACK,

	B_HEALTH_LID,
	B_TEMP_LID,
	B_TTEMP_LID,

	B_LOADING,
	B_NORMAL_FONT,
	B_MEDIUM_FONT,
	B_BIG_FONT,
	B_COUNTER_FONT
} KOBO_Banks;

#define	NOALPHA_THRESHOLD	64

#define	INTRO_SCENE	-100000

typedef enum
{
	STARFIELD_NONE = 0,
	STARFIELD_OLD,
	STARFIELD_PARALLAX
} KOBO_StarfieldModes;

#endif // _KOBO_H_
