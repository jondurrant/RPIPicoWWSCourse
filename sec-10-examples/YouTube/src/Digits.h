/*
 * Digits.h
 *
 *  Created on: 17 Dec 2023
 *      Author: jondurrant
 */

#ifndef SRC_DIGITS_H_
#define SRC_DIGITS_H_

#define DIGITS_PERCENT 		10
#define DIGITS_MINUS 			11
#define DIGITS_CELCIUS		12

#include "pico/stdlib.h"
#include "localPicoGraphics.h"

using namespace pimoroni;

class Digits {
public:
	Digits();
	virtual ~Digits();

	/***
	 * Draw digit
	 * @param digit
	 * @param x
	 * @param y
	 * @param graphics
	 * @return Width
	 */
	virtual int draw(uint8_t digit, uint8_t x, uint8_t y,  PicoGraphics *graphics);

	/***
	 * draw a Float
	 * @param f = target float
	 * @param x starting x position
	 * @param y starting y
	 * @param graphics object to write to. If Null will return size
	 * @param leadZero = Should include leading zeros
	 * @param leadSpace should include leading spaces
	 * @param sigFig number of significant figures
	 * @param decPlace number of decimal places
	 * @return number of columns needed to write
	 */
	virtual int drawFloat(float f, uint8_t x, uint8_t y,  PicoGraphics *graphics=NULL,
			bool leadZero=false, bool leadSpace=false,
			uint8_t sigFig=2, uint8_t decPlace=1);


	/***
	 * draw a Temperature
	 * @param f = target float
	 * @param x starting x position
	 * @param y starting y
	 * @param graphics object to write to. If Null will return size
	 * @param leadZero = Should include leading zeros
	 * @param leadSpace should include leading spaces
	 * @param sigFig number of significant figures
	 * @param decPlace number of decimal places
	 * @return number of columns needed to write
	 */
	virtual int drawTemp(float f, uint8_t x, uint8_t y,  PicoGraphics *graphics=NULL,
			bool leadZero=false, bool leadSpace=false,
			uint8_t sigFig=2, uint8_t decPlace=1);


	/***
	 * draw a Percentage
	 * @param f = target float
	 * @param x starting x position
	 * @param y starting y
	 * @param graphics object to write to. If Null will return size
	 * @param leadZero = Should include leading zeros
	 * @param leadSpace should include leading spaces
	 * @param sigFig number of significant figures
	 * @param decPlace number of decimal places
	 * @return number of columns needed to write
	 */
	virtual int drawPer(float f, uint8_t x, uint8_t y,  PicoGraphics *graphics=NULL,
			bool leadZero=false, bool leadSpace=false,
			uint8_t sigFig=2, uint8_t decPlace=1);


	int drawSymbol(char  sym, uint8_t x, uint8_t y,  PicoGraphics *graphics=NULL);

	int digitalClock(uint8_t hour, uint8_t min, uint8_t x, uint8_t y, PicoGraphics *graphics=NULL);



	/***
	 * Return number of rows needed to write any digits
	 */
	virtual int rows()=0;


protected:

	/***
	 * Draw a colon
	 * @param x
	 * @param y
	 * @param graphics
	 * @return Width
	 */
	virtual int drawColon(uint8_t x, uint8_t y,  PicoGraphics *graphics)=0;

	virtual int drawDot(uint8_t x, uint8_t y,  PicoGraphics *graphics)=0;

	virtual int drawSprite(uint8_t index, uint8_t x, uint8_t y,  PicoGraphics *graphics)=0;
};

#endif /* SRC_DIGITS_H_ */
