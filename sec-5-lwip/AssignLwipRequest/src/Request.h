/*
 * Request.h
 *
 * HTTP Request Object
 * To handle a HTTP GET Request
 *
 *  Created on: 20-Feb-2024
 *      Author: jondurrant
 */

#ifndef HTTPWS_GETTIMELWIPBM_SRC_REQUEST_H_
#define HTTPWS_GETTIMELWIPBM_SRC_REQUEST_H_

#include "RequestObserver.h"
#include <cstring>
#include <uri.hh>
#include "lwip/apps/http_client.h"


#define REQUEST_BUF_OVERFLOW -200


class Request {
public:

	/***
	 * Constructor
	 * Client provide storage for the returned payload
	 * @param buffer
	 * @param bufLen
	 */
	Request(char * buffer, uint bufLen);

	virtual ~Request();

	/***
	 * Set observer which will be notified when the request is completed
	 * @param obs - Observer object.
	 */
	void setObserver(RequestObserver *obs);

	/***
	 *  Issue HTTP GET for the given URL
	 * @param url - null terminated string.
	 * @return
	 */
	bool get(const char * url);

	/**
	 * Get the HTTP Status code of the request
	 * @return sucess is normally 200
	 */
	int getStatusCode();

	/***
	 * Return the payload. Should the HTTP GET of not have succeeded then the content of
	 * the payload is undefined.
	 * @return Null terminated char *
	 */
	char * getPayload();

	/***
	 * Get the URL accessed by the request
	 * @return num terminated char *
	 */
	const char * getUriChar();

private:
	char * pBuffer = NULL;
	uint xBufferLen = 0;
	RequestObserver *pObserver = NULL;
	int xStatusCode = -1;
	httpc_connection_t xSettings;

	uri *pUri = NULL;

private:
	/***
	 * Static function called on HTTP GET being compelted
	 * @param arg - pointer to the Request object that issued the request
	 * @param httpc_result - local code result, 0 is sucess
	 * @param rx_content_len - Content length of the payload
	 * @param srv_res - HTTP Status code
	 * @param err - error code
	 */
	static void getCompleteCB(
			void *arg,
			httpc_result_t httpc_result,
            u32_t rx_content_len,
			u32_t srv_res,
			err_t err);

	/***
	 * Static function called when the headers are available
	 * @param connection - HTTP Connection
	 * @param arg - pointer to the Request object that issued the request
	 * @param hdr - The headers
	 * @param hdr_len - Length of headers
	 * @param content_len - length of payload
	 * @return
	 */
	static err_t headersCB(
			httpc_state_t *connection,
			void *arg,
            struct pbuf *hdr,
			u16_t hdr_len,
			u32_t content_len);

	/***
	 * Static Function called when the payload is available
	 * @param arg - pointer to the Request object that issued the request
	 * @param conn - Connection object
	 * @param p - pointer to the payload buffer
	 * @param err - error code for the request
	 * @return
	 */
	static err_t payloadCB(
			void *arg,
			struct altcp_pcb *conn,
	         struct pbuf *p,
			 err_t err);

	/***
	 * Method to handle the completion of the request.
	 * @param arg - pointer to the Request object that issued the request
	 * @param httpc_result - local code result, 0 is sucess
	 * @param rx_content_len - Content length of the payload
	 * @param srv_res - HTTP Status code
	 * @param err - error code
	 */
	void handleComplete(
			void *arg,
			httpc_result_t httpc_result,
	        u32_t rx_content_len,
			u32_t srv_res,
			err_t err);


	/***
	 * Method called when the headers are available
	 * @param connection - HTTP Connection
	 * @param arg - pointer to the Request object that issued the request
	 * @param hdr - The headers
	 * @param hdr_len - Length of headers
	 * @param content_len - length of payload
	 * @return
	 */
	err_t handleHeaders(
			httpc_state_t *connection,
			void *arg,
	         struct pbuf *hdr,
			 u16_t hdr_len,
			 u32_t content_len);

	/***
	 *  Method called when the payload is available
	 * @param arg - pointer to the Request object that issued the request
	 * @param conn - Connection object
	 * @param p - pointer to the payload buffer
	 * @param err - error code for the request
	 * @return
	 */
    err_t handlePayload(
    		void *arg,
			struct altcp_pcb *conn,
		    struct pbuf *p,
			err_t err);

};

#endif /* HTTPWS_GETTIMELWIPBM_SRC_REQUEST_H_ */
