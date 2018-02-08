#ifndef PSG_H
#define PSG_H
#include "../global/TYPES.H"
#include "../events/EVENT.H"
#define NUM_NOTES 204
#define pauseA 	{0,0,0,TRUE,FALSE,0,5}
#define Ab		{8, 0x4, 0x35, TRUE, FALSE, 0, 5}
#define Bb    	{8, 0x7, 0x14, TRUE, FALSE, 0, 5}
#define Cb 		{8, 0x3, 0x8A, TRUE, FALSE, 0, 5}
#define Db		{8, 0x3, 0x27, TRUE, FALSE, 0, 5}
#define Eb		{8, 0x5, 0x9E, TRUE, FALSE, 0, 5}
#define F		{8, 0x5, 0x01, TRUE, FALSE, 0, 5}
#define C 		{8, 0x3, 0x57, TRUE, FALSE, 0, 5}
#define G		{8, 0x8, 0xEB, TRUE, FALSE, 0, 5}


extern int note = 0;

void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuningFine, int tuningRough);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void start_music();
void gun_shot();
void point_increment_sound();
bool update_music(ULONG32 time);
void set_envelope(int shape, unsigned int sustain);
void reset_sound();
void write_psg_noise_tone(int reg, UINT8 val);
typedef struct {
	int volume;
	int tuningRough;
	int tuningFine;
	bool tone_on;
	bool noise_on;
	int channel;
	int time;
}Notes;

extern const Notes Song[NUM_NOTES];
#endif