/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ULTIMA4_GFX_SCREEN_H
#define ULTIMA4_GFX_SCREEN_H

#include "graphics/screen.h"
#include "ultima/ultima4/core/types.h"
#include "ultima/ultima4/filesys/u4file.h"
#include "ultima/ultima4/gfx/scale.h"
#include "ultima/ultima4/map/direction.h"
#include "ultima/shared/core/file.h"

namespace Ultima {
namespace Ultima4 {

#define SCR_CYCLE_PER_SECOND 4
#define SCR_CYCLE_MAX 16
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

/*
 * bitmasks for LOS shadows
 */
#define ____H 0x01    // obscured along the horizontal face
#define ___C_ 0x02    // obscured at the center
#define __V__ 0x04    // obscured along the vertical face
#define _N___ 0x80    // start of new raster

#define ___CH 0x03
#define __VCH 0x07
#define __VC_ 0x06

#define _N__H 0x81
#define _N_CH 0x83
#define _NVCH 0x87
#define _NVC_ 0x86
#define _NV__ 0x84


enum LayoutType {
	LAYOUT_STANDARD,
	LAYOUT_GEM,
	LAYOUT_DUNGEONGEM
};

enum MouseCursor {
	MC_DEFAULT,
	MC_WEST,
	MC_NORTH,
	MC_EAST,
	MC_SOUTH
};

class Image;
class Map;
class Tile;
class TileView;
class Coords;

struct Cursor : public Graphics::ManagedSurface {
	Common::Point _hotspot;
};

struct MouseArea {
	int _nPoints;
	struct {
		int x, y;
	} _point[3];
	MouseCursor _cursor;
	int _command[3];
};

struct Layout {
	Common::String _name;
	LayoutType _type;
	Common::Point _tileShape;
	Common::Rect _viewport;
};

class Screen : public Graphics::Screen {
private:
	Cursor *_cursors[5];
	int _currentCursor;
private:
	/**
	 * Load the cursors
	 */
	void loadCursors();

	/**
	 * Loads the data for a single cursor from the passed file
	 */
	Cursor *loadCursor(Shared::File &src);
public:
	Std::vector<Layout *> _layouts;
	Scaler _filterScaler;
public:
	Screen();
	~Screen();

	void init();

	/**
	 * Reset the screen
	 */
	void clear();

	/**
	 * Sets a given mouse cursor
	 */
	void setCursor(MouseCursor cursor);
};

extern Screen *g_screen;

void screenInit(void);
void screenRefreshTimerInit(void);
void screenReInit(void);
void screenWait(int numberOfAnimationFrames);

const Std::vector<Common::String> &screenGetGemLayoutNames();
const Std::vector<Common::String> &screenGetFilterNames();
const Std::vector<Common::String> &screenGetLineOfSightStyles();

void screenDrawImage(const Common::String &name, int x = 0, int y = 0);
void screenDrawImageInMapArea(const Common::String &bkgd);

void screenCycle(void);
void screenEraseMapArea(void);
void screenEraseTextArea(int x, int y, int width, int height);
void screenGemUpdate(void);

void screenMessage(const char *fmt, ...) GCC_PRINTF(1, 2);
void screenPrompt(void);
void screenRedrawMapArea(void);
void screenRedrawTextArea(int x, int y, int width, int height);
void screenScrollMessageArea(void);
void screenShake(int iterations);
void screenShowChar(int chr, int x, int y);
void screenShowCharMasked(int chr, int x, int y, unsigned char mask);
void screenTextAt(int x, int y, const char *fmt, ...) GCC_PRINTF(3, 4);
void screenTextColor(int color);
bool screenTileUpdate(TileView *view, const Coords &coords, bool redraw = true); //Returns true if the screen was affected
void screenUpdate(TileView *view, bool showmap, bool blackout);
void screenUpdateCursor(void);
void screenUpdateMoons(void);
void screenUpdateWind(void);
Std::vector<MapTile> screenViewportTile(unsigned int width, unsigned int height, int x, int y, bool &focus);

void screenShowCursor(void);
void screenHideCursor(void);
void screenEnableCursor(void);
void screenDisableCursor(void);
void screenSetCursorPos(int x, int y);

int screenPointInMouseArea(int x, int y, const MouseArea *area);

Image *screenScale(Image *src, int scale, int n, int filter);
Image *screenScaleDown(Image *src, int scale);

extern int screenCurrentCycle;

} // End of namespace Ultima4
} // End of namespace Ultima

#endif
