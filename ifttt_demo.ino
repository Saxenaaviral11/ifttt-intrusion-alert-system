#include<ESP8266Webhook.h>
#include <ESP8266WiFi.h>


#define _SSID "OPPOA7"      
#define _PASSWORD "11112222"  
#define KEY "lBg2nE6UpXZrNq7sf2h_YI0zCNHHtUmet_TrsqN_4DF"        
#define EVENT "Intrusion"     

Webhook webhook(KEY,EVENT);

int pirpin = D7;
int pirstate;
int flag;

void calibrate();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pirpin,INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);

  calibrate();
}

void calibrate()
{
  Serial.println("CALIBRATING SENSOR");
  for(int i=0;i<30;i++)
  {
    Serial.println(".");
    delay(1000);
  }
  Serial.println("SENSOR CALIBRATED AND READY TO USE");
  delay(50);
}

void trigger()
{
  int Get = webhook.trigger();
  Serial.println(Get);
  if(Get)
  {
    Serial.println("True");
  }
  else{
    Serial.println("Failed");
  }
}

void loop() {
  
  int pirstate = digitalRead(pirpin);
  if(pirstate == HIGH){
    delay(500);
    flag = 1;
    Serial.println("Motion Detected");
  }
  else{
    Serial.println("No motion detected");
    flag = 0;
  }
  if(flag == 1){
    trigger();
  }
  
  delay(1000);
}
