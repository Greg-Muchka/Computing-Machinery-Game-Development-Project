#include <osbind.h>
#include "PSG.H"
/*===================== ================================================
- Name: gun_shot
- Purpose: writes to the psg to create a gun shot sound effect
- Returns nothing when called
====================================================================== */
void gun_shot()
{
	write_psg(6,0x0F);
	set_volume(1, 0x10);
	set_envelope(0, 0x1000);
	write_psg_noise_tone(7,0x1F);
    enable_channel(1, FALSE, TRUE); 

}
/*===================== ================================================
- Name: point_increment_sound
- Purpose: writes to the psg to create a explosion sound effect
- Returns nothing when called
====================================================================== */
void point_increment_sound()
{
	write_psg(6,0x1F);
	set_volume(2, 0x10);
	set_envelope(0, 0x1000);
	write_psg_noise_tone(7,0x1F);
	enable_channel(2, FALSE, TRUE);
}
/*===================== ================================================
- Name: reset_sound
- Purpose: writes to the psg to clear register 7 to allow multiple channels to be written to 
- Returns nothing when called
====================================================================== */
void reset_sound()
{
	long old_ssp = Super(0);
    write_psg(7, 0x3F);
	Super(old_ssp);
}
/*===================== ================================================
- Name: write_psg
- Purpose: writes to the psg given a register and a value 
- Returns nothing when called
====================================================================== */
void write_psg(int reg, UINT8 val){
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	
	if((reg >= 0 && reg <= 15) && (val >= 0 && val <= 255))
	{
		*PSG_reg_select = reg;	
        *PSG_reg_write  = val;
	}
}
/*===================== ================================================
- Name: write_psg_noise_tone
- Purpose: writes to the psg but only to register 7 to write sounds onntop of each other
- Returns nothing when called
====================================================================== */
void write_psg_noise_tone(int reg, UINT8 val){
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	
	if((reg >= 0 && reg <= 15) && (val >= 0 && val <= 255))
	{
		*PSG_reg_select = reg;	
        *PSG_reg_write  = (*PSG_reg_select & val);
	}
}
/*===================== ================================================
- Name: set_envelope
- Purpose: sets up the envelope for sound effects 
- Returns nothing when called
====================================================================== */
void set_envelope(int shape, unsigned int sustain)
{
    write_psg(13,shape);
	write_psg(11,((UINT8)(sustain & 0xFF))); 
	write_psg(12,(UINT8)(sustain >> 8));
	
  /*  write_psg(11, sustain >>8);
    write_psg(12, (UINT8)sustain);*/
}
/*===================== ================================================
- Name: set_tone
- Purpose: writes to the psg to set the tone given the channel, fine and rough tunning
- Returns nothing when called
====================================================================== */
void set_tone(int channel, int tuningFine, int tuningRough)
{
		if((channel >= 0 && channel <= 2) && (tuningFine >= 0 && tuningFine <= 255) && (tuningRough >= 0 && tuningRough <= 255))
		{
			switch(channel)
			{
				case 0:
				write_psg(0,tuningFine);
				write_psg(1,tuningRough);

				break;
				case 1:
				write_psg(2,tuningFine);
				write_psg(3,tuningRough);
				break; 
				case 2:
				write_psg(4,tuningFine);
				write_psg(5,tuningRough);
			}
		}
}
/*===================== ================================================
- Name: set_volume
- Purpose: writes to the psg to set the volume
- Returns nothing when called
====================================================================== */
void set_volume(int channel, int volume)
{
	if((channel >= 0 && channel <= 3) && (volume >= 0 && volume <= 255))
	{
		switch(channel)
		{
			case 0:
			write_psg(8,volume);
			break;
			case 1:
			write_psg(9,volume);
			break;
			case 2:
			write_psg(10,volume);
		}
	}
}
/*===================== ================================================
- Name: enable_channel 
- Purpose: writes to the psg to enable a channel
- Returns nothing when called
====================================================================== */
void enable_channel(int channel, int tone_on, int noise_on)
{
	if(channel >= 0 && channel < 3)
	{
		switch(channel)
		{
			case 0:
			if(tone_on)
				write_psg_noise_tone(7,0xFE);
			else
				write_psg_noise_tone(7,0xF7);
			break;
			case 1:
			if(tone_on)
				write_psg_noise_tone(7,0xFD);
			else
				write_psg_noise_tone(7,0xEF);
			break;
			case 2:
			if(tone_on)
				write_psg_noise_tone(7,0xFB);
			else
				write_psg_noise_tone(7,0x1F);
		}
	}
}
/*===================== ================================================
- Name: stop _sound
- Purpose: writes a 0 to turn volume off
- Returns nothing when called
====================================================================== */
void stop_sound()
{
	long old_ssp = Super(0);
	set_volume(0,0);
	set_volume(1,0);
	set_volume(2,0);
	Super(old_ssp);
}
/*===================== ================================================
- Name: start_music
- Purpose: starts the song at the beggining of the song array
- Returns nothing when called
====================================================================== */
void start_music()
{
	note = 0;
	write_psg(7, 0x3F);
	enable_channel(Song[note].channel, Song[note].tone_on, Song[note].noise_on);
	set_tone(Song[note].channel, Song[note].tuningFine, Song[note].tuningRough);
	set_volume(Song[note].channel, Song[note].volume);	
}
/*===================== ================================================
- Name: update_music
- Purpose: updates the song using the next note in the song array
- Returns nothing when called
====================================================================== */
bool update_music(ULONG32 tempo)
{	
	if(note < NUM_NOTES)
	{
		if(Song[note].time <= tempo)
		{
			note++;
			set_tone(Song[note].channel, Song[note].tuningFine, Song[note].tuningRough);
			set_volume(Song[note].channel, Song[note].volume);
			enable_channel(Song[note].channel, Song[note].tone_on, Song[note].noise_on);	
			return TRUE;
		}
	}
	else
		start_music(Song);
	
	return FALSE;
}


Notes Song[NUM_NOTES] = {	
	
	/*BAR ONE TWICE*/
	Bb, pauseA, F, pauseA, Cb, pauseA, Db, pauseA, C, pauseA, F, pauseA,
	Bb, pauseA, F, pauseA, Cb, pauseA, Db, pauseA, C, pauseA, F, pauseA,
	
	/*BAR TWO*/
	Bb, pauseA, F, pauseA, C, pauseA, Db, pauseA, Bb, pauseA, F, pauseA,
	
	/*BAR THREE TWICE*/
	C, pauseA, Db, pauseA, C, pauseA, F, pauseA, Bb, pauseA, F, pauseA,
	C, pauseA, Db, pauseA, C, pauseA, F, pauseA, Bb, pauseA, F, pauseA,
	
	/*BAR FOUR*/
	C, pauseA, Db, pauseA, C, pauseA, F, pauseA, Bb, pauseA, F, pauseA,
	
	/*BAR FIVE TWICE*/
	C, pauseA, Ab, pauseA, Bb, pauseA, F, pauseA, C, pauseA, Db, pauseA,
	C, pauseA, Ab, pauseA, Bb, pauseA, F, pauseA, C, pauseA, Db, pauseA,
	
	/*BAR SIX*/
	Bb, pauseA, F, pauseA, C, pauseA, Db, pauseA, C, pauseA, F, pauseA,
	
	/*BAR SEVEN*/
	Bb, pauseA, F, pauseA, C, pauseA, Db, pauseA, Eb, pauseA, G, pauseA,
	
	/*BAR EIGHT TWICE*/
	C, pauseA, Db, pauseA, C, pauseA, G, pauseA, Eb, pauseA, G, pauseA,
	C, pauseA, Db, pauseA, C, pauseA, G, pauseA, Eb, pauseA, G, pauseA,
	
	/*BAR NINE */
	C, pauseA, Db, pauseA, Eb, pauseA, G, pauseA, C, pauseA, Db, pauseA, 
	
	/*BAR TEN TWICE*/
	C, pauseA, G, pauseA, Eb, pauseA, G, pauseA, C, pauseA, Db, pauseA,
	C, pauseA, G, pauseA, Eb, pauseA, G, pauseA, C, pauseA, Db, pauseA,
	
	/*BAR ELEVEN TWICE*/
	Eb, pauseA, G, pauseA, C, pauseA, Db, pauseA, C, pauseA, G, pauseA,
	Eb, pauseA, G, pauseA, C, pauseA, Db, pauseA, C, pauseA, G, pauseA
	
};
