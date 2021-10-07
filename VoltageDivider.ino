                              //variables to for analog pins used
int analogPin5 = A5;
int analogPin4 = A4;
int analogPin3 = A3;

// variables to store the value read
int val1 = 0;  
int val2 = 0; 
int val3 = 0;

int setButton = LOW; //button to set init state and final state

int minAngle = 0; //hand completely stretched    out
int currentAngle = 0;
int maxAngle = 0; //hand in a fist


void setup() {
  //  setup serial
  Serial.begin(9600);           
}

void loop() {

  //stretch out hand
  //continue reading until button is pressed
  //once it is pressed the last value is the minAngle 


  setButton = LOW;
  if (minAngle == 0) {
    while (setButton == LOW) {
      
      minAngle = analogRead(analogPin5);
      Serial.println(minAngle);
      delay(100);
      setButton = digitalRead(4);
    }
    delay(5000);
    setButton = LOW;
    //same technique for the maxAngle
    while(setButton == LOW) {
  
      maxAngle = analogRead(analogPin5);
      Serial.println(maxAngle);
      delay(100);
      setButton = digitalRead(4);
    }
  }
  
  
  // read the input pins
  currentAngle = analogRead(analogPin5);          
  val3 = analogRead(analogPin3);
  

  // print values
  Serial.print(minAngle);
  Serial.print("\t");
  Serial.print(maxAngle);
  Serial.print("\t");
  Serial.print(currentAngle);
  Serial.print("\t");   
  Serial.print(val3);
  Serial.println("\t");          


  delay(500);
}



/**
 * Pseudocode:
 * press a button
 * make the motion and store those value in an array
 * set it to the "good" motion
 * 
 * press a button
 * make the motion and store those value in an array
 * compare to the "good" motion
 * 
**/
