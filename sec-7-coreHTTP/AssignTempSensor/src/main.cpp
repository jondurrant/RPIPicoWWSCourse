/***
 * main.cpp - HTTP Post Temperature
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
#include "Request.h"
#include "RequestObserver.h"
#include "hardware/adc.h"



//Check these definitions where added from the makefile
#ifndef WIFI_SSID
#error "WIFI_SSID not defined"
#endif
#ifndef WIFI_PASSWORD
#error "WIFI_PASSWORD not defined"
#endif

#define TEST_URL "http://vmu22a.local.jondurrant.com:5000/temp"

#define TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )
#define BUF_LEN 4096
char myBuffer[BUF_LEN];

Request *req = NULL;
RequestObserver *obs  = NULL;


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
	char tempS[10];
	const float conversion_factor = 3.3f / (1 << 12);
	adc_select_input(4);
	float v = (float)adc_read() * conversion_factor;
	float temp = 27.0 - ((v - 0.706)/0.001721);

	sprintf(tempS,"%.1f", temp);

	printf("Temp read is %s C\n", tempS);

	// Allocate the Request and Observer
	req = new Request(myBuffer, BUF_LEN);
	obs = new RequestObserver;

	//Set observer on the request
	req->setObserver(obs);

	//Issue HTTP Request
	std::map<std::string, std::string> query;
	query["temp"]=tempS;
	if (req->post(TEST_URL, &query)){
		printf("Requested OK\n");
	} else {
		printf("Request Failed\n");
	}

}





void main_task(void* params){

	printf("Main task started\n");

    //Init ADC
    adc_init();
	adc_set_temp_sensor_enabled(true);

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


	//Do HTTP Post
	doRequest();



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
