#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
IPAddress timeServerIP; // time.nist.gov NTP server address

const char* ntpServerName = "time.nist.gov";

#define FIREBASE_HOST "cook-easy-cbe63.firebaseio.com"   // host id for firebase db
#define FIREBASE_AUTH "1EEXugIv3fCz09N5lpKU3eRJ5bCda8sYeh96QwGm"  // secret key to link to firebase db

#define WIFI_SSID "orangewoodlabs"
#define WIFI_PASSWORD "9953562788"

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP


unsigned int localPort = 2390;  
WiFiUDP udp;

char s;
String tw1,tw2,tw3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
 
  udp.begin(localPort);
  
     
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); 
  delay(1000);
  int cb = udp.parsePacket();
  udp.read(packetBuffer, NTP_PACKET_SIZE);
  
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);
    Firebase.setInt("epoch", int(epoch));
  
if(Serial.available())
  {
    s=Serial.read();
    
    if(s == 'a'){ tw1="";
          while(1)
          { 
            s=Serial.read(); 
            if(s == '\n') 
              break;
            tw1=tw1+s;
          }
    
          }
//-----------------------------------------
   
    if(s == 'b'){ tw2="";
          while(1)
          { 
            s=Serial.read(); 
            if(s == '\n') 
              break;
            tw2=tw2+s;
          }
    
          }
  //------------------------------
      if(s == 'c'){ tw3="";
      
        while(1)
          { 
            s=Serial.read(); 
            if(s == '\n') 
              break;
            tw3=tw3+s;
          }
    
          }
  }

Firebase.setString("A", tw1);
delay(500); 
Firebase.setString("B", tw2);
delay(500); 
Firebase.setString("C", tw3);
delay(500); 

Serial.println("sent to fbase");
 }


unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
