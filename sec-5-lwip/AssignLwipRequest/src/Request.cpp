 /* Request.h
 *
 * HTTP Request Object
 * To handle a HTTP GET Request
 *
 *  Created on: 20-Feb-2024
 *      Author: jondurrant
 */

#include "Request.h"

Request::Request(char * buffer, uint bufLen) {
	pBuffer = (char *) buffer;
	xBufferLen = bufLen;
}

Request::~Request() {
	if (pUri != NULL){
		delete(pUri);
	}
}

void Request::setObserver(RequestObserver *obs){
	pObserver = obs;
}

bool Request::get(const char * url){

	//MISSING CODE
	return false;
}

int Request::getStatusCode(){
	return xStatusCode;
}

char * Request::getPayload(){
	return pBuffer;
}

void Request::getCompleteCB(
		void *arg,
		httpc_result_t httpc_result,
		u32_t rx_content_len,
		u32_t srv_res,
		err_t err){

	Request *self = (Request *)arg;
	self->handleComplete(arg, httpc_result, rx_content_len, srv_res, err);

}

err_t Request::headersCB(
		httpc_state_t *connection,
		void *arg,
        struct pbuf *hdr,
		u16_t hdr_len,
		u32_t content_len){

	Request *self = (Request *)arg;
	return self->handleHeaders(connection,  arg, hdr,  hdr_len,  content_len);
}

err_t Request::payloadCB(
		void *arg,
		struct altcp_pcb *conn,
	    struct pbuf *p, err_t err){

	Request *self = (Request *)arg;
	return self->handlePayload(arg,   conn, p,  err);
}

void Request::handleComplete(
		void *arg,
		httpc_result_t httpc_result,
	    u32_t rx_content_len,
		u32_t srv_res,
		err_t err){

	xStatusCode = srv_res;
	if (httpc_result == HTTPC_RESULT_ERR_TIMEOUT){
		xStatusCode = -1;
	}
	if (pObserver != NULL){
		pObserver->requestComplete(this);
	}
}

err_t Request::handleHeaders(
		httpc_state_t *connection,
		void *arg,
		struct pbuf *hdr,
		u16_t hdr_len,
		u32_t content_len){

	if (content_len <= xBufferLen){
		return ERR_OK;
	} else {
		return  ERR_BUF;
	}
}

err_t Request::handlePayload(
		void *arg,
		struct altcp_pcb *conn,
		struct pbuf *p, err_t err){

	//MISSING CODE
	return ERR_OK;
}

const char * Request::getUriChar(){
	return pUri->to_string().c_str();
}


