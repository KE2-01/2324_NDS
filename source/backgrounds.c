/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> // NDS development libraries
#include <stdio.h> // Standard C library for input and output functions
#include <stdlib.h> // Standard C library for memory allocation and conversion functions
#include <unistd.h> // Library for compatibility between operating systems

#include "definizioak.h"
#include "backgrounds.h"
#include "grafikoak.h"
#include "mainBG.h"
#include "ingameBG.h"
#include "overBG.h"
#include "stopBG.h"

// DMA channel for copying data to VRAM
static const int DMA_CHANNEL = 3;

/**
 * Show the main background
 */
void showMain() {	
	dmaCopyHalfWords(DMA_CHANNEL,
                     mainBGBitmap, // Bitmap of the main background
                     (uint16 *)BG_BMP_RAM(0), // Address of the main background
                     mainBGBitmapLen); // Length (in bytes) of the main background
}

/**
 * Show the ingame background
 */
void showIngame() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     ingameBGBitmap, // Bitmap of the ingame background
                     (uint16 *)BG_BMP_RAM(0), // Address of the ingame background
                     ingameBGBitmapLen); // Length (in bytes) of the ingame background
}

/**
 * Show the game over background
 */
void showOver() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     overBGBitmap, // Bitmap of the game over background
                     (uint16 *)BG_BMP_RAM(0), // Address of the game over background
                     overBGBitmapLen); // Length (in bytes) of the game over background
}

/**
 * Show the stop background
 */
void showStop() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     stopBGBitmap, // Bitmap of the stop background
                     (uint16 *)BG_BMP_RAM(0), // Address of the stop background
                     stopBGBitmapLen); // Length (in bytes) of the stop background
}

/**
 * Change the background
 * @param BG Background to show
 */
void changeBG(int BG) {
    switch (BG) {
        case BG_STARTUP:
            showMain(); // Show the main background
            break;
        case BG_INGAME:
            showIngame(); // Show the ingame background
            break;
        case BG_OVER:
            showOver(); // Show the game over background
            break;
        case BG_STOP:
            showStop(); // Show the stop background
            break;
        default:
            break; // Do nothing if the background is not recognized
    }
}