/***
 * main.cpp -HTTP GET Request
 * Call a TIME Webservice and use the returned value to set the RTC
 * Jon Durrant
 * 20-Feb-2024
 *
 *
 */


#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <stdio.h>
#include "pico/util/datetime.h"
#include <time.h>
#include "hardware/rtc.h"

#include "WifiHelper.h"

#include "lwip/apps/http_client.h"

#include "Request.h"
#include "TimeObserver.h"


#define TIME_URL "http://vmu22a.local.jondurrant.com:5000/time"




//Check these definitions where added from the makefile
#ifndef WIFI_SSID
#error "WIFI_SSID not defined"
#endif
#ifndef WIFI_PASSWORD
#error "WIFI_PASSWORD not defined"
#endif



#define BUF_LEN 4096
char myBuffer[BUF_LEN];

Request *req = NULL;
TimeObserver *obs  = NULL;


/***
 * Do a HTTP GET Request
 */
void doRequest(){

	// Allocate the Request and Observer
	req = new Request(myBuffer, BUF_LEN);
	obs = new TimeObserver();

	//Set observer on the request
	req->setObserver(obs);

	if (req->get(TIME_URL)){
		printf("Requested OK\n");
	} else {
		printf("Request Failed\n");
	}

}


/***
 * Main function
 * @return
 */
int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    datetime_t now = {
    		.year=2000,
			.month=1,
			.day=1,
			.hour=9,
			.min=0,
			.sec=0
    };


    rtc_init ();
    if(!rtc_set_datetime (&now)){
    	printf("RTC Initial value failed\n");
    }

    //Connect to WIFI
    if (WifiHelper::init()){
		printf("Wifi Controller Initialised\n");
	} else {
		printf("Failed to initialise controller\n");
		return 1;
	}
	printf("Connecting to WiFi... %s \n", WIFI_SSID);
	if (WifiHelper::join(WIFI_SSID, WIFI_PASSWORD)){
		printf("Connect to Wifi\n");
	} else {
		printf("Failed to connect to Wifi \n");
	}

	//Print IP Address
	char ipStr[20];
	WifiHelper::getIPAddressStr(ipStr);
	printf("IP ADDRESS: %s\n", ipStr);


	//do http request
	doRequest();

	int sec = 0;
	for (;;){
		  cyw43_arch_poll();

		  rtc_get_datetime(&now);
		  if (sec != now.sec){
			  sec = now.sec;
			  printf("%u-%u-%u %u:%u:%u\n",
						now.year,
						now.month,
						now.day,
						now.hour,
						now.min,
						now.sec
						);
		  }
	}


    return 0;
}
