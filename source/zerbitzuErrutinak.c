/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "game.h"

int STATE; // Automata zein egoeratan dagoen adierazteko erabilia
int seg3;   // Hiru segundo pasatzen ote diren ikusten joateko
int cactusX; // Kaktusen posizioa
int meteoriteY; // Meteoritoen posizioa Y ardatzarekiko
int meteoriteX; //Meteoritoen posizioa X ardatzarekiko
extern int playerY; // Jokalaria Y ardatzean
extern int playerVY; // Jokalariaren abiadura Y ardatzean

void ZE_Keyboard() {
	if (detectKey()) {
		int key = pressedKey();
		switch (STATE) {
		case STARTUP:
			if (key == A || key == START) {
				changeBG(BG_INGAME);
				cactusX = 300;
				meteoriteY = -50;
				STATE = INGAME;
			}
			break;
		
		case INGAME:
			if (cactusX > -50) {
				cactusX--;
			}else{
				cactusX = 300;
			}
			if (canJump() && (key == A || key == UP)) jump();
			if (key == DOWN) {
				cactusX=300;
				changeBG(BG_OVER);
				STATE = OVER;
			}
			break;

		case OVER:
			switch (key) {
			case A:
				changeBG(BG_INGAME);
				STATE = INGAME;
				break;
			//Inkesta bidez egiten da;
			/* case B:
				changeBG(BG_STOP);
				STATE = STOP;
				break;
			 */
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

void ZE_Timer0() {
	if (STATE == INGAME) {
		playerY+=playerVY;
		playerVY++;
		if (playerY >= 176) {
			playerY = 176;
		}
		if (cactusX <-16) {
			cactusX = 300;
		} else cactusX-=2;
		if (dinoKaktusTalka()) {
			cactusX=300;
			playerVY = 0;
			changeBG(BG_OVER);
			STATE = OVER;
		} else {
			meteoriteY += 2;
			meteoriteX --;
		hidePlayer(0,0,playerY);
		showPlayer(0,0,playerY);
		hideCactus(1,0,176);
		showCactus(1,cactusX, 176);
			
		}
	}
	/* switch (STATE) {
	case STARTUP:
		break;
	
	case INGAME:
		////////
		//DINO//
	  	////////

		//////////
		//KAKTUS//
		//////////
		cactusX--;
		//////////////
		//METEORITOA//
		//////////////
		meteoriteY++;
		if(dinoKaktusTalka()){
			//ingameToOver();
			STATE = OVER;
		}

		if (meteoriteY > 192-16) {
			//ingameToOver();
			STATE = OVER;
		}
		if (playerY < 176) {
			playerY++;
		}
		break;
	
	case OVER:
		break;

	case STOP:
		break;
		
	default:
		break;
	} */
}

void setZE()
{
// HAU BETE
	irqSet(IRQ_KEYS, ZE_Keyboard);
	irqSet(IRQ_TIMER0, ZE_Timer0);
}

