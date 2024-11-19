#include <Arduino.h>
#include <CD74HC4067.h>

//s0,s1,s2,s3

//change in input 10-5
CD74HC4067 input_mux(0,2,4,5);  // create a new CD74HC4067 object with its four control pins
CD74HC4067 output_mux(15,13,14,12);  // create a new CD74HC4067 object with its four control pins
const int g_common_input = A0;
const int g_common_output = 3;

// int mux_pins [] = {0,2,4,5,15,13,14,12};
int mux_pins [] = {15,13,14,12};
int button_pins [] = {5,4,0,2};
int incomingByte = 0; // for incoming serial data

void setup_relay() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN, HIGH);
  pinMode(g_common_input, INPUT);
  pinMode(g_common_output, OUTPUT);

  for(int i = 0; i < 4; i++){
    pinMode(mux_pins[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++){
    pinMode(button_pins[i], INPUT);
    
  }
  Serial.println("Relay");  
}

void all_relay(){
   digitalWrite(g_common_output, HIGH);
    for (int i = 0; i < 16; i++) {
        output_mux.channel(i);
        delay(100);
    }
    delay(2500);
    digitalWrite(g_common_output, LOW);
    for (int i = 0; i < 16; i++) {
        output_mux.channel(i);
        delay(100);
    }
    delay(2500);
}

int digButtons[4];
int digitalCurrent = -1;

int Motors[] = {0,1,2,3}; //motors
int Valves[] = {8,9,10,11}; //valves

void read_Digitals(){
  digitalCurrent = -1;
  digitalWrite(g_common_output, HIGH);
  // digitalWrite(LED_BUILTIN, LOW);
  for(int i=0; i<4; i++)
  {
    digButtons[i] = digitalRead(button_pins[i]);
  }
  if(digButtons[0] == 0){
      Serial.println("button0");
      digitalCurrent = 0;
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[0]);
  }
  if(digButtons[1] == 0){
      Serial.println("button1");
      digitalCurrent = 1;
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[1]);
  }
  if(digButtons[2] == 0){
      Serial.println("button2");
      digitalCurrent = 2;
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[2]);
  }
  if(digButtons[3] == 0){
      Serial.println("button3");
      digitalCurrent = 3;
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[3]);
  }
  // Serial.println(digitalCurrent);
  delay(10);
}

void relaysOSC(){
  digitalCurrent = -1;
  digitalWrite(g_common_output, HIGH);
  
  if(oscR1 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[0]);
  }
  if(oscR2 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[1]);
  }
  if(oscR3 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[2]);
  }
  if(oscR4 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Motors[3]);
  }
  if(oscR5 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Valves[0]);
  }
  if(oscR6 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Valves[1]);
  }
  if(oscR7 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Valves[2]);
  }
  if(oscR8 == 1){
      digitalWrite(g_common_output, LOW);
      output_mux.channel(Valves[3]);
  }
  
  delay(10);
}


