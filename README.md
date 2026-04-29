# Numpad Security System

An AVR-based numpad security system implemented on ATMega328p microcontroller. This project provides a secure PIN entry mechanism with EEPROM storage, LED feedback, and UART communication for terminal interaction.

## Features

- **4x4 Keypad Input**: Debounced keypad for reliable key detection
- **PIN Management**: Secure PIN storage in EEPROM with validation
- **LED Feedback**: Green/Red LED indicators for access status
- **UART Terminal**: Serial communication for system monitoring and commands
- **Timeout Handling**: Automatic timeout for security
- **State Machine**: Robust system state management for different modes

## Hardware Requirements

- ATMega328p microcontroller
- 4x4 matrix keypad
- Green and Red LEDs (connected to PB5 and PB4)
- UART interface for serial communication
- EEPROM for PIN storage

## Software Requirements

- AVR-GCC compiler
- AVRDUDE for flashing
- Make build system

## Project Structure

```
├── src/                    # Main source files
│   ├── main.c             # Application entry point
│   ├── keypad.c           # Keypad handling
│   ├── led.c              # LED control
│   ├── pin_key.c          # PIN management
│   ├── system.c           # System state machine
│   ├── system_state.c     # State management
│   └── terminal.c         # Terminal interface
├── utils/                 # Utility functions
│   ├── command_parser.c   # Command parsing (handles PIN change protocol)
│   ├── millis.c           # Millisecond timing
│   └── uart.c             # UART communication
├── include/               # Header files
│   ├── command_parser.h   # Command parsing declarations
│   ├── keypad.h           # Keypad function declarations
│   ├── led.h              # LED control declarations
│   ├── millis.h           # Millisecond timing declarations
│   ├── new_pin_holder.h   # PIN holder structure (protocol data)
│   ├── pin_key.h          # PIN management declarations
│   ├── system.h           # System state machine declarations
│   ├── system_state.h     # State management declarations
│   ├── terminal.h         # Terminal interface declarations
│   └── uart.h             # UART communication declarations
├── build/                 # Build output directory
├── Makefile               # Build configuration
├── wokwi.toml            # Wokwi simulation config
└── diagram.json          # Circuit diagram
```

## Building the Project

1. Ensure AVR-GCC and AVRDUDE are installed
2. Clone or navigate to the project directory
3. Run `make` to build the project:
   ```bash
   make
   ```
   This will generate `build/main.hex` and `build/main.elf`

## Flashing to Device

Use AVRDUDE to flash the hex file to your ATMega328p:

```bash
avrdude -c <programmer> -p atmega328p -U flash:w:build/main.hex
```

Replace `<programmer>` with your programmer type (e.g., arduino, usbasp)

## Usage

1. Power on the device
2. The system initializes and enters idle state
3. Use the keypad to enter PIN
4. Green LED indicates access granted
5. Red LED indicates access denied
6. Use UART terminal for system commands and monitoring

## Changing PIN via UART

The system supports changing the PIN through UART commands using a specific protocol. Send commands in the format:

```
PROTOCOL:OLD_PIN:NEW_PIN
```

Where:
- PROTOCOL: A 7-character protocol identifier
- OLD_PIN: Current 4-digit PIN
- NEW_PIN: New 4-digit PIN

Example:
```
CHANGE:1772:1234
```

The system will validate the old PIN and update to the new PIN if valid.

## Default PIN

The default PIN is set to "1772" in the code. You can change it via EEPROM functions.- IF no pin is already located in eeporm addr

## Simulation

This project can be simulated using Wokwi. The `wokwi.toml` file contains the simulation configuration.

## Contributing

Feel free to submit issues and pull requests for improvements.

## License

This project is open source. Check individual files for license information.