/*
  SPIRam.h - SPI RAM memory library for Arduino and compatible clones.
  Copyright (c) 2013 Martyn Van Berkel (http://www.tariox.com)

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  Based on code by Nick Gammon (http://www.gammon.com.au)
*/

#ifndef SPIRam_h
#define SPIRam_h

#include "Arduino.h"
#include <SPI.h>

#define SRAM_DEVICE 8  // SRAM on pin 8

// 23A256 commands
#define SRAM_READ  0b011  // Read data from memory array beginning at selected address
#define SRAM_WRITE 0b010  // Write data to memory array beginning at selected address
#define SRAM_RDSR  0b101  // Read STATUS register
#define SRAM_WRSR  0b001  // Write STATUS register

// operation modes (status register)
#define SRAM_BYTE_MODE 0b00000000  // Byte mode (default operation) 
#define SRAM_PAGE_MODE 0b10000000  // Page mode
#define SRAM_SEQN_MODE 0b01000000  // Sequential mode
#define SRAM_RSVD_MODE 0b11000000  // Reserved
#define SRAM_HOLD_MODE 0b00000001  // Set this bit to DISABLE hold mode


class SPIRam
{
  public:
    // SPIRam(byte slaveSelectPin = SRAM_DEVICE);
    SPIRam(byte slaveSelectPin);
    void initialize();
    void read (unsigned int address, byte * data, unsigned int length);
    void write (unsigned int address, byte * data, unsigned int length);
  private:
    byte _slaveSelectPin;
};

#endif
