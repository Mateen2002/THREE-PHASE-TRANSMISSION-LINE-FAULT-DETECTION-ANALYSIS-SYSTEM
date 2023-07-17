
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module
float fault_current = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS1 = 0;
double AmpsRMS2 = 0;
double AmpsRMS3 = 0;
double AmpsRMS4 = 0;
void setup(){ 
 lcd.begin(16, 2);
 Serial.begin(9600);
 lcd.print("  TRANSMISSION ");
 lcd.setCursor (0, 1);
 lcd.print("     LINE     ");
 delay(800);
 lcd.clear();
 lcd.print("FAULT DECTECTION");
}

void loop(){
 Voltage = getVPP1();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS1 = roundf((VRMS * 1000)/mVperAmp*100);
 Serial.print(AmpsRMS1);
 Serial.println(" Amps RMS");
 Voltage = getVPP2();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS2 = roundf((VRMS * 1000)/mVperAmp*100);
 Serial.print(AmpsRMS2);
 Serial.println(" Amps RMS");
 Voltage = getVPP3();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS3 = roundf((VRMS * 1000)/mVperAmp*100);
 Serial.print(AmpsRMS3);
 Serial.println(" Amps RMS");
 Voltage = getVPP4();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS4 = roundf((VRMS * 1000)/mVperAmp*100);
 Serial.print(AmpsRMS4);
 Serial.println(" Amps RMS");
 if ((AmpsRMS1 > 0.00) || (AmpsRMS2 > 0.00) || (AmpsRMS3 > 0.00)){
  lcd.clear();
  if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS2 == AmpsRMS3)){
    tone (13, 1000);
    lcd.print ("Three Phase");
    lcd.setCursor (0, 1);
    lcd.print("fault");
  }
  

  else if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS1 != 0.00)|| (AmpsRMS2 == AmpsRMS3) && (AmpsRMS2 != 0.00)|| (AmpsRMS3 == AmpsRMS1) && (AmpsRMS3 != 0.00)){
    tone (13, 1000);
    if (AmpsRMS4 > 0.00){
      lcd.print ("Double line to");
      lcd.setCursor (0, 1);
      lcd.print("Ground fault");
      }
    else{
      lcd.print("line to line");
      lcd.setCursor (0, 1);
      lcd.print("fault");
    }
  }
  else if ((AmpsRMS1 == AmpsRMS4) || (AmpsRMS2 == AmpsRMS4) || (AmpsRMS3 == AmpsRMS4)){
    tone (13, 1000);
    lcd.print ("Single line to");
    lcd.setCursor (0, 1);
    lcd.print("Ground fault");
  }
  delay(1000);
  lcd.clear();

  if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS1 > 0.00))
 {
  fault_current = AmpsRMS1;
  
  lcd.setCursor (0, 0);
  lcd.print("RED");
  lcd.setCursor (0, 1);
  lcd.print("YELLOW");
  
 }
 else if ((AmpsRMS2 == AmpsRMS3) && (AmpsRMS2 > 0.00))
 {
  fault_current = AmpsRMS2;
  
  lcd.setCursor (0, 0);
  lcd.print("YELLOW");
  lcd.setCursor (0, 1);
  lcd.print("BLUE");
  
 }
 else if  ((AmpsRMS3 == AmpsRMS1) && (AmpsRMS1 > 0.00))
 {
  fault_current = AmpsRMS3;
  
  lcd.setCursor (0, 0);
  lcd.print("BLUE");
  lcd.setCursor (0, 1);
  lcd.print("RED");
  
 }
   if ((AmpsRMS1 == AmpsRMS4) && (AmpsRMS4 > 0.00))
 {
  fault_current = AmpsRMS4*2;
  
  lcd.setCursor (0, 0);
  lcd.print("RED");
  lcd.setCursor (0, 1);
  lcd.print("GROUND");
  
 }
 if ((AmpsRMS2 == AmpsRMS4) && (AmpsRMS4 > 0.00))
 {
  fault_current = AmpsRMS4*2;
  
  lcd.setCursor (0, 0);
  lcd.print("YELLOW");
  lcd.setCursor (0, 1);
  lcd.print("GROUND");
  
 }
 if ((AmpsRMS3 == AmpsRMS4) && (AmpsRMS4 > 0.00))
 {
  fault_current = AmpsRMS4*2;
  
  lcd.setCursor (0, 0);
  lcd.print("BLUE");
  lcd.setCursor (0, 0);
  lcd.print("GROUND");
  
 }
 if (fault_current >= 135.0){
  lcd.setCursor(8, 0);
  lcd.print("2 KM");
  lcd.setCursor(8, 1);
  lcd.print("2 KM");
  if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS2 == AmpsRMS3)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("2 KM");
  }
 
 }
  if ((fault_current >= 66.0) && (fault_current < 135.0)){
  lcd.setCursor(8, 0);
  lcd.print("4 KM");
  lcd.setCursor(8, 1);
  lcd.print("4 KM");
  if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS2 == AmpsRMS3)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("4 KM");
  }
 }
 if ((fault_current >= 45.0) && (fault_current < 66.0)){
  lcd.setCursor(8, 0);
  lcd.print("6 KM");
  lcd.setCursor(8, 1);
  lcd.print("6 KM");
  if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS2 == AmpsRMS3)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("6 KM");
  }
 }
 if ((fault_current >= 35.0) && (fault_current < 45.0)){
  lcd.setCursor(8, 0);
  lcd.print("8 KM");
  lcd.setCursor(8, 1);
  lcd.print("8 KM");
  if ((AmpsRMS1 == AmpsRMS2) && (AmpsRMS2 == AmpsRMS3)){
     delay(1500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BLUE");
     lcd.setCursor(8, 0);
     lcd.print("8 KM");
  }
 }
 }
 else {
  noTone(13);
  lcd.clear();
  lcd.print("    NO FAULT    ");
 }
}

float getVPP1()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(A0);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
   
 }
 float getVPP2()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(A1);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
   
 }
 float getVPP3()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(A2);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
   
 }
 float getVPP4()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(A3);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
   
 }
