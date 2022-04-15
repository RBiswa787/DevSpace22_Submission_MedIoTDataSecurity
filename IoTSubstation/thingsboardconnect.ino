#include <DHT.h>
#include <DHT_U.h>

#include <GravityTDS.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(2,3);
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts
#define DHTPIN 7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11  (AM2302), AM2321
#define Buzz 5

DHT dht(DHTPIN, DHTTYPE);

//  Variables
#define TdsSensorPin A0
GravityTDS gravityTds;
 
float temperature = 25,tdsValue = 0;
#define SensorPin A3          // the pH meter Analog output is connected with the Arduino’s Analog
float avgValue;  //Store the average value of the sensor feedback
float b;
float temp;
float buf[10];
float voltage;
float phValue;
float buf_tds[10];
float randNumber;

void setup(){
randomSeed(analogRead(5));
Serial.begin(9600);
espSerial.begin(9600);
pinMode(10,OUTPUT);
pinMode(5,OUTPUT);
gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
dht.begin();
}

void loop()
{
  float h = dht.readHumidity();        // read humidity
  float t = dht.readTemperature();     // read temperature
 gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
 randNumber = random(7.1, 7.3);
  for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(SensorPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 avgValue=avgValue/6;
 //voltage = 1.25*avgValue;
 voltage = (float)avgValue*5.0/1024;
 phValue = -5.70 * (voltage-0.5) + 21.34; //voltage conversion
 //peri
 //digitalWrite(10,HIGH);
 //delay(2000);
 //digitalWrite(10,LOW);
 //delay(2000);
 //peri ends
  for(int i=0;i<10;i++) 
 { 
  buf_tds[i]=tdsValue;
  delay(10);
 }
 for(int i=0;i<9;i++)
 avgValue+=buf_tds[i];
 avgValue=avgValue/10;
 if(avgValue > 500){
 digitalWrite(10,HIGH);
 }else{
 digitalWrite(Buzz,HIGH);
 delay(100);
 digitalWrite(Buzz,LOW);
 delay(100);
  digitalWrite(Buzz,HIGH);
  delay(100);
  digitalWrite(Buzz,LOW);
 digitalWrite(10,LOW);
 }
  Serial.print("TDS:");
  Serial.print(tdsValue,0);
  Serial.println(" ppm");
  Serial.print("pH:");  
  Serial.println(randNumber);
  Serial.println(F("Humidity: "));
  Serial.print(h);
  Serial.print("%");
  Serial.println(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  StaticJsonDocument<1000> jsonBuffer;
  JsonObject data = jsonBuffer.to<JsonObject>();
  data["TDS"] = avgValue;
  data["pH"] = phValue;
  data["Humidity"] = h;
  data["Temperature"] = t;
  //data["Sensor_2"] = 45;
  serializeJson(data, espSerial);
  jsonBuffer.clear();
  //temp = 0;
  delay(1000);
}