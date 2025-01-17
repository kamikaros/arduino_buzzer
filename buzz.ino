#include "pitches.h"

const int buzzerPin = 2;
const int sensorPin = A0;

const int threshold = 100; //resistance needed for a sensor

int sensorValue = 0;

int mappedValue = 0;

int melody[] = {NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_G5 };

int durations[] = {8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 4, 4};     //for notes


void setup() {

  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

}


void loop() {
  
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  mappedValue = map(sensorValue, 0, 1023, 0, 255);
  mappedValue = constrain(mappedValue, 0, 255);       //limits range of sensor values (0-255)
  analogWrite(buzzerPin, mappedValue);
  delay(1);


  if (sensorValue > threshold){  //checks FSR value to allow early exit if released
    play();
  } else {
    noTone(buzzerPin);     //stop playing if FSR is released
  }
  delay(100);    //to prevent rapid retriggering 
}


void play(){
  
  int size = sizeof(durations) / sizeof(int);  
	  
	for (int note = 0; note < size; note++) {  
	  
	 int duration = 1000 / durations[note];  
	 tone(buzzerPin, melody[note], duration);  
	  
	 int pauseBetweenNotes = duration * 1.30;  
	 delay(pauseBetweenNotes);  
	     
	 noTone(buzzerPin);         //to turn off the buzzer at the end of the melody
  }
}


