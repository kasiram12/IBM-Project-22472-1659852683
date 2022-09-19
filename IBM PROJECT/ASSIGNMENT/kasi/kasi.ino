#define pirPin 7
int ldr=A0;


int value=0;

int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
void setup() {
Serial.begin(9600);
pinMode(2,OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(pirPin, INPUT);
}

void loop() {
value=analogRead(ldr);
Serial.println("LDR value is :");
Serial.println(value);
if(value<300)
  {
    digitalWrite(2,HIGH);
  }
  else
  {
    digitalWrite(2,LOW);
  }
  PIRSensor();
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
        digitalWrite(4,HIGH);
         delay(1000);
        digitalWrite(4,LOW);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
        digitalWrite(4,LOW);
         delay(50);
      }
   }
}
