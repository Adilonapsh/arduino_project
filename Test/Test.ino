
const int led1=14;
const int led2=12;
const int led3=13;
void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(led1,HIGH);
 delay(500);
 digitalWrite(led2,HIGH);
 delay(500);
 digitalWrite(led3,HIGH);
 delay(500);
 digitalWrite(led1,LOW);
 delay(500);
 digitalWrite(led2,LOW);
 delay(500);
 digitalWrite(led3,LOW);
 delay(500);
 
}
