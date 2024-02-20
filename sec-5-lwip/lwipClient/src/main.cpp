/***
 * main.cpp - LWIP Client for a HTTP connection
 * Jon Durrant
 * 19-Feb-2024
 *
 *
 */

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "lwip/ip4_addr.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"

#include <stdio.h>
#include "WifiHelper.h"



#define SERVER_HOST "192.168.22.128" //"vmu22a.local.jondurrant.com"
#define SERVER_PORT 5000
#define RELATIVE_URL "/time"

//Check these definitions where added from the makefile
#ifndef WIFI_SSID
#error "WIFI_SSID not defined"
#endif
#ifndef WIFI_PASSWORD
#error "WIFI_PASSWORD not defined"
#endif


char myBuff[4096];


/***
 * Call Back on completion of the HTTP Get
 * @param arg - passed into the get_file function
 * @param httpc_result - 0 if sucessful
 * @param rx_content_len - Conent length
 * @param srv_res - Sucess would be 200
 * @param err
 */
void result(
		void *arg,
		httpc_result_t httpc_result,
        u32_t rx_content_len,
		u32_t srv_res,
		err_t err)

{
    printf("\ntransfer complete\n");
    printf("local result: %d\n", httpc_result);
    printf("http result: %d\n", srv_res);
}

/***
 * Call Back when the header is available for the
 * @param connection - Connection. Can be used to close it early
 * @param arg - passed into the get_file function
 * @param hdr - The header buffer
 * @param hdr_len - Length of the header
 * @param content_len - Length of the content that will be sent
 * @return ERR_OK if OK. Anything else causes the connection to be terminated
 */
err_t headers(httpc_state_t *connection, void *arg,
              struct pbuf *hdr, u16_t hdr_len, u32_t content_len)
{
    printf("\nHeaders Recieved\n");
    printf("content length: %d\n", content_len);
    printf("Header length: %d\n", hdr_len);
    pbuf_copy_partial(hdr, myBuff, hdr->tot_len, 0);
    printf("Headers: \n");
    printf("%s", myBuff);
    return ERR_OK;
}

/***
 * Call back on  Payload being available
 * @param arg - passed into the get_file function
 * @param conn - the connection
 * @param p - The body or payload
 * @param err - error code if something went wrong
 * @return ERR_OK if ok.
 */
err_t payload(void *arg, struct altcp_pcb *conn,
           struct pbuf *p, err_t err)
{
    printf("Payload\n");
    pbuf_copy_partial(p, myBuff, p->tot_len, 0);
    printf("Length: %d\n", p->tot_len);
    myBuff[p->tot_len] = 0;
    printf("%s\n", myBuff);
    printf("END of payload\n");
    return ERR_OK;
}


int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

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


	//Print MAC Address
	char macStr[20];
	WifiHelper::getMACAddressStr(macStr);
	printf("MAC ADDRESS: %s\n", macStr);

	//Print IP Address
	char ipStr[20];
	WifiHelper::getIPAddressStr(ipStr);
	printf("IP ADDRESS: %s\n", ipStr);


	//Print Net Mask
	WifiHelper::getNetMaskStr(ipStr);
	printf("Net Mask: %s\n", ipStr);

	//Print Gateway
	WifiHelper::getGWAddressStr(ipStr);
	printf("Gateway: %s\n", ipStr);


	//HTTP Request
	httpc_connection_t settings;
	settings.result_fn = result;
	settings.headers_done_fn = headers;
	err_t err = httpc_get_file_dns(
		SERVER_HOST,
		SERVER_PORT,
		RELATIVE_URL,
		&settings,
		payload,
		NULL,
		NULL);


	for (;;) {

		cyw43_arch_poll();
	}

    return 0;
}
