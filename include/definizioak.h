// 2023-2024 ikasturtea

/*-------------------------------------
definizioak.h
-------------------------------------*/

#include <nds.h>		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

#define IME		(*(vuint32*)0x04000208) // Interrupt Master Enable -- Eten guztiak baimendu-galarazi
#define IE		(*(vuint32*)0x04000210) // Interrupt Enable -- Etenak banaka baimendu-galarazi
#define IF		(*(vuint32*)0x04000214) // Interrupt Flag -- Eten eskaeren erregistroa

// Etenak tratatzeko funtzioak
#define allowStops() IME=1 // Eten guztiak baimendu
#define denyStops() IME=0 // Eten guztiak galarazi

// Teklatuaren erregistroak
#define TEKLAK_DAT	(*(vu16*)0x4000130) // Teklatuaren datu-erregistroa
#define TEKLAK_KNT	(*(vu16*)0x4000132) // Teklatuaren kontrol-erregistroa

// Tenporizadorearen (Timer0) erregistroak
#define DENB0_KNT   (*(vuint16*)0x04000102) // Kontrol-erregistroa
#define DENB0_DAT    (*(vuint16*)0x04000100) // Datu-erregistroa



// Ukimen-pantailaren erregistroak
extern touchPosition PANT_DAT;

// Teklei izena eman diegu zenbakiak nahasgarriak izan daitezkeelako

#define A 0 
#define B 1
#define SELECT 2 
#define START 3
#define RIGHT 4 
#define LEFT 5
#define UP 6 
#define DOWN 7
#define R 8 
#define L 9

#define STARTUP 0
#define INGAME 1
#define OVER 2
#define STOP 3
extern int STATE;

#define BG_STARTUP 0
#define BG_INGAME 1
#define BG_OVER 2
#define BG_STOP 3