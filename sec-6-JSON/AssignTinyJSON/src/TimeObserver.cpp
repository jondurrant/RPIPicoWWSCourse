/*
 * TimeObserver.cpp
 *
 *  Created on: 26 Feb 2024
 *      Author: jondurrant
 */

#include "TimeObserver.h"
#include "Request.h"
#include "tiny-json.h"

#include <cstdio>
#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include <time.h>
#include "hardware/rtc.h"

#define MAX_TAGS 8

TimeObserver::TimeObserver() {
	// NOP

}

TimeObserver::~TimeObserver() {
	// NOP
}


void TimeObserver::requestComplete(Request *req){
    json_t pool[MAX_TAGS];
	datetime_t now;

	if (req->getStatusCode() == 200){

			json_t const* parent = json_create( req->getPayload(), pool,  MAX_TAGS);

			if ( parent != NULL ){
				json_t const* yearField = json_getProperty( parent, "year" );
				if ( yearField != NULL ){
					if ( json_getType( yearField ) == JSON_INTEGER ){
						now.year = json_getInteger( yearField );
					}
				}

				json_t const* monthField = json_getProperty( parent, "month" );
				if ( monthField != NULL ){
					if ( json_getType( monthField ) == JSON_INTEGER ){
						now.month = json_getInteger( monthField );
					}
				}

				json_t const* dayField = json_getProperty( parent, "day" );
				if ( dayField != NULL ){
					if ( json_getType( dayField ) == JSON_INTEGER ){
						now.day = json_getInteger( dayField );
					}
				}

				json_t const* hourField = json_getProperty( parent, "hour" );
				if ( hourField != NULL ){
					if ( json_getType( hourField ) == JSON_INTEGER ){
						now.hour = json_getInteger( hourField );
					}
				}

				json_t const* minField = json_getProperty( parent, "minute" );
				if ( minField != NULL ){
					if ( json_getType( minField ) == JSON_INTEGER ){
						now.min = json_getInteger( minField );
					}
				}

				json_t const* secField = json_getProperty( parent, "second" );
				if ( secField != NULL ){
					if ( json_getType( secField ) == JSON_INTEGER ){
						now.sec = json_getInteger( secField );
					}
				}

				now.dotw=0;
				if (rtc_set_datetime	(&now)){
					printf("RTC Set\n");
				} else {
					printf("RTC Reported Invalid DateTime (%u-%u-%u %u:%u:%u)\n",
							now.year,
							now.month,
							now.day,
							now.hour,
							now.min,
							now.sec
							);
				}

			}// Parse JSON
	}  else {
		printf("HTTP Response was not 200  = %d\n", req->getStatusCode());
	}
}
