/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int key; // Sakatutako tekla gordetzeko aldagaia; baloratu ea behar den



int detectKey() 
{
	// TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int pressedKey() 
{

	// Sakatutako teklaren balioa itzultzen du: A=0;B=1;Select=2;Start=3;Esk=4;Ezk=5;
	// Gora=6;Behera=7;R=8;L=9;
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

void configKeyboard(int KB_conf)
{
	// Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	TEKLAK_KNT |= KB_conf;
}

void configTimer(int Latch, int TIMER_conf)
{
	// Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	DENB0_DAT = Latch;
	DENB0_KNT |= TIMER_conf;
	
	
}

void allowKBStops()
{
	// Teklatuaren etenak baimendu
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE |= 0x1000;
	IME=1;
}

void denyKBStops()
{

	// Teklatuaren etenak galarazi
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE &= 0x0FFF;
	IME=1;
}  

void allowTimerStops()
{

// Tenporizadore baten etenak baimendu (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE |= 0x00000008;
	IME=1;
}

void denyTimerStops()
{

// Tenporizadore baten etenak galarazi (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE &= 0xFFFFFFF7;
	IME=1;

}

void startTimer0()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT |= 0x00C0;
}

void stopTimer0()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT &= 0xFF7F;
}
