#include <nds.h> // NDS development libraries
#include <stdio.h> // Standard C library for input and output functions
#include "definizioak.h" // Definitions
#include "periferikoak.h" // Peripheral functions
#include "backgrounds.h" // Background functions
#include "spriteak.h" // Sprite functions
#include "game.h" // Game functions

int STATE; // State of the game
int cactusX; // Horizontal position of the cactus
int meteoriteY; // Vertical position of the meteorite
int meteoriteX; // Horizontal position of the meteorite
extern int playerY; // Vertical position of the player
extern int playerVY; // Vertical speed of the player (jumping)
extern bool developerMode; // Developer mode

/**
 * Keyboard routine
 */
void ZE_Keyboard() {
	if (detectKey()) {
		int key = pressedKey();
		switch (STATE) {
			case STARTUP:
				if (key == A || key == START) {
					// Clear the top screen
					consoleDemoInit();
					// Set player position and speed
					playerY = 176;
					playerVY = 0;

					// Set cactus position
					cactusX = 300;

					// Set meteorite position
					meteoriteY = -50;
					meteoriteX = 250;

					// Set background and state to INGAME
					changeBG(BG_INGAME);
					STATE = INGAME;
				}
				break;
		
			case INGAME:
				if (cactusX > -50) {
					cactusX--;
				} else {
					cactusX = 300;
				}
				if (canJump() && (key == A || key == UP)) jump();
				if (key == DOWN) {
					cactusX = 300;
					changeBG(BG_OVER); // Set background to OVER
					STATE = OVER;
				}
				break;

			case OVER:
				switch (key) {
					case A:
						// Clear the top screen
						consoleDemoInit();

						// Reset player position and speed
						playerY = 176;
						playerVY = 0;

						// Reset cactus position
						cactusX = 300;

						// Reset meteorite position
						meteoriteY = -50;
						meteoriteX = 250;

						// Set background and state to INGAME
						changeBG(BG_INGAME);
						STATE = INGAME;
						break;
					default:
						break;
				}
				break;

			default:
				break;
		}
	}
}

/**
 * Timer routine
 */
void ZE_Timer0() {
	if (STATE == INGAME) {
		// Move player
		playerY += playerVY;
		playerVY++;

		// Prevent player from falling off the screen
		if (playerY >= 176) {
			playerY = 176;
		}

		// Reset cactus position if it goes off screen
		if (cactusX < -16) {
			cactusX = 300;
		} else cactusX -= 2;

		// Check for collision
		if (collisionCheck()) {
			// Collision detected
			// Reset cactus position and player speed
			// Stop the game, show the game over screen and set the state to OVER
			cactusX = 300;
			playerVY = 0;
			changeBG(BG_OVER);
			STATE = OVER;
		} else {
			// Hide all sprites
			hidePlayer(0,10,playerY);
			hideCactus(1,0,176);
			hideMeteorite(2,meteoriteX,meteoriteY);

			// Check if meteorite goes off screen
			if (meteoriteY > 192) {
				// Reset meteorite position
				meteoriteY = -50;
				meteoriteX = 300;
				// Reset player speed
				playerVY = 0;
				// Reset cactus position
				cactusX = 300;
				// Hide all sprites
				hidePlayer(0, 10, playerY);
				hideCactus(1, 0, 176);
				hideMeteorite(2,meteoriteX,meteoriteY);
				// End of the game
				changeBG(BG_OVER);
				STATE = OVER;
			} else {
				// Move meteorite
				meteoriteY += 2;
				meteoriteX--;
				// Show all sprites
				showPlayer(0,10,playerY);
				showCactus(1,cactusX, 176);
				showMeteorite(2,meteoriteX,meteoriteY);
			}
		}
	}
}

/**
 * Set routines
 */
void setZE() {
	// Set keyboard and timer routines
	irqSet(IRQ_KEYS, ZE_Keyboard);
	irqSet(IRQ_TIMER0, ZE_Timer0);
}

