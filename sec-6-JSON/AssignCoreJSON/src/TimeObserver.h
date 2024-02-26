/*
 * TimeObserver.h
 *
 * Observer for a Date Time webservice request.  Will set RTC to the received value
 *
 *  Created on: 26 Feb 2024
 *      Author: jondurrant
 */

#ifndef SEC_6_JSON_ASSIGNTINYJSON_SRC_TIMEOBSERVER_H_
#define SEC_6_JSON_ASSIGNTINYJSON_SRC_TIMEOBSERVER_H_

#include "RequestObserver.h"

class TimeObserver : public RequestObserver {
public:
	TimeObserver();
	virtual ~TimeObserver();

	/***
	 * Notification of the request being completed.
	 * @param req - The request object that was completed.
	 */
	virtual void requestComplete(Request *req);
};

#endif /* SEC_6_JSON_ASSIGNTINYJSON_SRC_TIMEOBSERVER_H_ */
