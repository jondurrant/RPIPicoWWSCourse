/*
 * TimeObserver.cpp
 *
 *  Created on: 26 Feb 2024
 *      Author: jondurrant
 */

#include "TimeObserver.h"
#include "Request.h"
#include "core_json.h"

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
	JSONStatus_t result;
	datetime_t now;
	char * value;
	size_t valueLength;
	char temp[5];

	if (req->getStatusCode() == 200){

			int jsonLen = strlen(req->getPayload());

			result = JSON_Validate(  req->getPayload(), jsonLen );

			if ( result == JSONSuccess ){

				result = JSON_Search(
						req->getPayload(),
						 jsonLen,
						 "year",
						 4,
						 &value,
						 &valueLength);
				if( result == JSONSuccess ){
					memcpy(temp, value, valueLength);
					temp[valueLength] = 0;
					now.year = atoi(temp);
				}

				result = JSON_Search(
						req->getPayload(),
						 jsonLen,
						 "month",
						 5,
						 &value,
						 &valueLength);
				if( result == JSONSuccess ){
					memcpy(temp, value, valueLength);
					temp[valueLength] = 0;
					now.month = atoi(temp);
				}

				result = JSON_Search(
						req->getPayload(),
						 jsonLen,
						 "day",
						 3,
						 &value,
						 &valueLength);
				if( result == JSONSuccess ){
					memcpy(temp, value, valueLength);
					temp[valueLength] = 0;
					now.day = atoi(temp);
				}

				result = JSON_Search(
						req->getPayload(),
						 jsonLen,
						 "hour",
						 4,
						 &value,
						 &valueLength);
				if( result == JSONSuccess ){
					memcpy(temp, value, valueLength);
					temp[valueLength] = 0;
					now.hour = atoi(temp);
				}

				result = JSON_Search(
						req->getPayload(),
						 jsonLen,
						 "minute",
						 6,
						 &value,
						 &valueLength);
				if( result == JSONSuccess ){
					memcpy(temp, value, valueLength);
					temp[valueLength] = 0;
					now.min = atoi(temp);
				}

				result = JSON_Search(
						req->getPayload(),
						 jsonLen,
						 "second",
						 6,
						 &value,
						 &valueLength);
				if( result == JSONSuccess ){
					memcpy(temp, value, valueLength);
					temp[valueLength] = 0;
					now.sec = atoi(temp);
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
