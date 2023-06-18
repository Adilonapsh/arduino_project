const int red= 5;
const int green= 4;
const int blue =14;


void setup() {
  // put your setup code here, to run once:
pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
pinMode(blue,OUTPUT);
digitalWrite(red,LOW);
digitalWrite(green,LOW);
digitalWrite(blue,LOW);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(red,HIGH);
delay(1000);
Serial.print("RED");
digitalWrite(red,LOW);
delay(1000);
digitalWrite(green,HIGH);
delay(2000);
digitalWrite(blue,HIGH);
delay(3000);
digitalWrite(green,LOW);
delay(2000);
digitalWrite(blue,LOW);
delay(3000);

}
