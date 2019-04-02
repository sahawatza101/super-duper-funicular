#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//const char* ssid = "E-Ju";
//const char* password = "12345678";
//const char* ssid = "Kwanz";
//const char* password = "00EB2PASS";
const char* ssid = "60044204"; 
const char* password = "1729800079868"; 

#define mqtt_server "raspberrypi.local"
#define mqtt_port 1883
#define mqtt_user ""
#define mqtt_password ""


///////////// Ploy Define Part/////////////////
const char * ploy_topic = "/server";
#define ploy_mqtt_server "m13.cloudmqtt.com"
#define ploy_mqtt_port 16216 
#define ploy_mqtt_user "casstgjz" 
#define ploy_mqtt_password "obhZCz79JMXe"
#define door_PIN D0
char *door_status = "Lock";
WiFiClient PloyWifiClient;
PubSubClient Ployclient(PloyWifiClient);
/////////////////////////////////////////

//
//WiFiClient espClient;
//PubSubClient client(espClient);


int pin = D7;

unsigned long duration;     
short count = 0;

void setup() 

{ 

  
  // initialize serial communications at 9600 bps:
  
  Serial.begin(115200); 
//  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);

//  WiFi.begin(ssid, password);

//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//  
//  client.setServer(mqtt_server, mqtt_port);
//  client.setCallback(callback);


  pinMode(pin, INPUT);

  
///// Ploy  Setup Part////////
  pinMode(door_PIN, OUTPUT);
  digitalWrite(door_PIN, HIGH);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Ployclient.setServer(ploy_mqtt_server, ploy_mqtt_port); 
  Ployclient.setCallback(ploy_callback);
/////////////////////////
}

 

void loop() 
 {
  if(digitalRead(pin))
  {
    Serial.println(pin);  
  }
  /*
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      } 
      else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
  
      return;
    }
  }*/


  
    duration = pulseIn(pin, HIGH, 1000000);

    float time = duration/1000.00; 
    

   // Serial.print("DelT=");

   // Serial.println(time);
    
    if(time > 1)
    {
      count = count +1 ;
      Serial.println(count);
    }
    /*
  if(time == 0.00)
   {
      if(count == 1)
      {
        Serial.println("1 Baht");
        count -= 1;
        return; 
      }
     else if(count == 2)
      {
        Serial.println("2 Baht");
        count -= 2;
        return ;
      }
      else if(count == 5)
      {
        Serial.println("5 Baht");
        count -= 5 ;
        return ;
      }
      else if(count == 10)
      {
        Serial.println("10 Baht");
        count -= 10;
        return;
      }
      else if(count > 6)
       {
          Serial.println("10 Baht");
          count -= 10;
          return;
       }
       else if(count > 5 && count < 10)
       {
          Serial.println("5 Baht");
          count = 5;
          return ;
       }
       else if(count > 2 && count < 5)
       {
          Serial.println("2 Baht");
          count -= 2;
          return;
       }      
     }

    
    if(time > 2){
      count = count + 1;
    }
    Serial.println(time);
    */
    if (time == 0){
      //Serial.println(count);
      if(count != 10 && count > 10)
      {
          Serial.println("10 Baht");
          count = count - 10;
        //  client.publish("KAPOOK/Coin","10");
      }
      if(count != 5 && count > 5 && count < 10)
      {
          Serial.println("5 baht");
          count = count - 5 ;  
       //   client.publish("KAPOOK/Coin","5");
      }
      if(count != 2 && count > 2 && count < 5)
      {
          Serial.println("2 Baht");
          count = count - 2 ;  
         // client.publish("KAPOOK/Coin","2");
      }
      if(count != 1 && count > 1 && count < 2)
      {
          Serial.println("1 Baht");
          count = count - 1 ;  
       //   client.publish("KAPOOK/Coin","1");
      }
      if(count == 1)
      {
          Serial.println("1 Baht");
          count = count - 1 ;  
        //  client.publish("KAPOOK/Coin","1");
      }
      if(count == 2)
      {
          Serial.println("2 Baht");
          count = count - 2 ;  
      //    client.publish("KAPOOK/Coin","2");
      }
      if(count == 5)
      {
          Serial.println("5 Baht");
          count = count - 5 ;  
         // client.publish("KAPOOK/Coin","5");
      }
      if(count == 10)
      {
          Serial.println("10 Baht");
          count = count - 10 ;  
  //client.publish("KAPOOK/Coin","10");
      }
     
    }




//////////// Ploy Loop Part/////////////
      if (!Ployclient.connected()) {
          Serial.print("MQTT connecting...");
          if (Ployclient.connect("ESP8266Client", ploy_mqtt_user, ploy_mqtt_password)) { 
            Ployclient.subscribe(ploy_topic); 
            Serial.println("connected");
          }
      
          else {
            Serial.print("failed, rc=");
            Serial.print(Ployclient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000); 
            return;
        }
      }
      Ployclient.loop();
////////////////////////////////////////////

}
 
 void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  int i=0;
  String msg = "";
  while (i<length)
  { 
    msg += (char)payload[i++];
  }
  /*if (msg == "1") {
    client.publish("KAPOOK/Coin","1");
    return;
  }
  else if (msg == "GET") {
    client.publish("KAPOOK/Coin","SENSOR OFF");
    return;
  }*/
  Serial.println(msg);
}



/////////////// Ploy Callback ///////////
void ploy_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message from ");
  Serial.println(ploy_topic);
  String msg = "";
  int i = 0;
  while (i < length) {
  msg += (char)payload[i++];
  }
  Serial.print("receive ");
  Serial.println(msg); 
  
  if (msg == "unlock") { 
  digitalWrite(door_PIN, LOW);
  door_status = "NodeMCU : Door Unlock";
  Ployclient.publish("/NodeMCU", door_status); // 
  } else if (msg == "lock") {
  digitalWrite(door_PIN, HIGH);
  door_status = "NodeMCU : Door Lock";
  Ployclient.publish("/NodeMCU", door_status);
  }else if(msg=="status"){
  Ployclient.publish("/NodeMCU", door_status);
  }
  
  if (door_status != "") {
  Serial.print("Answer ");
  Serial.println(door_status);
  }
}
//////////////////////////////////////////
