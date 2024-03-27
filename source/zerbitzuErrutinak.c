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

void ZE_Keyboard()
{
if (EGOERA == CLOSED)
{	
	if (pressedKey() == A)
	{
		EGOERA = OPEN;
		iprintf("\x1b[13;5HPasa diren segunduak=%d", seg3);
		erakutsiAteaIrekita();
		seg3 = 0;
		ErakutsiErronboa(1, 5, 5);
		ErakutsiErronboHandia(2, 100, 100);
	}
}
}

void ZE_Timer0()
{
	static int tik=0;
	static int seg=0;
	

if (EGOERA != WAITING)
{
	tik++; 
	if (tik == 5)
	{
		seg++;
		iprintf("\x1b[13;5HPasa diren segunduak=%d", seg);
		tik=0;
		if (EGOERA == OPEN)
		{
			seg3++;
			if (seg3 == 3)
			{
				erakutsiAtea();
				seg3 = 0;
				EGOERA = CLOSED;
				EzabatuErronboa(1, 5, 5);
				EzabatuErronboHandia(2, 100, 100);
			}
		}
				
	}
}
	
}

void setZE()
{
// HAU BETE
	irqSet(IRQ_KEYS, ZE_Keyboard);
	irqSet(IRQ_TIMER0, ZE_Timer0);
}

