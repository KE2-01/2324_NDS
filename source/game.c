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

void game() {
	// KB Config
	int KB_conf = 0b0100001111111111; // No keys with interrupts, all keys with direct polling
	configKeyboard(KB_conf);

	// Timer0 config (5 stops per second)
	int Latch = 58982; //65536 - ((1/5) * (33554432 / 1024)) = 65536 - (1/5) * 32768 = 65536 - 6554 = 58982
	int Timer0_conf = 0xC3; // Timer enabled, 1024 prescaler, clock overflow interrupt enabled (0b11000011)
	configTimer(Latch, Timer0_conf);

	// Activate interrupts
	allowKBStops();
	startTimer0();
	allowTimerStops();

	// Set ZE
	setZE();
	//Set variables
	playerY = 178;

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
	iprintf("\x1b[16;5HPlayer Y: %d", playerY);
}

/*bool dinoKaktusTalka(){
	int dinoX
	int dinoW = 16;
	int dinoH;
	int kaktusY;
	int kaktusW = 16;
	int kaktusH;
	if (
    dinoX   < kaktusX + kaktusW &&
    dinoX   + dinoW   > kaktusX &&
    playerY < kaktusY + kaktusH &&
    playerY + dinoH   > kaktusY
  ) {
    // Collision detected!
	return true;
  } else {
    // No collision
	return false;
  }
}*/
/*void ingameToOver(){
	cleanScreen();
	hidePlayer();
	changeBG(BG_OVER);
	//showScore();
}*/