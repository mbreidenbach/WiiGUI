.rodata
.balign 32
.globl cursorlength
.globl cursordata

cursorlength:	.long	picdataend - cursordata
cursordata:
.incbin "../include/cursor.jpg"
picdataend: