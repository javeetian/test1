#include <FS.h>
#include <ArduinoJson.h>
#include "DataConfig.h"

bool DataConfig::load(void)
{
    File f;
    if (!SPIFFS.begin()) return false;
    if (SPIFFS.exists("/config.json")) {
        f = SPIFFS.open("/config.json", "r");
    }
    else {
        f = SPIFFS.open("/config.json", "w");
    }
    
    if (!f) {
        Serial.println("file open failed");
        return false;
    }
    
  StaticJsonBuffer<1024> jsonBuffer;
  //f.readBytes
  
  char json[] =
  "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
    JsonObject& root = jsonBuffer.parseObject(json);
  
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return false;
    }
  
    // Fetch values.
    //
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do root["time"].as<long>();
    const char* sensor = root["sensor"];
    long time = root["time"];
    double latitude = root["data"][0];
    double longitude = root["data"][1];
  
    // Print values.
    Serial.println(sensor);
    Serial.println(time);
    Serial.println(latitude, 6);
    Serial.println(longitude, 6);


}