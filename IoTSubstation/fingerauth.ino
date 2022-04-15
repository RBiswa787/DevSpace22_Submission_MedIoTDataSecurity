//we adopted this finger authentication code from tutorial on circuitdigest.com

#include "FPS_GT511C3.h" 
#include "SoftwareSerial.h"

FPS_GT511C3 fps(4, 5);

void Enroll()
{
  int enrollid = 0;
  bool usedid = true;
  while (usedid == true)
  {
    usedid = fps.CheckEnrolled(enrollid);
    if (usedid==true) enrollid++;
  }
  fps.EnrollStart(enrollid);

  // enroll
  Serial.println("Enroll #");
  Serial.println(enrollid);
  while(fps.IsPressFinger() == false) delay(100);
  bool bret = fps.CaptureFinger(true);
  int iret = 0;
  if (bret != false)
  {
    Serial.println("Remove finger");
    fps.Enroll1(); 
    while(fps.IsPressFinger() == true) delay(100);
    Serial.println("Press again");
    while(fps.IsPressFinger() == false) delay(100);
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      Serial.println("Remove finger");
      fps.Enroll2();
      while(fps.IsPressFinger() == true) delay(100);
      Serial.println("Press yet again");
      while(fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        Serial.println("Remove finger");
        iret = fps.Enroll3();
        if (iret == 0)
        {
          Serial.println("Enrolling Success");
        }
        else
        {
          Serial.println("Enroll Failed:");
          Serial.println(iret);
        }
      }
      else Serial.println("Failed 1");
    }
    else Serial.println("Failed 2");
  }
  else Serial.println("Failed 3");
}

void setup()
{
  Serial.begin(9600);

  fps.Open();        = 
  fps.SetLED(true);   

  pinMode(2,INPUT);
  Serial.println("GT511C3 FPS"); 
  delay(2000);

}

void loop()
{ 
  if (digitalRead(2))
  {
  Enroll();
  }

  Serial.print("Hi!....."); 
  while (!fps.IsPressFinger());
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
      Serial.println("Welcome:"); 
      if (id==200) Serial.println("Unknown  "); 
      Serial.println(id);
      delay(1000);
  }

}

