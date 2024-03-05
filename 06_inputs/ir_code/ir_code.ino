class Photodiode {
  int photoPin;
  int readPin;
  int value;
  unsigned long previousMillis;

public:
  Photodiode(int pinA, int pinB) {
    photoPin = pinA;
    readPin = pinB;
    previousMillis = 0;
    value = 0;

    pinMode(photoPin, OUTPUT);
    digitalWrite(photoPin, HIGH);
  }

  void update() {

    if(previousMillis - millis() > 20) {
      value = analogRead(readPin);
      // Serial.println(value);
      previousMillis = millis();
    }

  }

  int getValue() {
    return value;
  }
};

Photodiode sensor(2,A0);                
int led=13;                 
int limit = 60;            

void setup()    
 {  
  pinMode(led,OUTPUT);      
  digitalWrite(led,LOW);    
  Serial.begin(9600);         
 }  

void loop()  
 {
  sensor.update();
  int value = sensor.getValue();
  Serial.println(value);
   
  if(value <= limit)              
  {  
    
   digitalWrite(led, HIGH);     
  }  
  else if(value > limit)         
  {  
   digitalWrite(led,LOW);      
  }  
 }  