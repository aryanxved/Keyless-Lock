//***********************IR Keyless Lock************************
//***********************Password:1616**************************
#include <Servo.h>
#define pinServo 3
#include <IRremote.h>
#include <LiquidCrystal.h>
//***********************Library********************************
Servo myservo; //allows for initial setup of servo motor
int ledred = 12; //led red is attached to pin 12
int ledgreen = 13; //led red is attached to pin 12
int pos = 0; //position is set to base degree
int i=1;//i is initially 1 as it runs through 4 times allowing for a 4 digit code
int p1=0; //storing value as initially as 0
int p2=0;//storing value as initially as 0
int p3=0;//storing value as initially as 0
int p4=0;//storing value as initially as 0
bool lock=true; //initializer for locking code
LiquidCrystal lcd(11, 10, 9, 6, 4, 2); //Sets LCD pins
//****************************Variables**************************
int RECV_PIN = 7;// IR Sensor connected to pin 7
IRrecv irrecv(RECV_PIN); //allows for setup of the pin
decode_results results;
//***************************IR Remote Code**********************

void setup()
{
  Serial.begin(9600);//setup for serial monitor
  Serial.println("Enabling IRin");
  Serial.println("Enabled IRin");
  pinMode(ledred, OUTPUT);//setup for ledred
  pinMode(ledgreen, OUTPUT);//setup for ledgreen
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
 Serial.println("Enabled IRin");
  myservo.attach(pinServo);//atached to pin 7
  lcd.begin(16, 2);
  lcd.print("Hello World");
}
//*************************Setup for Program*********************
void loop() {
    lcd.setCursor(0, 1);
    lcd.print(millis() / 10);
    digitalWrite(ledred, HIGH);//led red stays on till right is entered
    digitalWrite(ledgreen, LOW);//led green stays off
  if (i<=4 && irrecv.decode(&results)){// i runs 4 times
    switch (i) {
        case 1: //p1 is assigned a value
        p1=results.value; //p1 ties to the printed value
        Serial.println(p1); //p1 is printed
        irrecv.resume();
  
        case 2://p2 is assigned a value
        p2=results.value; //p2 ties to the printed value
        Serial.println(p2);//p2 is printed
        irrecv.resume();
        case 3://p3 is assigned a value
        p3=results.value;//p3 ties to the printed value
        Serial.println(p3);//p3 is printed
        irrecv.resume();
        case 4://p4 is assigned a value
        p4=results.value;//p4 ties to the printed value
        Serial.println(p4);//p4 is printed
        irrecv.resume();
      }
  i=i+1;
    //irrecv.resume(); // Receive the next value
  }
  
//&& is used instead of or since && includes all 4 values of the passcode
    if (p1 == 2295 && p2 == 26775 && p3 == 2295 && p4 == 26775)
    {
      if (lock) { 
          digitalWrite(ledred, LOW);
        lcd.println("Unlocking");
        Serial.println("Unlocking");        
        lock=false; //if bool is false lock opens
        delay(200);
        digitalWrite(ledgreen,LOW);
        delay(200);
        digitalWrite(ledgreen,HIGH);
        delay(200);
        digitalWrite(ledgreen,LOW);
        delay(200);
        digitalWrite(ledgreen,HIGH);
        delay(200);
        digitalWrite(ledgreen,LOW);
  
        Serial.println("Initializing");
        i=1;
        p1=0;
        p2=0;
        p3=0;
        p4=0;
              myservo.write(180);// Degrees servo motor moves
          delay(1500); //Time it takes for servo motor to move
        irrecv.resume(); // Receive the next value
      }
      else{
        lcd.println("Locking"); //LCD print locking
        Serial.println("Locking");
        lock=true;//if bool is true lock locks into initial state
        digitalWrite(ledred, HIGH);
        digitalWrite(ledgreen,HIGH);
        delay(200);
        digitalWrite(ledgreen,LOW);
        delay(200);
        digitalWrite(ledgreen,HIGH);
        delay(200);
        digitalWrite(ledgreen,LOW);
        delay(200);
        digitalWrite(ledgreen,HIGH);
        delay(200);
        i=1;
        p1=0;
        p2=0;
        p3=0;
        p4=0;
  
          myservo.write(90); // Degrees servo motor moves
          delay(1500); //Time it takes for servo motor to move
        }
      }
    }
