
#ifndef __DATA_CONFIG_H__
#define __DATA_CONFIG_H__


#include <Arduino.h>

class DataConfig {

    public:
        // uart
        u16 uartBaudRate;
        
        // wifi
        u8 wifiMode;
        char *wifiLocalSSID;
        char *wifiLocalPassword;
        char *wifiRemoteSSID;
        char *wifiRemotePassword;
        u8 wifiDHCP;
        u16 wifiDNS;
        u16 wifiIP;
        u16 wifiMask;

        // tcp
        u8 tcpMode;
        u16 tcpLocalIP;
        u16 tcpLocalPort;
        u16 tcpRemoteIP;
        u16 tcpRemotePort;

        // udp
        u8 udpMode;
        u16 udpIP;
        u16 udpPort;
        
        // init
        bool load(void);

};

#endif /* #ifndef __DATA_CONFIG_H__ */
