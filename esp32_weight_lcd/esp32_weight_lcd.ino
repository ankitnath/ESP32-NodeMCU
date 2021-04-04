#include <LiquidCrystal_I2C.h>

#include <HX711.h>

#include <Wire.h>
#define Window_Size 100

LiquidCrystal_I2C lcd(0x27,20,4); 

 int index1 = 0;
 float Value = 0;
 int sum = 0;
 int Readings[Window_Size];
 int Average = 0;

//constants
const int out = 26;
const int clck = 27;

HX711 scale(out, clck);
float CalibrationFactor = -55020;
//-55015;

void setup()
{
Serial.begin(9600);
lcd.init();
lcd.backlight();
scale.set_scale();
scale.tare();
long zero_factor = scale.read_average();

}

void loop()
{
  sum = sum - Readings[index1];
  Value = (scale.get_units());
  scale.set_scale(CalibrationFactor);
  Readings[index1] = Value;
  sum = sum + Value;
  index1 = (index1+1)% Window_Size;
  Average = sum / Window_Size;
  lcd.setCursor(0,0);
  lcd.print("Weight[kg] : ");
  Value = (scale.get_units());
  Serial.print("Weight in kg = ");
  Serial.println(Value,3);
  
  lcd.setCursor(0,1);
  lcd.print(Value,2);
  delay(500);
  
}
