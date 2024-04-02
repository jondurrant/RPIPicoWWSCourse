/*
 * Digits.cpp
 *
 *  Created on: 17 Dec 2023
 *      Author: jondurrant
 */

#include "Digits.h"

Digits::Digits() {
	// TODO Auto-generated constructor stub

}

Digits::~Digits() {
	// TODO Auto-generated destructor stub
}

int Digits::draw(uint8_t digit, uint8_t x, uint8_t y,  PicoGraphics *graphics){

	if (digit > 9){
		return 0;
	}

	return drawSprite(digit,  x,  y,   graphics);
}

int Digits::drawSymbol(char  sym, uint8_t x, uint8_t y,  PicoGraphics *graphics){
	int res = 0;

	if ((sym >= '0') && (sym <= '9')){
		uint8_t digit = sym - '0';
		res = drawSprite(digit, x, y, graphics );
	}else {
		switch(sym){
		case ':':
			res = drawColon(x, y, graphics);
			break;
		case '.':
			res = drawDot(x, y, graphics);
			break;
		case '%':
			res = drawSprite(DIGITS_PERCENT,  x,  y,   graphics);
			break;
		case '-':
			res = drawSprite(DIGITS_MINUS,  x,  y,   graphics);
			break;
		case 'C':
			res = drawSprite(DIGITS_CELCIUS,  x,  y,   graphics);
			break;
		case 'c':
			res = drawSprite(DIGITS_CELCIUS,  x,  y,   graphics);
			break;
		}
	}
	return res;
}

int Digits::drawFloat(float f, uint8_t x, uint8_t y,  PicoGraphics *graphics,
		bool leadZero, bool leadSpace,
		uint8_t sigFig, uint8_t decPlaces){

	int col=0;
	char buf[10];
	bool start = false;

	int sig = pow(10, sigFig-1);


	// Sig figures
	if (leadZero){
		start = true;
	}
	while (sig > 0){
		int digit =( (int)(f / sig)) % 10;
		if (sig == 1){
			start = true;
		}
		if (digit > 0){
			start = true;
		} else {
			if (leadSpace){
				col +=5;
			}
		}
		if (start){
			col += draw(digit, x+col, y, graphics);
			col++;
		}
		sig = sig /10;
	}


	if (decPlaces > 0 ){
		col--;
		col += drawSymbol('.', x+col, y, graphics);

		//Decimal places
		int dec = pow(10, decPlaces -1);
		int target = dec * f * 10;
		while (dec > 0){
			int digit = (target / dec) % 10;
			col += draw(digit, x+col, y, graphics);
			col++;
			dec = dec /10;
		}
	}

	return (col-1);
}

int Digits::digitalClock(uint8_t hour, uint8_t min, uint8_t x, uint8_t y, PicoGraphics *graphics){
	int col = 0;

	if (hour < 10){
		col += draw(0,  col+x, y, graphics);
	} else {
		col += draw(hour /10,  col+x, y, graphics);
	}
	col += draw(hour %10,  ++col+x, y, graphics);

	col += drawColon(col+x, y, graphics);

	if (min < 10){
		col += draw(0,  col+x, y, graphics);
	} else {
		col += draw(min /10,  col+x, y, graphics);
	}
	col += draw(min %10,  ++col+x, y, graphics);

	return col;
}

int Digits::drawPer(float f, uint8_t x, uint8_t y,  PicoGraphics *graphics,
			bool leadZero, bool leadSpace,
			uint8_t sigFig, uint8_t decPlace){
	int col = 0;
	col=drawFloat(f, x, y, graphics, leadZero, leadSpace, sigFig, decPlace);
	col++;
	col+=drawSymbol('%', x+col, y, graphics);
	return col;
}

int Digits::drawTemp(float f, uint8_t x, uint8_t y,  PicoGraphics *graphics,
			bool leadZero, bool leadSpace,
			uint8_t sigFig, uint8_t decPlace){
	int col = 0;
	col=drawFloat(f, x, y, graphics, leadZero, leadSpace, sigFig, decPlace);
	col++;
	col+=drawSymbol('C', x+col, y, graphics);
	return col;
}
