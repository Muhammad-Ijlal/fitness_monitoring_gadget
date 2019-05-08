/*
Nano 2, Devices Accelerometer, Bluetooth (Master), SDcard
Group # 2
Muhammad Asad
Faheem Abbas
Muhammad Mudasir
Muhammad Ijlal
*/ 

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

#define B_tx 2 // Arduino pin 2 declared transmitter
#define B_rx 3 // Arduino pin 3 declared receiver
volatile int secs=0,mins=0,hrs=0,day=0,mnth=0,year=0;

SoftwareSerial master =  SoftwareSerial(B_rx, B_tx);

File SPEED, H, RTC, SEC;  // SDcard File declaration.

float x,y,z ; 
float x1,y1,z1;
float x2,y2,z2;
float A[50]= {};
int A_len = 50;
float B[50]= {};
int B_len = 50;
float add1 =0;
int c1= 0;
float Dist, Dist1;
float h1,tri1,rect1;
float add =0;
int c = 0;
float D;
float x_diff, y_diff, z_diff;
float Speed, S_km;
float h,tri,rect;
int tmp=0,tm,bpm;

//void get_sync()
//{
//  master.write('a');
//  int y=master.available();
//  Serial.println(y);
//  while(y==0)
//  {
//    master.write('a');
//    Serial.println(y);
//    y=master.available();
//  }
//  char x=master.read();
//  while(x!='b')
//  {
//    Serial.print("waiting");
//    x=master.read();
//    Serial.println(x);
//  }
//  secs=master.read();
//  delay(2);
//  mins=master.read();
//  delay(2);
//  hrs=master.read();
//  delay(2);
//  day=master.read();
//  delay(2);
//  mnth=master.read();
//  delay(2);
//  year=master.read();
//  Serial.println(year);
//}

void get_time()
{
  secs=master.read();
  delay(2);
  mins=master.read();
  delay(2);
  hrs=master.read();
  delay(2);
  day=master.read();
  delay(2);
  mnth=master.read();
  delay(2);
  year=master.read();
  Serial.println(year);
}

void write_time()
{
//  RTC.print(secs);
//  RTC.print('/');
    RTC.print(mins);
//  RTC.print('/');
//  RTC.print(hrs);
//  RTC.print('/');
//  RTC.print(day);
//  RTC.print('/');
//  RTC.print(mnth);
//  RTC.print('/');
//  RTC.println(year);
}

void setup() 
{
 master.begin(38400);
 Serial.begin(9600);
 if (!SD.begin(4)) 
 {
   Serial.println("initialization failed!");
   return;
   // need to give declaration on lcd
 }
}

void loop() 
{
  while(1)
  {
    x2 =x1;
    y2 =y1;
    z2 =z1;
    delay(20);
    x =analogRead(A0);       // Reading x-axis value of the accelerometer ADXL335.
    y =analogRead(A1);       // Reading y-axis value of the accelerometer ADXL335.
    z =analogRead(A2);       // Reading z-axis value of the accelerometer ADXL335.
    // Below converting from a 0 to 1023 digital range      // to 0 to 3.3 volts (each 1 reading equals ~ 3.3 millivolts)
    x=(3.3*x/1023);         // x-axis value conversion 
    y=(3.3*y/1023);         // y-axis value conversion
    z=(3.3*z/1023);         // z-axis value conversion    
    x1 = (x-1.45);        // Setting offset 1.45 of x-axis value.
    y1 = (y-1.11);        // Setting offset 1.11 of x-axis value.
    z1 = (z-1.36);        // Setting offset 1.36 of x-axis value.       
    x_diff = x2-x1;       // Taking difference of two x-axis values. 
    y_diff = y2-y1;       // Taking difference of two y-axis values. 
    z_diff = z2-z1;       // Taking difference of two z-axis values.      
    D =sq(x_diff)+sq(y_diff)+sq(z_diff); // Applying distance formula by using axis values.
    D = sqrt(D);
    A[c]= (D);                                    // Using Array A.
    c = c+1;
    if (c==50)                                
    {
      add = 0;
      for(int i=0;i<50;i++)                   // Using for Loop till Array-A lenght.
      {
        if(A[i]>A[i+1])                    // Comparing two indexs values of Array_A. 
        {
          h=A[i]-A[i+1];                // Taking difference of two indexs values of Array_A.  
        }
        else
        {
          h=A[i+1]-A[i];                // Taking difference of two indexs values of Array_A.
        }                             
        tri=(0.02*h)/2;                   // Using Triangle formula (Width*Hight)/2.
        rect=A[i]*0.02;                   // Using Rectangle formula (Hight of every index*Width).
        add=add+(rect-tri);               // To find the required values of Speed.
      }
      c = 0;
      Speed= add;
      int send_format=Speed*100;
      master.write(send_format);
      SPEED = SD.open("SPEED.txt", FILE_WRITE);
      if (SPEED) 
      {  
        SPEED.println(Speed);
        SPEED.close();
      }
      break; 
      SEC = SD.open("SEC.txt", FILE_WRITE);
      if (SEC) 
      {  
        SEC.println(secs);
        SEC.close();
      }
      break; 
    }
  }
  if(master.available()>0)
  {
    bpm=master.read();
    tmp++;
    Serial.print(tmp);
    Serial.print("bpm ");
    Serial.println(bpm); //printing BPM on screen
    if(tmp==6)
    {
      delay(50);
      tm=master.read();
      get_time();
      Serial.println(tm);
      tmp=0;
      H = SD.open("H.txt", FILE_WRITE);
      if (H) 
      {  
        H.println(tm);
        H.close();
      }
      RTC = SD.open("RTC.txt", FILE_WRITE);
      if (RTC) 
      {  
        write_time();
        RTC.close();
      }
    }
  }
}


