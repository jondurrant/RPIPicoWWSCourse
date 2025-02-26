/***
 * main.cpp - SOCKET for HTTPS HACK
 * Jon Durrant
 * 4-Mar-2024
 *
 *
 */

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "lwip/ip4_addr.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "WifiHelper.h"
#include "TLSTransBlock.h"
#include "wolfssl/ssl.h"

//Check these definitions where added from the makefile
#ifndef WIFI_SSID
#error "WIFI_SSID not defined"
#endif
#ifndef WIFI_PASSWORD
#error "WIFI_PASSWORD not defined"
#endif

#define TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )



void runTimeStats(){
  TaskStatus_t         * pxTaskStatusArray;
  volatile UBaseType_t uxArraySize, x;
  unsigned long        ulTotalRunTime;


  /* Take a snapshot of the number of tasks in case it changes while this
  function is executing. */
  uxArraySize = uxTaskGetNumberOfTasks();
  printf("Number of tasks %d\n", uxArraySize);

  /* Allocate a TaskStatus_t structure for each task.  An array could be
  allocated statically at compile time. */
  pxTaskStatusArray = (TaskStatus_t*) pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

  if (pxTaskStatusArray != NULL){
    /* Generate raw status information about each task. */
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray,
                                       uxArraySize,
                                       &ulTotalRunTime);



    /* For each populated position in the pxTaskStatusArray array,
    format the raw data as human readable ASCII data. */
    for (x = 0; x < uxArraySize; x++){
      printf("Task: %d \t cPri:%d \t bPri:%d \t hw:%d \t%s\n",
             pxTaskStatusArray[x].xTaskNumber,
             pxTaskStatusArray[x].uxCurrentPriority,
             pxTaskStatusArray[x].uxBasePriority,
             pxTaskStatusArray[x].usStackHighWaterMark,
             pxTaskStatusArray[x].pcTaskName
      );
    }


    /* The array is no longer needed, free the memory it consumes. */
    vPortFree(pxTaskStatusArray);
  } else{
    printf("Failed to allocate space for stats\n");
  }

  HeapStats_t heapStats;
  vPortGetHeapStats(&heapStats);
  printf("HEAP avl: %d, blocks %d, alloc: %d, free: %d\n",
         heapStats.xAvailableHeapSpaceInBytes,
         heapStats.xNumberOfFreeBlocks,
         heapStats.xNumberOfSuccessfulAllocations,
         heapStats.xNumberOfSuccessfulFrees
  );

}


/***
 * Do a HTTP GET Request
 */
void doRequest(){
	uint16_t targetPort = 5443;
	char targetHost[]="vmu22a.local.jondurrant.com";
	char message[]="GET /time HTTP/1.1\r\n"
					"Host: localhost\r\n"
					"Connection: close\r\n"
					"\r\n";
	char buf[1024];
	int32_t retVal;

	TLSTransBlock sockTrans;

	if (!sockTrans.transConnect(targetHost, targetPort)){
		printf("Socket Connect Failed\r\n");
		return ;
	}

	retVal = sockTrans.transSend(message, strlen(message));
	if (retVal != strlen(message)){
		printf("Socket Send failed\n\r");
		return ;
	}

	retVal = 1;

	while (retVal >= 0){
		retVal = sockTrans.transRead(buf, sizeof(buf));
		if (retVal > 0){
			sockTrans.debugPrintBuffer("READ:", buf, retVal);
		}
	}

	sockTrans.transClose();

}





void main_task(void* params){

	printf("Main task started\n");


	if (WifiHelper::init()){
	printf("Wifi Controller Initialised\n");
	} else {
	printf("Failed to initialise controller\n");
	return;
	}


	printf("Connecting to WiFi... %s \n", WIFI_SSID);

	if (WifiHelper::join(WIFI_SSID, WIFI_PASSWORD)){
	printf("Connect to Wifi\n");
	}
	else {
	printf("Failed to connect to Wifi \n");
	}

	//Print IP Address
	char ipStr[20];
	WifiHelper::getIPAddressStr(ipStr);
	printf("IP ADDRESS: %s\n", ipStr);


	wolfSSL_Init();


	//Do HTTP Post
	doRequest();

	runTimeStats();



	while (true){

	//runTimeStats();

	vTaskDelay(3000);


	if (!WifiHelper::isJoined()){
	  printf("AP Link is down\n");

	  if (WifiHelper::join(WIFI_SSID, WIFI_PASSWORD)){
		printf("Connect to Wifi\n");
	  } else {
		printf("Failed to connect to Wifi \n");
	  }
	}

	}

}


void vLaunch(void) {
  TaskHandle_t task;

  xTaskCreate(main_task, "MainThread", 3000, NULL, TASK_PRIORITY, &task);

  /* Start the tasks and timer running. */
  vTaskStartScheduler();
}


int main(void) {
  stdio_init_all();
  sleep_ms(2000);
  printf("GO\n");

  /* Configure the hardware ready to run the demo. */
  const char* rtos_name;
  rtos_name = "FreeRTOS";
  printf("Starting %s on core 0:\n", rtos_name);
  vLaunch();

  return 0;
}
