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

bool Request::get(
		const char * url,
		std::map<std::string, std::string> *query){
	if (pUri != NULL){
		delete(pUri);
	}
	pUri = new uri (url);

	xSettings.result_fn = Request::getCompleteCB;
	xSettings.headers_done_fn = Request::headersCB;
	xSettings.use_proxy=false;

	if (pUri->get_scheme().compare("http") != 0 ){
		printf("Schema not implemented %s\n",
				pUri->get_scheme().c_str()
				);
		return false;
	}

	int serverPort = pUri->get_port();
	if (serverPort == 0){
		serverPort = 80;
	}

	strcpy(pBuffer, pUri->get_path().c_str());
	int length = strlen(pBuffer);

	if (query != NULL){
		pBuffer[length++] = '?';
		std::map<std::string, std::string>::iterator it = query->begin();
		while (it != query->end()){
			int newLen = length + it->first.length() + it->second.length() + 2;
			if (newLen > xBufferLen){

				return false;
			}
			strcpy(&pBuffer[length],  it->first.c_str());
			length +=  it->first.length();
			pBuffer[length++] = '=';

			strcpy(&pBuffer[length],  it->second.c_str());
			length +=  it->second.length();

			it++;
			if ( it != query->end()){
				pBuffer[length++] = '&';
			}
		}
		pBuffer[length] = 0;

	}

	err_t err = httpc_get_file_dns(
		pUri->get_host().c_str(),
		serverPort,
		pBuffer,
		&xSettings,
		Request::payloadCB,
		this,
		NULL);

	if (err != 0){
		return false;
	}
	return true;
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

	if (p->tot_len < xBufferLen){
		pbuf_copy_partial(p, pBuffer, p->tot_len, 0);
	    pBuffer[p->tot_len] = 0;
	} else {
		xStatusCode = REQUEST_BUF_OVERFLOW;
	}

	return ERR_OK;
}

const char * Request::getUriChar(){
	return pUri->to_string().c_str();
}

