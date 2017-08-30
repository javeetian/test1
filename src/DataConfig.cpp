#include <FS.h>
#include <ArduinoJson.h>
#include "DataConfig.h"

DataConfig::DataConfig()
{
    
}

DataConfig::~DataConfig()
{

}

 /*
{
  "baudrate": 115200,
  
  "wifi": {
    "mode": 3,
    "localSSID": "abc",
    "localPassword": "12345678",
    "dhcpd": true,
    "ip": 123,
    "mask": 456,
    "dns": 789,
    "remoteSSID": "def",
    "remotePasswrod": "abcdefgh",
    "dhcpc": false,
    "remoteIP": 123,
    "remoteMask": 456
  },
  
  "tcp": {
    "mode": 1,
    "host": "qq.com",
    "ip": 123,
    "port": 1234,
    "remoteIP": 456,
    "remotePort": 5678
  },
  
  "udp": {
    "mode": 1,
    "host": "baidu.com",
    "ip": 123,
    "port": 4321,
    "remoteIP": 456,
    "remotePort": 5678
  }
}
*/

bool DataConfig::readConfig(void)
{


    File f = SPIFFS.open(configFile, "r");
    
        if (!f) {
            Serial.println("file open failed");
            return false;
        }

    do {

        // file not larger than 1024

        StaticJsonBuffer<1024> jsonBuffer;
        char json[1024];
        if (!f.readBytes(json, f.size())) break;
    
        JsonObject& root = jsonBuffer.parseObject(json);
    
        if (!root.success()) {
            Serial.println("parseObject() failed");
            break;
        }
       
        // baudrate
        
        uartBaudRate = root["baudrate"];

        // wifi

        wifiMode = root["wifi"]["mode"];
        strcpy_P(wifiLocalSSID, root["wifi"]["localSSID"]);
        strcpy_P(wifiLocalPassword, root["wifi"]["localPassword"]);
        dhcpd = root["wifi"]["dhcpd"];
        wifiIP = root["wifi"]["ip"];
        wifiMask = root["wifi"]["mask"];
        wifiDNS = root["wifi"]["dns"];
        strcpy_P(wifiRemoteSSID, root["wifi"]["remoteSSID"]);
        strcpy_P(wifiRemotePassword, root["wifi"]["remotePassword"]);
        dhcpc = root["wifi"]["dhcpc"];
        wifiRemoteIP = root["wifi"]["remoteIP"];
        wifiRemoteMask = root["wifi"]["remoteMask"];

        // tcp

        tcpMode = root["tcp"]["mode"];
        strcpy_P(tcpHost, root["tcp"]["host"]);
        tcpLocalIP = root["tcp"]["ip"];
        tcpLocalPort = root["tcp"]["port"];
        tcpRemoteIP = root["tcp"]["remoteIP"];
        tcpRemotePort = root["tcp"]["remotePort"];

        // udp

        udpMode = root["udp"]["mode"];
        strcpy_P(udpHost, root["udp"]["host"]);
        udpLocalIP = root["udp"]["ip"];
        udpLocalPort = root["udp"]["port"];
        udpRemoteIP = root["udp"]["remoteIP"];
        udpRemotePort = root["udp"]["remotePort"];

        f.close();

        return true;

    } while (0);

    f.close();

    return false;
}

bool DataConfig::createConfig(void)
{

    File f = SPIFFS.open(configFile, "w");
    
        if (!f) {
            Serial.println("file write failed");
            return false;
        }

    StaticJsonBuffer<1024> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();

        // baudrate
        
        uartBaudRate = root["baudrate"] = 115200;
        
        // wifi
        
        JsonObject& wifi = root.createNestedObject("wifi");
        wifiMode = wifi["mode"] = WIFI_MODE_AP;
        strcpy_P(wifiLocalSSID, "lee");
        wifi["localSSID"] = "lee";
        strcpy_P(wifiLocalPassword, "12345678");
        wifi["localPassword"] = "12345678";
        dhcpd = wifi["dhcpd"] = 1;
        wifiIP = wifi["ip"] = 0xc0a80001;
        wifiMask = wifi["mask"] = 0xffffff01;
        wifiDNS = wifi["dns"] = 0x08080808;

        // tcp

        JsonObject& tcp = root.createNestedObject("tcp");
        tcpMode = tcp["mode"] = TCP_MODE_SERVER;
        tcpLocalIP = tcp["ip"] = 0xc0a80001;
        tcpLocalPort = tcp["port"] = 1234;

        // udp
        
        JsonObject& udp = root.createNestedObject("tcp");
        udpMode = udp["mode"] = UDP_MODE_SERVER;
        udpLocalIP = udp["ip"] = 0xc0a80001;
        udpLocalPort = udp["port"] = 1234;

        String json;
        root.printTo(json);
        if(!f.write((const uint8_t *)json.c_str(), strlen_P(json.c_str()))) {
            Serial.println("Can not reate file");
            f.close();
            return false;
        }
        f.close();
        return true;
}

bool DataConfig::load(void)
{
    if (!SPIFFS.begin()) return false;

    if (SPIFFS.exists(configFile)) {
        return readConfig();
    }
    else {
        return createConfig();
    }
}