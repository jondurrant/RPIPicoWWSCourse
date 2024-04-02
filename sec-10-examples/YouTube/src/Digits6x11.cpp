/*
 * Digits6x11.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: jondurrant
 */

#include "Digits6x11.h"

const uint8_t Digits6x11::DIGITS[]={
			//0
			30, 49, 49, 41, 41, 37, 37, 37, 35, 35, 30,
			//1
			12, 15, 12, 12, 12, 12, 12, 12, 12, 12, 63,
			//2
			63, 63, 51, 48, 48, 63, 63, 3, 3, 63, 63,
			//3
			63, 63, 51, 48, 48, 63, 63, 48, 48, 63, 63,
			//4
			24, 28, 30, 27, 27, 63, 63, 24, 24, 24, 60,
			//5
			63, 63, 3, 3, 63, 63, 48, 48, 51, 63, 63,
			//6
			63, 63, 3, 3, 63, 63, 51, 51, 51, 63, 63,
			//7
			63, 63, 48, 24, 24, 12, 12, 6, 6, 3, 3,
			//8
			63, 63, 51, 51, 63, 63, 51, 51, 51, 51, 63,
			//9
			63, 63, 51, 51, 51, 63, 48, 48, 51, 63, 63,
			//%
			51, 51, 24, 24, 12, 12, 6, 6, 51, 51, 0,
			//-
			0, 0, 0, 0, 63, 63, 0, 0, 0, 0, 0,
			//C
			59, 11, 8, 8, 56, 0, 0, 0, 0, 0, 0
	};

Digits6x11::Digits6x11() {
	// TODO Auto-generated constructor stub

}

Digits6x11::~Digits6x11() {
	// TODO Auto-generated destructor stub
}

int Digits6x11::rows(){
	return 11;
}


int Digits6x11::drawSprite(uint8_t index, uint8_t x, uint8_t y,  PicoGraphics *graphics){

	const uint8_t * sprite =  & Digits6x11::DIGITS[index * 11];

	if (graphics != NULL){
		for (uint8_t line=0; line< 11; line++){
			for (uint8_t column = 0; column < 6; column++){
				uint8_t mask = 1 << column;
				uint8_t pixel  = sprite[line] & mask;

				if (pixel > 0){
					Point p(x + column, y + line);
					graphics->pixel(p);
				}
			}
		}
	}
	return 6;
}


int Digits6x11::drawColon(uint8_t x, uint8_t y,  PicoGraphics *graphics){
	if (graphics != NULL){
		Point top1(x + 1, y + 3);
		graphics->pixel(top1);
		Point top2(x + 1, y + 4);
		graphics->pixel(top2);
		Point bot1(x + 1, y + 7);
		graphics->pixel(bot1);
		Point bot2(x + 1, y + 8);
		graphics->pixel(bot2);
	}
	return 3;
}

int Digits6x11::drawDot(uint8_t x, uint8_t y,  PicoGraphics *graphics){
	if (graphics != NULL){
		Point top1(x + 1, y + 9);
		graphics->pixel(top1);
		Point top2(x + 2, y + 9);
		graphics->pixel(top2);
		Point bot1(x + 1, y + 10);
		graphics->pixel(bot1);
		Point bot2(x + 1, y + 10);
		graphics->pixel(bot2);
	}
	return 4;
}


