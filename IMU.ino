/*
  Arduino LSM6DS3 - Simple Accelerometer

  This example reads the acceleration values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

int i = 0; // Value to keep track of overall cycle (outside of individual arrays)
int c = 0; // Value to input into arrays.

float arr_1x[104];
float arr_2x[104];
float arr_3x[104];
float arr_1z[104];
float arr_2z[104];
float arr_3z[104];

float arr_23x[208];
float arr_23z[208];

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

//  Serial.print("Accelerometer sample rate = ");
//  Serial.print(IMU.accelerationSampleRate());
//  Serial.println(" Hz");
//  Serial.println();
//  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
  
}

void loop() {
  float x, y, z;
  
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.println('\t');
    

//-----------------------------------
//Storing History for Quick Retrieval
//-----------------------------------
    if (i < 104) {
      arr_1x[c] = x;
      arr_1z[c] = z;        
      }
    else if (i == 104) {
      c = 0;
      arr_2x[c] = x;  
      arr_2z[c] = z; 
      }
    else if ((i > 104) && (i < 208)) {
      arr_2x[c] = x;
      arr_2z[c] = z;
    }
    else if (i == 208) {
      c = 0;
      arr_3x[c] = x;
      arr_23x[c+104] = x;
      arr_3z[c] = z;
      arr_23z[c+104] = z; //---------------------------------------------------------------------LEFT OFF HERE----------------------------------POPULATING ARRAY 23 WITH ARRAY 2 AND ARRAY 3 FOR X AND Z
    }
    else if ((i > 208) && (i < 312)) {
      arr_3x[c] = x;
      arr_3z[c] = z;
    }
    else if (i == 312) {
      memcpy(arr_1x, arr_2x, sizeof(arr_1x));
      memcpy(arr_2x, arr_3x, sizeof(arr_2x));
      memcpy(arr_1z, arr_2z, sizeof(arr_1z));
      memcpy(arr_2z, arr_3z, sizeof(arr_2z));
      memcpy(arr_23x, arr_2x, sizeof(arr_2x));
      i = 208;
      c = 0;
      arr_2x[c] = x;
      arr_2z[c] = z;
    }
    


//-------------------------------------------------
//Appending array 3 onto array 2 for indexing below
//-------------------------------------------------



//-----------------------------------
//Detecting if the Device is Vertical
//-----------------------------------
//  if ((x < -.6) && (z > .5)) {
//    for (c; c > c - 5; c--) {
//      if (c < 0) {
//        int nc = 104 - -1 * c;
//         if ((arr_2x[nc] < -.6) && (arr_2z[nc] > .5)) {
//          digitalWrite(LED_BUILTIN, HIGH);
//      }
//      else {
//        if ((arr_3x[c] < -.6) && (arr_3z[c] > .5)) {
//          digitalWrite(LED_BUILTIN, HIGH);
//        }
//      }
//          ;
//      }
//    
//    else {
//       digitalWrite(LED_BUILTIN, HIGH);
//        }
//    }
//  }
//  else {
//    digitalWrite(LED_BUILTIN, LOW);
//  }
//    i += 1;
//    c += 1;
}
// Resistor > analog pin > flex sensor > ground
// 3 analog output pins > 3 resistors > RGB LED > Ground
// Digital output pin > motor > ground
// 3.3 V > resistor > analog pin  > ground
}
