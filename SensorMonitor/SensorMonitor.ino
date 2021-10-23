/*
Serial Monitor
*/

#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

 // BLE service for this glove
BLEService gloveService("a98662ad-6993-4143-8fa6-4fadfcba0574");

// BLE Characteristics
BLEUnsignedCharCharacteristic flexSensorChar("82d72018-f4dd-45e2-a3e3-c363a1e14ada",  BLERead | BLENotify); 
BLEUnsignedCharCharacteristic xIMUChar("8096104e-4cd6-4e64-bc63-65f5e1ff9383",  BLERead | BLENotify); 
BLEUnsignedCharCharacteristic yIMUChar("50103d9a-1013-4640-8108-fa0a4d8f8575",  BLERead | BLENotify); 
BLEUnsignedCharCharacteristic zIMUChar("5aa97950-fd9c-449b-b691-8298a95450c3",  BLERead | BLENotify); 

//create a variable to store the last value of each sensor reading
int oldFlexSensorValue = 0;
long prevMillis = 0;  // last time the sensors were checked, in ms

void setup() {
  Serial.begin(9600);    // initialize serial communication
  //while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin to indicate when a central is connected

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet
  */
  BLE.setDeviceName("S.C.R.E.E.N Glove");
  BLE.setLocalName("S.C.R.E.E.N Glove");

  // add the service UUID
  BLE.setAdvertisedService(gloveService); 
  
  //add all of the characteristics to the service
  gloveService.addCharacteristic(flexSensorChar); 
  gloveService.addCharacteristic(xIMUChar);
  gloveService.addCharacteristic(yIMUChar);
  gloveService.addCharacteristic(zIMUChar);

  //add the service to BLE
  BLE.addService(gloveService); 

  //initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  

  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    // get the readings every 200ms
    // while the central is connected:
    while (central.connected()) {
      long currentMillis = millis();
      // if 200ms have passed, check the battery level:
      if (currentMillis - prevMillis >= 200) {
        prevMillis = currentMillis;
        updateSensorValues();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.print("Disconnected from central: ");
    //Serial.println(central.address());
  }
}

void updateSensorValues() {
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the charge level of a battery.
  */
  int flexSensorReading = analogRead(A7);
  int flexSensorValue = map(flexSensorReading, 0, 1023, 0, 100);

  //read the IMU values
  float x, y, z;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    //multiply each by 100 because ints are easier to send via BLE
    int xIMUVal = x * 100;
    int yIMUVal = y * 100;
    int zIMUVal = z * 100;
    
    xIMUChar.writeValue(xIMUVal);
    yIMUChar.writeValue(yIMUVal);
    zIMUChar.writeValue(zIMUVal);
  }
    

  //send sensor values to the app
  flexSensorChar.writeValue(flexSensorValue);            
}
