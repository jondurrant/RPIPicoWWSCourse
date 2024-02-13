/***
 * main.cpp -
 * Jon Durrant
 *
 * Assignment to use URILib to convert URL into the component parts for a web service call
 * 10-Feb-2024
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <cstdio>
#include <cstring>

#include <uri.hh>




struct End_Point {
    char schema[10];
    char host[20];
    long port;
    char path[20];
};
typedef  struct End_Point End_Point_t;




int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    //Setup
    End_Point_t endPoint;
    const char * url = "http://vmu22a:5000/time";
    uri *pUri;

    //Convert
	try  {
		pUri = new uri(url);

		printf("URI: %s\n", url);

		strcpy(endPoint.schema,  	pUri->get_scheme().c_str());
		strcpy(endPoint.host,  			pUri->get_host().c_str());
		strcpy(endPoint.path,  			pUri->get_path().c_str());
		endPoint.port =  pUri->get_port();

		//Make Schema lower case
		int schemaLen = strlen(endPoint.schema);
		for (int i=0; i < schemaLen; i++){
			endPoint.schema[i] = tolower(endPoint.schema[i]);
		}
		if (endPoint.port == 0){
			if (strcmp(endPoint.schema, "http") == 0){
				endPoint.port = 80;
			} else if (strcmp(endPoint.schema, "https") == 0){
				endPoint.port = 443;
			}
		}

		//Print it
		printf("Schema: %s, Host: %s, Port: %ld, Path: %s\n",
				endPoint.schema,
				endPoint.host,
				endPoint.port,
				endPoint.path
		);

	}  catch (std::invalid_argument iae) {
		printf("Invalid URI %s\n", url);
	}

	delete(pUri);


   for (;;){
	   sleep_ms(3000);
   }

    return 0;
}
