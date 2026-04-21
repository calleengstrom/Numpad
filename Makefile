
# MCU inställningar
MCU     = atmega328p
F_CPU   = 16000000UL

# Verktyg
CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Mappar
SRC_DIR   = src
INC_DIR   = include
BUILD_DIR = build

# Projekt
TARGET = main

# Hämta alla .c filer
UTILS_DIR = utils

SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(UTILS_DIR)/*.c)

# Objektfiler
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c)) \
      $(patsubst $(UTILS_DIR)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(UTILS_DIR)/*.c))

# Output
ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex

# Flaggor
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=c11 -I$(INC_DIR)

# Default target
all: $(HEX)

# Länkning
$(ELF): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# HEX
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Kompilering
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Flash (ändra COM-port!)
flash: $(HEX)
	$(AVRDUDE) -c arduino -p m328p -P COM3 -b 115200 -U flash:w:$(HEX):i

# Clean (funkar i Git Bash / WSL)
clean:
	rm -rf $(BUILD_DIR)
