
#include <DHT.h>
#include <SPI.h>
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>
#include <DallasTemperature.h>

#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27,16,2); 
RTC_DS3231 rtc;
DHT dht(5, DHTTYPE);
BlynkTimer timer;
char t[32];
char auth[] = "Z5RgwM26HlnwZ4iwQhFbGFy460OXGwmY";
char ssid[] = "Gupitaro_Kamar";
char pass[] = "Sidiq0212";

int Lamp=2;
int Pump=14;
int tLamp=0;
int tPump=0;

const int OnHour1 = 8;
const int OnMinute1 = 00;

const int OnHour2 = 16;
const int OnMinute2 = 00; 

const int OnHour3 = 18;
const int OnMinute3 = 00;

const int OffHour3 = 23;
const int OffMinute3 = 59;

const int OnHour4 = 0;
const int OnMinute4 = 00;

const int OffHour4 = 4;
const int OffMinute4 = 59;
  

void setup(void)
{
  dht.begin();
  Serial.begin(115200);
  Wire.begin(5, 4);
  
  rtc.begin();
  pinMode(A0, INPUT);
  pinMode(Lamp, OUTPUT);
  pinMode(Pump, OUTPUT);
  digitalWrite(Lamp, LOW);
  digitalWrite(Pump, LOW);
  //rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  lcd.begin();                      // initialize the lcd 
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
}
void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int moisture=analogRead(A0);
  Serial.println(moisture);
  int Nilai = 100-(moisture*100)/1023;
  Blynk.virtualWrite(V5, Nilai);
  Blynk.virtualWrite(V6, t);
  lcd.setCursor(0,0);
  lcd.print("Kelembapan: ");
  lcd.print(Nilai);
  lcd.print("% ");
  lcd.print("Temperatur: ");
  lcd.print(t);
  lcd.print(" C ");
  Blynk.virtualWrite(V1, t);
  Serial.print("Current humidity = ");
  Serial.print(Nilai);
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(t);
  Serial.println(" C ");
  DateTime now = rtc.now();       //Menampilkan RTC pada variable now
 
  Serial.print("Tanggal : ");
  Serial.print(now.day());        //Menampilkan Tanggal
  Serial.print("/");
  Serial.print(now.month());      //Menampilkan Bulan
  Serial.print("/");
  Serial.print(now.year());       //Menampilkan Tahun
  Serial.print(" ");
  
  Serial.print("Jam : ");
  Serial.print(now.hour());       //Menampilkan Jam
  Serial.print(":");
  Serial.print(now.minute());     //Menampilkan Menit
  Serial.print(":");
  Serial.print(now.second());     //Menampilkan Detik
  Serial.println();
  Blynk.run();

  if((now.hour() == OnHour1 && now.minute() >= OnMinute1)||(now.hour() == OnHour2 && now.minute() >= OnMinute2))
  {
    if(Nilai <= 50)
    {
      lcd.setCursor(0,0);
      lcd.print("Kelembapan: ");
      lcd.print(Nilai);
      lcd.print("% ");
      lcd.print("Temperatur: ");
      lcd.print(t);
      lcd.print(" C ");
   
      lcd.setCursor(0,1);
      lcd.print("Jam : ") ;
      lcd.print(now.hour());       //Menampilkan Jam
      lcd.print(":");
      lcd.print(now.minute());     //Menampilkan Menit
      lcd.print(":");
      lcd.print(now.second());
      lcd.scrollDisplayLeft();
      delay(1000);
      digitalWrite(Pump, HIGH);
      digitalWrite(Lamp, LOW);
      Blynk.notify("WAKTUNYA MENYIRAMM!!!");
    }
    else if(Nilai > 50)
    {
      lcd.setCursor(0,0);
      lcd.print("Kelembapan: ");
      lcd.print(Nilai);
      
      lcd.print("% ");
      lcd.print("Temperatur: ");
      lcd.print(t);
      lcd.print(" C ");

      lcd.setCursor(0,1);
      lcd.print("Jam : ") ;
      lcd.print(now.hour());       //Menampilkan Jam
      lcd.print(":");
      lcd.print(now.minute());     //Menampilkan Menit
      lcd.print(":");
      lcd.print(now.second());
      lcd.scrollDisplayLeft();
      delay(1000);
      digitalWrite(Pump, LOW);
      digitalWrite(Lamp, LOW);
      Blynk.notify("TANAMAN SUDAH DISIRAM..");
    }
  }
  else if((now.hour() >= OnHour3 && now.minute() >= OnMinute3)&&(now.hour() <= OffHour3 && now.minute() <= OffMinute3))
      {
      lcd.setCursor(0,0);
      lcd.print("Kelembapan: ");
      lcd.print(Nilai);
      lcd.print("% ");
      lcd.print("Temperatur: ");
      lcd.print(t);
      lcd.print(" C ");
    
      lcd.setCursor(0,1);
      lcd.print("Jam : ") ;
      lcd.print(now.hour());       //Menampilkan Jam
      lcd.print(":");
      lcd.print(now.minute());     //Menampilkan Menit
      lcd.print(":");
      lcd.print(now.second());
      lcd.scrollDisplayLeft();
      delay(1000);
      digitalWrite(Pump, LOW);
      digitalWrite(Lamp, HIGH);
      }
  else if((now.hour() >= OnHour4 && now.minute() >= OnMinute4)&&(now.hour() <= OffHour4 && now.minute() <= OffMinute4))
      {
      lcd.setCursor(0,0);
      lcd.print("Kelembapan: ");
      lcd.print(Nilai);
      lcd.print("% ");
      lcd.print("Temperatur: ");
      lcd.print(t);
      lcd.print(" C ");
    
      lcd.setCursor(0,1);
      lcd.print("Jam : ") ;
      lcd.print(now.hour());       //Menampilkan Jam
      lcd.print(":");
      lcd.print(now.minute());     //Menampilkan Menit
      lcd.print(":");
      lcd.print(now.second());
      lcd.scrollDisplayLeft();
      delay(1000);
      digitalWrite(Pump, LOW);
      digitalWrite(Lamp, HIGH);
      }
  else{
      lcd.setCursor(0,0);
      lcd.print("Kelembapan: ");
      lcd.print(Nilai);
      lcd.print("% ");
      lcd.print("Temperatur: ");
      lcd.print(t);
      lcd.print(" C ");
    
      lcd.setCursor(0,1);
      lcd.print("Jam : ") ;
      lcd.print(now.hour());       //Menampilkan Jam
      lcd.print(":");
      lcd.print(now.minute());     //Menampilkan Menit
      lcd.print(":");
      lcd.print(now.second());
      lcd.scrollDisplayLeft();
      delay(1000);
      digitalWrite(Pump, LOW);
      digitalWrite(Lamp, LOW);
  }
}


  
