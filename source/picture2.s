.rodata
.balign 32
.globl piclength2
.globl picdata2

piclength2:	.long	picdataend - picdata2
picdata2:
.incbin "../include/bet.jpg"
picdataend:

