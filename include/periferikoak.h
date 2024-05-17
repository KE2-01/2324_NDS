extern int detectKey();
extern int pressedKey();

extern void configKeyboard(int TEK_konf);
extern void configTimer(int Latch, int TENP_konf);

extern void allowKBStops();
extern void denyKBStops();

extern void allowTimerStops();
extern void denyTimerStops();

extern void startTimer0();
extern void stopTimer0();