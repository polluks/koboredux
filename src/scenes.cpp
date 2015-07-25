/*(GPLv2)
 * XKOBO, a video-oriented game
 * Copyright 1995, 1996 Akira Higuchi <a-higuti@math.hokudai.ac.jp>
 * Copyright 2006, 2007, 2009 David Olofson
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

#include "scenes.h"

const _scene scenes[] = {
#if 0
	/* Test map */
	{
		0, 32, 0,
		&enemy_m1, 128, &greenbullet, 16,
		1,{
			{&enemy_m4, 1, 5},
//			{&enemy4,  10, 5},
		},
		1,{
//			{32,  64, 31, 62},
			{48,  64, 4, 4},
		},
	},
#endif
	/* 1 */
	{
		0, 32, 96,
		&greenbullet, 128, &greenbullet, 16,
		1,{
			{&enemy4,  10, 5},
		},
		2,{
			{48,  64, 4, 4},
			{24,  80, 4, 4},
		},
	},
	/* 2 */
	{
		0, 32, 96,
		&greenbullet, 64, &greenbullet, 64,
		3,{
			{&enemy4,   10,  5},
			{&enemy4,   10,  5},
			{&enemy1,   10,  5},
		},
		4,{
			{16, 48, 6, 6},
			{48, 48, 6, 6},
			{16, 64, 6, 6},
			{48, 64, 6, 6},
		},
	},
	/* 3 */
	{
		64, 32, 64,
		&greenbullet, 64, &greenbullet, 16,
		1,{
			{&rock,	 20,  3},
		},
		6,{
			{16, 40,  4, 4},
			{16, 60,  4, 4},
			{16, 80,  4, 4},
			{48, 40,  4, 4},
			{48, 60,  4, 4},
			{48, 80,  4, 4},
		},
	},
	/* 4 */
	{
		0, 32, 96,
		&greenbullet, 32, &greenbullet, 8,
		1,{
			{&enemy4,  10, 5},
		},
		3,{
			{14,  55, 6, 6},
			{55,  14, 6, 6},
			{35,  70, 6, 6},
		},
	},
	/* 5 */
	{
		0, 32, 96,
		&greenbullet, 128, &greenbullet, 128,
		3,{
			{&enemy6,   10,  5},
			{&enemy6,   10,  5},
			{&enemy4,   10,  5},
		},
		2,{
			{32, 32, 6, 6},
			{32, 64, 6, 6},
		},
	},
	/* 6 */
	{
		0, 32, 96,
		&enemy1, 32, &enemy1, 8,
		0,{
			{&enemy1,  40, 10},
		},
		1,{
			{32,  64, 8, 8},
		},
	},
	/* 7 */
	{
		0, 32, 64,
		&ring, 64, &enemy1, 32,
		2,{
			{&enemy3,   30,  5},
			{&enemy6,   20,  5},
		},
		8,{
			{32, 54, 3, 3},
			{42, 54, 3, 3},
			{42, 64, 3, 3},
			{42, 74, 3, 3},
			{32, 74, 3, 3},
			{22, 74, 3, 3},
			{22, 64, 3, 3},
			{22, 54, 3, 3},
		},
	},
	/* 8 */
	{
		0, 32, 64,
		&enemy4, 64, &enemy1, 8,
		3,{
			{&ring  ,   20,  5},
			{&ring  ,   20,  5},
			{&ring  ,   20,  5},
		},
		8,{
			{48,  64, 4, 4},
			{16,  64, 4, 4},
			{32,  80, 4, 4},
			{32,  48, 4, 4},
			{44,  76, 4, 4},
			{20,  76, 4, 4},
			{44,  52, 4, 4},
			{20,  52, 4, 4},
		},
	},
	/* 9 */
	{
		0, 32, 96,
		&greenbullet, 16, &greenbullet, 8,
		1,{
			{&bomb2, 20, 5},
		},
		1,{
			{32, 32, 7, 7},
		},
	},
	/* 10 */
	{
		0, 32, 96,
		&bomb1, 128, &bomb1, 4,
		1,{
			{&rock,  100,  5},
		},
		1,{
			{32, 64, 12, 12},
		},
	},
	/* 11 */
	{
		0, 32, 96,
		&enemy2, 128, &enemy1, 32,
		5,{
			{&rock,	30, 5},
			{&enemy3,  50, 5},
			{&enemy6,  20, 5},
			{&enemy7,  10, 5},
			{&bomb1,   20, 5},
		},
		6,{
			{ 5, 64, 3, 3},
			{15, 64, 3, 3},
			{25, 64, 3, 3},
			{35, 64, 3, 3},
			{45, 64, 3, 3},
			{55, 64, 3, 3},
		},
	},
	/* 12 */
	{
		0, 47, 33,
		&greenbullet, 128, &greenbullet, 16,
		3,{
			{&enemy6,  10, 5},
			{&enemy6,  10, 5},
			{&rock,   100, 5},
		},
		3,{
			{ 15,  88,  12,  12},
			{ 21,  20,  12,  12},
			{ 50,  70,  12,  12},
		},
	},
	/* 13 */
	{
		0, 32, 64,
		&bomb2, 128, &enemy1, 32,
		2,{
			{&bomb1,   30, 5},
			{&bomb1,   20, 5},
		},
		5,{
			{ 24,  66,   3,   3},
			{ 23,  80,   3,   3},
			{ 44,  50,   3,   3},
			{ 39, 102,   3,   3},
			{ 15,  43,   3,   3},
		},
	},
	/* 14 */
	{
		0, 24, 107,
		&enemy2, 128, &greenbullet, 8,
		4,{
			{&enemy3,  10, 5},
			{&enemy6,  10, 5},
			{&rock,   100, 5},
			{&enemy2,  10, 5},
		},
		3,{
			{  9,  36,   5,   5},
			{ 44,  19,   5,   5},
			{ 46,  79,   5,   5},
		},
	},
	/* 15 */
	{
		0, 36, 94,
		&enemy4, 64, &bomb1, 32,
		2,{
			{&enemy6,  10, 5},
			{&rock,	50, 5},
		},
		5,{
			{ 16,  54,   4,   4},
			{ 47,  56,   4,   4},
			{ 24,  70,   4,   4},
			{ 31,  14,   4,   4},
			{ 27,  31,   4,   4},
		},
	},
	/* 16 */
	{
		0, 31, 37,
		&enemy6, 64, &enemy6, 8,
		3,{
			{&enemy1,  20, 5},
			{&enemy3,  10, 5},
			{&rock,   100, 5},
		},
		5,{
			{ 41,  84,   6,  10},
			{ 12, 115,   6,   5},
			{ 22,  92,   6,  10},
			{ 11,  26,   8,   8},
			{ 51,  65,   9,   7},
		},
	},
	/* 17 */
	{
		0, 53, 17,
		&greenbullet, 32, &enemy1, 32,
		1,{
			{&enemy3,  10, 5},
		},
		10,{
			{ 14,  99,   6,   6},
			{ 37,  18,   6,   6},
			{ 13,  67,   6,   6},
			{ 19,  46,   6,   6},
			{ 41,  59,   6,   6},
			{ 39,  97,   6,   6},
			{ 47,  32,   6,   6},
			{ 56, 100,   6,   6},
			{ 19,  25,   6,   6},
			{ 54,  76,   6,   6},
		},
	},
	/* 18 */
	{
		0, 32, 80,
		&enemy1, 32, &ring, 8,
		4,{
			{&rock,	40, 2},
			{&enemy1,  20, 5},
			{&rock,	40, 5},
			{&enemy1,  20, 5},
		},
		3,{
			{ 27, 104,   5,   5},
			{ 49, 105,   5,   5},
			{ 32,  90,   5,   5},
		},
	},
	/* 19 */
	{
		0, 32, 64,
		&ring, 128, &enemy1, 8,
		0,{
			{&enemy1,  30, 5},
		},
		16,{
			{  32, 91,  3, 3},
			{  42, 89,  3, 3},
			{  51, 83,  3, 3},
			{  57, 74,  3, 3},
			{  59, 64,  3, 3},
			{  57, 54,  3, 3},
			{  51, 45,  3, 3},
			{  42, 39,  3, 3},
			{  32, 37,  3, 3},
			{  22, 39,  3, 3},
			{  13, 45,  3, 3},
			{   7, 54,  3, 3},
			{   5, 64,  3, 3},
			{   7, 74,  3, 3},
			{  13, 83,  3, 3},
			{  22, 89,  3, 3},
		},
	},
	/* 20 */
	{
		0, 7, 84,
		&enemy7, 128, &enemy5, 16,
		0,{
			{&bomb2,   30, 5},
		},
		20,{
			{ 37,  82,   6,   6},
			{ 13,  99,   6,   6},
			{ 30,  44,   6,   6},
			{ 19,  14,   6,   6},
			{ 55,  85,   6,   6},
			{ 23,  69,   6,   6},
			{ 16,  35,   6,   6},
			{ 11,  52,   6,   6},
			{ 36, 116,   6,   6},
			{ 39,  97,   6,   6},
			{ 50, 114,   6,   6},
			{ 39,  22,   6,   6},
			{ 55,  43,   6,   6},
			{ 52,  71,   6,   6},
			{ 56, 100,   6,   6},
			{ 54,  25,   6,   6},
			{ 51,  57,   6,   6},
			{  7, 115,   6,   6},
			{ 47,   8,   6,   6},
			{  8,  70,   6,   6},
		},
	},
	/* 21 */
	{
		0, 26, 30,
		&enemy1, 128, &greenbullet, 16,
		2,{
			{&enemy3,  20, 5},
			{&rock,	50, 5},
		},
		6,{
			{ 27,  79,   5,   5},
			{  6, 105,   5,   5},
			{ 11,  50,   5,   5},
			{ 11,  23,   5,   5},
			{ 56,  57,   5,   5},
			{  7,  70,   5,   5},
		},
	},
	/* 22 */
	{
		0, 38, 120,
		&ring, 128, &greenbullet, 16,
		6,{
			{&ring,	10, 5},
			{&ring,	10, 5},
			{&ring,	10, 5},
			{&ring,	10, 5},
			{&ring,	10, 5},
			{&enemy_m1, 1, 5},
		},
		30,{
			{ 55,  25,   4,   4},
			{ 49,  12,   4,   4},
			{ 30,  84,   4,   4},
			{ 33,  97,   4,   4},
			{ 24,  21,   4,   4},
			{ 28,  52,   4,   4},
			{ 50, 117,   4,   4},
			{ 22,  95,   4,   4},
			{ 46,  56,   4,   4},
			{ 36,  10,   4,   4},
			{ 15,  77,   4,   4},
			{ 32,  74,   4,   4},
			{  7,  15,   4,   4},
			{ 13, 107,   4,   4},
			{  6,  51,   4,   4},
			{ 11,  62,   4,   4},
			{ 57,  76,   4,   4},
			{ 57,  95,   4,   4},
			{ 11,  90,   4,   4},
			{ 46,  93,   4,   4},
			{ 34,  27,   4,   4},
			{ 58,  56,   4,   4},
			{ 40,  45,   4,   4},
			{ 10,  31,   4,   4},
			{ 44,  35,   4,   4},
			{ 25, 122,   4,   4},
			{ 24,  62,   4,   4},
			{ 51, 107,   4,   4},
			{ 16,  50,   4,   4},
			{ 25, 110,   4,   4},
		},
	},
	/* 23 */
	{
		0, 13, 92,
		&bomb1, 64, &bomb1, 32,
		4,{
			{&enemy1,  20, 5},
			{&enemy2,  10, 5},
			{&enemy7,  10, 5},
			{&enemy6,  20, 5},
		},
		5,{
			{ 40,  95,  15,  15},
			{ 44,  28,  13,  18},
			{ 15,  16,  12,  15},
			{ 14,  50,  13,  12},
			{ 49,  62,  12,  11},
		},
	},
	/* 24 */
	{
		127, 32, 41,
		&enemy1, 128, &greenbullet, 16,
		3,{
			{&rock,	50, 5},
			{&enemy2,  20, 5},
			{&bomb2,   30, 5},
		},
		8,{
			{ 38,  73,   4,   4},
			{ 27,  98,   4,   4},
			{ 27,  71,   4,   4},
			{ 56,  89,   4,   4},
			{ 39,   6,   4,   4},
			{ 12,  67,   4,   4},
			{ 58,  14,   4,   4},
			{ 14,  21,   4,   4},
		},
	},
	/* 25 */
	{
		256, 32, 96,
		&greenbullet, 32, &enemy1, 32,
		2,{
			{&enemy6,  50, 5},
			{&rock,   100, 5},
		},
		2,{
			{25, 53, 7, 6},
			{40, 70, 5, 4},
		},
	},
	/* 26 */
	{
		0, 32, 64,
		&ring, 64, &ring, 16,
		0,{
			{&enemy1,  40, 10},
		},
		32,{
			{ 8,   8, 5, 5},
			{24,   8, 5, 5},
			{40,   8, 5, 5},
			{56,   8, 5, 5},
			{ 8,  24, 5, 5},
			{24,  24, 5, 5},
			{40,  24, 5, 5},
			{56,  24, 5, 5},
			{ 8,  40, 5, 5},
			{24,  40, 5, 5},
			{40,  40, 5, 5},
			{56,  40, 5, 5},
			{ 8,  56, 5, 5},
			{24,  56, 5, 5},
			{40,  56, 5, 5},
			{56,  56, 5, 5},
			{ 8,  72, 5, 5},
			{24,  72, 5, 5},
			{40,  72, 5, 5},
			{56,  72, 5, 5},
			{ 8,  88, 5, 5},
			{24,  88, 5, 5},
			{40,  88, 5, 5},
			{56,  88, 5, 5},
			{ 8, 104, 5, 5},
			{24, 104, 5, 5},
			{40, 104, 5, 5},
			{56, 104, 5, 5},
			{ 8, 120, 5, 5},
			{24, 120, 5, 5},
			{40, 120, 5, 5},
			{56, 120, 5, 5},
		},
	},
	/* 27 */
	{
		0, 32, 64,
		&greenbullet, 32, &enemy5, 32,
		3,{
			{&enemy1,  20, 5},
			{&bomb1,   50, 5},
			{&enemy_m2, 1, 5},
		},
		4,{
			{ 49,  64,   6,  10},
			{ 40,  40,  11,   4},
			{ 36,  95,  13,   4},
			{ 13,  74,   8,  10},
		},
	},
	/* 28 */
	{
		4, 45, 107,
		&enemy1, 32, &enemy5, 16,
		1,{
			{&rock,	50, 5},
		},
		4,{
			{ 15, 108,  11,  18},
			{ 13,  62,  12,  19},
			{ 46,  42,  11,  41},
			{ 16,  23,  13,  13},
		},
	},
	/* 29 */
	{
		0, 32, 60,
		&enemy2, 128, &greenbullet, 4,
		5,{
			{&enemy5,  20, 5},
			{&bomb2,   10, 5},
			{&rock,	50, 5},
			{&enemy_m1, 1, 5},
			{&enemy7,  10, 5},
		},
		5,{
			{ 40,  46,  13,   9},
			{ 20,  74,  12,   8},
			{ 24, 106,  11,   6},
			{ 29, 120,  14,   6},
			{ 54,  90,   5,   8},
		},
	},
	/* 30 */
	{
		0, 23, 71,
		&enemy5, 64, &greenbullet, 16,
		3,{
			{&enemy6,   2, 5},
			{&enemy6,   2, 5},
			{&enemy_m4, 1, 5},
		},
		20,{
			{ 38, 120,   5,   5},
			{ 43,  64,   5,   5},
			{ 32, 106,   5,   5},
			{ 14,  52,   5,   5},
			{ 48,  76,   5,   5},
			{  9, 110,   5,   5},
			{ 12,  34,   5,   5},
			{ 40,  90,   5,   5},
			{ 38,  33,   5,   5},
			{ 23,   9,   5,   5},
			{ 22, 120,   5,   5},
			{  9,  90,   5,   5},
			{  6,  15,   5,   5},
			{ 41,  46,   5,   5},
			{ 43,  13,   5,   5},
			{ 25,  88,   5,   5},
			{  8,  65,   5,   5},
			{ 57,  49,   5,   5},
			{ 52, 108,   5,   5},
			{  6,  77,   5,   5},
		},
	},
	/* 31 */
	{
		0, 32, 120,
		&ring, 64, &ring, 8,
		0,{
			{&enemy1, 10, 5},
		},
		16,{
			{ 24,   8,  6, 6},
			{ 24,  24,  6, 6},
			{ 24,  40,  6, 6},
			{ 24,  56,  6, 6},
			{ 24,  72,  6, 6},
			{ 24,  88,  6, 6},
			{ 24, 104,  6, 6},
			{ 24, 120,  6, 6},
			{ 40,   8,  6, 6},
			{ 40,  24,  6, 6},
			{ 40,  40,  6, 6},
			{ 40,  56,  6, 6},
			{ 40,  72,  6, 6},
			{ 40,  88,  6, 6},
			{ 40, 104,  6, 6},
			{ 40, 120,  6, 6},
		},
	},
	/* 32 */
	{
		0, 32, 96,
		&greenbullet, 128, &greenbullet, 16,
		0,{
			{&enemy1,  40, 10},
		},
		1,{
			{32, 64, 24, 24},
		},
	},
	/* 33 */
	{
		0, 24, 113,
		&enemy4, 32, &enemy4, 16,
		5,{
			{&enemy5,  30, 5},
			{&bomb1,   50, 5},
			{&enemy_m2, 1, 5},
			{&enemy2,  20, 5},
			{&rock,   100, 5},
		},
		5,{
			{ 17,  70,  13,  21},
			{ 46,  32,  10,  10},
			{ 49,  63,  10,  11},
			{ 18,  25,  14,  21},
			{ 45, 109,  10,  17},
		},
	},
	/* 34 */
	{
		0, 54, 120,
		&enemy6, 64, &greenbullet, 16,
		1,{
			{&bomb2,   10, 5},
		},
		15,{
			{  8,  87,   6,  15},
			{ 26,  72,   9,  12},
			{ 37, 110,   9,   6},
			{ 36,  31,  16,   5},
			{ 32,  11,  17,   9},
			{ 46,  51,   6,  12},
			{ 54,  96,   5,  10},
			{ 12,  39,   5,  11},
			{ 13, 116,   9,   9},
			{ 40,  93,   7,   6},
			{  7,  64,   6,   6},
			{  7,  10,   5,   8},
			{ 47,  77,   8,   5},
			{ 28,  46,   5,   6},
			{ 56,  14,   5,   5},
		},
	},
	/* 35 */
	{
		0, 32, 64,
		&enemy3, 128, &ring, 32,
		8,{
			{&enemy1,   10,  5},
			{&enemy_m1,  1,  5},
			{&bomb2,	10,  5},
			{&enemy2,   10,  5},
			{&enemy_m2,  1,  5},
			{&enemy4,   10,  5},
			{&enemy5,   10,  5},
			{&enemy7,   10,  5},
		},
		8,{
			{32, 48, 7, 7},
			{48, 48, 7, 7},
			{48, 64, 7, 7},
			{48, 80, 7, 7},
			{32, 80, 7, 7},
			{16, 80, 7, 7},
			{16, 64, 7, 7},
			{16, 48, 7, 7},
		},
	},
	/* 36 */
	{
		0, 32, 64,
		&greenbullet, 16, &enemy2, 64,
		5,{
			{&enemy1,   10, 10},
			{&enemy2,   10, 10},
			{&bomb2,	10, 10},
			{&enemy_m1,  1, 10},
			{&enemy_m2,  1, 10},
		},
		10,{
			{16, 20,  4, 4},
			{16, 40,  4, 4},
			{16, 60,  4, 4},
			{16, 80,  4, 4},
			{16,100,  4, 4},
			{48, 20,  4, 4},
			{48, 40,  4, 4},
			{48, 60,  4, 4},
			{48, 80,  4, 4},
			{48,100,  4, 4},
		},
	},
	/* 37 */
	{
		256, 32, 96,
		&greenbullet, 64, &ring, 64,
		0,{
			{&ring,	  0,  5},
		},
		1,{
			{32,  58, 18, 18},
		},
	},
	/* 38 */
	{
		0, 32, 72,
		&ring, 64, &bomb1, 4,
		1,{
			{&rock,   10,  5},
		},
		20,{
			{16,  48, 3, 3},
			{24,  48, 3, 3},
			{32,  48, 3, 3},
			{40,  48, 3, 3},
			{48,  48, 3, 3},
			{16,  64, 3, 3},
			{24,  64, 3, 3},
			{32,  64, 3, 3},
			{40,  64, 3, 3},
			{48,  64, 3, 3},
			{16,  80, 3, 3},
			{24,  80, 3, 3},
			{32,  80, 3, 3},
			{40,  80, 3, 3},
			{48,  80, 3, 3},
			{16,  96, 3, 3},
			{24,  96, 3, 3},
			{32,  96, 3, 3},
			{40,  96, 3, 3},
			{48,  96, 3, 3},
		},
	},
	/* 39 */
	{
		0, 32, 50,
		&enemy5, 32, &enemy2, 16,
		6,{
			{&enemy_m2,  1,  5},
			{&rock  ,   50,  5},
			{&rock  ,   50,  5},
			{&rock  ,   50,  5},
			{&enemy_m1,  1,  5},
			{&rock  ,   50,  5},
		},
		8,{
			{34,  14, 4, 4},
			{16,  22, 4, 4},
			{ 6,  35, 4, 4},
			{22,  38, 4, 4},
			{45,  40, 4, 4},
			{ 6,  52, 4, 4},
			{46,  66, 4, 4},
			{30,  70, 4, 4},
			{15,  90, 4, 4},
		},
	},
	/* 40 */
	{
		0, 28, 11,
		&bomb1, 128, &enemy1, 16,
		1,{
			{&enemy6,  10, 5},
		},
		35,{
			{ 12,  48,   9,   9},
			{ 14,  80,   6,   5},
			{ 42,  14,   7,   3},
			{ 52, 112,   4,   9},
			{ 33, 103,   5,   6},
			{ 17,  12,   4,   3},
			{ 49,  78,   5,   4},
			{ 49,  50,   4,   5},
			{ 19,  32,   5,   5},
			{ 32,  77,   6,   4},
			{  9, 113,   4,   9},
			{ 36,  38,   7,   6},
			{ 50,  96,   8,   3},
			{ 57,   7,   3,   5},
			{ 53,  34,   5,   7},
			{ 11,  94,   5,   3},
			{ 27,  63,   3,   6},
			{ 44,   4,   3,   3},
			{ 48,  63,   5,   6},
			{ 37,  51,   6,   3},
			{ 28, 116,   3,   3},
			{  8,  31,   4,   5},
			{  4,  18,   3,   3},
			{ 13,  69,   6,   4},
			{ 21,  96,   3,   3},
			{ 36, 114,   3,   3},
			{ 55,  87,   5,   3},
			{ 58,  63,   3,   7},
			{ 35,  87,   4,   4},
			{ 35,  25,   3,   4},
			{ 20, 107,   3,   5},
			{ 13,   4,   3,   3},
			{ 23,  21,   4,   4},
			{  5,   8,   3,   5},
			{ 47,  22,   7,   3},
		},
	},
	/* 41 */
	{
		0, 32, 96,
		&greenbullet, 64, &greenbullet, 16,
		1,{
			{&bomb2,	40, 10},
		},
		1,{
			{32, 64, 18, 18},
		},
	},
	/* 42 */
	{
		0, 54, 46,
		&enemy7, 64, &enemy5, 32,
		3,{
			{&bomb2,   10, 5},
			{&enemy1,  10, 5},
			{&enemy6,  10, 5},
		},
		20,{
			{  8, 106,   5,   8},
			{  7,  32,   5,  13},
			{ 39,  83,   9,   7},
			{ 54,  63,   8,   9},
			{ 28,  20,   6,  13},
			{ 16,  61,  14,  10},
			{ 55,  25,   6,  13},
			{ 53, 106,   8,   7},
			{ 38, 115,   5,   7},
			{ 22, 109,   7,  14},
			{ 12,  82,   7,   8},
			{ 39,  51,   5,   5},
			{ 57,  89,   5,   7},
			{ 41,  21,   5,   7},
			{ 10,  10,   9,   6},
			{ 20,  41,   5,   5},
			{ 38,  66,   5,   5},
			{ 54, 121,   7,   5},
			{ 37, 100,   5,   6},
			{ 41,   7,   5,   5},
		},
	},
	/* 43 */
	{
		0, 22, 107,
		&enemy2, 64, &bomb1, 8,
		7,{
			{&enemy4,  20, 5},
			{&bomb2,   30, 5},
			{&enemy2,  20, 5},
			{&enemy6,  20, 5},
			{&bomb2,   30, 5},
			{&enemy7,  30, 5},
			{&enemy_m3, 1, 5},
		},
		5,{
			{ 49,  38,   8,  14},
			{ 20,  86,   5,  10},
			{ 19,  28,  14,  16},
			{ 19,  57,  17,   8},
			{ 48,  86,   8,  18},
		},
	},
	/* 44 */
	{
		0, 32, 64,
		&enemy2, 64, &ring, 8,
		4,{
			{&bomb2,   20, 7},
			{&rock,	20, 8},
			{&enemy_m1, 1, 5},
			{&rock,	20, 8},
		},
		24,{
			{  46, 64,  3, 3},
			{  18, 64,  3, 3},
			{  32, 79,  3, 3},
			{  32, 48,  3, 3},
			{  43, 75,  3, 3},
			{  21, 75,  3, 3},
			{  43, 53,  3, 3},
			{  21, 53,  3, 3},
			{  32, 91,  3, 3},
			{  42, 89,  3, 3},
			{  51, 83,  3, 3},
			{  57, 74,  3, 3},
			{  59, 64,  3, 3},
			{  57, 54,  3, 3},
			{  51, 45,  3, 3},
			{  42, 39,  3, 3},
			{  32, 37,  3, 3},
			{  22, 39,  3, 3},
			{  13, 45,  3, 3},
			{   7, 54,  3, 3},
			{   5, 64,  3, 3},
			{   7, 74,  3, 3},
			{  13, 83,  3, 3},
			{  22, 89,  3, 3},
		},
	},
	/* 45 */
	{
		0, 31, 87,
		&bomb1, 64, &ring, 16,
		1,{
			{&bomb2,   20, 5},
		},
		10,{
			{ 18,  66,  15,  15},
			{ 52,  59,   7,  54},
			{ 31, 101,   8,   7},
			{ 39,  41,   4,  30},
			{  9,  97,   7,  13},
			{ 21,  44,  11,   5},
			{ 25, 118,   5,   5},
			{ 20,  16,   8,  14},
			{ 42, 122,  10,   4},
			{  5,  16,   4,   4},
		},
	},
	/* 46 */
	{
		0, 59, 34,
		&greenbullet, 64, &greenbullet, 16,
		4,{
			{&rock,	15, 5},
			{&enemy_m3, 1, 5},
			{&rock,	15, 5},
			{&enemy_m1, 1, 5},
		},
		35,{
			{ 46,  19,   9,  10},
			{ 45, 115,  10,   4},
			{ 14,  60,   5,   8},
			{ 48,  60,   5,  10},
			{ 21,  45,   8,   5},
			{ 11,  83,   5,  13},
			{ 39,  97,  13,   8},
			{ 36,  49,   4,   3},
			{ 18,   8,   5,   4},
			{ 40,  80,   9,   5},
			{ 54,  44,   8,   4},
			{ 13,  27,   9,   3},
			{ 15, 110,   3,   5},
			{  9, 122,   5,   4},
			{ 28,  63,   6,   6},
			{ 35,  39,   3,   3},
			{  6,   5,   5,   3},
			{  6, 113,   4,   3},
			{  6,  40,   4,   5},
			{ 29, 116,   3,   9},
			{ 29,   9,   4,   4},
			{ 59,  65,   3,  10},
			{ 21,  86,   3,   7},
			{  4,  60,   3,   6},
			{  6,  18,   5,   4},
			{ 29,  22,   5,   6},
			{ 52,   4,  10,   3},
			{ 18,  19,   4,   3},
			{ 46,  34,   5,   3},
			{ 57,  91,   3,   4},
			{ 59, 103,   3,   6},
			{ 25,  35,   4,   3},
			{ 19, 122,   3,   4},
			{ 54,  80,   3,   3},
			{  5, 101,   3,   3},
		},
	},
	/* 47 */
	{
		0, 24, 31,
		&enemy5, 64, &ring, 32,
		5,{
			{&enemy1,  10, 5},
			{&enemy7,  10, 5},
			{&enemy1,  10, 5},
			{&enemy7,  10, 5},
			{&bomb2,   10, 5},
		},
		35,{
			{ 29,  37,  19,   2},
			{ 24, 109,   3,  11},
			{  7,  62,   3,   4},
			{ 47,  92,   2,   4},
			{ 50, 112,   7,  12},
			{ 54,  22,   8,  10},
			{ 35, 104,   5,   7},
			{ 32,  69,   9,   5},
			{ 27,  46,  17,   5},
			{ 32,  14,   9,  10},
			{ 12,  28,   8,   4},
			{  5,  94,   4,  18},
			{ 46,  57,   7,   2},
			{ 46,  83,  11,   3},
			{ 58,  76,   4,   2},
			{ 56,  94,   4,   4},
			{ 59,  63,   2,   3},
			{ 16, 120,   3,   4},
			{ 14,  75,   2,  11},
			{ 17,  18,   2,   2},
			{  7,   6,   6,   4},
			{ 37,  28,   6,   2},
			{  6,  47,   2,   3},
			{ 50,  72,   2,   2},
			{ 57,  44,   2,   9},
			{ 18,   8,   2,   6},
			{ 46,   8,   2,   2},
			{ 25,  90,   4,   2},
			{  4,  37,   3,   3},
			{ 17,  98,   2,   2},
			{ 27,  58,   9,   2},
			{ 27,  81,   5,   3},
			{ 57,   7,   5,   2},
			{  7, 120,   2,   6},
			{ 36,  92,   3,   3},
		},
	},
	/* 48 */
	{
		0, 19, 92,
		&enemy1, 64, &enemy2, 128,
		3,{
			{&enemy1,  10, 5},
			{&bomb2,   10, 5},
			{&rock,	20, 5},
		},
		38,{
			{ 16,  54,   3,   3},
			{ 47,  56,   3,   4},
			{ 24,  70,   4,   3},
			{ 31,  14,   3,   3},
			{ 27,  31,   4,   3},
			{ 36,  94,   4,   4},
			{ 21,  19,   3,   4},
			{ 36,  68,   4,   3},
			{ 53,   4,   3,   3},
			{ 36,  80,   4,   4},
			{ 17,  36,   4,   3},
			{ 34, 118,   4,   3},
			{ 40,  13,   3,   4},
			{ 55, 121,   4,   4},
			{ 43,  26,   4,   3},
			{ 12,  71,   4,   4},
			{ 58, 108,   3,   4},
			{ 51,  36,   4,   4},
			{ 23,  94,   3,   3},
			{ 46,  73,   4,   4},
			{  9,  25,   4,   3},
			{ 27,  48,   3,   3},
			{ 50,  91,   3,   3},
			{ 14, 122,   3,   3},
			{ 17, 113,   3,   4},
			{ 16,   8,   3,   4},
			{ 36,  38,   3,   4},
			{ 25, 103,   4,   3},
			{ 55,  70,   3,   4},
			{ 28,  56,   3,   3},
			{ 23,  85,   3,   3},
			{ 50, 108,   3,   3},
			{ 25, 122,   3,   3},
			{ 14,  82,   4,   4},
			{ 50,  16,   4,   4},
			{ 38,  49,   4,   3},
			{  4,   6,   3,   3},
			{  7,  38,   3,   3},
		},
	},
	/* 49 */
	{
		0, 38, 67,
		&greenbullet, 32, &greenbullet, 8,
		6,{
			{&enemy2,  10, 5},
			{&bomb1,   50, 5},
			{&enemy1,  20, 5},
			{&enemy2,  10, 5},
			{&enemy_m1, 1, 5},
			{&enemy1,  20, 5},
		},
		22,{
			{ 28, 104,  10,   6},
			{ 43,  28,  12,   7},
			{ 22,  72,   7,  10},
			{ 11,  16,   8,   6},
			{ 50, 102,   8,   4},
			{ 12,  40,   5,   6},
			{ 49,  80,  11,   5},
			{  6,  95,   4,  13},
			{ 51,  61,   6,  10},
			{ 30,  14,   4,   4},
			{ 17, 118,   6,   6},
			{ 34,  52,   6,   7},
			{ 40, 119,  15,   6},
			{ 31,  91,  15,   4},
			{ 53,  10,   8,   9},
			{  8,  61,   4,   7},
			{  7,  28,   5,   4},
			{ 58,  92,   4,   4},
			{ 19,  55,   5,   5},
			{ 25,  29,   4,   5},
			{ 58,  44,   4,   4},
			{  9,  76,   4,   4},
		},
	},
	/* 50 */
	{
		0, 32, 120,
		&greenbullet, 8, &enemy1, 8,
		1,{
			{&bomb2, 80, 5},
		},
		1,{
			{32, 60, 30, 45},
		},
	},
	{
		/******************* dummy *************************/
		-1, 0, 0,
		&enemy1, 0, &enemy1, 0,
		0,{
			{&enemy1, 0, 0},
		},
		0,{
			{0, 0, 0, 0},
		},
	},
};
