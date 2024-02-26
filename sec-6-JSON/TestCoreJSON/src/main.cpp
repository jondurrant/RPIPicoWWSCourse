/***
 * main.cpp -
 * Demonstrate the FreeRTOS CoreJSON Library for parsing a JSON string
 * Jon Durrant
 * 4-Oct-2022
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

#include "core_json.h"



int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    // Variables used in this example.
	JSONStatus_t result;
	char buffer[] = "{\"year\": 2023,  \"month\": 9, \"day\": 18, \"hour\": 12, \"minute\": 0, \"second\": 0}";
	size_t bufferLength = sizeof( buffer ) - 1;
	char queryYear[] = "year";
	char queryMonth[] = "month";
	char queryDay[] = "day";
	char * value;
	size_t valueLength;

	int year, month, day;
	char temp[5];

	// Calling JSON_Validate() is not necessary if the document is guaranteed to be valid.
	result = JSON_Validate( buffer, bufferLength );

	if( result == JSONSuccess ) {
		result = JSON_Search( buffer, bufferLength, queryYear, strlen(queryYear),
							  &value, &valueLength );
		if( result == JSONSuccess ){
			memcpy(temp, value, valueLength);
			temp[valueLength] = 0;
			year = atoi(temp);
		}


		result = JSON_Search( buffer, bufferLength, queryMonth, strlen(queryMonth),
							  &value, &valueLength );
		if( result == JSONSuccess ){
			memcpy(temp, value, valueLength);
			temp[valueLength] = 0;
			month = atoi(temp);
		}

		result = JSON_Search( buffer, bufferLength, queryDay, strlen(queryDay),
							  &value, &valueLength );
		if( result == JSONSuccess ){
			memcpy(temp, value, valueLength);
			temp[valueLength] = 0;
			day = atoi(temp);
		}

	printf("DATE: %d-", year);
	if (month < 10){
		printf("0");
	}
	printf("%d-", month);
	if (day < 10){
		printf("0");
	}
	printf("%d\n", day);


	} else {
		printf("JSON Parse failed %d\n", result);
	}




   for (;;){
	   sleep_ms(3000);
   }

    return 0;
}
