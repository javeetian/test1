
#ifndef __DATA_CONFIG_H__
#define __DATA_CONFIG_H__


#include <Arduino.h>

class DataConfig {
    
    public:
        enum _wifiMode {
            WIFI_MODE_NONE,
            WIFI_MODE_AP,
            WIFI_MODE_STATION,
            WIFI_MODE_AP_STATION
        } wifiMode_t;
        
        enum _tcpMode {
            TCP_MODE_NONE,
            TCP_MODE_SERVER,
            TCP_MODE_CLIENT
        } tcpMode_t;

        enum _udpMode {
            UDP_MODE_NONE,
            UDP_MODE_SERVER,
            UDP_MODE_CLIENT
        } udpMode_t;

        String configFile = "/config.json";

        // uart
        u32 uartBaudRate;
        
        // wifi
        u8 wifiMode;
        char wifiLocalSSID[64];
        char wifiLocalPassword[64];
        bool dhcpd;
        u16 wifiIP;
        u16 wifiMask;
        u16 wifiDNS;
        char wifiRemoteSSID[64];
        char wifiRemotePassword[64];
        bool dhcpc;
        u16 wifiRemoteIP;
        u16 wifiRemoteMask;

        // tcp
        u8 tcpMode;
        char tcpHost[64];
        u16 tcpLocalIP;
        u16 tcpLocalPort;
        u16 tcpRemoteIP;
        u16 tcpRemotePort;

        // udp
        u8 udpMode;
        char udpHost[64];
        u16 udpLocalIP;
        u16 udpLocalPort;
        u16 udpRemoteIP;
        u16 udpRemotePort;
        
        // init
        DataConfig(void);
        ~DataConfig(void);
        bool load(void);
        bool readConfig(void);
        bool createConfig(void);

};

#endif /* #ifndef __DATA_CONFIG_H__ */
