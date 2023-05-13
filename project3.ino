#include "scheduler.h"

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;

int WCET1 = 280; // 40;
int WCET2 = 120; // 60;
int WCET3 = 40; //80;


// the loop function runs over and over again forever
void loop() {}

static void nonCSFunc(unsigned long delayMs)
{

  TickType_t xTickCountStart = xTaskGetTickCount();
  TickType_t xTickCountEnd = xTickCountStart;
  TickType_t xTickCountInterval = pdMS_TO_TICKS(delayMs - 7);

  while ((xTickCountEnd - xTickCountStart) < xTickCountInterval) {
    for (int i = 0; i < 1000; i++) {}
    xTickCountEnd = xTaskGetTickCount();
  }
}

static void testFunc1( void *pvParameters )
{
	(void) pvParameters;
  nonCSFunc(WCET1); //280

}

static void testFunc2( void *pvParameters )
{ 
	(void) pvParameters;	
  nonCSFunc(WCET2); //120

}

static void testFunc3( void *pvParameters )
{
	(void) pvParameters; 
  nonCSFunc(WCET3); //40
}

int main( void )
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
	char c1 = 'a';
	char c2 = 'b';			
	char c3 = 'c';
	char c4 = 'd';

	vSchedulerInit();

  // // TASK SET 1
  //Uncomment below 3 lines for task set 1

	// vSchedulerPeriodicTaskCreate(testFunc1, "t1", configMINIMAL_STACK_SIZE, &c1, 1, &xHandle1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(100), pdMS_TO_TICKS(40), pdMS_TO_TICKS(80));
	// vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 2, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(200), pdMS_TO_TICKS(60), pdMS_TO_TICKS(160));
  // vSchedulerPeriodicTaskCreate(testFunc3, "t3", configMINIMAL_STACK_SIZE, &c3, 3, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(300), pdMS_TO_TICKS(80), pdMS_TO_TICKS(220));

  // // TASK SET 2
  //Uncomment below 3 lines for task set 2

	vSchedulerPeriodicTaskCreate(testFunc1, "t1", configMINIMAL_STACK_SIZE, &c1, 1, &xHandle1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(710), pdMS_TO_TICKS(280), pdMS_TO_TICKS(710));
	vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 2, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(410), pdMS_TO_TICKS(120), pdMS_TO_TICKS(410));
  vSchedulerPeriodicTaskCreate(testFunc3, "t3", configMINIMAL_STACK_SIZE, &c3, 3, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(210), pdMS_TO_TICKS(40), pdMS_TO_TICKS(210));

	vSchedulerStart();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached. */
	
	for( ;; );
}

