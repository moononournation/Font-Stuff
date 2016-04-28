# Makefile to build light_ws2812 library examples
# This is not a very good example of a makefile - the dependencies do not work, therefore everything is rebuilt every time.

# Change these parameters for your device

F_CPU = 9600000
DEVICE = attiny13

# Tools:
CC = avr-gcc

DEP       = ws2812_config.h light_ws2812.h
LIB       = light_ws2812
MAIN      = main

CFLAGS = -g2 -I. -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) 
CFLAGS+= -Os -ffunction-sections -fdata-sections -fpack-struct -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions  
CFLAGS+= -Wall -Wno-pointer-to-int-cast
#CFLAGS+= -Wa,-ahls=$<.lst

LDFLAGS = -Wl,--relax,--section-start=.text=0,-Map=main.map

all: program

program: $(MAIN)
	@avr-size --format=avr --mcu=$(MCU) $^.o
	@avrdude -c usbtiny -p t13 -U flash:w:$(MAIN).hex -U lfuse:w:0x7A:m -U hfuse:w:0xFF:m

$(LIB): $(DEP)
	@echo Building Library 
	@$(CC) $(CFLAGS) -o $@.o -c $@.c 


$(MAIN): $(LIB) 
	@echo Building $@
	@$(CC) $(CFLAGS) -o $(LIB).o -c $(LIB).c 
	@$(CC) $(CFLAGS) -o $@.o $@.c $^.c
	@avr-objcopy -j .text -j .data -O ihex $@.o $@.hex
	@avr-objdump -d -S $@.o > $@.lss

.PHONY:	clean

clean:
	rm -f *.hex *.o *.lss
