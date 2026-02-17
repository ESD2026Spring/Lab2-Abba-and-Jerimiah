# STM32 Lab 2: Keypad & LCD Device Drivers

This repository contains a full implementation of custom device drivers for a 4x4 Matrix Keypad and a 16x2 I2C LCD using the STM32 Nucleo-F103RB.

## 🛠 Hardware Configuration

### 1. I2C LCD (via PCF8574)
- **SDA**: PB9 (Pin D14 on CN5 or CN9-9)
- **SCL**: PB8 (Pin D15 on CN5 or CN9-10)
- **Note**: The I2C address for this specific board was discovered to be **0x7E**.

### 2. 4x4 Matrix Keypad (Morpho Headers)
The Morpho headers (CN7) have a "zig-zag" layout. To get the pins in order, use this physical mapping:
- **Rows (Outputs)**: PA0, PA1, PA4, PB0 (Pins 28, 30, 32, 34 on CN7)
- **Columns (Inputs)**: PC0, PC1, PC2, PC3 (Pins 38, 36, 35, 37 on CN7)

---

## 💻 Software Implementation

### 1. Keypad Driver
Implemented a polling-based scanning algorithm:
- Sequence: Pulse Row LOW -> Read Columns -> Decode Key.
- Port Handling: Rows R1-R3 are on GPIOA, but Row R4 is on **GPIOB**.

### 2. LCD Driver
Implemented command and data registration over I2C using 4-bit nibble transmission.

### 3. Logic Features
- **Line Persistence (# Key)**: Toggles current line while saving the cursor position for Line 1 and Line 2 independently.
- **Smart Reset (* Key)**: Clears the screen and resets all cursor memories.
- **Auto-Wrap**: Automatically jumps to the next line when 16 characters are reached.

---

## 🚀 Troubleshooting & Challenges

### 1. The "Dead Column" 1
**Problem**: The first column (1, 4, 7, *) wasn't responding.
**Cause**: High-density header layout resulted in a loose wire.
**Solution**: Verified PC0 connectivity and ensured GPIO Pull-down resistors were enabled in CubeMX.

### 2. Character Swapping (Mapping)
**Problem**: Pressing '3' resulted in 'C'.
**Cause**: Physical wiring sequence didn't match the standard `keys[4][4]` table.
**Solution**: Remapped the character array in `keypad.c` to match the hardware reality.

### 3. Invalid Storage Class (Build Error)
**Problem**: Functions like `MX_GPIO_Init` caused compiler errors.
**Cause**: A missing closing brace `}` at the end of the `main()` function.
**Solution**: Audited all `{}` counts to ensure functional scope was correct.

---

## 📝 Reporting
For the final report, ensure to mention the use of **STM32 HAL** over MMIO for portability and the logic used for cursor memory (storing column offsets in an array).
