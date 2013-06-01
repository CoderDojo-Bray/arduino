
void setup()
{
    pinMode(13,OUTPUT);//设置数字8引脚为输出模式
}
void loop()
{
    int i;//定义变量i
    while(1)
    {
       i=analogRead(5);//读取模拟5口电压值
       if(i>200)//如果大于512（2.5V）
       {
          digitalWrite(13,HIGH);//点亮led灯
       }
       else//否则
       {
          digitalWrite(13,LOW);//熄灭led灯
       }
    }
}
