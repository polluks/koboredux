/*(GPLv2)
------------------------------------------------------------
   Kobo Deluxe - An enhanced SDL port of XKobo
------------------------------------------------------------
 * Copyright 2001-2003, 2007, 2009 David Olofson
 * Copyright 2005 Erik Auerswald
 * Copyright 2008 Robert Schuster
 * Copyright 2015-2016 David Olofson (Kobo Redux)
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

#include "kobolog.h"
#include "prefs.h"
#include "gfxengine.h"
#include "gamectl.h"
#include "game.h"

void prefs_t::init()
{
	comment("------------------------------------------------");
	comment(" Kobo Redux "KOBO_VERSION" Configuration File");
	comment("------------------------------------------------");
	comment(" Switches - [no]<switch> or <switch> [<value>]");
	comment(" Values - <key> [<value>|\"<string>\"]");
	comment("------------------------------------------------");

	section("System");
	yesno("logfile", logfile, 0); desc("Log To File");
	key("logformat", logformat, 0); desc("Log File Format");
	key("logverbosity", logverbosity, 2); desc("Log Verbosity Level");
	yesno("quickstart", quickstart, 0); desc("Quick Startup");

	section("Input");
	yesno("joystick", joystick, 0); desc("Enable Joystick");
	key("joystick_index", joystick_index, 0); desc("Joystick Number");
	yesno("mouse", mouse, 0); desc("Enable Mouse");
	key("mousemode", mousemode, MMD_CROSSHAIR); desc("Mouse Control Mode");
	key("fire_tap_time", fire_tap_time, 2);
			desc("Charge Release Tap Time");
	yesno("broken_numdia", broken_numdia, 0);
			desc("Broken NumPad Diagonals");
	key("dia_emphasis", dia_emphasis, 1);
			desc("Diagonals Emphasis Filter");
	yesno("mousecapture", mousecapture, 1); desc("In-game Mouse Capture");

	section("Game");
	yesno("scrollradar", scrollradar, 1); desc("Scrolling Radar");
	key("filter", filter, 2); desc("Logic-to-Video Motion Filter Mode");
	key("timefilter", timefilter, 50); desc("Time Filter");
	key("countdown", countdown, 5); desc("Get Ready Countdown");
	key("stars", stars, 500); desc("Number of Parallax Stars");
	key("cannonloud", cannonloud, 100); desc("Player Cannons Loudness");

	section("Audio");
	yesno("sound", sound, 1); desc("Enable Sound");
	yesno("music", music, 1); desc("Enable Music");
	key("audiodriver", audiodriver, ""); desc("Audio Driver");
	key("samplerate", samplerate, 48000); desc("Sample Rate");
	key("latency", latency, 20); desc("Sound Latency");
	key("audiobuffer", audiobuffer, 0); desc("Custom Audio Buffer Size");
	key("tsdelay", tsdelay, 5); desc("Timestamp Delay");

	key("sfxtheme", sfxtheme, ""); desc("Sound Theme");
	key("volume", volume, 100); desc("Master Volume");
	key("vol_boost", vol_boost, 2); desc("Volume Boost");
	key("ui_vol", ui_vol, 50); desc("User Interface Volume");
	key("sfx_vol", sfx_vol, 70); desc("Sound Effects Volume");
	key("music_vol", music_vol, 50); desc("Music Volume");
	key("title_vol", title_vol, 70); desc("Title Music Volume");

	section("Video");
	yesno("fullscreen", fullscreen, 1); desc("Fullscreen Display");
	key("width", width, 0); desc("Horizontal Resolution");
	key("height", height, 0); desc("Vertical Resolution");
	yesno("autoswap", autoswap, 0);
			desc("Automatically swap display dimension");
	key("maxfps", maxfps, 100); desc("Maximum fps");
	key("maxfps_strict", maxfps_strict, 0); desc("Strictly Regulated fps");
	key("videomode", videomode, 1); desc("Video Mode");
	yesno("vsync", vsync, 1); desc("Enable Vertical Sync");

	key("gfxtheme", gfxtheme, ""); desc("Graphics Theme");
	key("scalemode", scalemode, 0); desc("Scaling Filter Mode");
	yesno("alpha", alpha, 1); desc("Use Alpha Blending");
	key("brightness", brightness, 100); desc("Brightness");
	key("contrast", contrast, 100); desc("Contrast");
	key("planetdither", planetdither, -1); desc("Planet Dither Style");

	section("Debug");
	yesno("debug", debug, 0); desc("Enable Debug Features");
	yesno("show_fps", show_fps, 0); desc("Show Frame Rate");
	yesno("show_map_border", show_map_border, 0); desc("Show Map Border");
	yesno("show_coordinates", show_coordinates, 0);
			desc("Show Object Coordinates");
	yesno("show_tiles", show_tiles, 0); desc("Show Tile/Sprite Edges");
	yesno("show_hit", show_hit, 0); desc("Show Hit Zones");
	yesno("tsdebug", tsdebug, 0); desc("Timestamp Debug Output");
	yesno("soundtools", soundtools, 0); desc("Sound Design Tools");
	key("toolstheme", toolstheme, ""); desc("Authoring Tools Theme");
	yesno("force_fallback_gfxtheme", force_fallback_gfxtheme, 0);
			desc("Force Load Fallback Graphics Theme");
	yesno("force_fallback_sfxtheme", force_fallback_sfxtheme, 0);
			desc("Force Load Fallback Sound Theme");

	section("Cheat/test");
	yesno("cheat_pushmove", cheat_pushmove, 0);
			desc("Cheat: Enable Push Move Mode");
	yesno("cheat_freewheel", cheat_freewheel, 0);
			desc("Cheat: Free Physics When Releasing Controls");
	yesno("cheat_shield", cheat_shield, 0);
			desc("Cheat: Shield Always Up");
	yesno("cheat_invulnerability", cheat_invulnerability, 0);
			desc("Cheat: Player Invulnerable");
	yesno("cheat_firepower", cheat_firepower, 0);
			desc("Cheat: Extra Firepower");
	yesno("cheat_startlevel", cheat_startlevel, 0);
			desc("Cheat: Unlimited Start Level Selector");
	yesno("cheat_brokentrigger", cheat_brokentrigger, 0);
			desc("Cheat: Bombs Trigger But Can't Detonate");
	key("cheat_speed", cheat_speed, 0.0f); desc("Cheat: Game Speed");

	section("Paths");
	key("data", data, ""); desc("Alternate Data Path");
	key("themes", themes, ""); desc("Alternate Themes Path");
	key("scores", scores, ""); desc("Alternate Scores Path");

	section("Temporary variables");
	key("last_profile", last_profile, 0);
			desc("Last used player profile");
	key("number_of_joysticks", number_of_joysticks, 0);
			desc("Number of Connected Joysticks");

	section("Commands");
	comment(" (Never written to config files!)");
	command("showcfg", cmd_showcfg); desc("Show Configuration");
	command("hiscores", cmd_hiscores); desc("List High Scores");
	command("highscores", cmd_hiscores); desc("List High Scores");
	command("override", cmd_override); desc("Ignore Configuration File");
	command("autoshot", cmd_autoshot); desc("Ingame screenshots/movie");
	command("help", cmd_help); desc("Print usage info and exit");
	command("options_man", cmd_options_man);
			desc("Print options for 'man'");
	key("warp", cmd_warp, 0, false); desc("Warp To Stage");
}


void prefs_t::postload()
{
	if(cheat_speed == 1.0f)
		cheat_speed = 0.0f;
}
