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

        Serial.println("6");
        wifiMode = root["wifi"]["mode"];
        Serial.println("7");
        if (root["wifi"]["localSSID"]) strcpy_P(wifiLocalSSID, root["wifi"]["localSSID"]);
        Serial.println("8");
        if (root["wifi"]["localPassword"]) strcpy_P(wifiLocalPassword, root["wifi"]["localPassword"]);
        Serial.println("9");
        dhcpd = root["wifi"]["dhcpd"];
        Serial.println("a");
        wifiIP = root["wifi"]["ip"];
        Serial.println("b");
        wifiMask = root["wifi"]["mask"];
        Serial.println("c");
        wifiDNS = root["wifi"]["dns"];
        Serial.println("d");
        if (root["wifi"]["remoteSSID"]) strcpy_P(wifiRemoteSSID, root["wifi"]["remoteSSID"]);
        Serial.println("e");
        if (root["wifi"]["remotePassword"]) strcpy_P(wifiRemotePassword, root["wifi"]["remotePassword"]);
        Serial.println("f");
        dhcpc = root["wifi"]["dhcpc"];
        Serial.println("g");
        wifiRemoteIP = root["wifi"]["remoteIP"];
        Serial.println("h");
        wifiRemoteMask = root["wifi"]["remoteMask"];
        Serial.println("i");

        // tcp

        tcpMode = root["tcp"]["mode"];
        Serial.println("j");
        if (root["tcp"]["host"]) strcpy_P(tcpHost, root["tcp"]["host"]);
        Serial.println("k");
        tcpLocalIP = root["tcp"]["ip"];
        Serial.println("l");
        tcpLocalPort = root["tcp"]["port"];
        Serial.println("m");
        tcpRemoteIP = root["tcp"]["remoteIP"];
        Serial.println("n");
        tcpRemotePort = root["tcp"]["remotePort"];
        Serial.println("o");

        // udp

        udpMode = root["udp"]["mode"];
        Serial.println("p");
        if (root["udp"]["host"]) strcpy_P(udpHost, root["udp"]["host"]);
        Serial.println("q");
        udpLocalIP = root["udp"]["ip"];
        Serial.println("r");
        udpLocalPort = root["udp"]["port"];
        Serial.println("s");
        udpRemoteIP = root["udp"]["remoteIP"];
        Serial.println("t");
        udpRemotePort = root["udp"]["remotePort"];
        Serial.println("u");

        f.close();

        Serial.println("6666");
        return true;

    } while (0);

    Serial.println("7777");
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
        wifiMode = wifi["mode"] = (uint8_t) WIFI_MODE_AP_STATION;
        strcpy_P(wifiLocalSSID, "lee");
        wifi["localSSID"] = "lee";
        strcpy_P(wifiLocalPassword, "12345678");
        wifi["localPassword"] = "12345678";
        dhcpd = wifi["dhcpd"] = 1;
        wifiIP = wifi["ip"] = 0xc0a80001;
        wifiMask = wifi["mask"] = 0xffffff01;
        wifiDNS = wifi["dns"] = 0x08080808;

        strcpy_P(wifiRemoteSSID, "FruitFamily");
        wifi["remoteSSID"] = "FruitFamily";
        strcpy_P(wifiRemotePassword, "LN520tjw");
        wifi["remotePassword"] = "LN520tjw";

        // tcp

        JsonObject& tcp = root.createNestedObject("tcp");
        tcpMode = tcp["mode"] = (uint8_t) TCP_MODE_CLIENT;
        tcpLocalIP = tcp["ip"] = 0xc0a80001;
        tcpLocalPort = tcp["port"] = 1234;
        tcp["host"] = "192.168.0.14";
        strcpy_P(tcpHost, "192.168.0.14");
        tcpRemoteIP = tcp["ip"] = 0xc0a8000e;
        tcpRemotePort = tcp["port"] = 1234;

        // udp
        
        JsonObject& udp = root.createNestedObject("udp");
        udpMode = udp["mode"] = (uint8_t) UDP_MODE_SERVER;
        udpLocalIP = udp["ip"] = 0xc0a80003;
        udpLocalPort = udp["port"] = 1234;
        udpRemoteIP = tcp["ip"] = 0xc0a8000e;
        udpRemotePort = tcp["port"] = 12345;

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

    return createConfig();
    if (SPIFFS.exists(configFile)) {
        return readConfig();
    }
    else {
        return createConfig();
    }
}