/***
 * main.cpp -
 * Demonstrate the  TinyJSON Library for parsing a JSON string
 * Jon Durrant
 * 4-Oct-2022
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

#include "tiny-json.h"

#define MAX_TAGS 8

int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    // Variables used in this example.
    json_t pool[MAX_TAGS];
	char buffer[] = "{\"year\": 2023,  \"month\": 9, \"day\": 18, \"hour\": 12, \"minute\": 0, \"second\": 0}";
	size_t bufferLength = sizeof( buffer ) - 1;
	int year, month, day;



	json_t const* parent = json_create( buffer, pool,  MAX_TAGS);

	if ( parent != NULL ){
		json_t const* yearField = json_getProperty( parent, "year" );
		if ( yearField != NULL ){
			if ( json_getType( yearField ) == JSON_INTEGER ){
				year = json_getInteger( yearField );
			}
		}

		json_t const* monthField = json_getProperty( parent, "month" );
		if ( monthField != NULL ){
			if ( json_getType( monthField ) == JSON_INTEGER ){
				month = json_getInteger( monthField );
			}
		}

		json_t const* dayField = json_getProperty( parent, "day" );
		if ( dayField != NULL ){
			if ( json_getType( dayField ) == JSON_INTEGER ){
				day = json_getInteger( dayField );
			}
		}

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



   for (;;){
	   sleep_ms(3000);
   }

    return 0;
}
