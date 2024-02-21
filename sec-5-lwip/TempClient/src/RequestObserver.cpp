/*
 * RequestObserver.h
 *
 * Observer patter for the HTTP Request
 *
 *  Created on: 20 Feb 2024
 *      Author: jondurrant
 */

#include "RequestObserver.h"
#include "Request.h"
#include <cstdio>

RequestObserver::RequestObserver() {
	// TODO Auto-generated constructor stub

}

RequestObserver::~RequestObserver() {
	// TODO Auto-generated destructor stub
}

void RequestObserver::requestComplete(Request *req){
	printf("Request %s returned status %d\n",
			req->getUriChar(),
			req->getStatusCode()
			);
	if (req->getStatusCode() == 200){
		printf("%s\n", req->getPayload());
	}
}
