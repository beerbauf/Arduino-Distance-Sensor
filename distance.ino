
#include <LiquidCrystal.h>

const int ledPin = 13;
const int sensorPin = 0;

const long referenceMv = 5000;

//LED
const int numRows = 1;
const int numCols = 16;
LiquidCrystal lcd(12,11,9,8,7,6,5,4,3,2);

int getDistance(int mV);

void setup(){
  lcd.begin(numRows, numCols);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  int val = analogRead(sensorPin);
  int mV = (val * referenceMv) / 1023;

  int cm = getDistance(mV);
  lcd.setCursor(0,0);
  lcd.print(mV);
  lcd.setCursor(5,0);
  lcd.print("mV");
  lcd.setCursor(0,1);
  lcd.print(">> ");
  lcd.print(cm); 
  lcd.setCursor(6,1);
  lcd.print("cm");

  digitalWrite(ledPin, HIGH);
  delay(cm*10);
  digitalWrite(ledPin, LOW);
  delay(cm*10);
  delay(100);
  lcd.clear();
}

const int TABLE_ENTRIES=12;
const int firstElement=250;
const int INTERVAL =250;
static int distance[TABLE_ENTRIES]={150,140,130,100,60,50,40,35,30,25,20,15};

int getDistance(int mV){
  if(mV > INTERVAL *TABLE_ENTRIES-1)
    return distance[TABLE_ENTRIES];
  else{
    int index = mV/INTERVAL;
    float frac = (mV%250)/(float)INTERVAL;
    return distance[index]- ((distance[index]- distance[index+1])*frac);
  }
}
