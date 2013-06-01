
#define display_array_size 8
// ascii 8x8 dot font
#define data_null 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // null char
#define data_ascii_A 0x02,0x0C,0x18,0x68,0x68,0x18,0x0C,0x02 /*"A",0*/
/** 
 **"A"
 #define A  { //
    {0, 0, 0, 0, 0, 0, 1, 0}, //0x02
    {0, 0, 0, 0, 1, 1, 0, 0}, //0x0C
    {0, 0, 0, 1, 1, 0, 0, 0}, //0x18
    {0, 1, 1, 0, 1, 0, 0, 0}, //0x68
    {0, 1, 1, 0, 1, 0, 0, 0}, //0x68
    {0, 0, 0, 1, 1, 0, 0, 0}, //0x18
    {0, 0, 0, 0, 1, 1, 0, 0}, //0x0C
    {0, 0, 0, 0, 0, 0, 1, 0}  //0x02
}
**/
#define data_ascii_B 0x00,0x7E,0x52,0x52,0x52,0x52,0x2C,0x00 /*"B",1*/
#define data_ascii_C 0x00,0x3C,0x66,0x42,0x42,0x42,0x2C,0x00 /*"C",2*/
#define data_ascii_D 0x00,0x7E,0x42,0x42,0x42,0x66,0x3C,0x00 /*"D",3*/
#define data_ascii_E 0x00,0x7E,0x52,0x52,0x52,0x52,0x52,0x42 /*"E",4*/
#define data_ascii_F 0x00,0x7E,0x50,0x50,0x50,0x50,0x50,0x40 /*"F",5*/
#define data_ascii_G 0x00,0x3C,0x66,0x42,0x42,0x52,0x16,0x1E /*"G",6*/
#define data_ascii_H 0x00,0x7E,0x10,0x10,0x10,0x10,0x7E,0x00 /*"H",7*/
#define data_ascii_I 0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00 /*"I",8*/
// display array
byte data_ascii[][display_array_size] = {
  data_null,
  data_ascii_A, data_ascii_B,
  data_ascii_C,
  data_ascii_D,
  data_ascii_E,
  data_ascii_F,
  data_ascii_G,
  data_ascii_H,
  data_ascii_I,
};
//the pin to control ROW
const int row1 = 2; // the number of the row pin 24
const int row2 = 3; // the number of the row pin 23
const int row3 = 4; // the number of the row pin 22
const int row4 = 5; // the number of the row pin 21
const int row5 = 17; // the number of the row pin 4
const int row6 = 16; // the number of the row pin 3
const int row7 = 15; // the number of the row pin 2
const int row8 = 14; // the number of the row pin 1
//the pin to control COl
const int col1 = 6; // the number of the col pin 20
const int col2 = 7; // the number of the col pin 19
const int col3 = 8; // the number of the col pin 18
const int col4 = 9; // the number of the col pin 17
const int col5 = 10; // the number of the col pin 16
const int col6 = 11; // the number of the col pin 15
const int col7 = 12; // the number of the col pin 14
const int col8 = 13; // the number of the col pin 13

void displayNum(byte rowNum,int colNum)
{
  int j;
  byte temp = rowNum;
  for(j=2;j<6;j++)
  {
    digitalWrite(j, LOW);
  }
  digitalWrite(row5, LOW);
  digitalWrite(row6, LOW);
  digitalWrite(row7, LOW);
  digitalWrite(row8, LOW);
  for(j=6;j<14;j++)
  {
    digitalWrite(j, HIGH); }
    switch(colNum)
    {
      case 1: digitalWrite(col1, LOW); break;
      case 2: digitalWrite(col2, LOW); break;
      case 3: digitalWrite(col3, LOW); break;
      case 4: digitalWrite(col4, LOW); break;
      case 5: digitalWrite(col5, LOW); break;
      case 6: digitalWrite(col6, LOW); break;
      case 7: digitalWrite(col7, LOW); break;
      case 8: digitalWrite(col8, LOW); break;
      default: break;
    }
    for(j = 1 ;j < 9; j++)
    {
      temp = (0x80)&(temp) ;
      if(temp==0)
      {
        temp = rowNum<<j;
        continue;
      }
      switch(j)
      {
        case 1: digitalWrite(row1, HIGH); break;
        case 2: digitalWrite(row2, HIGH); break;
        case 3: digitalWrite(row3, HIGH); break;
        case 4: digitalWrite(row4, HIGH); break;
        case 5: digitalWrite(row5, HIGH); break;
        case 6: digitalWrite(row6, HIGH); break;
        case 7: digitalWrite(row7, HIGH); break;
        case 8: digitalWrite(row8, HIGH); break;
        default: break;
     }
    temp = rowNum<<j;
  }
}

void setup(){
  int i = 0 ;
  for(i=2;i<18;i++)
  {
    pinMode(i, OUTPUT);
  }

  for(i=2;i<18;i++) {
    digitalWrite(i, LOW);
  }
}
void loop(){
  int t1;
  int l;
  int arrage;
  for(arrage=0;arrage<10;arrage++)
  {
    for(l=0;l<512;l++)
    {
      for(t1=0;t1<8;t1++)
      {
        displayNum(data_ascii[arrage][t1],(t1+1));
      }
    }
  }
}
