
// Mesh has much greater memory requirements, and you may need to limit the
// max message length to prevent wierd crashes
#define RH_MESH_MAX_MESSAGE_LEN 50


#include <NMEAGPS.h>
#include "GPSPort.h"
#include <RHMesh.h>
#include <RH_RF69.h>
#include <SPI.h>




#define LED_RED 10
#define LED_GREEN 12

#define CHURCH_NODE 1 //The base node at camp ΒΣLLIGΣRΣΠCΣ
#define BIKE_NODE 2 //Which network node are we? 2..n for bikes 1..n-1
#define BELLIGERENCE "ΒΣLLIGΣRΣΠCΣ" //handy string to send

// Singleton instance of the radio driver
RH_RF69 driver(8, 7); // Adafruit Feather 32u4

// Class to manage message delivery and receipt, using the driver declared above
RHMesh manager(driver, BIKE_NODE);


void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  if (!manager.init()) {
    digitalWrite(LED_RED, HIGH);
    delay(400);
    digitalWrite(LED_RED, LOW); 
    delay(100);
  }
   digitalWrite(LED_GREEN, LOW);
   digitalWrite(LED_RED, HIGH);
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM

  // If you are using a high power RF69, you *must* set a Tx power in the
  // range 14 to 20 like this:
  driver.setTxPower(20);
  driver.setModemConfig(RH_RF69::GFSK_Rb2Fd5 );
}

uint8_t data[] = BELLIGERENCE;
// Dont put this on the stack:
uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
void loop() {
  digitalWrite(LED_GREEN, HIGH); 
  // Send a message to manager_server
  digitalWrite(LED_GREEN, HIGH);
  if (manager.sendtoWait(data, sizeof(data), CHURCH_NODE)!= RH_ROUTER_ERROR_NONE)
  {
    digitalWrite(LED_RED, LOW);
    delay(400);
    digitalWrite(LED_RED, HIGH); 
    delay(100);
    digitalWrite(LED_RED, LOW);
    delay(400);
    digitalWrite(LED_RED, HIGH); 
    delay(100);
  }
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW); 
  delay(300);
  digitalWrite(LED_RED, HIGH); 
 
}
