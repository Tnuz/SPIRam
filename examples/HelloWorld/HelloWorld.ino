/*
  HelloWorld.ino - Example sketch for SPI RAM memory library.
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
*/

#include <SPI.h>
#include <SPIRam.h>

SPIRam sram(8); // SS pin of 32k256 is connected to pin D8

char buf[4];    // small buffer for strcat function
int x = 0;      // counter starts at 0

void setup (void)
{
	Serial.begin (9600);
	sram.initialize();    // initialize sram
}


void loop (void)
{
	char in [50] = "Hello World ";
	strcat(in, itoa(x++, buf, 10));
	strcat(in, '\0');
	Serial.print ("in = ");
	Serial.println (in);
	sram.write (123, (byte *) in, (sizeof in) + 1); // write value of 'in' with the length of 'in' (50 bytes) to sram starting at address 123

	char out [50];
	sram.read (123, (byte *) out, sizeof out);      // read data with the length of 'out' (50 bytes) from sram starting at address 123
	Serial.print ("out = ");
	Serial.println (out);

	Serial.println ();
	delay (1000);
}
