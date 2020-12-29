int blueLed = 13;
int redLed = 12;
int redRGB = 9;
int greenRGB = 10;
int videoController = 2;
int volumeDial = A0;
int volumeVal;
int volume;
int tcpStop = 3;
//TCP Parameter
String tcpIp = "\"10.0.0.37\"";
String netType = "\"TCP\"";
String tcpPort = "8080";
String tcpPara = netType + "," + tcpIp + "," + tcpPort;

//Wifi Parameter
String ssid = "\"CGNM-88B8\"";
String pw = "\"251183006782\"";
String wifiPara = ssid + "," + pw;

void connect2Wifi(){
  String cmd = "AT+CWJAP=" + wifiPara;
  executeCmd(cmd);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, HIGH);
}

void connect2socket(){
  String cmd = "AT+CIPSTART=" + tcpPara;
  executeCmd(cmd);
  analogWrite(redRGB, 0);
  analogWrite(greenRGB, 20);
}

void diconnect2socket(){
  String cmd = "AT+CIPCLOSE";
  executeCmd(cmd);
  analogWrite(redRGB, 20);
  analogWrite(greenRGB, 0);
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
////////////////SETUP////////////////
void setup(){
    pinMode(blueLed,OUTPUT);
    pinMode(redLed,OUTPUT);
    pinMode(redRGB,OUTPUT);
    pinMode(greenRGB,OUTPUT);
    pinMode(videoController,INPUT);
    pinMode(volumeDial,INPUT);
    pinMode(tcpStop,INPUT);
//    Serial.begin(9600);
    Serial1.setTimeout(1500);
    Serial1.begin(115200);
    while(!Serial1){
      digitalWrite(redLed, HIGH);
      analogWrite(redRGB, 20);
    }
    connect2Wifi();
    connect2socket();
    volume = map(analogRead(volumeDial), 0, 1023, 0, 80);
}

////////////////LOOP////////////////
void loop(){
  int newVolume = map(analogRead(volumeDial), 0, 1023, 0, 80);
   delay(100);
  if(volume != newVolume){
    volume = newVolume;
    sendMsg(String(volume));
    }
  
  if(!digitalRead(videoController)){
      sendMsg("video");
      delay(300);
   }
  if(!digitalRead(tcpStop)){
      diconnect2socket();
      delay(300);
   }
  
  
}
