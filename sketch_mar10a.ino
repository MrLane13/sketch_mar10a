/*
 * ORIGINAL AUTHOR: Lane Mills
 * EDITING CONTRIBUTOR: 
 * LAST UPDATED: 03/10/16
 * 
 * This shetch is meant to drive a 3x3x3 LED cube.
 * *** VARIABLE EXPLANATION ***
 * Row:     a horizontal line of 3 LEDs
 * Column:  a vertical stack of 3 LEDs
 * Level:   a "floor" consisting of a 3x3 set of LEDs
 * 
 */

// DIGITAL PIN ASSIGNMENT VARIABLES
// First Row, Columns 0-2
const int C0 = 2;
const int C1 = 3;
const int C2 = 4;
// Second Row, Columns 3-5
const int C3 = 5;
const int C4 = 6;
const int C5 = 7;
// Third Row, Columns 7-10
const int C6 = 8;
const int C7 = 9;
const int C8 = 10;
// Levels 0-2 
const int L0 = 11;
const int L1 = 12;
const int L2 = 13;

// Variable to hold input of potentiometer which
// is connected to Analog Input Zero "A0"
const int SENSOR_PIN = 0;
const int MAX_SPEED = 10;


// *** INITIAL SETUP *** //
void setup() {
  // Set all LED pins to outputs on our board
  pinMode(C0, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(C5, OUTPUT);
  pinMode(C6, OUTPUT);
  pinMode(C7, OUTPUT);
  pinMode(C8, OUTPUT);
  pinMode(L0, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
}

// *** MAIN LOOP *** //
void loop() {
  Clr();
  float LEDSpeed = decodeSensor(analogRead(SENSOR_PIN),MAX_SPEED);
  RowStack(LEDSpeed*100);
  
}

// ***** BEGIN METHODS ***** //

/*  DECODE SENSOR METHOD
 *  sensorVal --> potentiometer reading
 *  divInto   --> Maximum possible value returned
 */
int decodeSensor(float sensorVal, int divInto){
  // 
  float percent;
  float sensorThreshold = 1023*1.5;
  // 
  percent = sensorVal/sensorThreshold;
  // 
  return (divInto*percent);
}

// n is interval time in ms
void RowStack(int n) {
  // First Row Stack Animation
  digitalWrite(L0,LOW);
  digitalWrite(C0,HIGH); 
  digitalWrite(C1,HIGH);
  digitalWrite(C2,HIGH);
  delay(n);
  digitalWrite(L1,LOW);
  delay(n/2);
  digitalWrite(L2,LOW);
  delay(n);
  Clr();
  // Second Row Stack Animation
  digitalWrite(L0,LOW);
  digitalWrite(C3,HIGH); 
  digitalWrite(C4,HIGH);
  digitalWrite(C5,HIGH);
  delay(n);
  digitalWrite(L1,LOW);
  delay(n/2);
  digitalWrite(L2,LOW);
  delay(n);
  Clr();
  // Third Row Stack Animation
  digitalWrite(L0,LOW);
  digitalWrite(C6,HIGH); 
  digitalWrite(C7,HIGH);
  digitalWrite(C8,HIGH);
  delay(n);
  digitalWrite(L1,LOW);
  delay(n/2);
  digitalWrite(L2,LOW);
  delay(n);
  Clr();
}

void Clr() {
  digitalWrite(C0,LOW); 
  digitalWrite(C1,LOW);
  digitalWrite(C2,LOW);
  digitalWrite(C3,LOW);
  digitalWrite(C4,LOW); 
  digitalWrite(C5,LOW);
  digitalWrite(C6,LOW);
  digitalWrite(C7,LOW);
  digitalWrite(C8,LOW);
  digitalWrite(L0,HIGH);//gound
  digitalWrite(L1,HIGH);//gound
  digitalWrite(L2,HIGH);//gound
}

