/* ================================================
- Module Name: clear_qk
- Purpose: header file for clear_qk.s

- Made by Marc Schroeder
================================================ */
#ifndef CLEAR_QK_H
#define CLEAR_QK_H

void clear_screen(UINT32 *base);
void VBL_ISR();
void IKBD_ISR();
#endif