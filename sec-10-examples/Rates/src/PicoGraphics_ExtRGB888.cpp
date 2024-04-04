/*
 * PicoGraphicsExtRGB888.cpp
 *
 *  Created on: 21 Dec 2023
 *      Author: jondurrant
 */

#include "PicoGraphics_ExtRGB888.h"
using namespace pimoroni;
#include <spng.h>
#include "FreeRTOS.h"



PicoGraphics_ExtRGB888::PicoGraphics_ExtRGB888(uint16_t width, uint16_t height, void *frame_buffer)
  : PicoGraphics_PenRGB888(width, height, frame_buffer) {
	if (frame_buffer == NULL){
		need_to_free = true;
	}
}

PicoGraphics_ExtRGB888::~PicoGraphics_ExtRGB888() {
	if (need_to_free){
		delete[]((uint8_t *)frame_buffer);
	}
}


uint32_t PicoGraphics_ExtRGB888::get_pixel(uint8_t row, uint8_t col){
	if  ((row >= bounds.h) || (col >= bounds.w)){
		return 0;
	}
	if(pen_type == PicoGraphics::PEN_RGB888) {
				uint32_t *p = (uint32_t *)frame_buffer;
				uint32_t pix = p[row * bounds.w +col];
				return pix;
		}
	 return 0;
}

uint32_t PicoGraphics_ExtRGB888::get_pixel(const pimoroni::Point &p){
	return get_pixel(p.y, p.x);
}

void PicoGraphics_ExtRGB888::set_pixel(uint8_t row, uint8_t col, int32_t pix){
	if  ((row >= bounds.h) || (col >= bounds.w)){
			return ;
	}
	if(pen_type == PicoGraphics::PEN_RGB888) {
			uint32_t *p = (uint32_t *)frame_buffer;
			p[row * bounds.w +col] = pix;
	}
}

void PicoGraphics_ExtRGB888::set_pixel(
		const Point &p,
		int32_t pix){
	set_pixel(p.y, p.x, pix);
}


void PicoGraphics_ExtRGB888::roll_down(
		const Point &to,
		const Point &from,
		uint8_t line,
		PicoGraphics_ExtRGB888 *source ){
	uint8_t width 	= source->bounds.w;
	uint8_t height	= source->bounds.h;
	if (line >= height){
		return;
	}


	for (int row =  height -2; row >= 0 ; row --){
		   for (int col = to.x+width -1; col >= to.x; col--){
			   uint32_t pix = get_pixel(row +to.y, col);
			   set_pixel(row + 1 + to.y, col, pix);
		   }
	   }
	   for (int col = 0; col < width; col++){
		   uint32_t pix = source->get_pixel(line + from.y, col + from.x);
		   set_pixel(to.y, col + to.x,  pix);
	   }
}


void PicoGraphics_ExtRGB888::roll_up(
		const Point &to,
		const Point &from,
		uint8_t line,
		PicoGraphics_ExtRGB888 *source ){
	uint8_t width 	= source->bounds.w;
	uint8_t height	= source->bounds.h;
	if (line >= height){
		return;
	}

	for (int row =  1 ; row < height ; row ++){
		   for (int col = to.x+width -1; col >= to.x; col--){
			   uint32_t pix = get_pixel(row +to.y, col);
			   set_pixel(row - 1 + to.y, col, pix);
		   }
	   }
	   for (int col = 0; col < width; col++){
		   uint32_t pix = source->get_pixel( from.y + height - line -1, col + from.x);
		   set_pixel(to.y + height - 1, col + to.x,  pix);
	   }
}

void PicoGraphics_ExtRGB888::roll_left(
		const Point &to,
		const Point &from,
		uint8_t column,
		PicoGraphics_ExtRGB888 *source ){
	uint8_t width 	= source->bounds.w;
	uint8_t height	= source->bounds.h;

	//printf("LEFT(%u) to(%u, %u) from(%u, %u) clip(%u, %u)\n",
	//		column, to.y, to.x, from.y, from.x, width, height);

	if (column >= width){
		printf("OUT OF BOUNDS %u >= %u\n", column, width);
		return;
	}

	for (int col =  1;  col <= width; col ++){
		int c = col + to.x;
		   for (int row =0; row < height; row++){
			   int r = row +to.y;
			   uint32_t pix = get_pixel(r,  c);
			   set_pixel(r, c -1, pix);
		   }
	   }

	  for (int row =0; row < height; row++){
		  uint32_t pix = source->get_pixel( from.y + row, column + from.x);
		   set_pixel(to.y + row, width -1 + to.x,  pix);
	   }

}


void PicoGraphics_ExtRGB888::roll_right(
		const Point &to,
		const Point &from,
		uint8_t column,
		PicoGraphics_ExtRGB888 *source ){
	uint8_t width 	= source->bounds.w;
	uint8_t height	= source->bounds.h;

	//printf("LEFT(%u) to(%u, %u) from(%u, %u) clip(%u, %u)\n",
	//		column, to.y, to.x, from.y, from.x, width, height);

	if (column >= width){
		printf("OUT OF BOUNDS %u >= %u\n", column, width);
		return;
	}

	for (int col =  width -1;  col >0; col --){
		int c = col + to.x;
		   for (int row =0; row < height; row++){
			   int r = row +to.y;
			   uint32_t pix = get_pixel(r,  c - 1);
			   set_pixel(r, c , pix);
		   }
	   }


	  for (int row =0; row < height; row++){
		  uint32_t pix = source->get_pixel( from.y + row, column + from.x);
		   set_pixel(to.y + row, 0 + to.x,  pix);
	   }

}


void PicoGraphics_ExtRGB888::wipe_right(
		uint8_t column,
		uint8_t r,
		uint8_t g,
		uint8_t b,
		const pimoroni::Rect *area){

	const Rect *pArea = area;
	if (area == NULL){
		pArea = & bounds;
	}

	uint8_t width 	= pArea->w;
	uint8_t height	= pArea->h;

	if (column >= width ){
		set_pen(0,0,0);
		rectangle(*pArea);
		return;
	}

	set_pen(r,g,b);
	for (int row = 0; row < height; row++){
		Point p(column + pArea->x, row + pArea->y);
		//set_pixel(p, 0x101010);
		PicoGraphics_PenRGB888::set_pixel(p);
	}

	if (column > 0){
		Rect wipeRect(pArea->x, pArea->y, column, height);
		set_pen(0,0,0);
		rectangle(wipeRect);
	}
}

void PicoGraphics_ExtRGB888::wipe_left(
		uint8_t column,
		uint8_t r,
		uint8_t g,
		uint8_t b,
		const pimoroni::Rect *area){

	const Rect *pArea = area;
	if (area == NULL){
		pArea = & bounds;
	}

	uint8_t width 	= pArea->w;
	uint8_t height	= pArea->h;

	if (column >= width ){
		set_pen(0,0,0);
		rectangle(*pArea);
		return;
	}

	uint8_t c = pArea->w - 1 - column;
	printf("left c = %u \n", c);

	set_pen(r,g,b);
	for (int row = 0; row < height; row++){
		Point p(c + pArea->x, row + pArea->y);
		PicoGraphics_PenRGB888::set_pixel(p);
	}

	if (column > 0){
		uint8_t x = (pArea->x + width -1 ) - column;
		Rect wipeRect(x + 1, pArea->y, column, height);
		printf("Wipe(%u, %u, %u, %u)\n", wipeRect.x, wipeRect.y, wipeRect.w, wipeRect.h);
		set_pen(0,0,0);
		rectangle(wipeRect);
	}
}

uint32_t PicoGraphics_ExtRGB888::paste(
		PicoGraphics_ExtRGB888 *clip,
		pimoroni::Rect *area,
		pimoroni::Point *from,
		pimoroni::Point *to){

	uint32_t res = 0;

	const Rect *pArea = area;
	if (area == NULL){
		pArea = & bounds;
	}

	Point org(0,0);
	const Point *pFrom = from;
	if (pFrom == NULL){
		pFrom = &org;
	}

	const Point *pTo = to;
	if (pTo == NULL){
		pTo = &org;
	}

	uint8_t width 	= pArea->w;
	if (bounds.w < width){
		width = bounds.w;
	}
	if (clip->bounds.w < width){
		width = clip->bounds.w;
	}
	uint8_t height	= pArea->h;
	if (bounds.h < height){
		height = bounds.h;
	}
	if (clip->bounds.h < height){
		height = clip->bounds.h;
	}

	//DEBUG
	/*
	printf("Paste to Mask(%u, %u, %u, %u) TO (%d, %d) From(%d, %d))\n",
			pArea->x, pArea->y, width, height,
			pTo->x, pTo->y,
			pFrom->x, pFrom->y);
	*/


	for (uint8_t x = 0; x < width; x++){
		for (uint8_t y=0; y < height; y++){
			uint32_t pix = clip->get_pixel(
					y + pFrom->y,
					x + pFrom->x);
			if (	((y + pTo->y + pArea->y) <( pArea->h + pArea->y)) &&
					((x + pTo->x + pArea->x) < (pArea->w + pArea->x))
					){
					set_pixel(
							y +  pTo->y + pArea->y, //Row
							x +  pTo->x + pArea->x, //Column
							pix);
					/*DEBUG
					printf("From(%d, %d) To(%d, %d) %X\n",
							x + pFrom->x,
							y + pFrom->y,
							x +  pTo->x + pArea->x,
							y +  pTo->y + pArea->y,
							pix
							);
						*/
					res++;
				} else {
					//printf("CLIP\n");
				}
		}
	}

	return res;
}

void PicoGraphics_ExtRGB888::png(const uint8_t * pPng, int length,
		pimoroni::Rect *area,
		pimoroni::Point *from
		){
		Rect *pArea;
		Point org(0,0);
		Point*pOffset = &org;
		size_t size;
		uint32_t width, height;
		uint32_t *out = NULL;
		struct spng_ihdr ihdr;

		if (area == NULL){
			pArea = &bounds;
		} else {
			pArea = area;
		}
		if (from != NULL){
			pOffset = from;
		}

		//spng_ctx *ctx = spng_ctx_new(0);
		struct spng_alloc spngAlloc;
		spngAlloc.malloc_fn = pvPortMalloc;
	    spngAlloc.realloc_fn = pvPortRealloc;
	    spngAlloc.calloc_fn = pvPortCalloc;
	     spngAlloc.free_fn = vPortFree;

		spng_ctx *ctx = spng_ctx_new2(&spngAlloc, 0);
		spng_set_png_buffer(ctx, pPng, length);

		spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &size);
		printf("PNG Out Buf size is %d\n", size);
		//out = (uint32_t *)malloc(size);
		out = (uint32_t *) pvPortMalloc(size);

		spng_get_ihdr(ctx, &ihdr);
		width = ihdr.width;
		height=ihdr.height;
		printf("PNG (%u, %u)\n", width, height);

		int res = spng_decode_image(ctx, out, size, SPNG_FMT_RGBA8, 0);

		printf("Decod complete = %d  %s\n", res, spng_strerror(res));


		for (int32_t y=0; y < height; y++){
			for (int32_t x=0; x<width; x++){
				//printf("Is (%u, %u) in (%d, %d, %d, %d)\n", x, y, pArea->x, pArea->y, pArea->w, pArea->y);
				//Mask the data
				if (   (y >= pArea->y)  &&
						(y < pArea->y + pArea->h) &&
						(x >= pArea->x) &&
						(x < pArea->x + pArea->w)
						){
								//Offset to pull from
							    if (( x + pOffset->x < width) &&
							    	 ( y + pOffset->y < height)
									 ){
										uint32_t index = x + pOffset->x + (y + pOffset->y) * width;
										//printf("index %d = %d + %d + ( %d + %d) % %d\n",
										//		index, x , pOffset->x , y , pOffset->y , width
										//		);
										printf("%d = %X\n", index, out[index]);
										uint8_t r = (out[index] & 0x000000FF) ;
										uint8_t g = (out[index] & 0x0000FF00) >> 8;
										uint8_t b = (out[index] & 0x00FF0000) >> 16;
										set_pen(r, g, b);
										pixel({x,y});
										printf("Set %d,%d = %X %X %X\n", x,y, r,g,b);
							    }
				}
			}
		}
		spng_ctx_free(ctx);
		//free(out);
		vPortFree(out);

}


void PicoGraphics_ExtRGB888::animate(const uint8_t * pPng, int length,
		pimoroni::Rect *bounds,
		uint8_t frame
		){
	Rect mask;

	Point offset;
	offset.y = 0;
	offset.x = (bounds->w * frame);
	png(pPng, length, bounds, &offset);
}

