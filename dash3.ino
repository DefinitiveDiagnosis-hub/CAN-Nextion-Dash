#include <mcp_can.h>
#include <SPI.h>

#define CAN0_INT 2
MCP_CAN CAN0(10);
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];

// Variable to store rpm:
int RealRPM = 0;
int Realfuel = 0;
int rpm;
int fuel;


void setup() {  

  Serial.begin(9600);  // Start serial comunication at baud=9600


  // I am going to change the Serial baud to a faster rate.
  delay(500);  // This delay is just in case the nextion display didn't start yet, to be sure it will receive the following command.
  Serial.print("baud=115200");  // Set new baud rate of nextion to 115200, but it's temporal. Next time nextion is power on,
                                // it will retore to default baud of 9600.
                                // To take effect, make sure to reboot the arduino (reseting arduino is not enough).
                                // If you want to change the default baud, send the command as "bauds=115200", instead of "baud=115200".
                                // If you change the default baud, everytime the nextion is power ON is going to have that baud rate, and
                                // would not be necessery to set the baud on the setup anymore.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to nextion.
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.end();  // End the serial comunication of baud=9600

  Serial.begin(115200);  // Start serial comunication at baud=115200
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  CAN0.setMode(MCP_NORMAL);
  pinMode(CAN0_INT, INPUT); 

}  // End of setup


void loop() {  

  delay(50);  
   CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

// if rxId == 7ED test ==rxBuf[1] needs coding here

  int rpm = rxBuf[1];
  rpm = constrain(rpm, 0, 208);
  // Send tachometer value:
  Serial.print("tach.pic=");  
  Serial.print(rpm); 
  Serial.write(0xff);  
  Serial.write(0xff);
  Serial.write(0xff);


  int fuel = rxBuf[5];
  fuel = constrain(fuel, 0, 100);
  // Send fuel level:
  Serial.print("fuel.val=");  
  Serial.print(fuel);  
  Serial.write(0xff);  
  Serial.write(0xff);
  Serial.write(0xff);

// if id is 7ed & buf is 2 needs putting here
  if (rxBuf[2] == 0x01) {
    Serial.print("vis check,1");  
    Serial.write(0xff);  
    Serial.write(0xff);
    Serial.write(0xff);
  } else {
    Serial.print("vis check,0");  
    Serial.write(0xff);  
    Serial.write(0xff);
    Serial.write(0xff);
  }

  if (rxBuf[3] == 0x01) {
    Serial.print("vis bat,1");  
    Serial.write(0xff);  
    Serial.write(0xff);
    Serial.write(0xff);
  } else {
    Serial.print("vis bat,0");  
    Serial.write(0xff);  
    Serial.write(0xff);
    Serial.write(0xff);
  }

  if (rxBuf[4] == 0x01) {
    Serial.print("vis oil,1");  
    Serial.write(0xff);  
    Serial.write(0xff);
    Serial.write(0xff);
  } else {
    Serial.print("vis oil,0"); 
    Serial.write(0xff);  
    Serial.write(0xff);
    Serial.write(0xff);
  }



}  // End of loop
