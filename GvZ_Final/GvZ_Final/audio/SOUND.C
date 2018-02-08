/* ================================================
- Module Name: sound
- Purpose: handles sound effects
================================================ */
#include <osbind.h>
#include "SOUND.H"
/* ================================================
- Name: gunShot
- Purpose: gun shot sound effect
================================================ */
void gunShot()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	
	ULONG32 CurTime = 0;
	ULONG32 PostTime = 0;
	ULONG32 ElapsedTime = 0;

	long old_ssp = Super(0);

	*PSG_reg_select = 6;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 0x0F;

	*PSG_reg_select = 7;		/* set channel A coarse tune = 0 */
	*PSG_reg_write  = 0x07;

	*PSG_reg_select = 8;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 0x10;

	*PSG_reg_select = 9;		/* set channel A coarse tune = 0 */
	*PSG_reg_write  = 0x10;
	
	*PSG_reg_select = 10;		/* enable channel A on mixer */
	*PSG_reg_write  = 0x10;

	*PSG_reg_select = 12;		/* set channel A volume = 11 */
	*PSG_reg_write  = 0x10;

	*PSG_reg_select = 13;		/* set channel A volume = 11 */
	*PSG_reg_write  = 0x00;
	
	CurTime = getTime();
	ElapsedTime = CurTime - PostTime;
		
	while (ElapsedTime < 70)
		;

	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;
	

	Cnecin();
	Super(old_ssp);
}
