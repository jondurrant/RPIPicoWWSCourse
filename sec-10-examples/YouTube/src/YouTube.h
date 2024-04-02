/*
 * YouTube.h
 *
 * YouTube Stats client to get Subscribers and display on Galactic Unicorn
 *
 *  Created on: 20 Mar 2024
 *      Author: jondurrant
 */

#ifndef SEC_10_EXAMPLES_YOUTUBE_SRC_YOUTUBE_H_
#define SEC_10_EXAMPLES_YOUTUBE_SRC_YOUTUBE_H_

#include "pico/stdlib.h"
#include "galactic_unicorn.hpp"
#include "PicoGraphics_ExtRGB888.h"

#define BUF_LEN 2048
#define MAX_TAGS 20

class YouTube {
public:
	YouTube();
	virtual ~YouTube();

	/***
	 * Get Number of Subscribers
	 * @return
	 */
	int getSubs();

	/***
	 * Display the number of subscribers
	 * @param subs
	 */
	void displaySubs(uint subs);

    /***
     * Initialise the display
     */
	void init();


private:
	char xUserBuf[BUF_LEN];

	pimoroni::GalacticUnicorn xGalacticUnicorn;
	PicoGraphics_ExtRGB888 *pGraphics;
	void * pScreenBuf;
};

#endif /* SEC_10_EXAMPLES_YOUTUBE_SRC_YOUTUBE_H_ */
