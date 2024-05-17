#include <nds.h> // NDS development libraries
#include <stdio.h> // Standard C library for input and output functions
#include <stdlib.h> // Standard C library for memory allocation and conversion functions
#include <unistd.h> // Library for compatibility between operating systems

#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "backgrounds.h"

int playerY = 0; // Player's Y position
int playerVY = 0; // Player's vertical speed (jumping)
extern int cactusX; // Cactus' X position
extern int meteoriteY; // Meteorite's Y position
extern int meteoriteX; // Meteorite's X position
touchPosition PANT_DAT; // Touch screen position data (global variable)
bool developerMode = false; // Developer mode

void game() {
	// Keyboard config
	int KB_conf = 0b0100001111111101; // No keys with interrupts, all keys with direct polling
	configKeyboard(KB_conf);

	// Timer0 config (20 stops per second)
	int Latch = 63998; //65536 - ((1/20) * (33554432 / 1024)) = 65536 - (1/20) * 32768 = 65536 - 1538 = 63998
	int Timer0_conf = 0xC3; // Timer enabled, 1024 prescaler, clock overflow interrupt enabled (0b11000011)
	configTimer(Latch, Timer0_conf);

	// Activate interrupts
	allowKBStops();
	startTimer0();
	allowTimerStops();

	// Set ZE
	setZE();
	// Set initial values for the player
	playerY = 176;
	playerVY = 0;

	// Set background and state
	changeBG(BG_STARTUP);
	STATE = STARTUP;

	// Main loop
	// The game will be running until the state is STOP
	while(STATE != STOP) {
		// If the developer mode is enabled, show the developer information
		// Otherwise, just show the game title and instructions if needed
		if (developerMode) {
			iprintf("\x1b[2;5HDino Run: EVOLUTION");
			iprintf("\x1b[4;5Hv0.1");
			if (STATE == STARTUP) iprintf("\x1b[6;5HPress START or A to play");
			iprintf("\x1b[8;5HSTATE: %d", STATE);
			iprintf("\x1b[10;5HPlayer can jump: %d", canJump());
			iprintf("\x1b[12;5HPlayer Y: %d", playerY);
			iprintf("\x1b[14;5HcactusX: %d", cactusX);
			iprintf("\x1b[16;5HplayerVY: %d", playerVY);
			iprintf("\x1b[18;5HmeteoriteY: %d", meteoriteY);
			iprintf("\x1b[20;5HmeteoriteX: %d", meteoriteX);
			iprintf("\x1b[22;5HDeveloper mode enabled!");
		} else {
			iprintf("\x1b[6;5HDino Run: EVOLUTION");
			iprintf("\x1b[8;5Hv0.1");
			if (STATE == STARTUP) iprintf("\x1b[16;5HPress START or A to play");
			else if (STATE == OVER) iprintf("\x1b[16;5HPress A to play again");
		}
		// Check the state of the game
		if(STATE == STARTUP || STATE == OVER) {
			if (detectKey()) {
				// If SELECT is pressed, toggle developer mode
				if (pressedKey() == SELECT && canJump()) {
					// Toggle developer mode
					developerMode = !developerMode;
					// Decrease the player's Y position by 1 to avoid toggling developer mode multiple times
					playerY--;
					// Clear the top screen to avoid overlapping text
					consoleDemoInit();
				}
				// If B is pressed, stop the game
				if (pressedKey() == B) {
					// Clear the top screen
					consoleDemoInit();
					
					// Change the background to STOP
					changeBG(BG_STOP);
					// Change the state to STOP
					STATE = STOP;
				}
			}
		} else if (STATE == INGAME) {
			// Handle touch screen
			touchRead(&PANT_DAT);
			// If the player is touching the meteorite, reset the meteorite position
			// Added a 8 pixel margin to make it easier to touch the meteorite
			// Otherwise, the sprite is too small and it's hard to touch it
			if (PANT_DAT.px > meteoriteX-8 && PANT_DAT.px < meteoriteX + 24 && PANT_DAT.py > meteoriteY-8 && PANT_DAT.py < meteoriteY + 24) {
				meteoriteY = -50;
				meteoriteX = 250;
			}
		}
	}

	// Stop interrupts
	denyKBStops();
	denyTimerStops();
	// Stop timer
	stopTimer0();
}

/**
 * Checks if the player can jump
 * @return true if the player can jump, false otherwise
 */
bool canJump() {
	return playerY == 176; // 192-16 (screen height - player height)
}

/**
 * Makes the player jump
 */
void jump() {
	playerVY = -7;
}

/**
 * Checks if the player is colliding with the cactus
 * @return true if the player is colliding with the cactus, false otherwise
 */
bool collisionCheck() {
	int dinoX = 10;
	int dinoW = 16;
	int dinoH = 16;
	int cactusY = 176;
	return (
	dinoX   < cactusX + 16 &&
    dinoX   + dinoW   > cactusX &&
    playerY < cactusY + 16 &&
    playerY + dinoH   > cactusY
    );
}