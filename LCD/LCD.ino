#include <SPI.h> // Including the SPI communication library as the lcd uses SPI communication.
#include <Adafruit_GFX.h> // Graphical Library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <avr/pgmspace.h>

#define TFT_CS 10 // Declaring PIN numbers for connecting LCD.                     
#define TFT_RST 9
#define TFT_DC 8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST); //Creating an object of LCD Class

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

static const uint8_t myBitmap [] PROGMEM = {
   0x00, 0x07, 0x00, 0x80, 0x1f, 0x00, 0x80, 0x79, 0x00, 0x80, 0x78, 0x00,
   0x80, 0x18, 0x00, 0x80, 0x1e, 0x00, 0x80, 0x7e, 0x00, 0x80, 0x7e, 0x00,
   0x80, 0x1e, 0x00, 0x80, 0x1e, 0x00, 0x80, 0x1e, 0x00, 0xc0, 0x3e, 0x00,
   0x60, 0x7f, 0x00, 0xa0, 0x7f, 0x00, 0xa0, 0x7f, 0x00, 0xe0, 0x7f, 0x00,
   0xe0, 0x7f, 0x00, 0xc0, 0x3f, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x0f, 0x00 };


static const uint8_t myBitmap1 [] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0x03, 0x00,
   0x7e, 0x04, 0x00, 0xff, 0x00, 0x00, 0xfc, 0x03, 0x00, 0xc0, 0x07, 0x00,
   0x80, 0x0f, 0x00, 0xc0, 0x0f, 0x00, 0xc0, 0x1d, 0x00, 0x60, 0x38, 0x00,
   0xe0, 0x70, 0x00, 0x80, 0xe3, 0x00, 0x00, 0x86, 0x03, 0x00, 0x02, 0x04,
   0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t myBitmap2 [] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0x01, 0xfc, 0xf9, 0x03,
   0xfe, 0xff, 0x07, 0xfe, 0xff, 0x0f, 0xfe, 0xff, 0x0f, 0xfe, 0xff, 0x0f,
   0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0xfc, 0xff, 0x07, 0xfc, 0xff, 0x03,
   0xf8, 0xff, 0x01, 0xf0, 0xff, 0x00, 0xc0, 0x7f, 0x00, 0xc0, 0x3f, 0x00,
   0x00, 0x1f, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };

   static const uint8_t myBitmap3 [] PROGMEM = {
   0x80, 0x1f, 0x00, 0x80, 0x1f, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x06, 0x00,
   0x00, 0x80, 0x01, 0x80, 0x9f, 0x01, 0xe0, 0x7f, 0x01, 0x70, 0xe0, 0x00,
   0x30, 0xc6, 0x00, 0x18, 0x86, 0x01, 0x08, 0x06, 0x01, 0x0c, 0x06, 0x03,
   0x0c, 0x06, 0x03, 0x08, 0x06, 0x01, 0x18, 0x80, 0x01, 0x18, 0x80, 0x01,
   0x30, 0xc0, 0x00, 0xe0, 0x70, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x0f, 0x00 };

int16_t secs=0,mins=0,hour=0,day=25,SWsecs=0;

void setup() {
  Serial.begin(9600);     //Initializing the serial monitor
  tft.initR();            //Initializing the LCD 
//  HB_anim();
//  welcome_note();         // Display the Welcome Note
    tft.fillScreen(CYAN);
    tft.drawXBitmap(30, 30, myBitmap, 20, 20, RED);
    tft.drawXBitmap(30, 70, myBitmap1, 20, 20, RED);
    tft.drawXBitmap(70, 30, myBitmap2, 20, 20, RED);
    tft.drawXBitmap(70, 70, myBitmap3, 20, 20, RED);
}

void loop(void) {
    
//  display_time(hour,mins,secs);
//  display_date_and_day(day,4,2017);
//  delay(1000);
//  secs++;
//  hour++;
////  tft.drawLine(Line_x0,Line_y0,Line_x1,Line_y1,RED); //Draw a diagonal line
////  tft.drawRect(start_x,start_y,rect_w,rect_h,BLACK); //Draw a rectangle
}

//void Heart()
//{
//  tft.setTextColor(BLACK);
//  tft.drawBitmap(50, 50, myBitmap, 30, 30, BLACK);
//}
//
//
//
//
//void display_time(int16_t hour,int16_t mins,int16_t secs)
//{
//  uint16_t bcolor = CYAN;
//  tft.setTextColor(BLACK);
//  display_hour(bcolor);
//  tft.print(":");
//  display_mins(bcolor);
//  display_secs(bcolor);
//}
//
//void display_secs(uint16_t bcolor)
//{
//  tft.fillRect(96,45,22,15,bcolor);
//  tft.setTextSize(2);
//  tft.setCursor(96,45);
//  if(secs<10)
//    tft.print("0");
//  tft.print(secs);
//}
//
//void display_mins(uint16_t bcolor)
//{
//  tft.fillRect(58,45,34,21,bcolor);
//  tft.setTextSize(3);
//  tft.setCursor(58,45);
//  if(mins<10)
//    tft.print("0");
//  tft.print(mins);
//}
//
//void display_hour(uint16_t bcolor)
//{
//  tft.fillRect(5,45,34,21,bcolor);
//  tft.setCursor(5,45);
//  tft.setTextSize(3);
//  if(hour<10)
//    tft.print("0");
//  tft.print(hour);
//}
//
//void display_date_and_day(int16_t day,int16_t month,int16_t year)
//{
//  // The algorithm is taken from the following source.
//  // Michael Keith and Tom Craver. (1990). The ultimate perpetual calendar? Journal of Recreational Mathematics, 22:4, pp.280-282.
//  byte y=year, m=month, d=day;
//  tft.setTextColor(BLACK);
//  static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
//  if(m<3)
//    y -= m;
//  byte DOW=(y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
//  tft.fillRect(5,20,112,15,BLUE);
//  tft.setCursor(5,20);
//  tft.setTextSize(2);
//  switch(DOW){
//    case 0:
//      tft.print("Mon");
//      break;
//    case 1:
//      tft.print("Tue");
//      break;
//    case 2:
//      tft.print("Wed");
//      break;
//    case 3:
//      tft.print("Thu");
//      break;
//    case 4:
//      tft.print("Fri");
//      break;
//    case 5:
//      tft.print("Sat");
//      break;
//    case 6:
//      tft.print("Sun");
//      break;
//    default:
//      tft.setTextColor(CYAN);
//      tft.print("   ");
//      break;          
//  }
//  tft.print(",");
//  switch(month){
//    case 1:
//      tft.print("Jan");
//      break;
//    case 2:
//      tft.print("Feb");
//      break;
//    case 3:
//      tft.print("Mar");
//      break;
//    case 4:
//      tft.print("Apr");
//      break;
//    case 5:
//      tft.print("May");
//      break;
//    case 6:
//      tft.print("Jun");
//      break;
//    case 7:
//      tft.print("Jul");
//      break;
//    case 8:
//      tft.print("Aug");
//      break;
//    case 9:
//      tft.print("Sep");
//      break;
//    case 10:
//      tft.print("Oct");
//      break;
//    case 11:
//      tft.print("Nov");
//      break;      
//    case 12:
//      tft.print("Dec");
//      break;      
//    default:
//      tft.setTextColor(CYAN);
//      tft.print("   ");
//      break;          
//  }
//  tft.setTextSize(1);
//  tft.print(" ");
//  tft.setTextSize(2);
//  if(day<10)
//    tft.print("0");
//  tft.print(day);
//}
//
//void welcome_note() // Function for printing Welcome Note on LCD Screen
//{
//  tft.fillScreen(BLACK);
//  tft.setCursor(30,20);
//  tft.setTextColor(CYAN);
//  tft.setTextSize(3);
//  tft.println("SDGP");
//  tft.setTextSize(1);
//  tft.setCursor(10,65);
//  tft.println("HEALTH AND FITNESS");
//  tft.setCursor(12,78);
//  tft.println("MANAGEMENT SYSTEM");
//  tft.setCursor(40,95);
//  tft.println("GROUP 2");
//}
//void HB_anim()
//{
//  tft.fillScreen(BLACK);
//  for(int i=0;i<5;i++)
//  {
//    HB_line(BLUE);
//    HB_line(BLACK);
//    delay(500);
//  }
//}

//void HB_line(char color)
//{
//  slow_Hline(0,15,63,color);
//  slow_D_upline(15,25,63,color);
//  slow_D_downline(25,48,13,color);
//  slow_D_upline(48,69,127,color);
//  slow_D_downline(69,85,23,color);
//  slow_D_upline(85,98,103,color);
//  slow_D_downline(98,103,38,color);
//  slow_Hline(103,128,63,color);
//}
//
//void slow_Hline(int16_t xs,int16_t xe,int16_t y,char color)
//{
//  for(int i=xs;i<xe;i+=2)
//  {
//    tft.drawPixel(i,y,color);
//    delay(10);
//  }
//}
//
//void slow_D_upline(int16_t xs,int16_t xe,int16_t y,char color)
//{
//  for(int i=xs;i<xe;i++)
//  {
//    y-=5;
//    tft.drawPixel(i,y,color);
//    delay(5);
//  }
//}
//void slow_D_downline(int16_t xs,int16_t xe,int16_t y,char color)
//{
//  for(int i=xs;i<xe;i++)
//  {
//    y+=5;
//    tft.drawPixel(i,y,color);
//    delay(5);
//  }
//}
