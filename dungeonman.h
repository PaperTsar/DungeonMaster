#ifndef DUNGEONMAN_H
#define DUNGEONMAN_H

#include "dm.h"

namespace DM {

class DungeonMan;
class Map;

enum ThingType {
	kPartyThingType = -1, // @ CM1_THING_TYPE_PARTY, special value
	kDoorThingType = 0,
	kTeleporterThingType = 1,
	kTextstringType = 2,
	kSensorThingType = 3,
	kGroupThingType = 4,
	kWeaponThingType = 5,
	kArmourThingType = 6,
	kScrollThingType = 7,
	kPotionThingType = 8,
	kContainerThingType = 9,
	kJunkThingType = 10,
	kProjectileThingType = 14,
	kExplosionThingType = 15,
	kThingTypeTotal = 16 // +1 than the last
}; // @ C[00..15]_THING_TYPE_...


enum SquareMask {
	kWallWestRandOrnAllowed = 0x1,
	kWallSouthRandOrnAllowed = 0x2,
	kWallEastRandOrnAllowed = 0x4,
	kWallNorthRandOrnAllowed = 0x8,
	kPitImaginary = 0x1,
	kPitInvisible = 0x4,
	kPitOpen = 0x8,
	kStairsUp = 0x4,
	kStairsNorthSouthOrient = 0x8,
	kDoorNorthSouthOrient = 0x8,
	kTeleporterVisible = 0x4,
	kTeleporterOpen = 0x8,
	kFakeWallImaginary = 0x1,
	kFakeWallOpen = 0x4,
	kFakeWallRandOrnOrFootPAllowed = 0x8,
	kThingListPresent = 0x10
};

enum SquareType {
	kChampionElemType = -2,
	kCreatureElemType = -1,
	kWallElemType = 0,
	kCorridorElemType = 1,
	kPitElemType = 2,
	kStairsElemType = 3,
	kDoorElemType = 4,
	kTeleporterElemType = 5,
	kFakeWallElemType = 6,
	kDoorSideElemType = 16,
	kDoorFrontElemType = 17,
	kStairsSideElemType = 18,
	kStairsFrontElemType = 19
}; // @ C[-2..19]_ELEMENT_...

class Square {
	byte dat;
public:
	Square(byte dat = 0) : dat(dat) {}
	Square(SquareType type) { setType(type); }
	Square &set(byte dat) { this->dat = dat; return *this; }
	Square &set(SquareMask mask) { dat |= mask; return *this; }
	bool get(SquareMask mask) { return dat & mask; }
	SquareType getType() { return (SquareType)(dat >> 5); } // @ M34_SQUARE_TYPE
	Square &setType(SquareType type) { dat = (dat & 0x1F) | type << 5; return *this; }
	byte toByte() { return dat; } // I don't like 'em casts
};


class DungeonFileHeader {
	friend class DungeonMan;

	uint16 dungeonId; // @ G0526_ui_DungeonID
	// equal to dungeonId
	uint16 ornamentRandomSeed;
	uint32 rawMapDataSize;
	uint8 mapCount;
	uint16 textDataWordCount;
	direction partyStartDir; // @ InitialPartyLocation
	uint16 partyStartPosX, partyStartPosY;
	uint16 squareFirstThingCount; // @ SquareFirstThingCount
	uint16 thingCounts[16]; // @ ThingCount[16]
}; // @ DUNGEON_HEADER

class Map {
	friend class DungeonMan;

	uint32 rawDunDataOffset;
	uint8 offsetMapX, offsetMapY;

	uint8 level; // only used in DMII
	uint8 width, height; // !!! THESRE ARE INCLUSIVE BOUNDARIES
	// orn short for Ornament
	uint8 wallOrnCount; /* May be used in a Sensor on a Wall or closed Fake Wall square */
	uint8 randWallOrnCount; /* Used only on some Wall squares and some closed Fake Wall squares */
	uint8 floorOrnCount; /* May be used in a Sensor on a Pit, open Fake Wall, Corridor or Teleporter square */
	uint8 randFloorOrnCount; /* Used only on some Corridor squares and some open Fake Wall squares */

	uint8 doorOrnCount;
	uint8 creatureTypeCount;
	uint8 difficulty;

	uint8 floorSet, wallSet, doorSet0, doorSet1;
}; // @ MAP

class Thing {
	friend class DungeonMan;

	static const Thing specThingNone;

	Thing() {}
	Thing(uint8 cell, uint8 type, uint8 index) : cell(cell), type(type), index(index) {}

	void set(uint16 dat) {
		cell = dat >> 14;
		type = (dat >> 10) & 0xF;
		index = dat & 0x1FF;
	}

	uint8 cell;
	uint8 type;
	uint8 index;
}; // @ THING

class DungeonData {
	friend class DungeonMan;

	// I have no idea the heck is this
	uint16 *mapsFirstColumnIndex = NULL; // @ G0281_pui_DungeonMapsFirstColumnIndex
	uint16 columCount; // @ G0282_ui_DungeonColumnCount

	// I have no idea the heck is this
	uint16 *columnsCumulativeSquareThingCount = NULL; // @ G0280_pui_DungeonColumnsCumulativeSquareThingCount
	Thing *squareFirstThings = NULL; // @ G0283_pT_SquareFirstThings
	uint16 *textData = NULL; // @ G0260_pui_DungeonTextData

	byte *rawThingData[16] = {NULL}; // @ G0284_apuc_ThingData

	byte ***mapData = NULL; // @ G0279_pppuc_DungeonMapData

	// TODO: ??? is this doing here
	uint16 eventMaximumCount; // @ G0369_ui_EventMaximumCount
}; // @ AGGREGATE

class CurrMapData {
	friend class DungeonMan;

	direction partyDir; // @ G0308_i_PartyDirection
	uint16 partyPosX; // @ G0306_i_PartyMapX
	uint16 partyPosY; // @ G0307_i_PartyMapY
	uint8 currPartyMapIndex; // @ G0309_i_PartyMapIndex

	uint8 index; // @ G0272_i_CurrentMapIndex
	byte **data; // @ G0271_ppuc_CurrentMapData
	Map *map; // @ G0269_ps_CurrentMap
	uint16 width; // @ G0273_i_CurrentMapWidth
	uint16 height; // @ G0274_i_CurrentMapHeight
	uint16 *colCumulativeSquareFirstThingCount; // @G0270_pui_CurrentMapColumnsCumulativeSquareFirstThingCount
}; // @ AGGREGATE

struct Messages {
	friend class DungeonMan;

private:
	bool newGame = true; // @ G0298_B_NewGame
	bool restartGameRequest = false; // @ G0523_B_RestartGameRequested
}; // @ AGGREGATE




class DungeonMan {
	DMEngine *_vm;

	uint32 _rawDunFileDataSize;	 // @ probably NONE
	byte *_rawDunFileData; // @ ???
	DungeonFileHeader _fileHeader; // @ G0278_ps_DungeonHeader

	DungeonData _dunData; // @ NONE
	CurrMapData _currMap; // @ NONE
	Map *_maps; // @ G0277_ps_DungeonMaps
	// does not have to be freed
	byte *_rawMapData; // @ G0276_puc_DungeonRawMapData
	Messages _messages; // @ NONE

	DungeonMan(const DungeonMan &other); // no implementation on purpose
	void operator=(const DungeonMan &rhs); // no implementation on purpose

	Square getSquare(int16 mapX, int16 mapY); // @ F0151_DUNGEON_GetSquare
	Square getRelSquare(direction dir, int16 stepsForward, int16 stepsRight, int16 posX, int16 posY); // @ F0152_DUNGEON_GetRelativeSquare

	void decompressDungeonFile(); // @ F0455_FLOPPY_DecompressDungeon

	Thing getSqureFirstThingIndex(int16 mapX, int16 mapY); // @ F0160_DUNGEON_GetSquareFirstThingIndex
public:
	DungeonMan(DMEngine *dmEngine);
	~DungeonMan();
	// TODO: this does stuff other than load the file!
	void loadDungeonFile();	// @ F0434_STARTEND_IsLoadDungeonSuccessful_CPSC
	void setCurrentMap(uint16 mapIndex); // @ F0173_DUNGEON_SetCurrentMap
	void mapCoordsAfterRelMovement(direction dir, int16 stepsForward, int16 stepsRight, int16 &posX, int16 &posY); // @ F0150_DUNGEON_UpdateMapCoordinatesAfterRelativeMovement
	SquareType getRelSquareType(direction dir, int16 stepsForward, int16 stepsRight, int16 posX, int16 posY) {
		return Square(getRelSquare(dir, stepsForward, stepsRight, posX, posY)).getType();
	} // @ F0153_DUNGEON_GetRelativeSquareType
};

}

#endif
