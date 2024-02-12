/***
 * main.cpp -
 * Jon Durrant
 * 4-Oct-2022
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <iostream>

#include <uri.hh>

#define URIS_COUNT			12

void decomURI(const char * const  uriStr){
	uri *pUri;

	try  {
		pUri = new uri(uriStr);

		printf("URI: %s\n", uriStr);

		std::cout << "\tSchema: ";
		std::cout << pUri->get_scheme();
		std::cout << "\n\tUser: ";
		std::cout <<  pUri->get_username();
		std::cout << "\n\tPassword: ";
		std::cout << pUri->get_password();
		std::cout << "\n\tHost: ";
		std::cout << pUri->get_host();
		std::cout << "\n\tPort: ";
		std::cout <<  pUri->get_port();
		std::cout << "\n\tPath:";
		std::cout << pUri->get_path();
		std::cout << "\n\tQuery: ";
		std::cout << pUri->get_query();
		std::cout << "\n\tFragment: ";
		std::cout << pUri->get_fragment();
		std::cout << "\n";
	}  catch (std::invalid_argument iae) {
		printf("Invalid URI %s\n", uriStr);
	}

	delete(pUri);
}


int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    const char * const uriList[URIS_COUNT] = {
    		"http://drjonea.co.uk",
			"https://drjonea.co.uk",
    		"http://drjonea.co.uk:80/",
    		"http://jon:pass@drjonea.co.uk/",
    		"http://drjonea.co.uk/home/foo/index.html",
			"http://drjonea.co.uk/home/foo/index.html#bar",
			"http://drjonea.co.uk/cmd?do=flash",
			"http://192.168.1.1/",
			"http://192.168.1.1/home/index.html",
    		"http://jon:pass@drjonea.co.uk:80/cmd?do=flash&speed=50",
			"Hello World",
			"mqtt://foo:jon@mqtt.com/"
    };


    for (int i=0; i < URIS_COUNT; i++){
    	decomURI(uriList[i]);
    }


   for (;;){
	   sleep_ms(3000);
   }

    return 0;
}
