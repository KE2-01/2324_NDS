/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

/* Fondo desberdinak erakutsi nahi izango baditugu, hemen fondo bakoitzaren burukoa (.h fitxategia) gehitu behar da. Buruko horiek
automatikoki sortzen dira, konpilatzerako garaian, baina horretarako gogoratu behar da */

#include "definizioak.h"
#include "fondoak.h"
#include "grafikoak.h"
#include "FondoBat.h"
#include "FondoBi.h"
#include "Atea.h"
#include "AteaIrekita.h"

/* Irudiak memorian kopiatzeko DMA kanala aukeratu (3.a) */
static const int DMA_CHANNEL = 3;

/* Pantailaratu nahi den grafiko bakoitzerako horrelako prozedura bat idatzi behar da */

void erakutsiFondoBat() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoBatBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     FondoBatBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}

void erakutsiFondoBi() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     FondoBiBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     FondoBiBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}

void erakutsiAtea() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     AteaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     AteaBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}

void erakutsiAteaIrekita() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     AteaIrekitaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     AteaIrekitaBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}

void changeBG(int BG) {
    switch (BG) {
        case BG_STARTUP:
            erakutsiFondoBat();
            break;
        case BG_INGAME:
            erakutsiFondoBi();
            break;
        case BG_OVER:
            erakutsiAtea();
            break;
        case BG_STOP:
            erakutsiAteaIrekita();
            break;
    }
}