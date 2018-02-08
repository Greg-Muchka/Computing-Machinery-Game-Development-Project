;================================================
; Name: clear_qk 
; Purpose: clears the screen quickly
; 
; Made by Marc Schroeder
;================================================
; quick clear (uses movem to reduce fetch-execute cycle overhead)
;
; takes about half the number of clock cycles as the code in clear.s, and
; so runs in about 1/100th of a second (at 8MHz) instead of 1/50th

		xdef		_clear_screen
		xdef		_VBL_ISR
		xdef		_IKBD_ISR
		xref		_do_VBL_ISR
		xref		_do_IKBD_ISR
base		equ		64		; offset from SP, not A6

_clear_screen:	movem.l		d0-7/a0-6,-(sp)
		lea		zeros,a0
		movem.l		(a0)+,d1-7/a1-6
		movea.l		base(sp),a0
		adda.l		#32000,a0
		move.w		#614,d0
fill_loop:	movem.l		d1-7/a1-6,-(a0)
		dbra		d0,fill_loop
		movem.l		d1-5,-(a0)
		movem.l		(sp)+,d0-7/a0-6
		rts

zeros:		ds.l		13

_IKBD_ISR:	movem.l	d0-7/a0-6,-(sp)
			jsr	_do_IKBD_ISR
			movem.l	(sp)+,d0-7/a0-6
			rte
			
_VBL_ISR:	movem.l	d0-7/a0-6,-(sp)
			jsr	_do_VBL_ISR
			movem.l	(sp)+,d0-7/a0-6
			rte