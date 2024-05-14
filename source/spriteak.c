/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> // NDS-rako garatuta dagoen liburutegia
#include <stdio.h>// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia
#include "spriteak.h"
#include "definizioak.h"

u16* gfxerronbo;
u16* gfxerronboHandia;
u16* gfxdino;
u16* gfxcactus;
u16* gfxmeteorite;


/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
gfxerronbo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
gfxerronboHandia=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
gfxdino = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
gfxcactus = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
gfxmeteorite = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void paletaNagusiaEzarri() {

	SPRITE_PALETTE[	1	] = RGB15(	31	,	0	,	0	); // 	GORRI	: RGB24={	FF	,	00	,	00	}
	SPRITE_PALETTE[	2	] = RGB15(	31	,	31	,	0	); // 	HORI	: RGB24={	FF	,	FF	,	00	}
	SPRITE_PALETTE[	3	] = RGB15(	31	,	31	,	31	); // 	ZURI	: RGB24={	FF	,	FF	,	FF	}
	SPRITE_PALETTE[	4	] = RGB15(	0	,	31	,	0	); // 	BERDE	: RGB24={	00	,	FF	,	00	}
	SPRITE_PALETTE[	5	] = RGB15(	0	,	0	,	31	); // 	URDIN	: RGB24={	00	,	00	,	FF	}
	SPRITE_PALETTE[	6	] = RGB15(	0	,	0	,	0	); // 	BELTZ	: RGB24={	00	,	00	,	00	}
	SPRITE_PALETTE[	7	] = RGB15(	0	,	31	,	31	); // 	ZIAN	: RGB24={	00	,	FF	,	FF	}
	SPRITE_PALETTE[	8	] = RGB15(	31	,	0	,	31	); // 	MAGENTA	: RGB24={	FF	,	00	,	FF	}
	SPRITE_PALETTE[	9	] = RGB15(	16	,	16	,	16	); // 	GRIS	: RGB24={	80	,	80	,	80	}
	SPRITE_PALETTE[	10	] = RGB15(	25	,	25	,	25	); // 	GRIS ARGI	: RGB24={	D0	,	D0	,	D0	}
	SPRITE_PALETTE[	11	] = RGB15(	8	,	8	,	8	); // 	GRIS ILUN	: RGB24={	40	,	40	,	40	}
	SPRITE_PALETTE[	12	] = RGB15(	31	,	19	,	0	); // 	LARANJA	: RGB24={	FF	,	99	,	00	}
	SPRITE_PALETTE[	13	] = RGB15(	19	,	0	,	4	); // 	GRANATE	: RGB24={	99	,	00	,	21	}
	SPRITE_PALETTE[	14	] = RGB15(	25	,	0	,	0	); // 	MARROI	: RGB24={	66	,	00	,	00	}
	SPRITE_PALETTE[	15	] = RGB15(	16	,	0	,	16	); // 	MORE	: RGB24={	80	,	00	,	80	}
	SPRITE_PALETTE[	16	] = RGB15(	25	,	19	,	31	); // 	LILA	: RGB24={	CC	,	99	,	FF	}
	SPRITE_PALETTE[	17	] = RGB15(	31	,	19	,	25	); // 	ARROSA	: RGB24={	FF	,	99	,	CC	}
	SPRITE_PALETTE[	18	] = RGB15(	23	,	21	,	21	); // 	URDIN ARGI	: RGB24={	BB	,	FF	,	FF	}
	SPRITE_PALETTE[	19	] = RGB15(	0	,	0	,	16	); // 	ITSAS URDIN	: RGB24={	00	,	00	,	80	}
	SPRITE_PALETTE[	20	] = RGB15(	0	,	16	,	16	); // 	BERDE URDINXKA	: RGB24={	00	,	80	,	80	}
	SPRITE_PALETTE[	21	] = RGB15(	0	,	12	,	0	); // 	BERDE ILUN	: RGB24={	00	,	66	,	00	}
	SPRITE_PALETTE[	22	] = RGB15(	16	,	16	,	0	); // 	OLIBA-BERDE	: RGB24={	80	,	80	,	00	}
	SPRITE_PALETTE[	23	] = RGB15(	19	,	31	,	19	); // 	VERDE ARGI	: RGB24={	99	,	FF	,	99	}
	SPRITE_PALETTE[	24	] = RGB15(	31	,	31	,	19	); // 	HORI ARGI	: RGB24={	FF	,	FF	,	99	}
}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko eskuineko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 erronbo[256] = 
{
0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,//0,0,0,0,0,0,2,2, 2,2,0,0,0,0,0,0,
0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,2,//0,0,0,0,0,2,2,2, 2,2,2,0,0,0,0,0,
0,0,2,2,2,2,2,2,0,2,2,2,2,2,2,2,//0,0,0,0,2,2,2,2, 2,2,2,2,0,0,0,0,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,
 
2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,//0,0,2,2,2,2,2,2, 2,2,2,2,2,2,0,0,
2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,//0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,//2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,//1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,//0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,//0,0,1,1,1,1,1,1, 1,1,1,1,1,1,0,0,

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//0,0,0,1,1,1,1,1, 1,1,1,1,1,0,0,0,
1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,//0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,
1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,//0,0,0,0,0,1,1,1, 1,1,1,0,0,0,0,0,
1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,//0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,
};
u8 cactus[256] = 
{
0,0,0,0,0,0,0,21,0,0,0,0,0,0,21,4, 		// 0 0  0  0  0  0  0  21 21 0  0  0  0  0  0  0 
0,0,21,21,0,0,21,4,0,21,4,4,21,0,21,4, 	// 0 0  0  0  0  0  21 4  4  21 0  0  0  0  0  0 
0,21,4,4,21,0,21,4,0,21,4,4,21,0,21,4, 	// 0 0  21 21 0  0  21 4  4  21 0  0  0  0  0  0
0,21,4,4,4,21,21,4,0,0,21,4,4,4,4,4, 	// 0 21 4  4  21 0  21 4  4  21 0  0  0  0  0  0
21,0,0,0,0,0,0,0,4,21,0,0,0,0,0,0, 		// 0 21 4  4  21 0  21 4  4  21 0  0  0  0  0  0
4,21,0,0,0,0,0,0,4,21,0,0,0,0,0,0, 		// 0 21 4  4  21 0  21 4  4  21 0  0  21 21 0  0
4,21,0,0,0,0,0,0,4,21,0,0,21,21,0,0,	// 0 21 4  4  4  21 21 4  4  21 0  21 4  4  21 0
4,21,0,21,4,4,21,0,4,21,0,21,4,4,21,0, 	// 0 0  21 4  4  4  4  4  4  21 0  21 4  4  21 0
0,0,0,21,4,4,4,4,0,0,0,0,21,21,21,4, 	// 0 0  0  21 4  4  4  4  4  21 0  21 4  4  21 0
0,0,0,0,0,0,21,4,0,0,0,0,0,0,21,4, 		// 0 0  0  0  21 21 21 4  4  21 21 4  4  4  21 0
0,0,0,0,0,0,21,4,0,0,0,0,0,0,21,4, 		// 0 0  0  0  0  0  21 4  4  4  4  4  4  21 0  0 
0,0,0,0,0,0,21,4,0,0,0,0,0,0,21,4, 		// 0 0  0  0  0  0  21 4  4  4  4  4  21 0  0  0 
4,21,0,21,4,4,21,0,4,21,21,4,4,4,21,0,  // 0 0  0  0  0  0  21 4  4  21 21 21 0  0  0  0
4,4,4,4,4,21,0,0,4,4,4,4,21,0,0,0, 		// 0 0  0  0  0  0  21 4  4  21 0  0  0  0  0  0 
4,21,21,21,0,0,0,0,4,21,0,0,0,0,0,0, 	// 0 0  0  0  0  0  21 4  4  21 0  0  0  0  0  0 
4,21,0,0,0,0,0,0,4,21,0,0,0,0,0,0, 		// 0 0  0  0  0  0  21 4  4  21 0  0  0  0  0  0 

};
u8 dino[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	11	11	11	11	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	11	15	8	8	8	11	0	0
0	,	11	,	11	,	0	,	0	,	0	,	0	,	0	,	11	,	4	,	21	,	11	,	11	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	11	11	8	15	11	0	0
11	,	21	,	4	,	4	,	21	,	11	,	11	,	11	,	11	,	21	,	4	,	4	,	4	,	4	,	21	,	21	,	 // 	0	0	0	0	0	0	0	0	11	21	4	4	4	21	11	0
11	,	11	,	11	,	11	,	0	,	0	,	0	,	0	,	11	,	15	,	8	,	8	,	8	,	11	,	0	,	0	,	 // 	0	11	11	0	0	0	0	0	11	4	4	6	4	21	11	0
0	,	11	,	11	,	8	,	15	,	11	,	0	,	0	,	11	,	21	,	4	,	4	,	4	,	21	,	11	,	0	,	 // 	11	4	21	11	11	0	0	0	11	4	4	6	21	2	2	11
11	,	4	,	4	,	6	,	4	,	21	,	11	,	0	,	11	,	4	,	4	,	6	,	21	,	2	,	2	,	11	,	 // 	11	21	4	4	21	11	11	11	21	4	4	6	21	11	11	0
21	,	4	,	4	,	6	,	21	,	11	,	11	,	0	,	4	,	4	,	4	,	4	,	4	,	21	,	11	,	0	,	 // 	11	21	4	4	4	4	21	21	4	4	4	4	4	21	11	0
0	,	11	,	21	,	21	,	4	,	4	,	4	,	21	,	11	,	21	,	4	,	21	,	11	,	11	,	4	,	4	,	 // 	0	11	21	21	4	4	4	21	4	4	4	4	4	4	21	11
11	,	21	,	21	,	4	,	11	,	4	,	4	,	4	,	0	,	11	,	21	,	21	,	21	,	11	,	11	,	11	,	 // 	11	21	4	21	11	11	4	4	4	4	4	4	4	4	4	11
0	,	0	,	11	,	21	,	21	,	21	,	21	,	21	,	0	,	0	,	0	,	11	,	11	,	21	,	11	,	21	,	 // 	11	21	21	4	11	4	4	4	4	21	4	21	4	21	4	11
0	,	0	,	0	,	0	,	0	,	11	,	12	,	11	,	0	,	0	,	0	,	0	,	0	,	11	,	12	,	2	,	 // 	0	11	21	21	21	11	11	11	11	21	21	4	21	4	4	11
4	,	4	,	4	,	4	,	4	,	4	,	21	,	11	,	4	,	4	,	4	,	4	,	4	,	4	,	4	,	11	,	 // 	0	0	11	21	21	21	21	21	21	21	21	21	21	21	11	0
4	,	21	,	4	,	21	,	4	,	21	,	4	,	11	,	11	,	21	,	21	,	4	,	21	,	4	,	4	,	11	,	 // 	0	0	0	11	11	21	11	21	21	21	21	21	11	11	0	0
21	,	21	,	21	,	21	,	21	,	21	,	11	,	0	,	21	,	21	,	21	,	21	,	11	,	11	,	0	,	0	,	 // 	0	0	0	0	0	11	12	11	11	11	11	11	0	0	0	0
11	,	11	,	11	,	11	,	0	,	0	,	0	,	0	,	2	,	11	,	2	,	11	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	11	12	2	2	11	2	11	0	0	0	0


};
u8 meteorite[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	1	1	0
0	,	0	,	0	,	0	,	0	,	0	,	1	,	1	,	0	,	0	,	0	,	0	,	1	,	1	,	12	,	12	,	 // 	0	0	0	0	0	0	0	0	0	0	0	1	1	1	1	0
0	,	0	,	1	,	1	,	12	,	12	,	12	,	2	,	0	,	1	,	12	,	12	,	2	,	2	,	2	,	2	,	 // 	0	0	0	0	0	0	0	0	0	1	1	1	12	1	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	1	,	1	,	0	,	 // 	0	0	0	0	0	0	1	1	1	12	12	12	1	1	0	0
0	,	0	,	0	,	1	,	1	,	1	,	1	,	0	,	0	,	1	,	1	,	1	,	12	,	1	,	0	,	0	,	 // 	0	0	0	0	1	1	12	12	12	2	2	12	1	0	0	0
1	,	12	,	12	,	12	,	1	,	1	,	0	,	0	,	12	,	2	,	2	,	12	,	1	,	0	,	0	,	0	,	 // 	0	0	1	1	12	12	12	2	2	2	2	12	1	0	0	0
2	,	2	,	2	,	12	,	1	,	0	,	0	,	0	,	2	,	2	,	12	,	1	,	0	,	0	,	0	,	0	,	 // 	0	1	12	12	2	2	2	2	2	2	12	1	0	0	0	0
1	,	12	,	12	,	2	,	2	,	2	,	3	,	3	,	1	,	12	,	2	,	3	,	3	,	3	,	2	,	3	,	 // 	1	12	12	2	2	2	3	3	2	2	12	1	0	0	0	0
1	,	12	,	3	,	3	,	3	,	3	,	3	,	2	,	1	,	12	,	3	,	3	,	3	,	3	,	3	,	2	,	 // 	1	12	2	3	3	3	2	3	2	12	12	1	0	0	0	0
1	,	12	,	3	,	3	,	3	,	3	,	3	,	2	,	1	,	12	,	12	,	3	,	3	,	3	,	2	,	12	,	 // 	1	12	3	3	3	3	3	2	2	12	1	0	0	0	0	0
0	,	1	,	12	,	12	,	12	,	12	,	12	,	12	,	0	,	0	,	1	,	1	,	1	,	1	,	1	,	1	,	 // 	1	12	3	3	3	3	3	2	2	12	1	0	0	0	0	0
2	,	2	,	12	,	1	,	0	,	0	,	0	,	0	,	2	,	12	,	12	,	1	,	0	,	0	,	0	,	0	,	 // 	1	12	3	3	3	3	3	2	12	1	0	0	0	0	0	0
2	,	12	,	1	,	0	,	0	,	0	,	0	,	0	,	2	,	12	,	1	,	0	,	0	,	0	,	0	,	0	,	 // 	1	12	12	3	3	3	2	12	12	1	0	0	0	0	0	0
12	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	12	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	1	12	12	12	12	12	12	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	1	1	1	1	1	1	0	0	0	0	0	0	0	0


};

//16x64
u8 erronboHandia[1024] = 
{
0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,

3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
 
2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,0,0,0,2,2,

2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,0,

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,

3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,

3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,

1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,
};

/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void SpriteakMemorianGorde()
{

	int i;
	// 16*16ko spriteentzako
	for (i = 0; i < 16 * 16 / 2; i++)
	{
		gfxerronbo[i] = erronbo[i * 2] | (erronbo[(i * 2) + 1] << 8);
		gfxdino[i] = dino[i * 2] | (dino[(i * 2) + 1] << 8);
		gfxcactus[i] = cactus[i * 2] | (cactus[(i * 2) + 1] << 8);
		gfxmeteorite[i] = meteorite[i * 2] | (meteorite[(i * 2) + 1] << 8);
	}
	// 32*32ko spriteentzako
	for (i = 0; i < 32 * 32 / 2; i++)
	{
		gfxerronboHandia[i] = erronboHandia[i * 2] | (erronboHandia[(i * 2) + 1] << 8);
	}
}

/* Funtzio honek erronbo bat irudikatzen du pantailako x,y posizioan. Pantailan ateratzea nahi den erronbo
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke */

void ErakutsiErronboa(int indizea, int x, int y)
{

	oamSet(&oamMain, // main graphics engine context
		   indizea,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxerronbo,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   false,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);

	oamUpdate(&oamMain);
}

/* Funtzio honek erronbo baten indizea pasata pantailatik ezabatzen du */
void EzabatuErronboa(int indizea, int x, int y)
{

	oamSet(&oamMain, // main graphics engine context
		   indizea,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxerronbo,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   true,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
	oamUpdate(&oamMain);
}

void ErakutsiErronboHandia(int indizea, int x, int y)
{

	oamSet(&oamMain, // main graphics engine context
		   indizea,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_32x32,
		   SpriteColorFormat_256Color,
		   gfxerronboHandia, //+16*16/2,                  // pointer to the loaded graphics
		   -1,				 // sprite rotation data
		   false,			 // double the size when rotating?
		   false,			 // hide the sprite?
		   false, false,	 // vflip, hflip
		   false			 // apply mosaic
	);

	oamUpdate(&oamMain);
}

void EzabatuErronboHandia(int indizea, int x, int y)
{

	oamSet(&oamMain, // main graphics engine context
		   indizea,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_32x32,
		   SpriteColorFormat_256Color,
		   gfxerronboHandia, //+16*16/2,                  // pointer to the loaded graphics
		   -1,				 // sprite rotation data
		   false,			 // double the size when rotating?
		   true,			 // hide the sprite?
		   false, false,	 // vflip, hflip
		   false			 // apply mosaic
	);
	oamUpdate(&oamMain);
}

void showPlayer(int index, int x, int y) {
	oamSet(&oamMain, // main graphics engine context
		   index,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxdino,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   false,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
}

void hidePlayer(int index, int x, int y) {
	oamSet(&oamMain, // main graphics engine context
		   index,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxdino,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   true,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
}

void showCactus(int index, int x, int y) {
	oamSet(&oamMain, // main graphics engine context
		   index,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxcactus,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   false,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
}

void hideCactus(int index, int x, int y) {
	oamSet(&oamMain, // main graphics engine context
		   index,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxcactus,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   true,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
}

void showMeteorite(int index, int x, int y) {
	oamSet(&oamMain, // main graphics engine context
		   index,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxmeteorite,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   false,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
}

void hideMeteorite(int index, int x, int y) {
	oamSet(&oamMain, // main graphics engine context
		   index,	 // oam index (0 to 127)
		   x, y,	 // x and y pixel location of the sprite
		   0,		 // priority, lower renders last (on top)
		   0,		 // this is the palette index if multiple palettes or the alpha value if bmp sprite
		   SpriteSize_16x16,
		   SpriteColorFormat_256Color,
		   gfxmeteorite,	 //+16*16/2,                  // pointer to the loaded graphics
		   -1,			 // sprite rotation data
		   false,		 // double the size when rotating?
		   true,		 // hide the sprite?
		   false, false, // vflip, hflip
		   false		 // apply mosaic
	);
}

void showSprite(int spriteID, int index, int x, int y) {
	switch (spriteID) {
	case 0:
		showPlayer(index, x, y);
		break;
	
	case 1:
		showCactus(index, x, y);
		break;

	case 2:
		showMeteorite(index, x, y);
		break;

	default:
		break;
	}
}

void hideSprite(int spriteID, int index, int x, int y) {
	switch (spriteID) {
	case 0:
		hidePlayer(index, x, y);
		break;
	
	case 1:
		hideCactus(index, x, y);
		break;

	case 2:
		hideMeteorite(index, x, y);
		break;

	default:
		break;
	}
}