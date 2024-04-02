/*
 * Digits6x11.h
 *
 *  Created on: 16 Dec 2023
 *      Author: jondurrant
 */

#ifndef SRC_DIGITS6X11_H_
#define SRC_DIGITS6X11_H_

#include "pico/stdlib.h"
#include "Digits.h"

using namespace pimoroni;

class Digits6x11 : public Digits {
public:
	Digits6x11();
	virtual ~Digits6x11();

	/***
	 * Return number of rows needed to write any digits
	 */
	virtual int rows();


protected:

	/***
	 * Draw a colon
	 * @param x
	 * @param y
	 * @param graphics
	 * @return Width
	 */
	virtual int drawColon(uint8_t x, uint8_t y,  PicoGraphics *graphics);

	virtual int drawDot(uint8_t x, uint8_t y,  PicoGraphics *graphics);

	virtual int drawSprite(uint8_t index, uint8_t x, uint8_t y,  PicoGraphics *graphics);

private:
	static const uint8_t DIGITS[143];
};

#endif /* SRC_DIGITS6X11_H_ */
