#include <nds.h>
#include <stdio.h>
#include "definizioak.h"

/**
 * Detect if a key is pressed
 * @return 1 if a key is pressed, 0 if not
 */
int detectKey() 
{
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;
}

/**
 * Detect which key is pressed
 * @return the value of the key pressed: A=0;B=1;Select=2;Start=3;Right=4;Left=5;Up=6;Down=7;R=8;L=9;
 */
int pressedKey() 
{
	if (~(TEKLAK_DAT) & 0x01) return A;
	if (~(TEKLAK_DAT) & 0x02) return B;
	if (~(TEKLAK_DAT) & 0x04) return SELECT;
	if (~(TEKLAK_DAT) & 0x08) return START;
	if (~(TEKLAK_DAT) & 0x10) return RIGHT;
	if (~(TEKLAK_DAT) & 0x20) return LEFT;
	if (~(TEKLAK_DAT) & 0x40) return UP;
	if (~(TEKLAK_DAT) & 0x80) return DOWN;
	if (~(TEKLAK_DAT) & 0x100) return R;
	if (~(TEKLAK_DAT) & 0x200) return L;
}

/**
 * Configure the keyboard
 * @param KB_conf the configuration of the keyboard
 */
void configKeyboard(int KB_conf)
{
	TEKLAK_KNT |= KB_conf;
}

/**
 * Configure the timer
 * @param Latch the value of the latch
 * @param TIMER_conf the configuration of the timer
 */
void configTimer(int Latch, int TIMER_conf)
{
	DENB0_DAT = Latch;
	DENB0_KNT |= TIMER_conf;	
}

/**
 * Allow the keyboard stops
 */
void allowKBStops()
{
	IME=0;
	IE |= 0x1000;
	IME=1;
}

/**
 * Deny the keyboard stops
 */
void denyKBStops()
{
	IME=0;
	IE &= 0x0FFF;
	IME=1;
}  

/**
 * Allow the timer stops
 */
void allowTimerStops()
{
	IME=0;
	IE |= 0x00000008;
	IME=1;
}

/**
 * Deny the timer stops
 */
void denyTimerStops()
{
	IME=0;
	IE &= 0xFFFFFFF7;
	IME=1;
}

/**
 * Start the timer
 */
void startTimer0()
{
	DENB0_KNT |= 0x00C0;
}

/**
 * Stop the timer
 */
void stopTimer0()
{
	DENB0_KNT &= 0xFF7F;
}
