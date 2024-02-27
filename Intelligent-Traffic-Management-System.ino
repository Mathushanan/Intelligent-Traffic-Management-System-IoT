#define road1RedLedPin    1
#define road1GreenLedPin  2
#define road1YellowLedPin 3

#define road2RedLedPin    4
#define road2GreenLedPin  5
#define road2YellowLedPin 6

#define road3RedLedPin    7
#define road3GreenLedPin  8
#define road3YellowLedPin 9

#define road4RedLedPin    10
#define road4GreenLedPin  11
#define road4YellowLedPin 12

#define YellowLightDuration=5

#define lowDensityDuration=10
#define mediumDensityDuration=20
#define highDensityDuration=30

int road1MinUltraSensor=0;
int road1MaxUltraSensor=0;

int road2MinUltraSensor=0;
int road2MaxUltraSensor=0;

int road3MinUltraSensor=0;
int road3MaxUltraSensor=0;

int road4MinUltraSensor=0;
int road4MaxUltraSensor=0;

int road1RfidSensor=0;
int road2RfidSensor=0;
int road3RfidSensor=0;
int road4RfidSensor=0;




void readUltraSonicSensorData(){

}

String getRoadDensity(String roadType){

  if(roadType=="road1"){

    if(road1MinUltraSensor==0 && road1MaxUltraSensor==0){
      return "low density";
    }
    if(road1MinUltraSensor==1 && road1MaxUltraSensor==0){
      return "medium density";
    }
    if(road1MinUltraSensor==1 && road1MaxUltraSensor==1){
      return "high density";
    }


  }
  else if(roadType=="road2"){

    if(road2MinUltraSensor==0 && road2MaxUltraSensor==0){
      return "low density";
    }
    if(road2MinUltraSensor==1 && road2MaxUltraSensor==0){
      return "medium density";
    }
    if(road2MinUltraSensor==1 && road2MaxUltraSensor==1){
      return "high density";
    }

  }
  else if(roadType=="road3"){

    if(road3MinUltraSensor==0 && road3MaxUltraSensor==0){
      return "low density";
    }
    if(road3MinUltraSensor==1 && road3MaxUltraSensor==0){
      return "medium density";
    }
    if(road3MinUltraSensor==1 && road3MaxUltraSensor==1){
      return "high density";
    }

  }
  else{

    if(road4MinUltraSensor==0 && road4MaxUltraSensor==0){
      return "low density";
    }
    if(road4MinUltraSensor==1 && road4MaxUltraSensor==0){
      return "medium density";
    }
    if(road4MinUltraSensor==1 && road4MaxUltraSensor==1){
      return "high density";
    }

  }


}

void genarateDensityBasedTrafficSignalProcess(){

int roadDensity[4];
int roads[4];



}

void readRfidSensorData(){

}

void setup() {
 

}

void loop() {
  
}
