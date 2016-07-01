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

/*
* Based on the Reverse Engineering work of Christophe Fontanel,
* maintainer of the Dungeon Master Encyclopaedia (http://dmweb.free.fr/)
*/

#ifndef GFX_H
#define GFX_H

#include "common/scummsys.h"
#include "common/rect.h"
#include "common/memstream.h"
#include "dm.h"
#include "common/array.h"

namespace DM {


/* View lanes */
#define kViewLaneCenter 0 // @ C0_VIEW_LANE_CENTER 
#define kViewLaneLeft 1 // @ C1_VIEW_LANE_LEFT   
#define kViewLaneRight 2 // @ C2_VIEW_LANE_RIGHT  

#define kHalfSizedViewCell_LeftColumn 0 // @ C00_VIEW_CELL_LEFT_COLUMN  
#define kHalfSizedViewCell_RightColumn 1 // @ C01_VIEW_CELL_RIGHT_COLUMN 
#define kHalfSizedViewCell_BackRow 2 // @ C02_VIEW_CELL_BACK_ROW     
#define kHalfSizedViewCell_CenterColumn 3 // @ C03_VIEW_CELL_CENTER_COLUMN
#define kHalfSizedViewCell_FrontRow 4 // @ C04_VIEW_CELL_FRONT_ROW    

/* Shift sets */
#define kShiftSet_D0BackD1Front 0 // @ C0_SHIFT_SET_D0_BACK_OR_D1_FRONT
#define kShiftSet_D1BackD2Front 1 // @ C1_SHIFT_SET_D1_BACK_OR_D2_FRONT
#define kShiftSet_D2BackD3Front 2 // @ C2_SHIFT_SET_D2_BACK_OR_D3_FRONT

#define kCellOrder_DoorFront 0x0008 // @ MASK0x0008_DOOR_FRONT                                   
#define kCellOrder_Alcove 0x0000 // @ C0000_CELL_ORDER_ALCOVE                                 
#define kCellOrder_BackLeft 0x0001 // @ C0001_CELL_ORDER_BACKLEFT                               
#define kCellOrder_BackRight 0x0002 // @ C0002_CELL_ORDER_BACKRIGHT                              
#define kCellOrder_DoorPass1_BackLeft 0x0018 // @ C0018_CELL_ORDER_DOORPASS1_BACKLEFT                     
#define kCellOrder_BackLeft_BackRight 0x0021 // @ C0021_CELL_ORDER_BACKLEFT_BACKRIGHT                     
#define kCellOrder_DoorPass1_BackRight 0x0028 // @ C0028_CELL_ORDER_DOORPASS1_BACKRIGHT                    
#define kCellOrder_BackRight_FrontRight 0x0032 // @ C0032_CELL_ORDER_BACKRIGHT_FRONTRIGHT                   
#define kCellOrder_DoorPass2_FrontRight 0x0039 // @ C0039_CELL_ORDER_DOORPASS2_FRONTRIGHT                   
#define kCellOrder_BackLeft_FrontLeft 0x0041 // @ C0041_CELL_ORDER_BACKLEFT_FRONTLEFT                     
#define kCellOrder_DoorPass2_FrontLeft 0x0049 // @ C0049_CELL_ORDER_DOORPASS2_FRONTLEFT                    
#define kCellOrder_DoorPass1_BackRight_BackLeft 0x0128 // @ C0128_CELL_ORDER_DOORPASS1_BACKRIGHT_BACKLEFT           
#define kCellOrder_DoorPass1_BackLeft_BackRight 0x0218 // @ C0218_CELL_ORDER_DOORPASS1_BACKLEFT_BACKRIGHT           
#define kCellOrder_BackLeft_BackRight_FrontRight 0x0321 // @ C0321_CELL_ORDER_BACKLEFT_BACKRIGHT_FRONTRIGHT          
#define kCellOrder_BackRight_FrontLeft_FrontRight 0x0342 // @ C0342_CELL_ORDER_BACKRIGHT_FRONTLEFT_FRONTRIGHT         
#define kCellOrder_DoorPass2_FrontLeft_FrontRight 0x0349 // @ C0349_CELL_ORDER_DOORPASS2_FRONTLEFT_FRONTRIGHT         
#define kCellOrder_BackRight_BackLeft_FrontLeft 0x0412 // @ C0412_CELL_ORDER_BACKRIGHT_BACKLEFT_FRONTLEFT           
#define kCellOrder_BackLeft_FrontRight_FrontLeft 0x0431 // @ C0431_CELL_ORDER_BACKLEFT_FRONTRIGHT_FRONTLEFT          
#define kCellOrder_DoorPass2_FrontRight_FrontLeft 0x0439 // @ C0439_CELL_ORDER_DOORPASS2_FRONTRIGHT_FRONTLEFT         
#define kCellOrder_BackLeft_BackRight_FrontLeft_FrontRight 0x3421 // @ C3421_CELL_ORDER_BACKLEFT_BACKRIGHT_FRONTLEFT_FRONTRIGHT
#define kCellOrder_BackRight_BackLeft_FrontRight_FrontLeft 0x4312 // @ C4312_CELL_ORDER_BACKRIGHT_BACKLEFT_FRONTRIGHT_FRONTLEFT


#define kFloorSetGraphicCount 2 // @ C002_FLOOR_SET_GRAPHIC_COUNT
#define kWallSetGraphicCount 13 // @ C013_WALL_SET_GRAPHIC_COUNT
#define kStairsGraphicCount 18 // @ C018_STAIRS_GRAPHIC_COUNT
#define kDoorSetGraphicsCount 3 // @ C003_DOOR_SET_GRAPHIC_COUNT
#define kDoorButtonCount 1 // @ C001_DOOR_BUTTON_COUNT
#define kNativeBitmapIndex 0 // @ C0_NATIVE_BITMAP_INDEX
#define kCoordinateSet 1 // @ C1_COORDINATE_SET
#define kCreatureTypeCount 27 // @ C027_CREATURE_TYPE_COUNT
#define kExplosionAspectCount 4 // @ C004_EXPLOSION_ASPECT_COUNT
#define kObjAspectCount 85 // @ C085_OBJECT_ASPECT_COUNT
#define kProjectileAspectCount 14 // @ C014_PROJECTILE_ASPECT_COUNT

/* Explosion aspects */
#define kExplosionAspectFire 0 // @ C0_EXPLOSION_ASPECT_FIRE  
#define kExplosionAspectSpell 1 // @ C1_EXPLOSION_ASPECT_SPELL 
#define kExplosionAspectPoison 2 // @ C2_EXPLOSION_ASPECT_POISON
#define kExplosionAspectSmoke 3 // @ C3_EXPLOSION_ASPECT_SMOKE 

/* Creature info GraphicInfo */
#define kCreatureInfoGraphicMaskAdditional 0x0003 // @ MASK0x0003_ADDITIONAL                        
#define kCreatureInfoGraphicMaskFlipNonAttack 0x0004 // @ MASK0x0004_FLIP_NON_ATTACK                  
#define kCreatureInfoGraphicMaskSide 0x0008 // @ MASK0x0008_SIDE                             
#define kCreatureInfoGraphicMaskBack 0x0010 // @ MASK0x0010_BACK                             
#define kCreatureInfoGraphicMaskAttack 0x0020 // @ MASK0x0020_ATTACK                           
#define kCreatureInfoGraphicMaskSpecialD2Front 0x0080 // @ MASK0x0080_SPECIAL_D2_FRONT                                                                               
#define kCreatureInfoGraphicMaskSpecialD2FrontIsFlipped 0x0100 // @ MASK0x0100_SPECIAL_D2_FRONT_IS_FLIPPED_FRONT 
#define kCreatureInfoGraphicMaskFlipAttack 0x0200 // @ MASK0x0200_FLIP_ATTACK                      
#define kCreatureInfoGraphicMaskFlipDuringAttack 0x0400 // @ MASK0x0400_FLIP_DURING_ATTACK               

class ExplosionAspect {
public:
	uint16 _pixelWidth;
	uint16 _height;

	ExplosionAspect(uint16 byteWidth, uint16 height) :_pixelWidth(byteWidth * 2), _height(height) {}
}; // @ EXPLOSION_ASPECT

extern ExplosionAspect gExplosionAspects[kExplosionAspectCount];

extern byte gProjectileScales[7]; // @ G0215_auc_Graphic558_ProjectileScales


#define kDerivedBitmapViewport 0 // @ C000_DERIVED_BITMAP_VIEWPORT                    
#define kDerivedBitmapThievesEyeVisibleArea 1 // @ C001_DERIVED_BITMAP_THIEVES_EYE_VISIBLE_AREA    
#define kDerivedBitmapDamageToCreatureMedium 2 // @ C002_DERIVED_BITMAP_DAMAGE_TO_CREATURE_MEDIUM   
#define kDerivedBitmapDamageToCreatureSmall 3 // @ C003_DERIVED_BITMAP_DAMAGE_TO_CREATURE_SMALL    
#define kDerivedBitmapFirstWallOrnament 4 // @ C004_DERIVED_BITMAP_FIRST_WALL_ORNAMENT         
#define kDerivedBitmapFirstDoorOrnament_D3 68 // @ C068_DERIVED_BITMAP_FIRST_DOOR_ORNAMENT_D3     
#define kDerivedBitmapFirstDoorOrnament_D2 69 // @ C069_DERIVED_BITMAP_FIRST_DOOR_ORNAMENT_D2    
#define kDerivedBitmapFirstDoorButton 102 // @ C102_DERIVED_BITMAP_FIRST_DOOR_BUTTON         
#define kDerivedBitmapFirstObject 104 // @ C104_DERIVED_BITMAP_FIRST_OBJECT              
#define kDerivedBitmapFirstProjectile 282 // @ C282_DERIVED_BITMAP_FIRST_PROJECTILE          
#define kDerivedBitmapFirstExplosion 438 // @ C438_DERIVED_BITMAP_FIRST_EXPLOSION           
#define kDerivedBitmapFirstCreature 495 // @ C495_DERIVED_BITMAP_FIRST_CREATURE            


#define kScale16_D3 16 // @ C16_SCALE_D3 
#define kScale20_D2 20 // @ C20_SCALE_D2 

/* Object aspect GraphicInfo */
#define kObjectFlipOnRightMask 0x0001 // @ MASK0x0001_FLIP_ON_RIGHT 
#define kObjectAlcoveMask 0x0010 // @ MASK0x0010_ALCOVE        

/* Projectile aspect GraphicInfo */
#define kProjectileSideMask 0x0010 // @ MASK0x0010_SIDE                      
#define kProjectileScaleWithKineticEnergyMask 0x0100 // @ MASK0x0100_SCALE_WITH_KINETIC_ENERGY 
#define kProjectileAspectTypeMask 0x0003 // @ MASK0x0003_ASPECT_TYPE               

/* Projectile aspect type */
#define kProjectileAspectHasBackGraphicRotation 0 // @ C0_PROJECTILE_ASPECT_TYPE_HAS_BACK_GRAPHIC_AND_ROTATION   
#define kProjectileAspectBackGraphic 1 // @ C1_PROJECTILE_ASPECT_TYPE_HAS_BACK_GRAPHIC_AND_NO_ROTATION
#define kProjectileAspectHasRotation 2 // @ C2_PROJECTILE_ASPECT_TYPE_NO_BACK_GRAPHIC_AND_ROTATION    
#define kProjectileAspectHasNone 3 // @ C3_PROJECTILE_ASPECT_TYPE_NO_BACK_GRAPHIC_AND_NO_ROTATION 

/* Projectile aspects */
#define kProjectileAspectExplosionLightningBolt 3 // @ C03_PROJECTILE_ASPECT_EXPLOSION_LIGHTNING_BOLT           
#define kProjectileAspectExplosionFireBall 10 // @ C10_PROJECTILE_ASPECT_EXPLOSION_FIREBALL                
#define kProjectileAspectExplosionDefault 11 // @ C11_PROJECTILE_ASPECT_EXPLOSION_DEFAULT                 
#define kProjectileAspectExplosionSlime 12 // @ C12_PROJECTILE_ASPECT_EXPLOSION_SLIME                   
#define kProjectileAspectExplosionPoisonBoltCloud 13 // @ C13_PROJECTILE_ASPECT_EXPLOSION_POISON_BOLT_POISON_CLOUD

enum ViewCell {
	kViewCellFronLeft = 0, // @ C00_VIEW_CELL_FRONT_LEFT
	kViewCellFrontRight = 1, // @ C01_VIEW_CELL_FRONT_RIGHT
	kViewCellBackRight = 2, // @ C02_VIEW_CELL_BACK_RIGHT
	kViewCellBackLeft = 3, // @ C03_VIEW_CELL_BACK_LEFT
	kViewCellAlcove = 4, // @ C04_VIEW_CELL_ALCOVE
	kViewCellDoorButtonOrWallOrn = 5 // @ C05_VIEW_CELL_DOOR_BUTTON_OR_WALL_ORNAMENT
};

enum GraphicIndice {
	kInscriptionFontIndice = 120, // @ C120_GRAPHIC_INSCRIPTION_FONT
	kDoorMaskDestroyedIndice = 301, // @ C301_GRAPHIC_DOOR_MASK_DESTROYED
	kChampionPortraitsIndice = 26, // @ C026_GRAPHIC_CHAMPION_PORTRAITS
	kMovementArrowsIndice = 13, // @ C013_GRAPHIC_MOVEMENT_ARROWS
	kObjectIcons_000_TO_031 = 42, // @ C042_GRAPHIC_OBJECT_ICONS_000_TO_031
	kObjectIcons_032_TO_063 = 43, // @ C043_GRAPHIC_OBJECT_ICONS_032_TO_063
	kObjectIcons_064_TO_095 = 44, // @ C044_GRAPHIC_OBJECT_ICONS_064_TO_095
	kObjectIcons_096_TO_127 = 45, // @ C045_GRAPHIC_OBJECT_ICONS_096_TO_127
	kObjectIcons_128_TO_159 = 46, // @ C046_GRAPHIC_OBJECT_ICONS_128_TO_159
	kObjectIcons_160_TO_191 = 47, // @ C047_GRAPHIC_OBJECT_ICONS_160_TO_191
	kObjectIcons_192_TO_223 = 48, // @ C048_GRAPHIC_OBJECT_ICONS_192_TO_223
	kInventoryGraphicIndice = 17, // @ C017_GRAPHIC_INVENTORY
	kPanelEmptyIndice = 20, // @ C020_GRAPHIC_PANEL_EMPTY
	kFoodLabelIndice = 30, // @ C030_GRAPHIC_FOOD_LABEL
	kWaterLabelIndice = 31, // @ C031_GRAPHIC_WATER_LABEL
	kPoisionedLabelIndice = 32, // @ C032_GRAPHIC_POISONED_LABEL
	kPanelResurectReincaranteIndice = 40, // @ C040_GRAPHIC_PANEL_RESURRECT_REINCARNATE 
	kBorderPartyShieldIndice = 37, // @ C037_GRAPHIC_BORDER_PARTY_SHIELD
	kBorderPartyFireshieldIndice = 38, // @ C038_GRAPHIC_BORDER_PARTY_FIRESHIELD
	kBorderPartySpellshieldIndice = 39, // @ C039_GRAPHIC_BORDER_PARTY_SPELLSHIELD
	kStatusBoxDeadChampion = 8, // @ C008_GRAPHIC_STATUS_BOX_DEAD_CHAMPION
	kSlotBoxNormalIndice = 33, // @ C033_GRAPHIC_SLOT_BOX_NORMAL                   
	kSlotBoxWoundedIndice = 34, // @ C034_GRAPHIC_SLOT_BOX_WOUNDED                  
	kChampionIcons = 28, // @ C028_GRAPHIC_CHAMPION_ICONS
	kFontGraphicIndice = 557, // @ C557_GRAPHIC_FONT 
	kSlotBoxActingHandIndice = 35, // @ C035_GRAPHIC_SLOT_BOX_ACTING_HAND
	kPanelRenameChampionIndice = 27, // @ C027_GRAPHIC_PANEL_RENAME_CHAMPION
	kMenuActionAreaIndice = 10, // @ C010_GRAPHIC_MENU_ACTION_AREA
	kMenuSpellAreLinesIndice = 11, // @ C011_GRAPHIC_MENU_SPELL_AREA_LINES
	kMenuSpellAreaBackground = 9, // @ C009_GRAPHIC_MENU_SPELL_AREA_BACKGROUND
	kPanelOpenScrollIndice = 23, // @ C023_GRAPHIC_PANEL_OPEN_SCROLL
	kPanelOpenChestIndice = 25, // @ C025_GRAPHIC_PANEL_OPEN_CHEST
	kEyeForObjectDescriptionIndice = 19, // @ C019_GRAPHIC_EYE_FOR_OBJECT_DESCRIPTION
	kArrowForChestContentIndice = 18, // @ C018_GRAPHIC_ARROW_FOR_CHEST_CONTENT
	kObjectDescCircleIndice = 29, // @ C029_GRAPHIC_OBJECT_DESCRIPTION_CIRCLE
	kFloorOrn_15_D3L_footprints = 241, // @ C241_GRAPHIC_FLOOR_ORNAMENT_15_D3L_FOOTPRINTS
	kFieldMask_D3R_GraphicIndice = 69, // @ C069_GRAPHIC_FIELD_MASK_D3R
	kFieldTeleporterGraphicIndice = 73, // @ C073_GRAPHIC_FIELD_TELEPORTER
	kFirstExplosionGraphicIndice = 348, // @ C348_GRAPHIC_FIRST_EXPLOSION
	kFirstObjectGraphicIndice = 360, // @ C360_GRAPHIC_FIRST_OBJECT
	kFirstCreatureGraphicIndice = 446, // @ C446_GRAPHIC_FIRST_CREATURE
	kFirstProjectileGraphicIndice = 316, // @ C316_GRAPHIC_FIRST_PROJECTILE 
	kFirstExplosionPatternGraphicIndice = 351 // @ C351_GRAPHIC_FIRST_EXPLOSION_PATTERN 
};

extern uint16 gPalSwoosh[16];
extern uint16 gPalMousePointer[16];
extern uint16 gPalCredits[16];
extern uint16 gPalEntrance[16];
extern uint16 gPalDungeonView[6][16];

class Box {
public:
	uint16 _x1;
	uint16 _x2;
	uint16 _y1;
	uint16 _y2;

	Box(uint16 x1, uint16 x2, uint16 y1, uint16 y2) : _x1(x1), _x2(x2 + 1), _y1(y1), _y2(y2 + 1) {}
	Box() {}
	bool isPointInside(Common::Point point) {
		return (_x1 <= point.x) && (point.x < _x2) && (_y1 <= point.y) && (point.y < _y2);
	}
	void setToZero() { _x1 = _x2 = _y1 = _y2 = 0; }
}; // @ BOX_BYTE, BOX_WORD

extern Box gBoxMovementArrows; // G0002_s_Graphic562_Box_MovementArrows

// The frames in the original sources contain inclusive boundaries and byte widths, not pixel widths
struct Frame {
	uint16 _destFromX, _destToX, _destFromY, _destToY;
	uint16 _srcWidth, _srcHeight;
	uint16 _srcX, _srcY;

	Frame() {}
	Frame(uint16 destFromX, uint16 destToX, uint16 destFromY, uint16 destToY,
		  uint16 srcWidth, uint16 srcHeight, uint16 srcX, uint16 srcY) :
		_destFromX(destFromX), _destToX(destToX + 1), _destFromY(destFromY), _destToY(destToY + 1),
		_srcWidth(srcWidth * 2), _srcHeight(srcHeight), _srcX(srcX), _srcY(srcY) {}
};

enum WallSet {
	kWallSetStone = 0 // @ C0_WALL_SET_STONE
};

enum FloorSet {
	kFloorSetStone = 0 // @ C0_FLOOR_SET_STONE
};

enum StairIndex {
	kStairsNativeIndex_Up_Front_D3L = 0, // @ G0675_i_StairsNativeBitmapIndex_Up_Front_D3L
	kStairsNativeIndex_Up_Front_D3C = 1, // @ G0676_i_StairsNativeBitmapIndex_Up_Front_D3C
	kStairsNativeIndex_Up_Front_D2L = 2, // @ G0677_i_StairsNativeBitmapIndex_Up_Front_D2L
	kStairsNativeIndex_Up_Front_D2C = 3, // @ G0678_i_StairsNativeBitmapIndex_Up_Front_D2C
	kStairsNativeIndex_Up_Front_D1L = 4, // @ G0679_i_StairsNativeBitmapIndex_Up_Front_D1L
	kStairsNativeIndex_Up_Front_D1C = 5, // @ G0680_i_StairsNativeBitmapIndex_Up_Front_D1C
	kStairsNativeIndex_Up_Front_D0C_Left = 6, // @ G0681_i_StairsNativeBitmapIndex_Up_Front_D0C_Left
	kStairsNativeIndex_Down_Front_D3L = 7, // @ G0682_i_StairsNativeBitmapIndex_Down_Front_D3L
	kStairsNativeIndex_Down_Front_D3C = 8, // @ G0683_i_StairsNativeBitmapIndex_Down_Front_D3C
	kStairsNativeIndex_Down_Front_D2L = 9, // @ G0684_i_StairsNativeBitmapIndex_Down_Front_D2L
	kStairsNativeIndex_Down_Front_D2C = 10, // @ G0685_i_StairsNativeBitmapIndex_Down_Front_D2C
	kStairsNativeIndex_Down_Front_D1L = 11, // @ G0686_i_StairsNativeBitmapIndex_Down_Front_D1L
	kStairsNativeIndex_Down_Front_D1C = 12, // @ G0687_i_StairsNativeBitmapIndex_Down_Front_D1C
	kStairsNativeIndex_Down_Front_D0C_Left = 13, // @ G0688_i_StairsNativeBitmapIndex_Down_Front_D0C_Left
	kStairsNativeIndex_Side_D2L = 14, // @ G0689_i_StairsNativeBitmapIndex_Side_D2L
	kStairsNativeIndex_Up_Side_D1L = 15, // @ G0690_i_StairsNativeBitmapIndex_Up_Side_D1L
	kStairsNativeIndex_Down_Side_D1L = 16, // @ G0691_i_StairsNativeBitmapIndex_Down_Side_D1L
	kStairsNativeIndex_Side_D0L = 17 // @ G0692_i_StairsNativeBitmapIndex_Side_D0L
};

enum ViewWall {
	kViewWall_D3L_RIGHT = 0, // @ C00_VIEW_WALL_D3L_RIGHT 
	kViewWall_D3R_LEFT = 1, // @ C01_VIEW_WALL_D3R_LEFT  
	kViewWall_D3L_FRONT = 2, // @ C02_VIEW_WALL_D3L_FRONT 
	kViewWall_D3C_FRONT = 3, // @ C03_VIEW_WALL_D3C_FRONT 
	kViewWall_D3R_FRONT = 4, // @ C04_VIEW_WALL_D3R_FRONT 
	kViewWall_D2L_RIGHT = 5, // @ C05_VIEW_WALL_D2L_RIGHT 
	kViewWall_D2R_LEFT = 6, // @ C06_VIEW_WALL_D2R_LEFT  
	kViewWall_D2L_FRONT = 7, // @ C07_VIEW_WALL_D2L_FRONT 
	kViewWall_D2C_FRONT = 8, // @ C08_VIEW_WALL_D2C_FRONT 
	kViewWall_D2R_FRONT = 9, // @ C09_VIEW_WALL_D2R_FRONT 
	kViewWall_D1L_RIGHT = 10, // @ C10_VIEW_WALL_D1L_RIGHT
	kViewWall_D1R_LEFT = 11, // @ C11_VIEW_WALL_D1R_LEFT 
	kViewWall_D1C_FRONT = 12  // @ C12_VIEW_WALL_D1C_FRONT
};

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

class FieldAspect {
public:
	uint16 _nativeBitmapRelativeIndex;
	uint16 _baseStartUnitIndex; /* Index of the unit (16 pixels = 8 bytes) in bitmap where blit will start from. A random value of 0 or 1 is added to this base index */
	uint16 _transparentColor; /* Bit 7: Do not use mask if set, Bits 6-0: Transparent color index. 0xFF = no transparency */
	byte _mask; /* Bit 7: Flip, Bits 6-0: Mask index. 0xFF = no mask */
	uint16 _pixelWidth;
	uint16 _height;
	uint16 _xPos;
	uint16 _bitplaneWordCount;
	FieldAspect(uint16 native, uint16 base, uint16 transparent, byte mask, uint16 byteWidth, uint16 height, uint16 xPos, uint16 bitplane)
		: _nativeBitmapRelativeIndex(native), _baseStartUnitIndex(base), _transparentColor(transparent), _mask(mask),
		_pixelWidth(byteWidth * 2), _height(height), _xPos(xPos), _bitplaneWordCount(bitplane) {}
	FieldAspect() {}
}; // @ FIELD_ASPECT


class Viewport {
public:
	uint16 _posX, _posY;
	uint16 _width, _height;
	Viewport() {}
	Viewport(uint16 posX, uint16 posY, uint16 width, uint16 height)
		:_posX(posX), _posY(posY), _width(width), _height(height) {}
};

struct CreatureAspect {
	uint16 _firstNativeBitmapRelativeIndex;
	uint16 _firstDerivedBitmapIndex;
	byte _byteWidthFront;
	byte _heightFront;
	byte _byteWidthSide;
	byte _heightSide;
	byte _byteWidthAttack;
	byte _heightAttack;
	byte _coordinateSet_TransparentColor;
	byte _replacementColorSetIndices;

	byte getCoordSet() { return (_coordinateSet_TransparentColor >> 4) & 0xF; } // @ M71_COORDINATE_SET
	byte getTranspColour() { return  _coordinateSet_TransparentColor & 0xF; } // @ M72_TRANSPARENT_COLOR
	byte getReplColour10() { return (_replacementColorSetIndices >> 4) & 0xF; } // @ M74_COLOR_10_REPLACEMENT_COLOR_SET
	byte getReplColour9() { return _replacementColorSetIndices & 0xF; } // @ M73_COLOR_09_REPLACEMENT_COLOR_SET
}; // @ CREATURE_ASPECT

struct ObjectAspect {
	byte _firstNativeBitmapRelativeIndex;
	byte _firstDerivedBitmapRelativeIndex;
	byte _width;
	byte _height;
	byte _graphicInfo; /* Bits 7-5 and 3-1 Unreferenced */
	byte _coordinateSet;
	ObjectAspect(byte firstN, byte firstD, byte byteWidth, byte h, byte grap, byte coord) :
		_firstNativeBitmapRelativeIndex(firstN), _firstDerivedBitmapRelativeIndex(firstD),
		_width(byteWidth * 2), _height(h), _graphicInfo(grap), _coordinateSet(coord) {}
}; // @ OBJECT_ASPECT

struct ProjectileAspect {
	byte _firstNativeBitmapRelativeIndex;
	byte _firstDerivedBitmapRelativeIndex;
	byte _width;
	byte _height;
	uint16 _graphicInfo; /* Bits 15-9, 7-5 and 3-2 Unreferenced */

	ProjectileAspect(byte firstN, byte firstD, byte byteWidth, byte h, uint16 grap) :
		_firstNativeBitmapRelativeIndex(firstN), _firstDerivedBitmapRelativeIndex(firstD),
		_width(byteWidth * 2), _height(h), _graphicInfo(grap) {}
}; // @ PROJECTIL_ASPECT

struct CreatureReplColorSet {
	uint16 _RGBColor[6];
	byte _D2ReplacementColor;
	byte _D3ReplacementColor;
}; // @ CREATURE_REPLACEMENT_COLOR_SET

extern Viewport gDefultViewPort;
extern Viewport gDungeonViewport;

#define kAlcoveOrnCount 3
#define kFountainOrnCount 1


#define kDoorButton 0 // @ C0_DOOR_BUTTON
#define kWallOrnInscription 0 // @ C0_WALL_ORNAMENT_INSCRIPTION
#define kFloorOrnFootprints 15 // @ C15_FLOOR_ORNAMENT_FOOTPRINTS
#define kDoorOrnDestroyedMask 15 // @ C15_DOOR_ORNAMENT_DESTROYED_MASK
#define kDoorOrnThivesEyeMask 16 // @ C16_DOOR_ORNAMENT_THIEVES_EYE_MASK

class DisplayMan {
	friend class DM::TextMan;

	DMEngine *_vm;
	uint16 _screenWidth;
	uint16 _screenHeight;
	byte *_vgaBuffer;

	/// Related to graphics.dat file
	uint16 _grapItemCount; // @ G0632_ui_GraphicCount
	uint32 *_packedItemPos;
	byte *_packedBitmaps;
	byte **_bitmaps;

	// pointers 13,14 and [15-19] are owned by this array
	byte *_wallSetBitMaps[25];	// @G[0696..0710]_puc_Bitmap_WallSet_...
	uint16 _stairIndices[kStairsGraphicCount];

	// pointers are not owned by these fields
	byte *_floorBitmap;
	byte *_ceilingBitmap;
	byte *_palChangesProjectile[4]; // @G0075_apuc_PaletteChanges_Projectile

	DisplayMan(const DisplayMan &other); // no implementation on purpose
	void operator=(const DisplayMan &rhs); // no implementation on purpose

	byte *getCurrentVgaBuffer();
	// the original function has two position parameters, but they are always set to zero
	void loadIntoBitmap(uint16 index, byte *destBitmap); // @ F0466_EXPAND_GraphicToBitmap
	void unpackGraphics();
	void loadFNT1intoBitmap(uint16 index, byte *destBitmap);

	void drawFloorPitOrStairsBitmapFlippedHorizontally(StairIndex relIndex, Frame &frame); // @ F0105_DUNGEONVIEW_DrawFloorPitOrStairsBitmapFlippedHorizontally
	void drawFloorPitOrStairsBitmap(StairIndex relIndex, Frame &frame); // @ F0104_DUNGEONVIEW_DrawFloorPitOrStairsBitmap
	void drawWallSetBitmap(byte *bitmap, Frame &f); // @ F0100_DUNGEONVIEW_DrawWallSetBitmap
	void drawWallSetBitmapWithoutTransparency(byte *bitmap, Frame &f); // @ F0101_DUNGEONVIEW_DrawWallSetBitmapWithoutTransparency
	void drawSquareD3L(direction dir, int16 posX, int16 posY); // @ F0116_DUNGEONVIEW_DrawSquareD3L
	void drawSquareD3R(direction dir, int16 posX, int16 posY); // @ F0117_DUNGEONVIEW_DrawSquareD3R
	void drawSquareD3C(direction dir, int16 posX, int16 posY); // @ F0118_DUNGEONVIEW_DrawSquareD3C_CPSF
	void drawSquareD2L(direction dir, int16 posX, int16 posY); // @ F0119_DUNGEONVIEW_DrawSquareD2L
	void drawSquareD2R(direction dir, int16 posX, int16 posY); // @ F0120_DUNGEONVIEW_DrawSquareD2R_CPSF
	void drawSquareD2C(direction dir, int16 posX, int16 posY); // @ F0121_DUNGEONVIEW_DrawSquareD2C
	void drawSquareD1L(direction dir, int16 posX, int16 posY); // @ F0122_DUNGEONVIEW_DrawSquareD1L
	void drawSquareD1R(direction dir, int16 posX, int16 posY); // @ F0122_DUNGEONVIEW_DrawSquareD1R
	void drawSquareD1C(direction dir, int16 posX, int16 posY); // @ F0124_DUNGEONVIEW_DrawSquareD1C
	void drawSquareD0L(direction dir, int16 posX, int16 posY); // @ F0125_DUNGEONVIEW_DrawSquareD0L
	void drawSquareD0R(direction dir, int16 posX, int16 posY); // @ F0126_DUNGEONVIEW_DrawSquareD0R
	void drawSquareD0C(direction dir, int16 posX, int16 posY); // @ F0127_DUNGEONVIEW_DrawSquareD0C


	void applyCreatureReplColors(int replacedColor, int replacementColor); // @ F0093_DUNGEONVIEW_ApplyCreatureReplacementColors

	bool isDrawnWallOrnAnAlcove(int16 wallOrnOrd, ViewWall viewWallIndex); // @ F0107_DUNGEONVIEW_IsDrawnWallOrnamentAnAlcove_CPSF

	uint16 *_derivedBitmapByteCount; // @ G0639_pui_DerivedBitmapByteCount
	byte **_derivedBitmaps; // @ G0638_pui_DerivedBitmapBlockIndices

public:
	// some methods use this for a stratchpad, don't make assumptions about content between function calls
	byte *_tmpBitmap;

	explicit DisplayMan(DMEngine *dmEngine);
	~DisplayMan();

	void loadWallSet(WallSet set); // @ F0095_DUNGEONVIEW_LoadWallSet
	void loadFloorSet(FloorSet set); // @ F0094_DUNGEONVIEW_LoadFloorSet

	void setUpScreens(uint16 width, uint16 height);
	void loadGraphics(); // @ F0479_MEMORY_ReadGraphicsDatHeader, F0460_START_InitializeGraphicData
	void loadCurrentMapGraphics(); // @ F0096_DUNGEONVIEW_LoadCurrentMapGraphics_CPSDF
	void loadPalette(uint16 *palette);

	/// Gives the width of an IMG0 type item
	uint16 getWidth(uint16 index);
	/// Gives the height of an IMG1 type item
	uint16 getHeight(uint16 index);

	void blitToBitmap(byte *srcBitmap, uint16 srcWidth, uint16 srcX, uint16 srcY,
					  byte *destBitmap, uint16 destWidth,
					  uint16 destFromX, uint16 destToX, uint16 destFromY, uint16 destToY,
					  Color transparent = kColorNoTransparency, Viewport &viewport = gDefultViewPort);
	void blitToBitmap(byte *srcBitmap, uint16 srcWidth, uint16 srcX, uint16 srcY,
					  byte *destBitmap, uint16 destWidth, Box &box, Color transparent = kColorNoTransparency, Viewport &viewport = gDefultViewPort);
	void blitToBitmapShrinkWithPalChange(byte *srcBitmap, int16 srcWidth, int16 srcHight,
										 byte *destBitmap, int16 destWidth, int16 destHeight, byte *palChange); // @ F0129_VIDEO_BlitShrinkWithPaletteChanges

	void blitToBitmap(byte *srcBitmap, uint16 srcWidth, uint16 srcHeight, byte *destBitmap, uint16 destWidth, uint16 destX = 0, uint16 destY = 0);
	void blitToScreen(byte *srcBitmap, uint16 srcWidth, uint16 srcX, uint16 srcY,
					  uint16 destFromX, uint16 destToX, uint16 destFromY, uint16 destToY,
					  Color transparent = kColorNoTransparency, Viewport &viewport = gDefultViewPort);
	void blitToScreen(byte *srcBitmap, uint16 srcWidth, uint16 srcX, uint16 srcY,
					  Box &box,
					  Color transparent = kColorNoTransparency, Viewport &viewport = gDefultViewPort);
	void blitBoxFilledWithMaskedBitmap(byte *src, byte *dest, byte *mask, byte *tmp, Box &box, int16 lastUnitIndex,
									   int16 firstUnitIndex, int16 destPixelWidth, Color transparent,
									   int16 xPos, int16 yPos, int16 destHeight, int16 height2, Viewport &viewport = gDefultViewPort); // @ F0133_VIDEO_BlitBoxFilledWithMaskedBitmap
	void blitBoxFilledWithMaskedBitmapToScreen(byte *src, byte *mask, byte *tmp, Box &box, int16 lastUnitIndex,
									   int16 firstUnitIndex, int16 destPixelWidth, Color transparent,
									   int16 xPos, int16 yPos, int16 destHeight, int16 height2, Viewport &viewport = gDungeonViewport); // @ F0133_VIDEO_BlitBoxFilledWithMaskedBitmap

	void flipBitmapHorizontal(byte *bitmap, uint16 width, uint16 height);
	void flipBitmapVertical(byte *bitmap, uint16 width, uint16 height);
	byte *getExplosionBitmap(uint16 explosionAspIndex, uint16 scale, int16 &returnPixelWidth, int16 &returnHeight); // @ F0114_DUNGEONVIEW_GetExplosionBitmap

	void clearBitmap(byte *bitmap, uint16 width, uint16 height, Color color);
	void clearScreen(Color color);
	void clearScreenBox(Color color, Box &box, Viewport &viewport = gDefultViewPort); // @ D24_FillScreenBox
	void drawDungeon(direction dir, int16 posX, int16 posY); // @ F0128_DUNGEONVIEW_Draw_CPSF
	void updateScreen();
	byte* getBitmap(uint16 index);
	Common::MemoryReadStream getCompressedData(uint16 index);
	uint32 getCompressedDataSize(uint16 index);
	void drawField(FieldAspect *fieldAspect, Box &box); // @ F0113_DUNGEONVIEW_DrawField

	int16 getScaledBitmapPixelCount(int16 pixelWidth, int16 pixelHeight, int16 scale); // @ F0459_START_GetScaledBitmapByteCount
	int16 getScaledDimension(int16 dimension, int16 scale); // @ M78_SCALED_DIMENSION
	void cthulhu(Thing thingParam, direction directionParam,
												   int16 mapXpos, int16 mapYpos, int16 viewSquareIndex,
												   uint16 orderedViewCellOrdinals); // @ F0115_DUNGEONVIEW_DrawObjectsCreaturesProjectilesExplosions_CPSEF
	uint16 getNormalizedByteWidthM77(uint16 byteWidth); // @ M77_NORMALIZED_BYTE_WIDTH
	uint16 getVerticalOffsetM23(uint16 val); // @ M23_VERTICAL_OFFSET
	uint16 getHorizontalOffsetM22(uint16 val); // @ M22_HORIZONTAL_OFFSET

	int16 _championPortraitOrdinal; // @ G0289_i_DungeonView_ChampionPortraitOrdinal
	int16 _currMapAlcoveOrnIndices[kAlcoveOrnCount]; // @ G0267_ai_CurrentMapAlcoveOrnamentIndices
	int16 _currMapFountainOrnIndices[kFountainOrnCount]; // @ G0268_ai_CurrentMapFountainOrnamentIndices
	int16 _currMapWallOrnInfo[16][2]; // @ G0101_aai_CurrentMapWallOrnamentsInfo
	int16 _currMapFloorOrnInfo[16][2]; // @ G0102_aai_CurrentMapFloorOrnamentsInfo
	int16 _currMapDoorOrnInfo[17][2]; // @ G0103_aai_CurrentMapDoorOrnamentsInfo
	byte *_currMapAllowedCreatureTypes; // @ G0264_puc_CurrentMapAllowedCreatureTypes
	byte _currMapWallOrnIndices[16]; // @ G0261_auc_CurrentMapWallOrnamentIndices
	byte _currMapFloorOrnIndices[16]; // @ G0262_auc_CurrentMapFloorOrnamentIndices
	byte _currMapDoorOrnIndices[18]; // @ G0263_auc_CurrentMapDoorOrnamentIndices

	int16 _currMapViAltarIndex; // @ G0266_i_CurrentMapViAltarWallOrnamentIndex

	Thing _inscriptionThing; // @ G0290_T_DungeonView_InscriptionThing

	bool _useByteBoxCoordinates; // @ G0578_B_UseByteBoxCoordinates
	bool _doNotDrawFluxcagesDuringEndgame; // @ G0077_B_DoNotDrawFluxcagesDuringEndgame

	bool isDerivedBitmapInCache(int16 derivedBitmapIndex); // @  F0491_CACHE_IsDerivedBitmapInCache
	byte *getDerivedBitmap(int16 derivedBitmapIndex); // @ F0492_CACHE_GetDerivedBitmap



};

}

#endif
