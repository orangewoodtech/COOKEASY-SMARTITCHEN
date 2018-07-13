#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//Defining Web Server

ESP8266WebServer server(80);
/* Configuration Variables for the AP name and IP. */
//Credentials for hotspot
const char *ssid = "COOKEASY";
const char *password = "EASYCOOK";

int pos;  

IPAddress ap_local_IP(192, 168, 1, 1);
IPAddress ap_gateway(192, 168, 1, 254);
IPAddress ap_subnet(255, 255, 255, 0);

//Creating the input form
const char INDEX_HTML[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta content=\"text/html; charset=ISO-8859-1\""
  " http-equiv=\"content-type\">"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<title>ESP8266 Web Form Demo</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<h1>COOK EASY</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<P>"
  "<label>ssid:&nbsp;</label>"
  "<input maxlength=\"30\" name=\"ssid\"><br>"
  "<label>Password:&nbsp;</label><input maxlength=\"30\" name=\"Password\"><br>"
  "<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
  "</P>"
  "</FORM>"
  "</body>"
  "</html>";

String ss; // to read ssid from eeprom
String pd; // to read password from eeprom

void setup() {
  delay(1000);
  pinMode(D7, INPUT); 
  Serial.begin(115200);//Starting serial comunication
  EEPROM.begin(512);//Starting and setting size of the EEPROM

  for (int n = 0; n < 99; n++) { // read ssid from eeprom
    byte sch = EEPROM.read(n);
    if (sch == ';') break;
    ss = ss + char(sch);
  }

  for (int n = 100; n > 0; n++) { // read password from eeprom
    byte pch = EEPROM.read(n);
    if (pch == ';') break;
    pd = pd + char(pch);
  }

  Serial.println(ss); // print the data read from eeprom
  Serial.println(pd);
  Serial.println();
  delay(3000);

  byte pch = EEPROM.read(400);
  Serial.print("at 400--");
  Serial.println(pch);


  if (EEPROM.read(400) == '0')
  { Serial.println("Configuring access point...");
    Serial.println("Setting soft-AP configuration ... ");
    WiFi.softAPConfig(ap_local_IP, ap_gateway, ap_subnet);
    Serial.print("Setting soft-AP ... ");
    WiFi.softAP(ssid, password);
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
  }
    else {
      WiFi.mode(WIFI_STA);  // change to station mode
      WiFi.begin("orangewoodlabs", "9953562788");
      Serial.print("connecting");
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);

        Serial.println();
        Serial.print("connected: ");
        //      Serial.println(WiFi.localIP());
      }
    }
    
    
    

    /**IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);**/
    //Configuring the web server
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
  }



  void loop() {
    //EEPROM.write(400,'0');
    server.handleClient();//Checks for web server activity
    
    digitalWrite(D7, HIGH);
    
    if (digitalRead(D7) == 0)
    { Serial.println("SET AP MODE");
      EEPROM.write(400, '0');
      EEPROM.commit();
      delay(1000);
      espreset();
     }
  
  }// end of loop

    
      


