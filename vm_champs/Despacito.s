.name "DespacitoDespacitoDespacitoDespacitoDespacitoDespacitoDespacitoDespacito"
.comment "Diridiri, dirididi Daddy"

		live	%1
		lfork	%2000
live: 	sti		r1,%:live,%22
		sti		r1,%:live,%27
		ld		%0,r2
live2:	live	%1
		live	%1
		zjmp	%:live2
