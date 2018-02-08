	xdef		_get_video_base,_set_video_base

super_on:
	move.l	d0,-(sp)
	
	clr.l	-(sp)
	move.w	#$20,-(sp)
	trap	#1
	addq.l	#6,sp
	
	move.l	d0,old_ssp
	move.l	(sp)+,d0
	
	rts
	
super_off:
	
	move.l	d0,-(sp)
	
	move.l	(old_ssp),-(sp)
	move.w	#$20,-(a7)
	trap	#1
	addq.l	#6,sp
	
	move.l	(sp)+,d0
	rts
	
_get_video_base:
	move.l	d0,-(sp)
	
	clr.l	d0
	
	jsr		super_on
	
	lea		$FFFF8201,a0
	movep.w	(a0),d0
	lsl.l	#$8,d0
	
	jsr super_off
	
	move.l	(sp)+,a0
	rts
	
_set_video_base:
	link	a6,#0
	movem.l	d0-2/a0-2,-(sp)
	
	jsr		super_on
	
	move.l	8(a6),d0
	lsr.l	#8,d0
	lea		$FFFF8201,a0
	movep.w	d0,0(a0)
	
	jsr 	super_off
	
	movem.l	(sp)+,d0-2/a0-2
	unlk	a6
	rts
	
old_ssp:	ds.l	1