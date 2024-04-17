/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

// Guk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"

int denb; // denbora neurtzen joateko; baloratu ea beharrezkoa den
int playerY; // Jokalaria Y ardatzean
extern int cactusX; // Kaktusen posizioa

void game() {
	// KB Config
	int KB_conf = 0b0100001111111111; // No keys with interrupts, all keys with direct polling
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
	//Set variables
	playerY = 176;

	// Set background
	changeBG(BG_STARTUP);
	STATE = STARTUP;

	while(STATE != STOP) {
		/*************************************1.JARDUERAN**************************************/
		// ZAI egoeran dagoela, hemen teklatuaren inkesta egin, sakatu den tekla pantailaratu, eta START
		// sakatzean egoera aldatu
		iprintf("\x1b[2;5HDino Run");
		iprintf("\x1b[4;5Hv0.1");
		iprintf("\x1b[6;5HPress START or A to play");
		iprintf("\x1b[8;5HSTATE: %d", STATE);
		iprintf("\x1b[10;5HPlayer can jump: %d", canJump());
		iprintf("\x1b[12;5HPlayer Y: %d", playerY);
		iprintf("\x1b[14;5HcactusX: %d", cactusX);
			
	}

	denyKBStops();
	denyTimerStops();
	stopTimer0();
}

bool canJump() {
	return playerY == 176;//192-16
}

void jump() {
	playerY = 150;
}

/* bool dinoKaktusTalka(){
	int dinoX = 0;
	int dinoW = 16;
	int dinoH = 16;
	int cactusY = 176;
	return (
	dinoX   < cactusX + 16 &&
    dinoX   + dinoW   > cactusX &&
    playerY < cactusY + 16 &&
    playerY + dinoH   > cactusY
    )
} */

//////
//Trash//
/*void ingameToOver(){
	cleanScreen();
	hidePlayer();
	changeBG(BG_OVER);
	//showScore();
}*/