/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"

int EGOERA; // Automata zein egoeratan dagoen adierazteko erabilia
int seg3;   // Hiru segundo pasatzen ote diren ikusten joateko

void ZE_Keyboard() {
(|START)	switch (EGOERA)
	{
	case STARTUP:
		/* code */
		break;

	case INGAME:
		// Tekla bat sakatu dela detektatu
		if (detectKey()) {
			int key = pressedKey();

			if (key == A || key == UP) {
				//DinoVy=-5;
				jump();
			}
		}
		break;
		
	case OVER:
		break;
	
	default:
		break;
	}
}

void ZE_Timer0() {
	switch (EGOERA)
	{
	case STARTUP:
		/* code */
		break;
	
	case INGAME:
		checkJump();
		
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

		if (cactusX < -16) {
			cactusX = 256;
		}

		if (meteoriteY == 192) {
			EGOERA = OVER;
		}
		break;
	
	case OVER:
		/* code */
		break;

	case STOP:
		/* code */
		break;
		
	default:
		break;
	}
}

void setZE()
{
// HAU BETE
	irqSet(IRQ_KEYS, ZE_Keyboard);
	irqSet(IRQ_TIMER0, ZE_Timer0);
}

