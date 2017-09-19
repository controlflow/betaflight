/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Created by jflyper */

#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "platform.h"
#include "build/debug.h"
#include "common/utils.h"

#if defined(VTX_COMMON)

const uint16_t vtx58frequencyTable[6][8] =
{
    { 5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725 }, // Boscam A
    { 5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866 }, // Boscam B
    { 5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945 }, // Boscam E
    { 5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880 }, // FatShark
    { 5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917 }, // RaceBand
    { 5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621 }, // LowRace
};

const char * const vtx58BandNames[] = {
    "--------",
    "BOSCAM A",
    "BOSCAM B",
    "BOSCAM E",
    "FATSHARK",
    "RACEBAND",
    "LOW RACE",
};

const char vtx58BandLetter[] = "-ABEFRL";

const char * const vtx58ChannelNames[] = {
    "-", "1", "2", "3", "4", "5", "6", "7", "8",
};

bool vtx58_Freq2Bandchan(uint16_t freq, uint8_t *pBand, uint8_t *pChannel)
{
    // Use reverse lookup order so that 5880MHz get RaceBand 7 instead of FatShark 8.
    for (int8_t band = ARRAYLEN(vtx58frequencyTable) - 1 ; band >= 0 ; band--) {
        for (uint8_t channel = 0 ; channel < 8 ; channel++) {
            if (vtx58frequencyTable[band][channel] == freq) {
                *pBand = band + 1;
                *pChannel = channel + 1;
                return true;
            }
        }
    }

    *pBand = 0;
    *pChannel = 0;

    return false;
}

#endif
