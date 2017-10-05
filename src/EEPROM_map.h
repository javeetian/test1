/*
  +----------------------------------------------------------------------+
  | CoogleIOT for ESP8266                                                |
  +----------------------------------------------------------------------+
  | Copyright (c) 2017 John Coggeshall                                   |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License");      |
  | you may not use this file except in compliance with the License. You |
  | may obtain a copy of the License at:                                 |
  |                                                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Authors: John Coggeshall <john@coggeshall.org>                       |
  +----------------------------------------------------------------------+
*/

#ifndef COOGLEIOT_EEPROM_MAP
#define COOGLEIOT_EEPROM_MAP

#define COOGLEIOT_AP_PASSWORD_ADDR 5 // 5-21
#define COOGLEIOT_AP_PASSWORD_MAXLEN 16

#define COOGLEIOT_AP_NAME_ADDR 22
#define COOGLEIOT_AP_NAME_MAXLEN 25 // 22-47

#define COOGLEIOT_REMOTE_AP_PASSWORD_ADDR 48
#define COOGLEIOT_REMOTE_AP_PASSWORD_MAXLEN 64 // 48-112

#define COOGLEIOT_MQTT_HOST_ADDR 113
#define COOGLEIOT_MQTT_HOST_MAXLEN 64 // 113 - 177

#define COOGLEIOT_MQTT_USER_ADDR 178
#define COOGLEIOT_MQTT_USER_MAXLEN 16 // 178 - 194

#define COOGLEIOT_MQTT_USER_PASSWORD_ADDR 195
#define COOGLEIOT_MQTT_USER_PASSWORD_MAXLEN 24 // 195 - 219

#define COOGLEIOT_MQTT_CLIENT_ID_ADDR 220
#define COOGLEIOT_MQTT_CLIENT_ID_MAXLEN 32 // 220 - 252

#define COOGLEIOT_MQTT_PORT_ADDR 253
#define COOGLEIOT_MQTT_PORT_MAXLEN 2 // 253 - 255 (int)

#define COOGLEIOT_FIRMWARE_UPDATE_URL_ADDR 282
#define COOGLEIOT_FIRMWARE_UPDATE_URL_MAXLEN 255 // 282 - 537

#define COOGLEIOT_REMOTE_AP_NAME_ADDR 538
#define COOGLEIOT_REMOTE_AP_NAME_MAXLEN 25 // 538- 563

enum {
  // uart
  BAUDRATE_ADDR_START = 564,
  BAUDRATE_ADDR_END = BAUDRATE_ADDR_START + 4,

  // wifi
  
  WIFI_MODE_ADDR_START,
  WIFI_MODE_ADDR_END = WIFI_MODE_ADDR_START + 4,

  WIFI_LOCAL_SSID_ADDR_START,
  WIFI_LOCAL_SSID_ADDR_END = WIFI_LOCAL_SSID_ADDR_START + 25,

  WIFI_LOCAL_PASSWORD_ADDR_START,
  WIFI_LOCAL_PASSWORD_ADDR_END = WIFI_LOCAL_PASSWORD_ADDR_START + 16,

  WIFI_LOCAL_IP_ADDR_START,
  WIFI_LOCAL_IP_ADDR_END = WIFI_LOCAL_IP_ADDR_START + 4,

  WIFI_LOCAL_MASK_ADDR_START,
  WIFI_LOCAL_MASK_ADDR_END = WIFI_LOCAL_MASK_ADDR_START + 4,

  WIFI_LOCAL_GATEWAY_ADDR_START,
  WIFI_LOCAL_GATEWAY_ADDR_END = WIFI_LOCAL_GATEWAY_ADDR_START + 4,

  WIFI_LOCAL_DNS_ADDR_START,
  WIFI_LOCAL_DNS_ADDR_END = WIFI_LOCAL_DNS_ADDR_START + 4,

  WIFI_REMOTE_SSID_ADDR_START,
  WIFI_REMOTE_SSID_ADDR_END = WIFI_REMOTE_SSID_ADDR_START + 64,

  WIFI_REMOTE_PASSWORD_ADDR_START,
  WIFI_REMOTE_PASSWORD_ADDR_END = WIFI_REMOTE_PASSWORD_ADDR_START + 64,

  // tcp

  TCP_MODE_ADDR_START,
  TCP_MODE_ADDR_END = TCP_MODE_ADDR_START + 4,

  TCP_LOCAL_IP_ADDR_START,
  TCP_LOCAL_IP_ADDR_END = TCP_LOCAL_IP_ADDR_START + 4,

  TCP_LOCAL_PORT_ADDR_START,
  TCP_LOCAL_PORT_ADDR_END = TCP_LOCAL_PORT_ADDR_START + 4,

  TCP_REMOTE_HOST_ADDR_START,
  TCP_REMOTE_HOST_ADDR_END = TCP_REMOTE_HOST_ADDR_START + 64,

  TCP_REMOTE_PORT_ADDR_START,
  TCP_REMOTE_PORT_ADDR_END = TCP_REMOTE_PORT_ADDR_START + 4,

  // udp

  UDP_MODE_ADDR_START,
  UDP_MODE_ADDR_END = UDP_MODE_ADDR_START + 4,

  UDP_LOCAL_IP_ADDR_START,
  UDP_LOCAL_IP_ADDR_END = UDP_LOCAL_IP_ADDR_START + 4,

  UDP_LOCAL_PORT_ADDR_START,
  UDP_LOCAL_PORT_ADDR_END = UDP_LOCAL_PORT_ADDR_START + 4,

  UDP_REMOTE_HOST_ADDR_START,
  UDP_REMOTE_HOST_ADDR_END = UDP_REMOTE_HOST_ADDR_START + 64,

  UDP_REMOTE_PORT_ADDR_START,
  UDP_REMOTE_PORT_ADDR_END = UDP_REMOTE_PORT_ADDR_START + 4,
  
};
#endif
