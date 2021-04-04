#include <FB_HTTPClient32.h>
#include <FirebaseESP32.h>
#include <FirebaseJson.h>
#include <WiFi.h>

 
 
#define FIREBASE_HOST "https://no-q-test-1-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "esUAcRpO0gbVnfblC5MwAIxMlMflWKJQ4uxMhaJ8"
#define WIFI_SSID "WorkFlo 2.4"
#define WIFI_PASSWORD "Work@OYO"
 
 
//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
int As = 15; 
int Vrdata = 0; 
 
void setup()
{
 
  Serial.begin(115200);
 
 pinMode(As, INPUT);
 
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
 
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */
 
  //String path = "/data";
  
 
  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}
 
void loop()
{
   Vrdata = analogRead(As);
 int Sdata = map(Vrdata,0,4095,0,1000);
 Serial.println(Sdata); 
delay(100); 
  json.set("/dataID/data", Sdata);
  Firebase.updateNode(firebaseData,"/Sensor",json);
 
}
