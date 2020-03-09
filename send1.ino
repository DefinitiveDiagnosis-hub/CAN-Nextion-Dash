#include <mcp_can.h>
#include <SPI.h>
//#define CAN0_INT 2

MCP_CAN CAN0(10);

//RPM
int sensorPin0 = A0;
int sensorValue0 = 0;
int sensor2Pin0 = A1;
int sensor2Value0 = 0;
int rpmA = 0;
int rpmC = 0;
int rpmD = 0;
int rpmE = 0;
int rpmF= 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
Serial.begin(115200);


if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);
 
}
 
void loop() {

int Button2 = digitalRead(2);
int Button3 = digitalRead(3);
int Button4 = digitalRead(4);

  //RPM
  sensorValue0 = analogRead(sensorPin0);
  rpmA = sensorValue0  ;
  sensor2Value0 = analogRead(sensor2Pin0);
  rpmF = sensor2Value0  ;
  
  unsigned char rpmB[7] = {rpmA, rpmA, rpmC, rpmD, rpmE, rpmF, rpmA};

  
  CAN0.sendMsgBuf(0x7E8, 0, 8, rpmB);
  delay(10);    


  if (Button2 == HIGH) {
  rpmC = 0x01  ;
  } else {
    rpmC = 0x02  ;
  }

  if (Button3 == HIGH) {
  rpmD = 0x01  ;
  } else {
    rpmD = 0x02  ;
  }
  if (Button4 == HIGH) {
  rpmE = 0x01  ;
  } else {
    rpmE = 0x02  ;
  }

  CAN0.sendMsgBuf(0x7E8, 0, 8, rpmB); 
  
}
