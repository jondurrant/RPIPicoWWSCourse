/*
 * PicoGraphicsExtRGB888.h
 *
 *  Created on: 21 Dec 2023
 *      Author: jondurrant
 */

#ifndef SRC_PICOGRAPHICS_EXTRGB888_H_
#define SRC_PICOGRAPHICS_EXTRGB888_H_

#include "localPicoGraphics.h"

class PicoGraphics_ExtRGB888 : public pimoroni::PicoGraphics_PenRGB888 {
public:
	PicoGraphics_ExtRGB888(uint16_t width, uint16_t height, void *frame_buffer);
	virtual ~PicoGraphics_ExtRGB888();

	uint32_t get_pixel(uint8_t row, uint8_t col);
	uint32_t get_pixel(const pimoroni::Point &p);
	void set_pixel(uint8_t row, uint8_t col, int32_t pix);
	void set_pixel(const pimoroni::Point &p, int32_t pix);

	void roll_down(
			const pimoroni::Point &to,
			const pimoroni::Point &from,
			uint8_t line,
			PicoGraphics_ExtRGB888 *source );


	void roll_up(
			const pimoroni::Point &to,
			const pimoroni::Point &from,
			uint8_t line,
			PicoGraphics_ExtRGB888 *source );

	void roll_left(
			const pimoroni::Point &to,
			const pimoroni::Point &from,
			uint8_t column,
			PicoGraphics_ExtRGB888 *source );

	void roll_right(
			const pimoroni::Point &to,
			const pimoroni::Point &from,
			uint8_t column,
			PicoGraphics_ExtRGB888 *source );

	void wipe_right(
			uint8_t column,
			uint8_t r = 0,
			uint8_t g = 0,
			uint8_t b = 0,
			const pimoroni::Rect *area= NULL );

	void wipe_left(
			uint8_t column,
			uint8_t r = 0,
			uint8_t g = 0,
			uint8_t b = 0,
			const pimoroni::Rect *area= NULL );

	uint32_t paste(
			PicoGraphics_ExtRGB888 *clip,
			pimoroni::Rect *area=NULL,
			pimoroni::Point *from = NULL,
			pimoroni::Point *to = NULL);

	void png(const uint8_t * pPng, int length,
			pimoroni::Rect *area=NULL,
			pimoroni::Point *from = NULL
			);

	void animate(const uint8_t * pPng, int length,
			pimoroni::Rect *bounds,
			uint8_t frame
			);

protected:
	bool need_to_free = false;

};

#endif /* SRC_PICOGRAPHICS_EXTRGB888_H_ */
