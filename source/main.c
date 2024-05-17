#include <nds.h> // NDS development libraries
#include <stdio.h> // Standard C library for input and output functions
#include <stdlib.h> // Standard C library for memory allocation and conversion functions
#include <unistd.h> // Library for compatibility between operating systems

#include "grafikoak.h"		
#include "definizioak.h"
#include "spriteak.h"
#include "game.h"


int main(void) {
	HasieratuGrafikoakSpriteak();
	allowStops();

	// Launch the game
	game();

	denyStops();
	return(0);
}