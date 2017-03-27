
/*
  IR to RF project for the livingroom projector
  Homegear 120" HD Motorized 16:9 Projector Screen W/ Remote Control
*/

#include <RCSwitch.h>
#include <IRremote.h>

#define RFSendPin 10
#define IRReceivePin 11

#define IR_STOP 16728510
#define IR_DOWN 16744830
#define IR_UP   16712190

#define RF_DOWN "011011001000100001011100"
#define RF_STOP "011011001000100001011010"
#define RF_UP   "011011001000100001011001"

#define PULSELENGTH 365
#define PROTOCOL 1

IRrecv irrecv(IRReceivePin);              // IR Receiver data pin is connected to Arduino Pin #11
decode_results results;

RCSwitch mySwitch = RCSwitch();

void setup()
{
  Serial.begin(9600);
  
  mySwitch.enableTransmit(RFSendPin);     // RF Transmitter data is connected to Arduino Pin #10  
  mySwitch.setPulseLength(PULSELENGTH);  
  mySwitch.setProtocol(PROTOCOL);
  irrecv.enableIRIn(); // Start the IR receiver
  Serial.println("Serial interface initialized");
}

void loop() {
  
  if (irrecv.decode(&results)) {
    
    Serial.println(results.value, DEC);
    
    switch(results.value)
    {
      case IR_STOP:
        Serial.println("IR STOP CODE TRIGGERED, CONVERTING TO RF STOP");
        mySwitch.send(RF_STOP);
        delay(200);
        mySwitch.send(RF_STOP);
        delay(200);
        mySwitch.send(RF_STOP);
        break;
     case IR_UP:
        Serial.println("IR UP CODE TRIGGERED, CONVERTING TO RF UP");
        mySwitch.send(RF_UP);
        delay(200);
        mySwitch.send(RF_UP);
        delay(200);
        mySwitch.send(RF_UP);
        break;
     case IR_DOWN:
        Serial.println("IR DOWN CODE TRIGGERED, CONVERTING TO RF DOWN");
        mySwitch.send(RF_DOWN);
        delay(200);
        mySwitch.send(RF_DOWN);
        delay(200);
        mySwitch.send(RF_DOWN);
        break;
    }
    irrecv.resume();
    delay(200);
  }
}
