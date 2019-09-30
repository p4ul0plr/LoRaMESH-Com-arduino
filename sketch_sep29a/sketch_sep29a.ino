#include <LoRaMESH.h>
#include <SoftwareSerial.h>
#include <stdint.h>
#include <stdbool.h>

#define infra_red_sensor 2
int cont = 0;

/* Defines ----------------------- */
#define CMD_ANALOG  51

/* Payload buffer */
uint8_t bufferPayload[MAX_PAYLOAD_SIZE] = {0};
uint8_t bufferSerial[30] = {0};
uint8_t payloadSize = 0;

/* Local device ID */
uint16_t localId;

/* Remote device ID */
uint16_t remoteId;

/* Local device Unique ID */
uint32_t localUniqueId;

/* Local device Net */
uint16_t localNet;

/* Received command */
uint8_t command;

bool isMaster;

/* Value read on the analog input */
uint16_t AdcIn;

/* SoftwareSerial handles */
SoftwareSerial* hSerialCommands = NULL;

void localRead(){
  if(LocalRead(&localId, &localNet, &localUniqueId) != MESH_OK)
    Serial.print("Couldn't read local ID\n\n");
  else
  {
    Serial.print("Local ID: ");
    Serial.println(localId);
    Serial.print("Local NET: ");
    Serial.println(localNet);
    Serial.print("Local Unique ID: ");
    Serial.println(localUniqueId, HEX);
    Serial.print("\n");
  }
  }

void setup() {
  delay(1000);
  Serial.begin(9600); /* Initialize monitor serial */
  
  /* Initialize SoftwareSerial */
  hSerialCommands = SerialCommandsInit(4, 3, 9600);
//  pinMode /( 3 , INPUT_PULLUP);

  /* Gets the local device ID */
  localRead();
 
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(infra_red_sensor, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int read = digitalRead(infra_red_sensor);
  if (read == 0) {
    cont ++;
    Serial.print("n = ");
    Serial.print(cont);
    Serial.println(" - Mosca!");
    delay(0-500);
  }
  if (hSerialCommands->available()) {
      delay(10);
      int i=0;
      while(hSerialCommands->available()){
        bufferSerial[i] = hSerialCommands -> read();
        Serial.print("Byte: ");
        Serial.print((uint8_t)bufferSerial[i],HEX);
        Serial.print(" ");
        i++;
      }
      Serial.println("");
      if (bufferSerial[2] = 50) {
        bufferPayload[0] = cont;
        PrepareFrameCommand(0, CMD_ANALOG, bufferPayload, 1);
        SendPacket();  
        //Serial.println(AdcIn);
        //localRead();
      }
//      bufferSerial[2] = 0;
//      Serial.print(bufferSerial[0]);
//      Serial.print(bufferSerial[1]); 
//      Serial.print(bufferSerial[2]);
  }
}
