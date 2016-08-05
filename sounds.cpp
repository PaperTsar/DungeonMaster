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

#include "audio/audiostream.h"
#include "audio/decoders/raw.h"

#include "dm.h"
#include "gfx.h"
#include <audio/mixer.h>
#include "timeline.h"
#include "dungeonman.h"


namespace DM {



Sound g60_sounds[k34_D13_soundCount] = {
	Sound(533, 112,  11, 3, 6), /* k00_soundMETALLIC_THUD 0 */
	Sound(534, 112,  15, 0, 3), /* k01_soundSWITCH 1 */
	Sound(535, 112,  72, 3, 6), /* k02_soundDOOR_RATTLE 2 */
	Sound(550, 112,  60, 3, 5), /* k03_soundATTACK_PAIN_RAT_HELLHOUND_RED_DRAGON 3 */
	Sound(536, 112,  10, 3, 6), /* k04_soundWOODEN_THUD_ATTACK_TROLIN_ANTMAN_STONE_GOLEM 4 */
	Sound(537, 112,  99, 3, 7), /* k05_soundSTRONG_EXPLOSION 5 */
	Sound(539, 112, 110, 3, 6), /* k06_soundSCREAM 6 */
	Sound(551, 112,  55, 3, 5), /* k07_soundATTACK_MUMMY_GHOST_RIVE 7 */
	Sound(540, 112,   2, 3, 6), /* k08_soundSWALLOW 8 */
	Sound(541, 112,  80, 3, 6), /* k09_soundCHAMPION_0_DAMAGED 9 */
	Sound(542, 112,  82, 3, 6), /* k10_soundCHAMPION_1_DAMAGED 10 */
	Sound(543, 112,  84, 3, 6), /* k11_soundCHAMPION_2_DAMAGED 11 */
	Sound(544, 112,  86, 3, 6), /* k12_soundCHAMPION_3_DAMAGED 12 */
	Sound(545, 112,  95, 3, 6), /* k13_soundSPELL 13 */
	Sound(552, 112,  57, 3, 5), /* k14_soundATTACK_SCREAMER_OITU 14 */
	Sound(553, 112,  52, 3, 5), /* k15_soundATTACK_GIANT_SCORPION_SCORPION 15 */
	Sound(546, 112,  40, 2, 4), /* k16_soundCOMBAT_ATTACK_SKELETON_ANIMATED_ARMOUR_DETH_KNIGHT 16 */
	Sound(547, 112,  70, 1, 4), /* k17_soundBUZZ 17 */
	Sound(549, 138,  75, 3, 6), /* k18_soundPARTY_DAMAGED 18 */
	Sound(554, 112,  50, 3, 5), /* k19_soundATTACK_MAGENTA_WORM_WORM 19 */
	Sound(537, 112,  98, 0, 4), /* k20_soundWEAK_EXPLOSION 20 */
	Sound(555, 112,  96, 2, 4), /* k21_soundATTACK_GIGGLER 21 */
	Sound(563, 138,  24, 0, 4), /* k22_soundMOVE_ANIMATED_ARMOUR_DETH_KNIGHT 22 Atari ST: not present */
	Sound(564, 138,  21, 0, 4), /* k23_soundMOVE_COUATL_GIANT_WASP_MUNCHER 23 Atari ST: not present */
	Sound(565, 138,  23, 0, 4), /* k24_soundMOVE_MUMMY_TROLIN_ANTMAN_STONE_GOLEM_GIGGLER_VEXIRK_DEMON 24 Atari ST: not present */
	Sound(566, 138, 105, 0, 4), /* k25_soundBLOW_HORN 25 Atari ST: not present */
	Sound(567, 138,  27, 0, 4), /* k26_soundMOVE_SCREAMER_ROCK_ROCKPILE_MAGENTA_WORM_WORM_PAIN_RAT_HELLHOUND_RUSTER_GIANT_SCORPION_SCORPION_OITU 26 Atari ST: not present */
	Sound(568, 138,  28, 0, 4), /* k27_soundMOVE_SWAMP_SLIME_SLIME_DEVIL_WATER_ELEMENTAL 27 Atari ST: not present */
	Sound(569, 138, 106, 0, 4), /* k28_soundWAR_CRY 28 Atari ST: not present */
	Sound(570, 138,  56, 0, 4), /* k29_soundATTACK_ROCK_ROCKPILE 29 Atari ST: not present */
	Sound(571, 138,  58, 0, 4), /* k30_soundATTACK_WATER_ELEMENTAL 30 Atari ST: not present */
	Sound(572, 112,  53, 0, 4), /* k31_soundATTACK_COUATL 31 Atari ST: not present */
	Sound(573, 138,  29, 0, 4), /* k32_soundMOVE_RED_DRAGON 32 Atari ST: not present */
	Sound(574, 150,  22, 0, 4)}; /* k33_soundMOVE_SKELETON 33 Atari ST: not present */

void DMEngine::f503_loadSounds() {
	for (uint16 soundIndex = 0; soundIndex < k34_D13_soundCount; ++soundIndex) {
		SoundData *soundData = _gK24_soundData + soundIndex;

		uint16 graphicIndex = g60_sounds[soundIndex]._graphicIndex;
		soundData->_byteCount = _displayMan->getCompressedDataSize(graphicIndex) - 2; // the header is 2 bytes long
		soundData->_firstSample = new byte[soundData->_byteCount];

		Common::MemoryReadStream stream = _displayMan->getCompressedData(graphicIndex);
		soundData->_sampleCount = stream.readUint16BE();
		stream.read(soundData->_firstSample, soundData->_byteCount);
	}
}

void DMEngine::f060_SOUND_Play(uint16 soundIndex, uint16 period, uint8 leftVolume, uint8 rightVolume) {
	SoundData *sound = &_gK24_soundData[soundIndex];
	Audio::AudioStream *stream = Audio::makeRawStream(sound->_firstSample, sound->_byteCount, (72800 / period) * 8, 0, DisposeAfterUse::NO);

	signed char balance = ((int16)rightVolume - (int16)leftVolume) / 2;

	Audio::SoundHandle handle;
	_mixer->playStream(Audio::Mixer::kSFXSoundType, &handle, stream, -1, 127, balance);
}

void DMEngine::f65_playPendingSound() {
	while (!_pendingSounds.empty()) {
		PendingSound pendingSound = _pendingSounds.pop();
		f060_SOUND_Play(pendingSound._soundIndex, g60_sounds[pendingSound._soundIndex]._period, pendingSound._leftVolume, pendingSound._rightVolume);
	}
}

bool DMEngine::f505_soundGetVolume(int16 mapX, int16 mapY, uint8* leftVolume, uint8* rightVolume) {
	static byte K0030_aauc_DistanceToSoundVolume[25][25] = {
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4,  5,  5,  5,  5,  5,  5,  5, 5, 4, 4, 4, 4, 4},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 5,  6,  6,  6,  6,  5,  5,  5, 5, 5, 5, 4, 4, 4},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 5,  6,  6,  6,  6,  6,  6,  5, 5, 5, 5, 5, 4, 4},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 5,  7,  7,  7,  7,  6,  6,  6, 6, 5, 5, 5, 5, 4},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 5,  8,  8,  7,  7,  7,  7,  6, 6, 6, 5, 5, 5, 4},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 4, 6,  9,  9,  8,  8,  8,  7,  7, 6, 6, 6, 5, 5, 5},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 6, 10, 10, 10,  9,  8,  8,  7, 7, 6, 6, 5, 5, 5},
		{1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 7, 12, 12, 11, 10,  9,  9,  8, 7, 7, 6, 6, 5, 5},
		{1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 4, 7, 15, 14, 13, 12, 11,  9,  8, 8, 7, 6, 6, 5, 5},
		{1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 4, 8, 20, 19, 16, 14, 12, 10,  9, 8, 7, 7, 6, 6, 5},
		{1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 4, 8, 29, 26, 21, 16, 13, 11, 10, 8, 7, 7, 6, 6, 5},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 8, 58, 41, 26, 19, 14, 12, 10, 9, 8, 7, 6, 6, 5},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 6, 64, 58, 29, 20, 15, 12, 10, 9, 8, 7, 6, 6, 5},
		{0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 6, 41, 29, 19, 13, 10,  8,  7, 6, 6, 5, 5, 4, 4},
		{0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 6, 21, 19, 15, 12, 10,  8,  7, 6, 5, 5, 4, 4, 4},
		{0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 6, 14, 13, 12, 10,  9,  7,  7, 6, 5, 5, 4, 4, 4},
		{0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 5, 11, 10, 10,  9,  8,  7,  6, 6, 5, 5, 4, 4, 4},
		{0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 5,  9,  8,  8,  7,  7,  6,  6, 5, 5, 4, 4, 4, 4},
		{0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 5,  7,  7,  7,  7,  6,  6,  5, 5, 5, 4, 4, 4, 4},
		{0, 1, 1, 1, 1, 1, 1, 2, 2, 1, 3, 4,  6,  6,  6,  6,  6,  5,  5, 5, 4, 4, 4, 4, 3},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 4,  6,  6,  5,  5,  5,  5,  5, 4, 4, 4, 4, 3, 3},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 4,  5,  5,  5,  5,  5,  4,  4, 4, 4, 4, 3, 3, 3},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3,  5,  5,  4,  4,  4,  4,  4, 4, 4, 3, 3, 3, 3},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3,  4,  4,  4,  4,  4,  4,  4, 4, 3, 3, 3, 3, 3},
		{1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3,  4,  4,  4,  4,  4,  4,  4, 3, 3, 3, 3, 3, 3}};

	int16 L1678_i_RightVolumeColumnIndex = 0;
	int16 L1679_i_LineIndex = 0;
	int16 L1680_i_LeftVolumeColumnIndex = 0;


	switch (_dungeonMan->_g308_partyDir) {
	case kDirNorth:
		L1678_i_RightVolumeColumnIndex = mapX - _dungeonMan->_g306_partyMapX;
		L1679_i_LineIndex = mapY - _dungeonMan->_g307_partyMapY;
		break;
	case kDirEast:
		L1678_i_RightVolumeColumnIndex = mapY - _dungeonMan->_g307_partyMapY;
		L1679_i_LineIndex = -(mapX - _dungeonMan->_g306_partyMapX);
		break;
	case kDirSouth:
		L1678_i_RightVolumeColumnIndex = -(mapX - _dungeonMan->_g306_partyMapX);
		L1679_i_LineIndex = -(mapY - _dungeonMan->_g307_partyMapY);
		break;
	case kDirWest:
		L1678_i_RightVolumeColumnIndex = -(mapY - _dungeonMan->_g307_partyMapY);
		L1679_i_LineIndex = mapX - _dungeonMan->_g306_partyMapX;
		break;
	}
	if ((L1678_i_RightVolumeColumnIndex < -12) || (L1678_i_RightVolumeColumnIndex > 12)) { /* Sound is not audible if source is more than 12 squares away from the party */
		return false;
	}
	if ((L1679_i_LineIndex < -12) || (L1679_i_LineIndex > 12)) { /* Sound is not audible if source is more than 12 squares away from the party */
		return false;
	}
	L1680_i_LeftVolumeColumnIndex = -L1678_i_RightVolumeColumnIndex + 12;
	L1678_i_RightVolumeColumnIndex += 12;
	L1679_i_LineIndex += 12;
	*rightVolume = K0030_aauc_DistanceToSoundVolume[L1679_i_LineIndex][L1678_i_RightVolumeColumnIndex];
	*leftVolume = K0030_aauc_DistanceToSoundVolume[L1679_i_LineIndex][L1680_i_LeftVolumeColumnIndex];
	return true;
}

void DMEngine::f064_SOUND_RequestPlay_CPSD(uint16 soundIndex, int16 mapX, int16 mapY, uint16 mode) {
	Sound* sound;
	uint8 leftVolume, rightVolume;

	if (mode && (_dungeonMan->_g272_currMapIndex != _dungeonMan->_g309_partyMapIndex))
		return;

	sound = &g60_sounds[soundIndex];
	if (mode > k1_soundModePlayIfPrioritized) { /* Add an event in the timeline to play the sound (mode - 1) ticks later */
		TimelineEvent event;
		M33_setMapAndTime(event._mapTime, _dungeonMan->_g272_currMapIndex, _g313_gameTime + mode - 1);
		event._type = k20_TMEventTypePlaySound;
		event._priority = sound->_priority;
		event._C._soundIndex = soundIndex;
		event._B._location._mapX = mapX;
		event._B._location._mapY = mapY;
		_timeline->f238_addEventGetEventIndex(&event);
		return;
	}

	if (!f505_soundGetVolume(mapX, mapY, &leftVolume, &rightVolume)) {
		return;
	}
	if (!mode) { /* Play the sound immediately */
		f060_SOUND_Play(soundIndex, sound->_period, leftVolume, rightVolume);
		return;
	}
	_pendingSounds.push(PendingSound(leftVolume, rightVolume, soundIndex));
}

}