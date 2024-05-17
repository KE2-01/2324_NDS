extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaErreserbatu();

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu pantaila nagusian. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. */

extern void paletaNagusiaEzarri();

/* Irudikatutako Spriteak memorian kargatzen ditu.*/

extern void SpriteakMemorianGorde();

/* Sprite handler */
extern void showSprite(int spriteID, int indizea, int x, int y);
extern void hideSprite(int spriteID, int indizea, int x, int y);

/* Just in case */
extern void showPlayer(int indizea, int x, int y);
extern void hidePlayer(int indizea, int x, int y);

extern void showCactus(int indizea, int x, int y);
extern void hideCactus(int indizea, int x, int y);

extern void showMeteorite(int indizea, int x, int y);
extern void hideMeteorite(int indizea, int x, int y);
