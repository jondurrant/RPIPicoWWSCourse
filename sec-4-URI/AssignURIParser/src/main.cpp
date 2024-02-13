/***
 * main.cpp -
 * Jon Durrant
 *
 * Assignment to use URIParser to convert URL into the component parts for a web service call
 * 10-Feb-2024
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include <uriparser/Uri.h>
#include <cstdio>
#include <cstring>

struct End_Point {
    char schema[10];
    char host[20];
    long port;
    char path[20];
};
typedef  struct End_Point End_Point_t;


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

    //Setup
	End_Point_t endPoint;
	const char * url = "http://vmu22a:5000/time";
	UriUriA uri;
	const char * errorPos;

	//Parse
	int res = uriParseSingleUriA(&uri, url, &errorPos);

	if (res == URI_SUCCESS) {
		printf("URI: %s\n", url);

		int len = uri.scheme.afterLast - uri.scheme.first;
		memcpy(endPoint.schema, uri.scheme.first, len);
		endPoint.schema[len] = 0;

		len = uri.hostText.afterLast - uri.hostText.first;
		memcpy(endPoint.host, uri.hostText.first, len);
		endPoint.host[len] = 0;

		len = uri.pathTail->text.afterLast - uri.pathHead->text.first;
		memcpy(endPoint.path, uri.pathHead->text.first, len);
		endPoint.path[len] = 0;

		len = uri.portText.afterLast - uri.portText.first;
		char portStr[8];
		memcpy(portStr, uri.portText.first, len);
		portStr[len]=0;
		endPoint.port = atoi(portStr);

		//Make Schema lower case
		len = strlen(endPoint.schema);
		for (int i=0; i < len; i++){
			endPoint.schema[i] = tolower(endPoint.schema[i]);
		}
		if (endPoint.port < 1){
			if (strcmp(endPoint.schema, "http") == 0){
				endPoint.port = 80;
			} else if (strcmp(endPoint.schema, "https") == 0){
				endPoint.port = 443;
			} else {
				endPoint.port = 0;
			}
		}

		//Print it
		printf("Schema: %s, Host: %s, Port: %ld, Path: %s\n",
				endPoint.schema,
				endPoint.host,
				endPoint.port,
				endPoint.path
		);

	} else {
	  printf("URI %s Failed %d\n", url, res);
	}

	uriFreeUriMembersA(&uri);




   for (;;){
	   sleep_ms(3000);
   }

    return 0;
}
