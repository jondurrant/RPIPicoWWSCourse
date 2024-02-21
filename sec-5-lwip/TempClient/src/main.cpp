/***
 * main.cpp -HTTP GET Request
 *
 * Send temp of the Pico as read from ADC to web service
 * Jon Durrant
 * 20-Feb-2024
 *
 *
 */


#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>

#include <stdio.h>


#include "WifiHelper.h"

#include "lwip/apps/http_client.h"

#include "Request.h"
#include "RequestObserver.h"
#include "hardware/adc.h"



//Test URL
#define TEST_URL "http://vmu22a.local.jondurrant.com:5000/temp"



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
RequestObserver *obs  = NULL;


/***
 * Do a HTTP GET Request
 */
void doRequest(){
	char tempS[10];
	const float conversion_factor = 3.3f / (1 << 12);
	adc_select_input(4);
	float v = (float)adc_read() * conversion_factor;
	float temp = 27.0 - ((v - 0.706)/0.001721);

	sprintf(tempS,"%.1f", temp);

	// Allocate the Request and Observer
	req = new Request(myBuffer, BUF_LEN);
	obs = new RequestObserver();

	//Set observer on the request
	req->setObserver(obs);

	//Issue HTTP Request
	std::map<std::string, std::string> query;
	query["temp"]=tempS;
	if (req->get(TEST_URL, &query)){
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

    //Init ADC
    adc_init();
	adc_set_temp_sensor_enabled(true);

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

	for (;;){
		  cyw43_arch_poll();
	}


    return 0;
}
