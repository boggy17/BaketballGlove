
//function prototypes
bool beginRecording(); 
int findBeginningOfShot(int arr[]);
int findEndingOfShot(int arr[]);
int find_shot(int motion[], int points);

//globals
const int flexSensor1 = 5; //analog pin
const int buttonPin   = 4; //digital pin

//preset motion for a target shot
int targetMotion[256]; //= {199, 199, 199, 199, 199, 199, 199, 199, 200, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 200, 199, 199, 199, 199, 200, 199, 199, 200, 199, 199, 200, 200, 200, 200, 199, 200, 199, 199, 199, 200, 200, 200, 199, 200, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 200, 198, 198, 198, 198, 197, 197, 195, 193, 190, 188, 185, 183, 180, 176, 158, 121, 88, 68, 55, 45, 37, 31, 26, 22, 20, 16, 15, 13, 12, 11, 9, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 25, 26, 29, 31, 33, 36, 39, 42, 44, 47, 49, 51, 52, 54, 55, 56, 57, 58, 60, 60, 61, 62, 63, 64, 65, 66, 66, 66, 67, 68, 70, 70, 70, 72, 73, 73, 73, 74, 75, 74, 74, 74, 73, 72, 71, 68, 66, 64, 61, 58, 55, 53, 50, 50, 47, 46, 45, 44, 44, 42, 41, 41, 39, 40, 40, 41, 42, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 64, 67, 69, 72, 77, 80, 83, 87, 91, 94, 97, 101, 104, 107, 110, 113, 116, 117, 120, 123, 124, 125, 127, 128, 129, 130, 131, 132, 132, 132, 133, 133, 134, 134, 135, 136, 136, 136, 137, 137, 137, 137, 138, 137, 138, 138, 139, 139, 139, 139, 139, 140, 140, 140, 141, 141, 141, 141, 142, 141, 142, 142, 142, 142, 142, 143, 143, 143, 143, 143, 143, 143, 143, 143, 144, 145, 144, 145, 145, 144, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 146, 146, 147, 146, 147, 147, 146, 147, 147, 148, 147, 147, 148, 147, 147, 148, 148, 148, 148, 148, 148, 147, 148, 148, 148, 149, 149, 148, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 150, 149, 150, 150, 149, 150, 151, 150, 150, 149, 150, 151, 151, 151, 151, 150, 151, 151, 150, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 152, 151, 151, 151, 151, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 153, 153, 152, 152, 153, 153, 152, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 154, 153, 153, 153, 153, 153, 153, 153, 152, 153, 154, 153, 154, 153, 154, 153, 154, 153, 154, 154, 154, 154, 155, 154, 154, 153, 154, 154, 155, 155, 155, 154, 155, 154, 154, 155, 155, 154, 155, 155, 155, 155, 155, 155, 155, 155, 156, 155, 155, 155, 155, 156, 155, 155, 156, 155, 155, 156, 155, 156, 156, 156, 156, 156, 156, 156, 155, 156, 156, 156, 156, 156, 156, 156, 155, 156, 156, 156, 157, 156, 156, 156, 156, 157, 156, 156, 157, 156, 156, 156, 157, 156, 156, 157, 157, 157, 157, 157, 157, 157, 156, 157, 157, 156, 157, 157, 156, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157};

int targetRecorded = 0;
int buttonState = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //preset motion for a target shot
  
  pinMode(flexSensor1, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // get an input into the array
  int val = 0;

  //if the target shot has not been recorded
  if (targetRecorded == 0) {

    if (beginRecording() == true) {
      //record target shot
      for (int i = 0; i< 256; i++) {

        targetMotion[i] = analogRead(flexSensor1);
        Serial.print(targetMotion[i]);
        delay(10);
        Serial.print(", ");
      }
      Serial.println();
      Serial.println("Target has been set!");
      targetRecorded = 1;
    }
  }

  
  int shot[256];
  int shotRecorded = 0;
  if (beginRecording() == true) {

    //record shot
    for (int i = 0; i< 256; i++) {

        shot[i] = analogRead(flexSensor1);
        Serial.print(shot[i]);
        delay(10);
        Serial.print(", ");
      }
      Serial.println();
      Serial.println("Shot has been recorded!");
      shotRecorded = 1;
  }
  delay(1000);

  if (shotRecorded == 1) {
    Serial.println("Begin Comparing!");
    //find where the shot begins and go back ten points
    int targetStartIndex = 0, targetStopIndex = 0, testStartIndex = 0, testStopIndex = 0;
    targetStartIndex = find_shot(targetMotion, 10.0); //findBeginningOfShot(targetMotion);
    targetStopIndex  = 255;//findEndingOfShot(targetMotion);
    testStartIndex   = find_shot(shot, 10.0);//findBeginningOfShot(targetMotion);
    testStopIndex    = 255;//findEndingOfShot(targetMotion);
    Serial.print(testStartIndex);
    Serial.print(", ");
    Serial.println(testStopIndex);
    Serial.print(targetStartIndex);
    Serial.print(", ");
    Serial.println(targetStopIndex);
//    printf("%i, %i \n", testStartIndex, testStopIndex);
//    printf("%i, %i \n", targetStartIndex, targetStopIndex);
    delay(1000);
    Serial.println("Compare!");
    //find the range of between the indexes
    int range = testStopIndex - testStartIndex; //not sure if this would be different between the test and target
    int diff[range];
    int sum = 0;
    for (int i = 0; i < range; i++) {
        
        diff[i] = pow((shot[testStartIndex + i] - targetMotion[targetStartIndex + i]), 2);
        sum += diff[i];
//        printf("%i \n", diff[i]);
        Serial.println(diff[i]);
    }
    Serial.println(sum);  
  }

  delay(10000);
  val = analogRead(flexSensor1);
  Serial.print(val);
  Serial.print("\t");
  Serial.println("\t");  
}

//if a button is pressed, count down from 5 secods
bool beginRecording() {
  int buttonState = 0;
  
  while (buttonState == 0) {
      Serial.println("Waiting...");
      delay(1000);
      buttonState = digitalRead(buttonPin);
      Serial.println(buttonState);
  }
  //if the button has been pressed count up to 3 and begin recording
  if (buttonState == 1) {
  
    //count down
    for (int i = 0; i < 5; i++) {
    
      Serial.println(i);
      delay(1000);
    }
    Serial.println("Begin Recording!");
    return true;
  }
  return false;
}

int findBeginningOfShot(int arr[]) {
    //find i where the bigest change between arr[i] and arr[i+1]

    int targetChange = 10;
    for (int i = 0; i < 255; i++) { //stops at 511 because i will use i+1
        
        //calc the change and make it positive
        int change = abs(arr[i+1] - arr[0]);
        if (change > targetChange) {
            return i;
        }
    }
    
    printf("No shot detected!");
    return 0;
}

//given an array and an index find where the values of the array begin to level off indicating the shooting motion has stopped
//arr is a complete array of the motion
int findEndingOfShot(int arr[]) {
    
    int targetChange = 10;
    for (int i = 255; i > 0; i--) { //stops at 511 because i will use i+1
        
        //calc the change and make it positive
        int change = abs(arr[i-1] - arr[255]);
        if (change > targetChange) {
            return i;
        }
    }
    
    printf("No shot detencted!");
    return 0;
}

int find_shot(int motion[], int points){
    int startIndex = 0;
    double max_change = 0;
    
    for(int i = 0; i < 256; i+=points){
        //Serial.print("I: ");
        //Serial.println(i);

        int minD = motion[i];
        int maxD = motion[i];
        
        for(int j = i; j < i+points; j++){

            if(j <= 256){
                //update maxD
                if(motion[j] > maxD){
                    maxD = motion[j];
                }
                
                //update minD
                if(motion[i] < minD){
                    minD = motion[j];
                }
            }
        }

        //compute change
        if((maxD - minD) > max_change){
            max_change = maxD - minD;
            Serial.print("MAX CHANGE: ");
            Serial.println(max_change);
            
            startIndex = i;
            Serial.print("i: ");
            Serial.println(i);

            Serial.println("--------");
            
        }
    }

    return startIndex;
}

//return a pointer to an array that has the readings from the shot
int * getMotion() {

  int motion[512];
  
  for (int i = 0; i < 512; i++) {

    motion[i] = analogRead(flexSensor1);
  }
  
  return motion;
}
