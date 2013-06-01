
int g;

void buzzer()
{
        for(g=0;g<80;g++)    
        {
        digitalWrite(8,HIGH);
        delay(1);
        digitalWrite(8,LOW);
        delay(1);
        }
}
void setup()
{
    pinMode(8,OUTPUT);
}
void loop()
{
    char i,j,k;
    i=analogRead(5);
    while(1)
    {
      j=analogRead(5);
      k=j-i;
      if(k>123)
      {
          buzzer();
      }
      else
      {
          digitalWrite(8,LOW);
      }
    } 
}

