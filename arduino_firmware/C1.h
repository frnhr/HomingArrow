
int led = 13;

void blink_loop();

typedef struct {
	unsigned long interval;     // blink interval, millis
	bool state;				    // led HIGH or LOW
	unsigned _last_blink;  // millis of last blink
} Blink;
Blink blink = {
	1000,  // interval
	true,  // state
	0	   // _last_blink
};
