#include <nds.h> // NDS development libraries
#include <stdio.h> // Standard C library for input and output functions
#include <stdlib.h> // Standard C library for memory allocation and conversion functions
#include <unistd.h> // Library for compatibility between operating systems

#define IME (*(vuint32*)0x04000208) // Interrupt Master Enable
#define IE (*(vuint32*)0x04000210) // Interrupt Enable
#define IF (*(vuint32*)0x04000214) // Interrupt Flag

// Stop handlers
#define allowStops() IME=1 // Enable all stops
#define denyStops() IME=0 // Disable all stops

// Keyboard registers
#define TEKLAK_DAT	(*(vu16*)0x4000130) // Data register of the keyboard
#define TEKLAK_KNT	(*(vu16*)0x4000132) // Control register of the keyboard

// Timer registers
#define DENB0_KNT   (*(vuint16*)0x04000102) // Control register of Timer0
#define DENB0_DAT    (*(vuint16*)0x04000100) // Data register of Timer0

// Touch screen
extern touchPosition PANT_DAT;

// Keyboard keys
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

// Sprite IDs
#define PLAYER 0
#define CACTUS 1
#define METEORITE 2