/*
  SPIRam.cpp - SPI RAM memory library for Arduino and compatible clones.
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

#include "Arduino.h"
#include "SPIRam.h"



SPIRam::SPIRam(byte slaveSelectPin)
{
  pinMode(slaveSelectPin, OUTPUT);
  _slaveSelectPin = slaveSelectPin;
}



// setup SRAM device by turning into sequential mode
void SPIRam::initialize ()
{
  digitalWrite (_slaveSelectPin, LOW);   // select device 
  SPI.transfer (SRAM_WRSR); 
  SPI.transfer (SRAM_SEQN_MODE); 
  digitalWrite (_slaveSelectPin, HIGH);  // deselect device
}  // end of sram_setup



// read 'length' bytes into 'data' to device from address 'address'
void SPIRam::read (unsigned int address, byte * data, unsigned int length)
{
  if (length == 0)  // don't bother if nothing to do
     return;
  digitalWrite (_slaveSelectPin, LOW);     // select device
  SPI.transfer (SRAM_READ);                // read mode
  SPI.transfer (address >> 8);             // high-order address byte
  SPI.transfer (address & 0xFF);           // low-order address byte
  for ( ; length ; --length)
    *data++ = SPI.transfer (0);            // data byte
  digitalWrite (_slaveSelectPin, HIGH);    // deselect device
}  // end of sram_write



// write 'length' bytes from 'data' to device at address 'address'
void SPIRam::write (unsigned int address, byte * data, unsigned int length)
{
  if (length == 0)  // don't bother if nothing to do
     return;
  digitalWrite (_slaveSelectPin, LOW);  
  SPI.transfer (SRAM_WRITE);               // write mode
  SPI.transfer (address >> 8);             // high-order address byte
  SPI.transfer (address & 0xFF);           // low-order address byte
  for ( ; length ; --length)
    SPI.transfer (*data++);                // data byte
  digitalWrite (_slaveSelectPin, HIGH);    // deselect device
}  // end of sram_write
