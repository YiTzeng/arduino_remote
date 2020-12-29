#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3

LiquidCrystal_I2C lcd(I2C_ADDR, 20, 4);

int blueLed = 13;
int redLed = 12;
int redRGB = 9;
int greenRGB = 10;
int keySpace = 2;
int volumeDial = A0;
int volumeVal;
int volume;
int keyF = 3;

//TCP Parameter
//replace IP with your IP using ifconfig
String tcpIp = "\"IP\"";
String netType = "\"TCP\"";
String tcpPort = "8080";
String tcpPara = netType + "," + tcpIp + "," + tcpPort;

//Wifi Parameter
//replace ssid & and password with your setting
String ssid = "\"ssid\"";
String pw = "\"wifi password\"";
String wifiPara = ssid + "," + pw;

void checkAllConnections(){
   if(Serial1.available()){
      String espMsg = Serial1.readString();
      if(espMsg.indexOf("WIFI DISCONNECT") != -1){
        displayWifiStatus(false);
        connect2Wifi();
      }
      if(espMsg.indexOf("CLOSED") != -1){
        displayScoketStatus(false);
        connect2socket();
      }
   }
}

void connect2Wifi(){
  String cmd = "AT+CWJAP=" + wifiPara;
  executeCmd(cmd);
  displayWifiStatus(true);
}

void disconnect2Wifi(){
  String cmd = "AT+CWQAP";
  executeCmd(cmd);
  displayWifiStatus(false);
} 

void connect2socket(){
  String cmd = "AT+CIPSTART=" + tcpPara;
  executeCmd(cmd);
  displayScoketStatus(true);
}

void diconnect2socket(){
  String cmd = "AT+CIPCLOSE";
  executeCmd(cmd);
  displayScoketStatus(false);
}

void sendMsg(String msg){
  String cmd = "AT+CIPSEND=" + String(msg.length());
  executeCmd(cmd);
  do{
    executeCmd(msg);
  }while(!msgReceived());
}

void executeCmd(String cmd){
  do{
    Serial1.println(cmd);
  }while(!cmdCompletion());
}

boolean cmdCompletion(){
  return Serial1.find("OK");
} 

boolean msgReceived(){
  return Serial1.find("true");
}
//Show wifi & socket connection with led & lcd
void displayWifiStatus(boolean conStatus){
  if(conStatus){
    lcd.setCursor(8,0);
    lcd.print("ON ");
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, HIGH);
  }
  else{
    lcd.setCursor(8,0);
    lcd.print("OFF");
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, LOW);
  }
}

void displayScoketStatus(boolean conStatus){
  if(conStatus){
    lcd.setCursor(8,1);
    lcd.print("ON ");
    digitalWrite(redRGB, LOW);
    digitalWrite(greenRGB, HIGH);
  }
  else{
    lcd.setCursor(8,1);
    lcd.print("OFF");
    digitalWrite(redRGB, HIGH);
    digitalWrite(greenRGB, LOW);
  }
}

////////////////SETUP////////////////
void setup(){
    pinMode(blueLed,OUTPUT);
    pinMode(redLed,OUTPUT);
    pinMode(redRGB,OUTPUT);
    pinMode(greenRGB,OUTPUT);
    pinMode(keySpace,INPUT);
    pinMode(volumeDial,INPUT);
    pinMode(keyF,INPUT);
    Serial1.begin(115200);
    Serial1.setTimeout(1500);
    digitalWrite(redLed, HIGH);
    digitalWrite(redRGB, HIGH);
    //lcd begin & setting
    lcd.init(); // initialize the lcd 
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wifi:");
    lcd.setCursor(0,1);
    lcd.print("Socket:");
    displayWifiStatus(false);
    displayScoketStatus(false);
    //wait for connection between esp8266 & arduino board
    while(!Serial1){}
    connect2Wifi();
    connect2socket();
    //get initial value of dial
    volume = map(analogRead(volumeDial), 0, 1023, 0, 50);
}

////////////////LOOP////////////////
void loop(){
  checkAllConnections();
  int newVolume = map(analogRead(volumeDial), 0, 1023, 0, 50);
  delay(100);
  //send new volume when dial is changed
  if(volume != newVolume){
    volume = newVolume;
    sendMsg(String(volume));
    }
  
  if(!digitalRead(keySpace)){
      sendMsg("space");
      delay(300);
   }
  if(!digitalRead(keyF)){
      sendMsg("f");
      delay(300);
   }
  
}
