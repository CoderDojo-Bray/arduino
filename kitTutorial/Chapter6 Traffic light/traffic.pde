
int ledred=10;   
int ledyellow=7; 
int ledgreen=4; 
void setup()
{
   pinMode(ledred,OUTPUT);
   pinMode(ledyellow,OUTPUT);
   pinMode(ledgreen,OUTPUT);
}
void loop()
{
   digitalWrite(ledred,HIGH);
   delay(1000);
   digitalWrite(ledred,LOW);
   digitalWrite(ledyellow,HIGH);
   delay(200);
   digitalWrite(ledyellow,LOW);
   digitalWrite(ledgreen,HIGH);
   delay(1000);
   digitalWrite(ledgreen,LOW);
}
