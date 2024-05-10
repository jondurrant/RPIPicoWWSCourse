/*
 * http.cpp
 *
 *  Created on: 7 Nov 2023
 *      Author: jondurrant
 */

#include "CppUTest/TestHarness.h"
#include "pico/stdlib.h"
#include "Request.h"

#define BUF_LEN 1024


#define PROTOCOL "http"

TEST_GROUP(HTTPGrp){



};

TEST(HTTPGrp, HTTPget){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		//char url[] = "http://vmu22a.local.jondurrant.com:5000/time";
		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/time";

		CHECK(req.get(url));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPpost){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		//char url[] = "http://vmu22a.local.jondurrant.com:5000/time";
		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/time";

		CHECK(req.post(url));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPquery){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		//char url[] = "http://vmu22a.local.jondurrant.com:5000/time";
		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/temp";

		std::map<std::string, std::string> query;

		query["temp"] = "20.5";

		CHECK(req.get(url, &query));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPpostData){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		//char url[] = "http://vmu22a.local.jondurrant.com:5000/time";
		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/temp";

		std::map<std::string, std::string> query;

		query["temp"] = "20.5";

		CHECK(req.post(url, &query));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPgetAuth){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		//char url[] = "http://vmu22a.local.jondurrant.com:5000/time";
		char url[] = PROTOCOL "://john:hello@" TEST_SERVER ":" TEST_PORT "/user";

		CHECK(req.get(url));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPpostAuth){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		char url[] = PROTOCOL "://john:hello@" TEST_SERVER ":" TEST_PORT "/user";

		CHECK(req.post(url));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPgetUserCred){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);
		char user[] = "john";
		char passwd[] = "hello";

		req.setCredentials(user, passwd);
		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/user";

		CHECK(req.get(url));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPpostUserCred){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);
		char user[] = "john";
		char passwd[] = "hello";

		req.setCredentials(user, passwd);
		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/user";

		CHECK(req.post(url));

		CHECK_EQUAL(200, 	req.getStatusCode());
}

TEST(HTTPGrp, HTTPgetUnknown){
		char userBuf[BUF_LEN];
		Request req((char *)userBuf, BUF_LEN);

		char url[] = PROTOCOL "://" TEST_SERVER ":" TEST_PORT "/fail";

		CHECK(req.post(url));

		CHECK(200 < req.getStatusCode());
}





