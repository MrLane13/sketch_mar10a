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
 * There is one animation runnable on the LED Cube - RowStack()
 * This will iterate through and for each row of columns will
 * "Stack" the LED's floors from bottom to top until it reaches
 * the end.
 * The animation speed is controlled by an externally connected 
 * potentiometer (variable resistor) and is connected to Analog
 * Pin 'A0' which has an integer value of '0' when using analogRead()
 */

// DIGITAL PIN ASSIGNMENT VARIABLES FOR LEDs
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

// Variable to hold input of potentiometer
const int SENSOR_PIN = 0;
// Maximum speed scaler that the animation will run at
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
  // Set LEDs to all off
  Clr();
  // Create an LEDSpeed value, which will be from 0-10
  float LEDSpeed = decodeSensor(analogRead(SENSOR_PIN),MAX_SPEED);
  // Run our RowStack() method, passing the speed value
  RowStack(LEDSpeed*100); // multiplied by 100 milliseconds 
}

// ***** BEGIN METHODS ***** //

/*  SPEED SCALE METHOD
 *  sensorVal --> potentiometer reading
 *  scale     --> Maximum possible scaler value for animation speed
 *  
 *  Notice that the value set to 'sensorThreshold' is based upon
 *  the potentiometer you have. The one I am using is sent a maximum
 *  of 10 Vpp and so the Analog Input pin I have it connected to will
 *  give me a maximum value of around 1023 * 1.5
 *  Edit this variables assigned value if the data sheet on your potentiometer
 *  reads a different maximum threshold.
 *  
 *  This method takes in the potentiometer's reading from pin 'A0' and
 *  also the maximum 'scale' value you would like for your animation speed.
 *  It then changes the 'A0' input into a percentage of it's highest threshold.
 *  This percentage is then multiplied by your speed scale, and returned as an int
 *  (NOTE: integer math means it will ROUND DOWN to the nearest int value produced by
 *  multiplying your 'scale' by your 'percent')
 */
int speedScale(float sensorVal, int scale){
  // Local variables
  float percent;
  float sensorThreshold = 1023*1.5;
  // Creating our percentage
  percent = sensorVal/sensorThreshold;
  // Returning our speed scale
  return (scale*percent);
}

/* ROW STACK METHOD
 * n  --> time delay in milliseconds betweeen each 
 * animation execution
 * 
 * Notice that for each new Row Animation that we first
 * turn on the bottom Level, then all three Columns in the
 * Row. Then, in order to add the "animation" of the LED's 
 * taking over higher and higher Level, we add a delay between
 * when we turn on each new Level. This process is repeated for 
 * each of the three Rows in our 3x3x3 Cube
 */
void RowStack(int n) {
  // First Row's Animation
  digitalWrite(L0,LOW);     // Turn on First Floor
  digitalWrite(C0,HIGH);    // Turn on First Column
  digitalWrite(C1,HIGH);    // Turn on Second Column
  digitalWrite(C2,HIGH);    // Turn on Third Column
  delay(n);
  digitalWrite(L1,LOW);     // Turn on Second Floor
  delay(n/2);
  digitalWrite(L2,LOW);     // Turn on Third Floor
  delay(n);
  Clr();                    // Turn off all LEDs
  
  // Second Row's Animation
  digitalWrite(L0,LOW);     // Turn on First Floor
  digitalWrite(C3,HIGH);    // Turn on First Column
  digitalWrite(C4,HIGH);    // Turn on Second Column
  digitalWrite(C5,HIGH);    // Turn on Third Column
  delay(n);
  digitalWrite(L1,LOW);     // Turn on Second Floor
  delay(n/2);
  digitalWrite(L2,LOW);     // Turn on Third Floor
  delay(n);
  Clr();                    // Turn off all LEDs
  
  // Third Row's Animation
  digitalWrite(L0,LOW);     // Turn on First Floor
  digitalWrite(C6,HIGH);    // Turn on First Column
  digitalWrite(C7,HIGH);    // Turn on Second Column
  digitalWrite(C8,HIGH);    // Turn on Third Column
  delay(n);
  digitalWrite(L1,LOW);     // Turn on Second Floor
  delay(n/2); 
  digitalWrite(L2,LOW);     // Turn on Third Floor
  delay(n);
  Clr();                    // Turn off all LEDs
}


/* TURN ALL LEDs OFF METHOD
 * This method is void, and simply sets all Column outputs
 * to 'LOW' or logic zero, and all Level outputs to 'HIGH'
 * or logic one - Resulting in the LEDs turning off
 * 
 * Take note that the reason for the Column pins being sent a 'LOW'
 * and the Level pins being sent a 'HIGH' is because the Level pins are 
 * treated as common ground for the LEDs. I.E. the shorter (gnd) pin
 * on the LEDs on each Level is soldered to the wire that connects to this
 * pin. 
 * 
 * When we turn an LED on, what we are doing is sending a small current
 * to that LED. Since current flows from positive (HIGH) to negative, or gnd
 * (LOW) we need to give the 'gnd' pins of our LEDs a value of 'LOW' so that
 * the current can flow THROUGH the LED and produce light.
 */
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
  digitalWrite(L0,HIGH); // ground
  digitalWrite(L1,HIGH); // ground
  digitalWrite(L2,HIGH); // ground
}

