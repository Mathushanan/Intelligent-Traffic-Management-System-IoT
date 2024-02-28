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

#define yellowLightDuration=5

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

int roadDensity[4];
int roadType[4]={1,2,3,4};

void assignRoadDensity(){

  roadDensity[0]=getRoadDensity("road1");
  roadDensity[1]=getRoadDensity("road2");
  roadDensity[2]=getRoadDensity("road3");
  roadDensity[3]=getRoadDensity("road4");

}

void sortRoadsInDecendingOrder(){

  for(int i=0;i<3;i++){

    for(int j=0;j<3-i);j++){

      if(roadDensity[j]<roadDensity[j+1]){
        
        int temp=roadDensity[j];
        roadDensity[j]=roadDensity[j+1];
        roadDensity[j+1]=temp;

        int tmp=roadType[j];
        roadType[j]=roadType[j+1];
        roadType[j+1]=tmp;

      }

    }
  }



}

void openRoad1(int greenLightDuration){

  digitalWrite(road1RedLedPin,LOW);
  digitalWrite(road1GreenLedPin,HIGH);

  digitalWrite(road2RedLedPin,HIGH);
  digitalWrite(road3RedLedPin,HIGH);
  digitalWrite(road4RedLedPin,HIGH);

  delay(greenLightDuration);

  digitalWrite(road1GreenLedPin,LOW);

  digitalWrite(road1YellowLedPin,HIGH);

  delay(yellowLightDuration);

  digitalWrite(road1YellowLedPin,LOW);

}

void openRoad2(int greenLightDuration){

  digitalWrite(road2RedLedPin,LOW);
  digitalWrite(road2GreenLedPin,HIGH);

  digitalWrite(road1RedLedPin,HIGH);
  digitalWrite(road3RedLedPin,HIGH);
  digitalWrite(road4RedLedPin,HIGH);

  delay(greenLightDuration);

  digitalWrite(road2GreenLedPin,LOW);

  digitalWrite(road2YellowLedPin,HIGH);

  delay(yellowLightDuration);

  digitalWrite(road2YellowLedPin,LOW);

}

void openRoad3(int greenLightDuration){

  digitalWrite(road3RedLedPin,LOW);
  digitalWrite(road3GreenLedPin,HIGH);

  digitalWrite(road1RedLedPin,HIGH);
  digitalWrite(road2RedLedPin,HIGH);
  digitalWrite(road4RedLedPin,HIGH);

  delay(greenLightDuration);

  digitalWrite(road3GreenLedPin,LOW);

  digitalWrite(road3YellowLedPin,HIGH);

  delay(yellowLightDuration);

  digitalWrite(road3YellowLedPin,LOW);

}

void openRoad4(int greenLightDuration){

  digitalWrite(road4RedLedPin,LOW);
  digitalWrite(road4GreenLedPin,HIGH);

  digitalWrite(road1RedLedPin,HIGH);
  digitalWrite(road2RedLedPin,HIGH);
  digitalWrite(road3RedLedPin,HIGH);

  delay(greenLightDuration);

  digitalWrite(road4GreenLedPin,LOW);

  digitalWrite(road4YellowLedPin,HIGH);

  delay(yellowLightDuration);

  digitalWrite(road4YellowLedPin,LOW);

}

void openSuitableRoad(int roadNumber){

  if(roadNumber==1){
    openRoad1();
  }

  if(roadNumber==2){
    openRoad2();
  }

  if(roadNumber==3){
    openRoad3();
  }

  if(roadNumber==4){
    openRoad4();
  }

}

void openRoadsInOrder(){

  openSuitableRoad(roadType[0]);
  openSuitableRoad(roadType[1]);
  openSuitableRoad(roadType[2]);
  openSuitableRoad(roadType[3]);

}


void genarateDensityBasedTrafficSignalProcess(){
  
  assignRoadDensity();
  sortRoadsInDecendingOrder();
  openRoadsInOrder();

}

int road1RfidSensor=0;
int road2RfidSensor=0;
int road3RfidSensor=0;
int road4RfidSensor=0;

void readRfidSensorData(){

}

void setup() {
 

}

void loop() {
  
}
