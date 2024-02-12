/***
 * main.cpp -
 * Jon Durrant
 *
 * Test of the URI Parser library
 * 4-Feb-2024
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include <uriparser/Uri.h>

#define URIS_COUNT			12

void decomURI(const char * const  uriStr){
	UriUriA uri;
	const char * errorPos;

	int res = uriParseSingleUriA(&uri, uriStr, &errorPos);

	if (res == URI_SUCCESS) {
		printf("URI: %s\n", uriStr);

		int len = uri.scheme.afterLast - uri.scheme.first;
		printf("\tSchema: %.*s\n", len, uri.scheme.first);
		len = uri.userInfo.afterLast - uri.userInfo.first;
		printf("\tuserinfo: %.*s\n", len, uri.userInfo.first);
		len = uri.hostText.afterLast - uri.hostText.first;
		printf("\thostText: %.*s\n",len,  uri.hostText.first);
		len = uri.portText.afterLast - uri.portText.first;
		printf("\tportText: %.*s\n",len,  uri.portText.first);
		len = uri.query.afterLast - uri.query.first;
		printf("\tquery: %.*s\n",len,  uri.query.first);
		 len = uri.fragment.afterLast - uri.fragment.first;
		printf("\tfragment: %.*s\n",len,  uri.fragment.first);

		len = uri.pathTail->text.afterLast - uri.pathHead->text.first;
		printf("\tpathHead: %.*s\n",len,  uri.pathHead->text.first);

	} else {
	  printf("URI %s Failed %d\n", uriStr, res);
	}

	uriFreeUriMembersA(&uri);
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
