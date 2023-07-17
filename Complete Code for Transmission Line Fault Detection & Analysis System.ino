// TRANSMISSION LINE FAULT DETECTION & ANALYSIS SYSTEM //
// Hack Tech Engineering by Engr Muhammad Huzaifa Waseem //

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial nodemcu(9, 10);
int mVperAmp = 100;
float I1 = 0.00;
float I2 = 0.00;
float I3 = 0.00;
int FT = 1;
int MAP = 0;
double pickup_current = 0.55;
double fault_current = 0;
double Voltage1 = 0;
double Voltage2 = 0;
double Voltage3 = 0;
double Voltage4 = 0;
double VRMS1 = 0;
double VRMS2 = 0;
double VRMS3 = 0;
double VRMS4 = 0;
double AmpsRMS1 = 0;
double AmpsRMS2 = 0;
double AmpsRMS3 = 0;
double AmpsRMS4 = 0;
void setup(){ 
 pinMode (7, OUTPUT);
 pinMode (6, INPUT); 
 lcd.begin(16, 2);
 Serial.begin(9600);
 Serial.begin(9600);
 nodemcu.begin(115200);
 delay(1000);
 Serial.println("Program started");
 lcd.print("  TRANSMISSION ");
 lcd.setCursor (0, 1);
 lcd.print("      LINE     ");
 delay(800);
 lcd.clear();
 lcd.print("FAULT DECTECTION");
 lcd.setCursor (0, 1);
 lcd.print("     SYSTEM"); 
 delay(800);
}

void loop(){
 sendStatus();
 Voltage1 = getVPP1();
 VRMS1 = (Voltage1/2.0) *0.707;
 AmpsRMS1 = (VRMS1 * 1000)/mVperAmp;
 Serial.print(AmpsRMS1);
 Serial.println(" Neutral RMS");
 Voltage2 = getVPP2();
 VRMS2 = (Voltage2/2.0) *0.707;
 AmpsRMS2 = (VRMS2 * 1000)/mVperAmp;
 Serial.print(AmpsRMS2);
 Serial.println(" Red RMS");
 Voltage3 = getVPP3();
 VRMS3 = (Voltage3/2.0) *0.707;
 AmpsRMS3 = (VRMS3 * 1000)/mVperAmp;
AmpsRMS3 = (AmpsRMS3+(AmpsRMS3*(0.40)));
 Serial.print(AmpsRMS3);
 Serial.println(" Green RMS");
 Voltage4 = getVPP4();
 VRMS4 = (Voltage4/2.0) *0.707;
 AmpsRMS4 = (VRMS4 * 1000)/mVperAmp;
 Serial.print(AmpsRMS4);
 Serial.println(" Blue RMS");
 if (((AmpsRMS2 > pickup_current) && (AmpsRMS1 >= 0.37)) || ((AmpsRMS3 > pickup_current) && (AmpsRMS1 >= 0.37)) || ((AmpsRMS4 > pickup_current) && (AmpsRMS1 >= 0.37)) || ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current)) || ((AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current)) || ((AmpsRMS4 > pickup_current) && (AmpsRMS2 > pickup_current))){
  lcd.clear();
  digitalWrite (7, HIGH);
  while (digitalRead(6) == LOW){
     Serial.print(AmpsRMS1);
     Serial.println(" Neutral RMS");
     Serial.print(AmpsRMS2);
     Serial.println(" RED RMS");
     Serial.print(AmpsRMS3);
     Serial.println(" GREEN RMS");
     Serial.print(AmpsRMS4);
     Serial.println(" BLUE RMS");
    lcd.clear();    
    if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current) && (AmpsRMS1 < 0.40)){
    tone (13, 1000);
    lcd.print ("Three Phase");
    lcd.setCursor (0, 1);
    lcd.print("fault");
    FT = 2;
  }
  else if ((AmpsRMS2 > pickup_current) || (AmpsRMS3 > pickup_current) || (AmpsRMS4 > pickup_current)){
    if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current)|| (AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current)|| (AmpsRMS4 > pickup_current) && (AmpsRMS2 > pickup_current)){
    tone (13, 1000);
    if (AmpsRMS1 >= 0.38){
      lcd.clear();
      lcd.print ("Double line to");
      lcd.setCursor (0, 1);
      lcd.print("Ground fault");
      FT = 3; 
    }
    else{
      lcd.print ("line to line");
      lcd.setCursor (0, 1);
      lcd.print("fault");
      FT = 4;
      } 
  }
    else {
    tone (13, 1000);
    lcd.print ("Single line to");
    lcd.setCursor (0, 1);
    lcd.print("Ground fault");
    FT = 5;
    }  
  }  
  delay(1000);
  lcd.clear();

  if ((AmpsRMS2 > pickup_current) && (AmpsRMS1 >= 0.37))
 {
  fault_current = AmpsRMS2;
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("RED");
  lcd.setCursor (0, 1);
  lcd.print("GROUND");
  
 }
 if ((AmpsRMS3 > pickup_current) && (AmpsRMS1 >= 0.37))
 {
  fault_current = AmpsRMS3;
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("GREEN");
  lcd.setCursor (0, 1);
  lcd.print("GROUND");
  
 }
 if ((AmpsRMS4 > pickup_current) && (AmpsRMS1 >= 0.37))
 {
  fault_current = AmpsRMS4;
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("BLUE");
  lcd.setCursor (0, 1);
  lcd.print("GROUND");
  
 }  
  if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current))
 {
  fault_current = AmpsRMS3;
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("RED");
  lcd.setCursor (0, 1);
  lcd.print("GREEN");
  
 }
 else if ((AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current))
 {
  fault_current = AmpsRMS3;
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("GREEN");
  lcd.setCursor (0, 1);
  lcd.print("BLUE");
  
 }
 else if  ((AmpsRMS4 > pickup_current) && (AmpsRMS2 > pickup_current))
 {
  fault_current = AmpsRMS2;
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("BLUE");
  lcd.setCursor (0, 1);
  lcd.print("RED");
  
 }

 if (fault_current >= 1.10){
   MAP = 2;
  lcd.setCursor(8, 0);
  lcd.print("2 KM");
  lcd.setCursor(8, 1);
  lcd.print("2 KM");
  if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("2 KM");
  }
 }
  if ((fault_current >= 0.83) && (fault_current < 1.10)){
    MAP = 4;
  lcd.setCursor(8, 0);
  lcd.print("4 KM");
  lcd.setCursor(8, 1);
  lcd.print("4 KM");
  if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("4 KM");
  }
 }
 if ((fault_current >= 0.72) && (fault_current < 0.83)){
   MAP = 6;
  lcd.setCursor(8, 0);
  lcd.print("6 KM");
  lcd.setCursor(8, 1);
  lcd.print("6 KM");
  if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("6 KM");
  }
 }
 if ((fault_current >= pickup_current) && (fault_current < 0.72)){
   MAP = 8;
  lcd.setCursor(8, 0);
  lcd.print("8 KM");
  lcd.setCursor(8, 1);
  lcd.print("8 KM");
  if ((AmpsRMS2 > pickup_current) && (AmpsRMS3 > pickup_current) && (AmpsRMS4 > pickup_current)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("8 KM");
  }
 }
 delay(1000);

  } 
 }
 else {
  digitalWrite (7, LOW);
  noTone(13);
  lcd.clear();
  lcd.print("    NO FAULT    ");
  FT = 1;
  }
 }
}
void sendStatus(){  
     StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  I1 = AmpsRMS1; 
  I2 = AmpsRMS2; 
  I3 = AmpsRMS3;  
  data["FT"] = FT;
  data["MAP"] = MAP;
  data["I1"] = I1;
  data["I2"] = I2;
  data["I3"] = I3;
  data.printTo(nodemcu);
  jsonBuffer.clear();
    
}
float getVPP1()
{
  lcd.clear();
  lcd.print("FAULT DETECTING"); 
  lcd.setCursor (0, 1);  
  lcd.print("----------"); 
  float result1;
  int readValue1;             //value read from the sensor
  int maxValue1 = 0;          // store max value here
  int minValue1 = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue1 = analogRead(A0);
       // see if you have a new maxValue
       if (readValue1 > maxValue1) 
       {
           /*record the maximum sensor value*/
           maxValue1 = readValue1;
       }
       if (readValue1 < minValue1) 
       {
           /*record the minimum sensor value*/
           minValue1 = readValue1;
       }
   }
   
   // Subtract min from max
   result1 = ((maxValue1 - minValue1) * 5.0)/1024.0;
      
   return result1;
   
 }
 float getVPP2()
{
  lcd.setCursor (0, 1);  
  lcd.print("------------");
  float result2;
  int readValue2;             //value read from the sensor
  int maxValue2 = 0;          // store max value here
  int minValue2 = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue2 = analogRead(A1);
       // see if you have a new maxValue
       if (readValue2 > maxValue2) 
       {
           /*record the maximum sensor value*/
           maxValue2 = readValue2;
       }
       if (readValue2 < minValue2) 
       {
           /*record the minimum sensor value*/
           minValue2 = readValue2;
       }
   }
   
   // Subtract min from max
   result2 = ((maxValue2 - minValue2) * 5.0)/1024.0;
      
   return result2;
   
 }
 
 float getVPP3()
{
  lcd.setCursor (0, 1);  
  lcd.print("--------------");
  float result3;
  int readValue3;             //value read from the sensor
  int maxValue3 = 0;          // store max value here
  int minValue3 = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue3 = analogRead(A2);
       // see if you have a new maxValue
       if (readValue3 > maxValue3) 
       {
           /*record the maximum sensor value*/
           maxValue3 = readValue3;
       }
       if (readValue3 < minValue3) 
       {
           /*record the minimum sensor value*/
           minValue3 = readValue3;
       }
   }
   
   // Subtract min from max
   result3 = ((maxValue3 - minValue3) * 5.0)/1024.0;
      
   return result3;
   
 }
 float getVPP4()
{
  lcd.setCursor (0, 1);  
  lcd.print("----------------");
  float result4;
  int readValue4;             //value read from the sensor
  int maxValue4 = 0;          // store max value here
  int minValue4 = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue4 = analogRead(A3);
       // see if you have a new maxValue
       if (readValue4 > maxValue4) 
       {
           /*record the maximum sensor value*/
           maxValue4 = readValue4;
       }
       if (readValue4 < minValue4) 
       {
           /*record the minimum sensor value*/
           minValue4 = readValue4;
       }
   }
   
   // Subtract min from max
   result4 = ((maxValue4 - minValue4) * 5.0)/1024.0;
      
   return result4;
   
 }
