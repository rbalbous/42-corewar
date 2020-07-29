.name "afoures le bg"
.comment "jump live jump live jump live jump live jump.."

live:	sti		r1,%:live,%8
		live	%1
		ldi		%:live,%8,r2
		ld		%1,r3
jump:	st		r2,50
		st		r3,41
		ld		%0,r4
		zjmp	%32

