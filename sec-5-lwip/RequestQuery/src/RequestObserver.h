/*
 * RequestObserver.h
 *
 * Observer patter for the HTTP Request
 *
 *  Created on: 20 Feb 2024
 *      Author: jondurrant
 */

#ifndef HTTPWS_GETTIMELWIPBM_SRC_REQUESTOBSERVER_H_
#define HTTPWS_GETTIMELWIPBM_SRC_REQUESTOBSERVER_H_

class Request;

class RequestObserver {
public:
	RequestObserver();
	virtual ~RequestObserver();

	/***
	 * Notification of the request being completed.
	 * @param req - The request object that was completed.
	 */
	virtual void requestComplete(Request *req);
};

#endif /* HTTPWS_GETTIMELWIPBM_SRC_REQUESTOBSERVER_H_ */
