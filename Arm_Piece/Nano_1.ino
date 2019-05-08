// Arduino Nano_1 LCD, RTC, Pulse Sensor, Bluetooth.
// Muhammad Ijlal
// Muhammad Asad
// Faheem Abbas
// Muhammad Mudasir
 
#include <SPI.h> // Including the SPI communication library as the lcd uses SPI communication.
#include <Adafruit_GFX.h> // Graphical Library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <Pushbutton.h>
#include <Math.h>
#include <avr/interrupt.h>
#include <DS3231.h>
#include <SoftwareSerial.h>

#define TFT_CS 10 // Declaring PIN numbers for connecting LCD.                     
#define TFT_RST 9
#define TFT_DC 8
#define beat A1
#define B_tx 4
#define B_rx 5


static const uint8_t tempr [] PROGMEM = {
   0x00, 0x07, 0x00, 0x80, 0x1f, 0x00, 0x80, 0x79, 0x00, 0x80, 0x78, 0x00,
   0x80, 0x18, 0x00, 0x80, 0x1e, 0x00, 0x80, 0x7e, 0x00, 0x80, 0x7e, 0x00,
   0x80, 0x1e, 0x00, 0x80, 0x1e, 0x00, 0x80, 0x1e, 0x00, 0xc0, 0x3e, 0x00,
   0x60, 0x7f, 0x00, 0xa0, 0x7f, 0x00, 0xa0, 0x7f, 0x00, 0xe0, 0x7f, 0x00,
   0xe0, 0x7f, 0x00, 0xc0, 0x3f, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x0f, 0x00 };


static const uint8_t sp [] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0x03, 0x00,
   0x7e, 0x04, 0x00, 0xff, 0x00, 0x00, 0xfc, 0x03, 0x00, 0xc0, 0x07, 0x00,
   0x80, 0x0f, 0x00, 0xc0, 0x0f, 0x00, 0xc0, 0x1d, 0x00, 0x60, 0x38, 0x00,
   0xe0, 0x70, 0x00, 0x80, 0xe3, 0x00, 0x00, 0x86, 0x03, 0x00, 0x02, 0x04,
   0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t heart [] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0x01, 0xfc, 0xf9, 0x03,
   0xfe, 0xff, 0x07, 0xfe, 0xff, 0x0f, 0xfe, 0xff, 0x0f, 0xfe, 0xff, 0x0f,
   0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0xfc, 0xff, 0x07, 0xfc, 0xff, 0x03,
   0xf8, 0xff, 0x01, 0xf0, 0xff, 0x00, 0xc0, 0x7f, 0x00, 0xc0, 0x3f, 0x00,
   0x00, 0x1f, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };

static const uint8_t clk [] PROGMEM = {
   0x80, 0x1f, 0x00, 0x80, 0x1f, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x06, 0x00,
   0x00, 0x80, 0x01, 0x80, 0x9f, 0x01, 0xe0, 0x7f, 0x01, 0x70, 0xe0, 0x00,
   0x30, 0xc6, 0x00, 0x18, 0x86, 0x01, 0x08, 0x06, 0x01, 0x0c, 0x06, 0x03,
   0x0c, 0x06, 0x03, 0x08, 0x06, 0x01, 0x18, 0x80, 0x01, 0x18, 0x80, 0x01,
   0x30, 0xc0, 0x00, 0xe0, 0x70, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x0f, 0x00 };

SoftwareSerial slave =  SoftwareSerial(B_rx, B_tx);
DS3231  rtc(SDA, SCL);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST); //Creating an object of LCD Class

int16_t prefun,secs,mins,hrs,day,mnth,year; // declare varaibles to save the previous value of different entities of time and date.
#define funB 2   // set the value of funB i.e. the function button to 2, the pin to which the button is connected.
volatile int8_t fun=0; // declare variables to save the state of different controls.
#define buzzer 12
uint16_t bcolor;
#define stateB 3
#define buzzer 12

int bpm , thresh;//bpm=beat per mint(heart rate)   //thresh is 70% of high peak
int val[100]={};  //array to read 100 analoglog values from sensor
int peak[100]={} ,tt , high_peak, total_peak , avg , tm, tmp=0;
int Speed_R;  // Variable to receive the speed value from accelerometer. 
int weight=115;
float dis=0;
volatile int SWsecs=0,SWhrs=0,SWmins=0;

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Time t;

void InitializeInterrupt() // initialize interrupts
{
  cli(); // disable global interrupts
//  EIMSK=0b00000011; // Enabling both external interrupts.
//  EICRA=0b00001111; // Using Rising Edge as external interrupt trigger.
  TCCR1A = 0; // set entire TCCR1A register to 0.
  TCCR1B = 0; // same for TCCR1B.
  OCR1A = 15624;// set compare match register to 15624 that is 1s for a 16Mhz clock:
  TCCR1B |= (1 << WGM12); // turn on CTC mode i.e clear timer on match:
  TCCR1B |= (1 << CS10); // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt:
  sei(); // enable global interrupts:
}

void InitializeIO()
{
  pinMode(buzzer,OUTPUT);
  pinMode(funB,INPUT);
  pinMode(beat,INPUT);
}

void Initprevalues()
{
  t=rtc.getTime();
  secs=t.sec;
  mins=t.min;
  hrs=t.hour;
  day=t.date;
  prefun=1;
}

void sendtime()
{
  slave.write(t.sec);
  slave.write(t.min);
  slave.write(t.hour);
  slave.write(t.date);
  slave.write(t.mon);
  slave.write(t.year%100); 
}

void setup()
{
  slave.begin(38400);
  Serial.begin(9600);
  rtc.begin();
  tft.initR();            //Initializing the LCD 
//  HB_anim();
//  welcome_note();       // Display the Welcome Note
  InitializeIO();
  Initprevalues();
  InitializeInterrupt();
}

void loop()
{
  if(fun==0)
  {
    if(prefun!=fun)
    {
      bcolor=CYAN;
      tft.fillScreen(bcolor);
      display_time();
      display_date_and_day();
      display_heart_beat();
      display_Speed();
      display_temp();
      //display_Cal();
      display_Stopwatch();
      prefun=fun;  
    }  
    beat_over_10secs();
    bpm=tt;
    Serial.print("Your Heart Beat is(Beat per 10secs):");
    Serial.println(bpm); //printing BPM on screen
    slave.write(bpm);
    if(tmp==6)
    {
      Serial.print("Your Heart Beat is(Beat per mint):");
      Serial.println(tm); //printing BPM on screen
      slave.write(tm);
      sendtime();
      display_beat();
      tmp=0;
      tm=0;
    }
    peak[100]={0};
    val[100]={0};
    //cal_and_display_C();
    display_T();
  }
}

void cal_distance()
{
  float S=Speed_R/100.0;
  dis=dis+((S*2.23)/3600.0);
}

void cal_and_display_C()
{
  int Cal = weight*0.63*dis;
  tft.fillRect(53,109,46,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(53,109);
  tft.print(Cal);
}

void display_Cal()
{
  tft.setTextColor(RED);
  tft.fillRect(7,109,46,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(7,109);
  tft.print("Cal:");
  tft.setTextColor(BLACK);
  cal_and_display_C();
}

void display_Stopwatch()
{
  tft.fillRect(7,104,20,20,bcolor);
  tft.drawXBitmap(7,104, clk, 20, 20, RED);
  tft.drawRect(29,106,89,18,RED);
  display_SWh();
  tft.setCursor(55,108);
  tft.print(":");
  display_SWm();
  tft.setCursor(84,108);
  tft.print(":");
  display_SWs();
}

void display_SWs()
{
  tft.fillRect(92,108,22,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(92,108);
  if(SWsecs<10)
    tft.print("0");
  tft.print(SWsecs);
}

void display_SWm()
{
  tft.fillRect(64,108,22,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(64,108);
  if(SWmins<10)
    tft.print("0");
  tft.print(SWmins);
}

void display_SWh()
{
  tft.fillRect(35,108,22,15,bcolor);
  tft.setCursor(35,108);
  tft.setTextSize(2);
  if(SWhrs<10)
    tft.print("0");
  tft.print(SWhrs);
}

void display_T()
{
  tft.fillRect(95,69,22,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(95,69);
  int T = rtc.getTemp();
  tft.print(T);
}

void display_temp()
{
  tft.fillRect(72,67,20,20,bcolor);
  tft.drawXBitmap(72, 67, tempr, 20, 20, RED);
  display_T();
}

void display_S()
{
  tft.fillRect(50,89,46,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(50,89);
  float S=Speed_R/100.0;
  tft.print(S);
}

void display_Speed()
{
  tft.fillRect(25,87,20,20,bcolor);
  tft.drawXBitmap(25,87, sp, 20, 20, RED);
  display_S();
}

void display_beat()
{
  tft.fillRect(35,69,34,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(35,69);
  tft.print(tm);
}

void display_heart_beat()
{
  tft.fillRect(7,67,20,20,bcolor);
  tft.drawXBitmap(7,67 , heart, 20, 20, RED);
  display_beat();
}

ISR(TIMER1_COMPA_vect)
{
  t=rtc.getTime();
  SWsecs++;
  if(fun==0)
  {
    if(secs!=t.sec)
    {
      display_secs();
      secs=t.sec;
      display_SWs();
      if(mins!=t.min)
      {
        display_mins();
        mins=t.min;
        display_SWm();
        if(hrs!=t.hour)
        {
          display_hour();
          hrs=t.hour;
          display_SWh();
          if(day!=t.date)
          {
            display_date_and_day();
            day=t.date;
          }
        }
      }
    }
    display_S();
  }
  if(slave.available()>0) 
  {
    Speed_R=slave.read();
  }
  cal_distance();
  StopWatch();
}

ISR(INT0_vect)
{
//  byte fp=digitalRead(funB); 
//  delay(100);
//  if(fp==digitalRead(funB))
//    fun=(fun+1)%2;
}

ISR(INT1_vect)
{
//  byte sp=digitalRead(stateB);
//  delay(100);
//  if(sp==digitalRead(stateB))
//  {
//    if(fun==0)
//      showdate=1;
//    else if(fun<=3)
//      state=(state+1)%3;
//  }
}

void StopWatch()
{
  if(SWsecs==60)
  {
    SWsecs=0;
    SWmins++;
    if(SWmins==60)
    {
      SWmins=0;
      SWhrs++;
      if(SWhrs==100)
      {
        SWhrs=0;
      }
    }
  }
}

void display_time()
{
  tft.setTextColor(BLACK);
  display_hour();
  tft.print(":");
  display_mins();
  display_secs();
}

void display_secs()
{
  tft.fillRect(96,41,22,15,bcolor);
  tft.setTextSize(2);
  tft.setCursor(96,41);
  if(t.sec<10)
    tft.print("0");
  tft.print(t.sec);
}

void display_mins()
{
  tft.fillRect(58,41,34,21,bcolor);
  tft.setTextSize(3);
  tft.setCursor(58,41);
  if(t.min<10)
    tft.print("0");
  tft.print(t.min);
}

void display_hour()
{
  tft.fillRect(5,41,34,21,bcolor);
  tft.setCursor(5,41);
  tft.setTextSize(3);
  if(t.hour<10)
    tft.print("0");
  tft.print(t.hour);
}

void display_date_and_day()
{
  // The algorithm is taken from the following source.
  // Michael Keith and Tom Craver. (1990). The ultimate perpetual calendar? Journal of Recreational Mathematics, 22:4, pp.280-282.
  byte y=t.year,m=t.mon,d=t.date;
  static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  if(m<3)
    y -= m;
  byte DOW=(y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
  tft.fillRect(5,16,112,15,bcolor);
  tft.setCursor(5,16);
  tft.setTextSize(2);
  switch(DOW){
    case 0:
      tft.print("Mon");
      break;
    case 1:
      tft.print("Tue");
      break;
    case 2:
      tft.print("Wed");
      break;
    case 3:
      tft.print("Thu");
      break;
    case 4:
      tft.print("Fri");
      break;
    case 5:
      tft.print("Sat");
      break;
    case 6:
      tft.print("Sun");
      break;
    default:
      tft.print("   ");
      break;          
  }
  tft.print(",");
  tft.print(rtc.getMonthStr(1));
  tft.setTextSize(1);
  tft.print(" ");
  tft.setTextSize(2);
  if(d<10)
    tft.print("0");
  tft.print(d);
}

void values()
{
  for(int i=0 ; i<100 ; i++) //loop to read values 100 times
  {
    int a=analogRead(A0);
    val[i]=a;//reading values from pin A0
    delay(20);
  }
}

int peak_detection()
{
  int a=0;
  for(int i=0 ; i<100; i++)
  {
    if(val[i]<val[i+1]) //comparing two values
    {
      if(val[i+1]>val[i+2]) //comparing two idex values
      {
        peak[a]=val[i+1]; //if one of the value is detected as peak then it will be saved in new array
        a++;//a is increasing to increase the index of peak array
      }
    }
  }
  a--;
  threshhold(a);
  //return total_peak;
}

int threshhold(int a)
{
  high_peak=peak[0];
   for(int i=0 ; i<=a ; i++) //detecting the highest value in array
  {
    if(high_peak<peak[i])
    high_peak=peak[i];
  }
  thresh=(0.98 * high_peak); //99% of highest value
  nop(thresh , peak ,a); //detecting the number of peaks which has value high than thresh
}

int nop(int thresh , int peak[100] , int a)
{
  int tp=0;
  for(int i=0 ; i<=a ; i++)
  {
    if(peak[i]>thresh)//if ith index of peak array will be greater than thresh, it will count as peak
    tp++;
  }
  total_peak=tp;//total number of peaks
}

int beat_over_10secs()
{
  tt=0;
  for(int i=0 ; i<5 ;i++)
  {
    values();//calling the values function to save the sensor values
    peak_detection();//detecting peak and return a value
    tt+=total_peak;
  }
  tmp++;
  tm+=tt;
}

void welcome_note() // Function for printing Welcome Note on LCD Screen
{
  tft.fillScreen(BLACK);
  tft.setCursor(30,20);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println("SDGP");
  tft.setTextSize(1);
  tft.setCursor(10,65);
  tft.println("HEALTH AND FITNESS");
  tft.setCursor(12,78);
  tft.println("MANAGEMENT SYSTEM");
  tft.setCursor(40,95);
  tft.println("GROUP 2");
}
void HB_anim()
{
  tft.fillScreen(BLACK);
  for(int i=0;i<5;i++)
  {
    HB_line(BLUE);
    HB_line(BLACK);
    delay(500);
  }
}

void HB_line(char color)
{
  slow_Hline(0,15,63,color);
  slow_D_upline(15,25,63,color);
  slow_D_downline(25,48,13,color);
  slow_D_upline(48,69,127,color);
  slow_D_downline(69,85,23,color);
  slow_D_upline(85,98,103,color);
  slow_D_downline(98,103,38,color);
  slow_Hline(103,128,63,color);
}

void slow_Hline(int16_t xs,int16_t xe,int16_t y,char color)
{
  for(int i=xs;i<xe;i+=2)
  {
    tft.drawPixel(i,y,color);
    delay(10);
  }
}

void slow_D_upline(int16_t xs,int16_t xe,int16_t y,char color)
{
  for(int i=xs;i<xe;i++)
  {
    y-=5;
    tft.drawPixel(i,y,color);
    delay(5);
  }
}
void slow_D_downline(int16_t xs,int16_t xe,int16_t y,char color)
{
  for(int i=xs;i<xe;i++)
  {
    y+=5;
    tft.drawPixel(i,y,color);
    delay(5);
  }
}
//  S_km = Speed*3600/1000;
