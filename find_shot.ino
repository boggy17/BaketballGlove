double targetMotion[512];
bool compared;

void setup() {
    Serial.begin(300);

    //wait for serial
    while (!Serial) ;
    
    randomSeed(0);
    
    //create dummy target data
    for(int i = 0; i < 512; i++){
        
        //fill array with numbers
        double randInt = random(0,512);
        double randDec = random(0,100);

        randDec /= 100;

        double randMotion = randInt + randDec;
        
        targetMotion[i] = randMotion;
    }
    
    //loop control
    compared = 0;
}

//find greatest change in parameter points over array
//assume this is shot
int find_shot(double motion[], int points){
    int startIndex = 0;
    double max_change = 0;
    
    for(int i = 0; i < 512; i+=points){
        //Serial.print("I: ");
        //Serial.println(i);

        int minD = motion[i];
        int maxD = motion[i];
        
        for(int j = i; j < i+points; j++){

            if(j <= 512){
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

void loop() {

    if(!compared){   
        //_make dummy compare data
        double compareMotion[512];
        
        for(int i = 0; i < 512; i++){
            double randInt = random(0,512);
            double randDec = random(0,100);
    
            randDec /= 100;
    
            double randMotion = randInt + randDec;
            
            compareMotion[i] = randMotion;
        }
    
        //find greatest change over variable points in array
        int points = 10;
        int compare_points = 10;
        
        int shot_index = find_shot(compareMotion, points);

        //print checks
        Serial.print("GREATEST CHANGE @ index = ");
        Serial.println(shot_index);

        Serial.println("--------");
        for(int i = shot_index; i < shot_index + compare_points; i++){
            if(i < 512){
                Serial.print("VAL: ");
                Serial.println(compareMotion[i]);
            }
        }
        Serial.println("--------");

        compared = 1;
    }
}
