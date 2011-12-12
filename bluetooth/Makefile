CC=avr-gcc
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=attiny2313
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref	
OBJ2HEX=avr-objcopy 

####### Files:

SOURCES       = bt.c

OBJECTS	      = bt.o

TARGET=	bluetooth

####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

%.elf:	$(OBJECTS)

####### Build rules

$(TARGET):	$(OBJECTS)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
		$(CC) $(ALL_CFLAGS) $(OBJECTS) --output $(TARGET).elf $(LDFLAGS)	
		$(OBJ2HEX) -R .eeprom -O ihex $(TARGET) $(TARGET).hex
erase:
	avrdude -c usbtiny -p attiny2313 -e 

fuses: 
	avrdude -c usbtiny -p attiny2313 -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

bt:
	avrdude -c usbtiny -b 115200 -p attiny2313 -e -D -U flash:w:bluetooth.hex:i

####### Compile

test.o:		bt.c