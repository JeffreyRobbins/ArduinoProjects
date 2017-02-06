//************************* Include Librarie ******************************
#include <LiquidCrystal.h>  //         Liquid Crystal library             *
#include <Wire.h>           //         Wire library                       *
#include <Time.h>           //         Time library                       *
#include <DS1307RTC.h>      //         DS1307 Real time clock library     *
//*************************************************************************

//*************************************************************************
LiquidCrystal lcd(12, 11,7, 6, 5, 4);//Setup lcd variables                *
//*************************************************************************

//************************* Define variables *****************************
int contrastPin = 10;      //          Pin for display contrast          *
int backLightPin = 9;      //          Pin for Backlight                 *
int contrast = 20;         //          Value for contrast                *
int backLight = 0;         //          Value for Display brightness      *
byte tic = 0;              //          Place holder for spec char        *
byte cursorLocation = 15;  //          Place holder ofr cursor pos       *
byte displayPosition = 32; //          Place holder for char pos         *
byte firstLetter = 0;      //          Place holder for first letter     *
byte lastLetter = 1;       //          Place holder for last letter      *
//************************************************************************

//**************************Define varaibles******************************
String stringMessage = "Hey Bud, I got the new LCD displays today... Yahoo!!!  Oh, and by the way, DANIEL IS AWESOME!!!  YEAH... ";
//************************************************************************

//************************************************************************
const char *dayOfWeek[8] =    //                                         *
  {"Err","Sun","Mon","Tue",   //       Setup Dayu of Week array          *
   "Wed","Thu","Fri","Sat"};  //                                         *
//************************************************************************
  
//************************* Define spec characters *************************
byte one[8] = {                 //                                         *
  0b01110,                      //                                         *   
  0b11101,                      //                                         *
  0b11111,                      //           Spec character one            *
  0b11111,                      //                                         *
  0b11111,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     //                                         *
//**************************************************************************
byte two[8] = {                 //                                         *
  0b01110,                      //                                         *
  0b11101,                      //                                         *
  0b11111,                      //           Spec character two            *
  0b11000,                      //                                         *
  0b11111,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     //                                         *
//**************************************************************************
byte three[8] = {               //                                         *
  0b01110,                      //                                         *
  0b11011,                      //                                         *
  0b11110,                      //           Spec character three          *
  0b10000,                      //                                         *
  0b11110,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     
//**************************************************************************
byte four[8] = {                //                                         * 
  0b01110,                      //                                         *
  0b11011,                      //                                         *
  0b11110,                      //           Spec character four           *
  0b10000,                      //                                         *
  0b11110,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     //                                         *
//**************************************************************************
byte five[8] = {                //                                         *
  0b01110,                      //                                         *
  0b11011,                      //                                         *
  0b11110,                      //           Spec character five           *
  0b11000,                      //                                         *
  0b11110,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     //                                         *
//**************************************************************************
byte six[8] = {                 //                                         *
  0b01110,                      //                                         *
  0b11101,                      //                                         *
  0b11111,                      //           Spec character six            *
  0b11000,                      //                                         *
  0b11111,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     //                                         *
//**************************************************************************
byte seven[8] = {               //                                         *
  0b01110,                      //                                         *
  0b11101,                      //                                         *
  0b11111,                      //           Spec character seven          *
  0b11111,                      //                                         *
  0b11111,                      //                                         *
  0b11111,                      //                                         *
  0b01110,                      //                                         *
  0b00000};                     //                                         *
//**************************************************************************

//****************************** Start of setup ****************************
void setup() {                            //                               *
  Serial.begin(9600);                     //  Start serial                 *
  lcd.begin(16, 4);                       //  Setup lcd size               *
  lcd.createChar(0, one);                 //  Load spec char one           *
  lcd.createChar(1, two);                 //  Load spec char two           *
  lcd.createChar(2, three);               //  Load spec char three         *
  lcd.createChar(3, four);                //  Load spec char four          *
  lcd.createChar(4, five);                //  Load spec char five          *
  lcd.createChar(5, six);                 //  Load spec char six           *
  lcd.createChar(6, seven);               //  Load spec char seven         *
//**************************************************************************

//************************ Set contrast and backlihgt **********************
  pinMode(contrastPin, OUTPUT);          //  Setup contrast pin for output *
  analogWrite(contrastPin,contrast);     //  Set contrast                  *
  pinMode(backLightPin, OUTPUT);         //  Setup backlight pit           *
  analogWrite(backLightPin, backLight);  //  Set backlight                 *
}                                        //  End of setup                  *
//**************************************************************************

//***************************** Program loop *******************************
void loop() {                            //                                *
  tmElements_t tm;                       //  Set time elements             *
                                         //                                *
  lcd.setCursor(0,0);                    //  Set cursor position           *
//************************** Read real time clock **************************
  if (RTC.read(tm)) {                    //  Read time form RTC            *
    //Serial.print("Ok, Time = ");       //  Used for debugging            *
    if(tm.Hour > 12){                    //  Check for military time       *
      print2digits(tm.Hour - 12);        //  Set to standard time          *
    }                                    //                                *
//************************** Adjust for 24hr format ************************
    else if(tm.Hour == 0) {              //  Check for military time       *
      print2digits(tm.Hour + 12);        //  Set to standard time and      *
    }                                    //    print Hour                  *
//************************** Call print subroutine *************************
    else {                               //                                *
      print2digits(tm.Hour);             //  Print Hour                    *
    }                                    //                                *
//************************** Print Minute and Second ***********************
    lcd.print(":");                      //  Print a colon                 *
    print2digits(tm.Minute);             //  Print the Minute              *
    lcd.print(":");                      //  Print a colon                 *
    print2digits(tm.Second);             //  Print the Second              *
//******************* Adjust for 24hr format convert to PM ***************** 
    if(tm.Hour >= 12) {                  //  Check for military time       *
      lcd.print(" PM ");                 //  Print standard time PM        *
    }                                    //                                *
//******************* Adjust for 24hr format convert to AM ***************** 
    else {                               //                                *
      lcd.print(" AM ");                 //  Print standard time AM        *
    }                                    //                                *
//**************************************************************************
    //lcd.write(tic);                    //  Used to print spec char 1st ln*
    tic++;                               //  Incement spec char pointer    *
//                                                                         *
//**************************** Print Day and Date **************************
//                                                                         *
    lcd.setCursor(0,1);                  //  Set cursor position           *
    lcd.print(dayOfWeek[tm.Wday]);       //  Print Day of week             *
    lcd.print(" ");                      //  Leave a space                 *
    lcd.print(tm.Month);                 //  Print Month                   *
    lcd.print("/");                      //  Print a slash                 *
    lcd.print(tm.Day);                   //  Print the Day                 *
    lcd.print("/");                      //  Print a slash                 *
    lcd.print(tmYearToCalendar(tm.Year));//  Print the Year                *
//                                                                         *
//**** Routine for scrolling one line keeping track of cursor position *****
//                                                                         *
    lcd.setCursor(displayPosition,0);    //  Set cursor position           *
                                         //                                *
    if(displayPosition < 17){            //  Check if position < 17        *
      displayPosition = 17;              //  Set to 17 if it is            *
      firstLetter++;                     //  Incement firstLetter          *
    }                                    //                                *
//                                                                         *
//************* Routine for keeping track of print position ****************
//                                                                         *
    lcd.print(stringMessage.substring(firstLetter,lastLetter));//          *
    displayPosition--;                                         //          *
                                                               //          *
    if(firstLetter > stringMessage.length()) {                 //          *
        firstLetter = 0;                                       //          *
    }                                                          //          *
//                                                                         *
//************************* Reset position markers *************************
//                                                                         *
    if(lastLetter > stringMessage.length() + 14) {//                       *
        firstLetter = 0;                         //  Reset firsrLetter     *
        lastLetter = 0;                          //  Reset lastLetter      *
        displayPosition = 32;                    //  Reset displayPosition *
    }                                            //                        *
//**************************************************************************
    Serial.print(firstLetter);                   //  Print firstLetter     *
    Serial.print(" : ");                         //  Print colon           *
    Serial.print(lastLetter);                    //  Print lastLetter      *
    Serial.print(", ");                          //  Print comma           *
//**************************************************************************
//                  Routine for printing scrolling line                    *
//                                                                         *
    Serial.println(stringMessage.substring(firstLetter,lastLetter));//     *
    lastLetter++;                                //  Incement lastLetter   *
//**************************************************************************
    if(cursorLocation > 31) cursorLocation = 15; //  Reset cursorLocation  *
//**************************************************************************
//                   Routine for printing Special char                     *
//                                                                         *
    lcd.setCursor(cursorLocation,1);  //    Set cursor position            *
    lcd.print(" ");                   //    Print spacebefore spec char    *
    lcd.write(tic);                   //    Print spec char                *
    cursorLocation++;                 //    Incement cursor position       *
//**************************************************************************   
    if(tic >= 6) tic = 0;             //    Reset char pointer             *
  }                                   //                                   *
//**************************************************************************
//                   Routine for checking of RTC is set                    *
  else {                           //                                      *
                                   //                                      *
    if (RTC.chipPresent()) {       //      Check if RTC present            *
      lcd.print("DS1307 stopped.");//      Tell that RTC is not set        *
    }                              //                                      *
                                   //                                      *
    else {                         //                                      *
      lcd.print("DS1307 error!");  //      Tell if RTC not connected       *
      //Serial.println();          //      For debugging                   *
    }                              //                                      *
                                   //                                      *
    delay(9000);                   //      Wait 9 seconds                  *
  }                                //                                      *
  delay(250);                      //      Wait 1/4 second                 *
}                                  //                                      *
//**************************************************************************
//               Routine for print time in two digit format                *
//                                                                         *
void print2digits(int number) {    //      Get Time variable               *
  if (number >= 0 && number < 10) {//      Check if 1 digit or 2           *
    lcd.print('0');                //      If one digit print 0 in front   *
  }                                //                                      *
  lcd.print(number);               //      If not just print number        *
}                                  //                                      *
//**************************************************************************   
