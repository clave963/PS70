int ledButton = 3;
int motorButton = 4;
int ledPin = 5;

void setup(){
  Serial.begin (9600);
  pinMode(ledButton, INPUT_PULLUP);
  pinMode (motorButton, INPUT_PULLUP);

}

void loop() {
  Serial.print("Led Button: ");
  Serial.print(digitalRead(ledButton));
  Serial.print ("Motor Button: ");
  Serial.println(digitalRead(motorButton));

  if(digitalRead(ledButton) == 0){
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
  }

}