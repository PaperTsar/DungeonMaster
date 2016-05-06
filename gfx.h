#ifndef GFX_H
#define GFX_H

#include "common/scummsys.h"
#include "dm/dm.h"

namespace DM {

struct Frame;
enum Color {
	kColorNoTransparency = 255,
	kColorBlack = 0,
	kColorDarkGary = 1,
	kColorLightGray = 2,
	kColorDarkBrown = 3,
	kColorCyan = 4,
	kColorLightBrown = 5,
	kColorDarkGreen = 6,
	kColorLightGreen = 7,
	kColorRed = 8,
	kColorGold = 9,
	kColorFlesh = 10,
	kColorYellow = 11,
	kColorDarkestGray = 12,
	kColorLightestGray = 13,
	kColorBlue = 14,
	kColorWhite = 15
};

enum dmPaletteEnum {
	kPalSwoosh = 0,
	kPalMousePointer = 1,
	kPalCredits = 2,
	kPalEntrance = 3,
	kPalDungeonView0 = 4,
	kPalDungeonView1 = 5,
	kPalDungeonView2 = 6,
	kPalDungeonView3 = 7,
	kPalDungeonView4 = 8,
	kPalDungeonView5 = 9,
};




class DisplayMan {
	DMEngine *_vm;
	dmPaletteEnum _currPalette;
	uint16 _screenWidth;
	uint16 _screenHeight;
	byte *_vgaBuffer;
	uint16 _itemCount;
	uint32 *_packedItemPos;
	byte *_packedBitmaps; // TODO: this doesn't not contaion graphics exclusively, will have to be moved
	DisplayMan(const DisplayMan &other); // no implementation on purpose
	void operator=(const DisplayMan &rhs); // no implementation on purpose

	byte **_bitmaps;
	byte *getCurrentVgaBuffer();
	void loadIntoBitmap(uint16 index, byte *destBitmap);
	void unpackGraphics();
	void drawWallSetBitmap(byte *bitmap, Frame &f, uint16 srcWidth);
public:
	DisplayMan(DMEngine *dmEngine);
	~DisplayMan();
	void setUpScreens(uint16 width, uint16 height);
	void loadGraphics();
	void loadPalette(dmPaletteEnum palette);

	/// Gives the width of an IMG0 type item
	uint16 width(uint16 index);
	/// Gives the height of an IMG1 type item
	uint16 height(uint16 index);

	void blitToBitmap(byte *srcBitmap, uint16 srcWidth, uint16 srcX, uint16 srcY,
					  byte *destBitmap, uint16 destWidth,
					  uint16 destFromX, uint16 destToX, uint16 destFromY, uint16 destToY,
					  Color transparent = kColorNoTransparency);
	void blitToBitmap(byte *srcBitmap, uint16 srcWidth, uint16 srcHeight, byte *destBitmap, uint16 destWidth, uint16 destX = 0, uint16 destY = 0);
	void blitToScreen(byte *srcBitmap, uint16 srcWidth, uint16 srcX, uint16 srcY,
					  uint16 destFromX, uint16 destToX, uint16 destFromY, uint16 destToY,
					  Color transparent = kColorNoTransparency);

	void flipBitmapHorizontal(byte *bitmap, uint16 width, uint16 height);
	void flipBitmapVertical(byte *bitmap, uint16 width, uint16 height);

	void clearBitmap(byte *bitmap, uint16 width, uint16 height, Color color);
	void clearScreen(Color color);
	void drawDungeon(direction dir, uint16 posX, uint16 posY);
	void updateScreen();
};

}



#endif
