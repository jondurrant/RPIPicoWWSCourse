/*
 * YouTube.cpp
 *
 *  Created on: 20 Mar 2024
 *      Author: jondurrant
 */

#include "YouTube.h"
#include "Request.h"
#include <cstdio>
#include "tiny-json.h"

#include "FreeRTOS.h"
#include "Digits6x11.h"

YouTube::YouTube() {
	pScreenBuf = pvPortMalloc (
				PicoGraphics_ExtRGB888::buffer_size(
						xGalacticUnicorn.WIDTH,
						xGalacticUnicorn.HEIGHT));

		if (pScreenBuf != NULL){
			pGraphics = new PicoGraphics_ExtRGB888(
					xGalacticUnicorn.WIDTH,
					xGalacticUnicorn.HEIGHT,
					pScreenBuf);
		} else {
			pGraphics = NULL;
			printf("ERROR: FAILED TO ALLOCATE\n");
		}
}

YouTube::~YouTube() {
	delete(pGraphics);
	vPortFree(pScreenBuf);
}


void YouTube::init(){
	xGalacticUnicorn.init();
	pGraphics->set_pen(10, 0, 0);
	pGraphics->clear();
	xGalacticUnicorn.update(pGraphics);
}


/***
 * Get Number of Subscribers
 * @return
 */
int YouTube::getSubs(){

	Request req((char *)xUserBuf, BUF_LEN);
	char json[BUF_LEN];
	 json_t pool[MAX_TAGS];
	bool res;
	char url[] = "https://youtube.googleapis.com/youtube/v3/channels";

	std::map<std::string, std::string> query;

	query["id"]="UCMX47a_aT7tujbsiD5iD70Q";
	query["key"]=YOUTUBEAPIKEY;
	query["part"]="statistics";
	res = req.get(url, &query);
	if ( res ){
		res = (req.getStatusCode() == 200);
	}
	if (res){
		printf("WS: %.*s\n", req.getPayloadLen(), req.getPayload());
		memcpy(json, req.getPayload(), req.getPayloadLen());
		json[req.getPayloadLen()] = 0;
		json_t const* parent = json_create(
				json,
				pool,
				MAX_TAGS);
		if ( parent != NULL ){
			json_t const* items = json_getProperty( parent, "items" );
			if (items != NULL){
				items = json_getChild( items);
				if (items != NULL){
					json_t const* stats = json_getProperty( items, "statistics" );
					if (stats != NULL){
						json_t const* statsCount = json_getProperty( stats, "subscriberCount" );
						if (statsCount != NULL){
							if ( json_getType( statsCount ) == JSON_TEXT ){
								int count = atoi(json_getValue( statsCount ));
								return count;
							}
						}
					}
				}
			}
		}
	} else {
		printf("WSp failed %d\n", req.getStatusCode());
	}
	return 0;
}

/***
 * Display the number of subscribers
 * @param subs
 */
void YouTube::displaySubs(uint subs){
	Digits6x11 digits;
	pGraphics->set_pen(0, 0, 0);
	pGraphics->clear();

	pGraphics->set_pen(0x80, 0, 0);
	Rect yt(0,0, 15, 11);
	pGraphics->rectangle(yt);
	pGraphics->set_pen(0xff, 0xff, 0xff);
	pGraphics->triangle({3,2}, {3,8}, {11, 5});
/*
	pGraphics->pixel({4,3});
	pGraphics->set_pen(0x00, 0xff, 0x00);
	pGraphics->pixel({4,7});
	pGraphics->set_pen(0x00, 0x00, 0xff);
	pGraphics->pixel({10,5});
*/
	pGraphics->set_pen(0xff, 0xff, 0xff);

	float f =  (float)subs;
	digits.drawFloat(
			f, 17, 0,
			pGraphics,
			false,  false,
			5, 0
			);
	xGalacticUnicorn.update(pGraphics);

}
