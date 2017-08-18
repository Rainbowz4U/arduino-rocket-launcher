//By Rainbowz4U
#include <LiquidCrystal.h>
#include <Wire.h>   

//LCD Setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Button Setup
int inPin = 13;   // pushbutton connected to digital pin 13
int button = 1;     // variable to store the read value

//Switch Setup
int inSwitch = 9;
int button2 = 0;

//Speaker Setup
int speakerPin = 10; //Piezo to digital pin 10

//Launch Pin Setup
int launchPin = 8; //connected to digital pin 8, HIGH closes circuit to ignitors so rocket goes boom!

//Seconds Setup
int seconds = 11;
int h = seconds * 100;

//LED Setup
int LEDPin = 7;

void setup() {
  Serial.begin(9600);
  
  //Button Setup
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input
  
  //Launch Pin Setup
  pinMode(launchPin, OUTPUT);

  //Switch Setup
  pinMode(inSwitch, INPUT);

  //LED Setup
  pinMode(LEDPin, OUTPUT);

  //LCD Setup
   lcd.begin(16, 2);
   lcd.print("Systems Ready");

    //Play startup Sound
    tone(speakerPin, 700);
    delay(250);
    noTone(speakerPin);
    tone(speakerPin, 800);
    delay(250);
    noTone(speakerPin);
    tone(speakerPin, 600);
    delay(250);
    noTone(speakerPin);

    Serial.println("Initialization Complete");
}

void loop() {
  if (button2 == LOW) {
    
    //Button
    button2 = digitalRead(inSwitch);   // read the input pin
    digitalWrite(LEDPin, LOW);

    

   delay(10);
  }

 if (button2 == HIGH) {
  digitalWrite(LEDPin, HIGH);
  button2 = digitalRead(inSwitch);
  button = digitalRead(inPin);
  if (button == 0 ){ //Code for Launch Button Pressed
    Serial.println("LAUNCH ACTIVATED");
    
    //Play Sound
    tone(speakerPin, 700);
    delay(250);
    noTone(speakerPin);
    tone(speakerPin, 800);
    delay(250);
    noTone(speakerPin);
    
   for (h!=0; h--;){ 
     
        lcd.clear();
        lcd.print(h/100);
        
        //Play sound last 10 seconds
        if (h <= 1000) {
          if (h == 1000 ){
            tone(speakerPin, 800); //Play sound
          }
            if (h <= 1000 && (h % 100) / 10 == 0 && h > 50){
            tone(speakerPin, 800); //Play sound
          }
           if ((h % 100) / 10 == 8) {
              noTone(speakerPin);}
         }
          
        delay(10);
    }
      
    //Launch Power to Igniter
    digitalWrite(launchPin, HIGH);
    tone(speakerPin, 900); //Play sound
    lcd.clear();
    lcd.write("LAUNCHING!");
    delay(8000); //Send current to ignitor for 8 seconds
    digitalWrite(launchPin, LOW); //Turn Power off after 8 Seconds.
    noTone(speakerPin);
    //initialize 
    delay(5000);
    
    button =1;
    button2 =LOW; 
    
  }
  else if (button2 == LOW) {
    digitalWrite(LEDPin, LOW);
    lcd.clear();
    lcd.write("Systems Ready");
  }
 } 
  

  
}
