#include <SPI.h>
#include <MFRC522.h>

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

#define yellowLightDuration    5

#define lowDensityDuration     10
#define mediumDensityDuration  20
#define highDensityDuration    30

#define emergencyDuration 40

#define Road1_MinUltraSensor_TriggerPin 13
#define Road1_MinUltraSensor_EchoPin    14

#define Road1_MaxUltraSensor_TriggerPin 15 
#define Road1_MaxUltraSensor_EchoPin    16

#define Road2_MinUltraSensor_TriggerPin 17
#define Road2_MinUltraSensor_EchoPin    18

#define Road2_MaxUltraSensor_TriggerPin 19
#define Road2_MaxUltraSensor_EchoPin    20

#define Road3_MinUltraSensor_TriggerPin 21
#define Road3_MinUltraSensor_EchoPin    22

#define Road3_MaxUltraSensor_TriggerPin 23
#define Road3_MaxUltraSensor_EchoPin    24

#define Road4_MinUltraSensor_TriggerPin 25
#define Road4_MinUltraSensor_EchoPin    26

#define Road4_MaxUltraSensor_TriggerPin 27 
#define Road4_MaxUltraSensor_EchoPin    28

#define ThresholdValueUltraSonicSensor 50

#define Road1_SS_PIN  29  
#define Road1_RST_PIN 30 

#define Road2_SS_PIN  31  
#define Road2_RST_PIN 32 

#define Road3_SS_PIN  33 
#define Road3_RST_PIN 34

#define Road4_SS_PIN  35  
#define Road4_RST_PIN 36 

MFRC522 Road1_mfrc522(Road1_SS_PIN,Road1_RST_PIN); 
MFRC522 Road2_mfrc522(Road2_SS_PIN,Road2_RST_PIN); 
MFRC522 Road3_mfrc522(Road3_SS_PIN,Road3_RST_PIN); 
MFRC522 Road4_mfrc522(Road4_SS_PIN,Road4_RST_PIN); 

bool isRoad1_Rfid_Detected = false; 
bool isRoad2_Rfid_Detected = false; 
bool isRoad3_Rfid_Detected = false; 
bool isRoad4_Rfid_Detected = false; 


int road1MinUltraSensor=0;
int road1MaxUltraSensor=0;

int road2MinUltraSensor=0;
int road2MaxUltraSensor=0;

int road3MinUltraSensor=0;
int road3MaxUltraSensor=0;

int road4MinUltraSensor=0;
int road4MaxUltraSensor=0;

int roadDensity[4];
int roadType[4]={1,2,3,4};




void assignUltraSonicSensorStatus();
int findDistanceFromUltraSonicSensorData(int triggerPin,int echoPin);
String getRoadDensity(String roadType);
void assignRoadDensity();
void sortRoadsInDecendingOrder();
void openRoad1(int greenLightDuration);
void openRoad2(int greenLightDuration);
void openRoad3(int greenLightDuration);
void openRoad4(int greenLightDuration);
void openSuitableRoad(int roadNumber);
void openRoadsInOrder();
void genarateDensityBasedTrafficSignalProcess();

void checkForEmergencyVehicles();
void isEmergencyVehiclePresent();
void genarateEmergencyBasedTrafficSignalProcess();



void setup() {

  Serial.begin(9600);

  SPI.begin();

  Road1_mfrc522.PCD_Init(); 
  Road2_mfrc522.PCD_Init(); 
  Road3_mfrc522.PCD_Init(); 
  Road4_mfrc522.PCD_Init(); 
 
  pinMode(Road1_Sensor1_TriggerPin, OUTPUT); 
  pinMode(Road1_Sensor1_EchoPin, INPUT);  
  pinMode(Road1_Sensor2_TriggerPin, OUTPUT); 
  pinMode(Road1_Sensor2_EchoPin, INPUT);  

  pinMode(Road2_Sensor1_TriggerPin, OUTPUT); 
  pinMode(Road2_Sensor1_EchoPin, INPUT);  
  pinMode(Road2_Sensor2_TriggerPin, OUTPUT); 
  pinMode(Road2_Sensor2_EchoPin, INPUT);  

  pinMode(Road3_Sensor1_TriggerPin, OUTPUT); 
  pinMode(Road3_Sensor1_EchoPin, INPUT);  
  pinMode(Road3_Sensor2_TriggerPin, OUTPUT); 
  pinMode(Road3_Sensor2_EchoPin, INPUT); 
   
  pinMode(Road4_Sensor1_TriggerPin, OUTPUT); 
  pinMode(Road4_Sensor1_EchoPin, INPUT);  
  pinMode(Road4_Sensor2_TriggerPin, OUTPUT); 
  pinMode(Road4_Sensor2_EchoPin, INPUT);  

}


void loop() {
  


  if(isEmergencyVehiclePresent()){

    genarateEmergencyBasedTrafficSignalProcess();

  }else{

    genarateDensityBasedTrafficSignalProcess();

  }
  
  
}

int EmergencyVehilePriotrization[4];

void assignRfidSensorStatus(){
  
  if (Road1_mfrc522.PICC_IsNewCardPresent() && Road1_mfrc522.PICC_ReadCardSerial()) {

    isRoad1_Rfid_Detected = true;
    EmergencyVehilePriotrization[0]=1;


  }
  if (Road2_mfrc522.PICC_IsNewCardPresent() && Road2_mfrc522.PICC_ReadCardSerial()) {

    isRoad2_Rfid_Detected = true;
    EmergencyVehilePriotrization[1]=2;

  }
  if (Road3_mfrc522.PICC_IsNewCardPresent() && Road3_mfrc522.PICC_ReadCardSerial()) {

    isRoad3_Rfid_Detected = true;
    EmergencyVehilePriotrization[2]=3;

  }
  if (Road4_mfrc522.PICC_IsNewCardPresent() && Road4_mfrc522.PICC_ReadCardSerial()) {

    isRoad4_Rfid_Detected = true;
    EmergencyVehilePriotrization[3]=4;

  }

}


bool isEmergencyVehiclePresent(){

  if(isRoad1_Rfid_Detected||isRoad2_Rfid_Detected||isRoad3_Rfid_Detected||isRoad4_Rfid_Detected){

    return true;

  }else{

    return false;

  }

}


int roadType[4]={1,2,3,4};

void genarateEmergencyBasedTrafficSignalProcess(){





}

void genarateDensityBasedTrafficSignalProcess(){
  
  assignRoadDensity();
  sortRoadsInDecendingOrder();
  openRoadsInOrder();

}

void assignRoadDensity(){

  assignUltraSonicSensorStatus();
  roadDensity[0]=getRoadDensity("road1");
  roadDensity[1]=getRoadDensity("road2");
  roadDensity[2]=getRoadDensity("road3");
  roadDensity[3]=getRoadDensity("road4");

}

void assignUltraSonicSensorStatus(){

  road1MinUltraSensor=findDistanceFromUltraSonicSensorData(Road1_MinUltraSensor_TriggerPin,Road1_MinUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;
  road1MaxUltraSensor=findDistanceFromUltraSonicSensorData(Road1_MaxUltraSensor_TriggerPin,Road1_MaxUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;

  road2MinUltraSensor=findDistanceFromUltraSonicSensorData(Road2_MinUltraSensor_TriggerPin,Road2_MinUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;
  road2MaxUltraSensor=findDistanceFromUltraSonicSensorData(Road2_MaxUltraSensor_TriggerPin,Road2_MaxUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;

  road3MinUltraSensor=findDistanceFromUltraSonicSensorData(Road3_MinUltraSensor_TriggerPin,Road3_MinUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;
  road3MaxUltraSensor=findDistanceFromUltraSonicSensorData(Road3_MaxUltraSensor_TriggerPin,Road3_MaxUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;

  road4MinUltraSensor=findDistanceFromUltraSonicSensorData(Road4_MinUltraSensor_TriggerPin,Road4_MinUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;
  road4MaxUltraSensor=findDistanceFromUltraSonicSensorData(Road4_MaxUltraSensor_TriggerPin,Road4_MaxUltraSensor_EchoPin)<=ThresholdValueUltraSonicSensor?1:0;

}

int findDistanceFromUltraSonicSensorData(int triggerPin,int echoPin){

  long duration;
  long distance;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration_1 * 0.034 / 2;

  return distance;

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

void openRoadsInOrder(){

  openSuitableRoad(roadType[0]);
  openSuitableRoad(roadType[1]);
  openSuitableRoad(roadType[2]);
  openSuitableRoad(roadType[3]);

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





