//You can find me on https://www.instagram.com/furmatech3d/
//I made this for DRV8825 and NEMA17 but you can change this values for your controller

#include <IRremote.h>
#include <IRremoteInt.h>

int dirPin = 7;    //drv8825 s pin
int stepPin = 8;

int powER = 6;     //which pin gives 5volt on arduino (for sleeping mode)


#include <AccelStepper.h>
#define motorInterfaceType 1 // it must be 1 for  "Steppers Motors"
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

int RECV_PIN = 11; //IR pin

IRrecv irrecv(RECV_PIN);
decode_results results;

#define CH1 0x3D9AE3F7 //up  (controller's channel, you can change this channel code according to your remoter's channel)
#define CH2 0x1BC0157B //down


void setup()
{

  Serial.begin(9600); 
  irrecv.enableIRIn();

  pinMode(dirPin, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(stepPin, OUTPUT);

  stepper.setMaxSpeed(2500); // set speed
  stepper.setAcceleration(500); // set acceleration

}

void loop() {

  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX); // prints remoter's channel to serial screen 

    if (results.value == CH1)
    {
      digitalWrite(6, HIGH);
      stepper.moveTo(230000); //change this value according to rollerblind height. On NEMA17 and 16 microsteps it is 1.5 meters .
      stepper.runToPosition();
      delay(100);
      digitalWrite(6, LOW);

    }

    if (results.value == CH2)
    {
      digitalWrite(6, HIGH);
      stepper.moveTo(0);
      stepper.runToPosition();
      delay(100);
      digitalWrite(6, LOW);
    }
    irrecv.resume();
  }
}
