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

#include "CoogleIOTWebserver.h"
#include <ESP8266WebServer.h>

#ifdef COOGLEIOT_DEBUG

#define MDNS_DEBUG_RX
#define MDNS_DEBUG_TX
#define MDNS_DEBUG_ERR

#endif

CoogleIOTWebserver::CoogleIOTWebserver(CoogleIOT &_iot)
{
	setIOT(_iot);

	this->serverPort = 80;

	iot->info("Creating Configuration Web Server");

	setWebserver(new ESP8266WebServer(this->serverPort));
}

CoogleIOTWebserver::CoogleIOTWebserver(CoogleIOT &_iot, int port)
{
	setIOT(_iot);

	this->serverPort = port;

	iot->info("Creating Configuration Web Server");
	setWebserver(new ESP8266WebServer(this->serverPort));
}

CoogleIOTWebserver::~CoogleIOTWebserver()
{
	delete webServer;
}

CoogleIOTWebserver &CoogleIOTWebserver::initializePages()
{
	webServer->on("/", std::bind(&CoogleIOTWebserver::handleRoot, this));
	webServer->on("/css", std::bind(&CoogleIOTWebserver::handleCSS, this));
	webServer->on("/reset", std::bind(&CoogleIOTWebserver::handleReset, this));
	webServer->on("/restart", std::bind(&CoogleIOTWebserver::handleRestart, this));
	webServer->on("/jquery", std::bind(&CoogleIOTWebserver::handleJS, this));

	webServer->on("/api/status", std::bind(&CoogleIOTWebserver::handleApiStatus, this));
	webServer->on("/api/reset", std::bind(&CoogleIOTWebserver::handleApiReset, this));
	webServer->on("/api/restart", std::bind(&CoogleIOTWebserver::handleApiRestart, this));
	webServer->on("/api/save", std::bind(&CoogleIOTWebserver::handleSubmit, this));

	webServer->on("/firmware-upload",
				  HTTP_POST,
				  std::bind(&CoogleIOTWebserver::handleFirmwareUploadResponse, this),
				  std::bind(&CoogleIOTWebserver::handleFirmwareUpload, this));

	webServer->onNotFound(std::bind(&CoogleIOTWebserver::handle404, this));

	return *this;
}

CoogleIOTWebserver &CoogleIOTWebserver::setServerPort(int port)
{
	this->serverPort = port;
	return *this;
}

CoogleIOTWebserver &CoogleIOTWebserver::setWebserver(ESP8266WebServer *server)
{
	this->webServer = server;
	return *this;
}

CoogleIOTWebserver &CoogleIOTWebserver::setIOT(CoogleIOT &_iot)
{
	this->iot = &_iot;
	return *this;
}

bool CoogleIOTWebserver::initialize()
{
	iot->info("Initializing Webserver");

	initializePages();
	webServer->begin();

	iot->info("Webserver Initiailized!");

	return true;
}

void CoogleIOTWebserver::loop()
{
	webServer->handleClient();
}

String CoogleIOTWebserver::htmlEncode(char *input)
{
	String i = String(input);
	return htmlEncode(i);
}

String CoogleIOTWebserver::htmlEncode(String &input)
{
	char t;
	String retval, escape;

	for (int i = 0; i < input.length(); i++)
	{
		t = input.charAt(i);
		switch (t)
		{
		case '&':
			escape = "&amp;";
			break;

		case '<':
			escape = "&lt;";
			break;

		case '>':
			escape = "&gt;";
			break;

		case '"':
			escape = "&quot;";
			break;

		case '\'':
			escape = "&#39;";
			break;

		default:
			escape = t;
			break;
		}

		retval = retval + escape;
	}

	return retval;
}
void CoogleIOTWebserver::handleRoot()
{
	String page(FPSTR(WEBPAGE_Home));
	String wifi_local_ssid, wifi_local_password, wifi_remote_ssid, wifi_remote_password,
		wifi_local_ip, wifi_local_mask, wifi_local_gateway,
		tcp_local_ip, tcp_local_port, tcp_remote_host, tcp_remote_port,
		udp_local_ip, udp_local_port, udp_remote_host, udp_remote_port,
		firmware_url, local_ip, mac_address, wifi_status;

	wifi_local_ip = String(iot->getLocalIP());
	wifi_local_mask = String(iot->getLocalMask());
	wifi_local_gateway = String(iot->getLocalGateway());

	wifi_local_ssid = iot->getWiFiLocalSSID();
	wifi_local_password = iot->getWiFiLocalPassword();
	wifi_remote_ssid = iot->getWiFiRemoteSSID();
	wifi_remote_password = iot->getWiFiRemotePassword();

	tcp_local_ip = String(iot->getTCPLocalIP());
	tcp_local_port = String(iot->getTCPLocalPort());
	tcp_remote_host = iot->getTCPRemoteHost();
	tcp_remote_port = String(iot->getTCPRemotePort());

	udp_local_ip = String(iot->getUDPLocalIP());
	udp_local_port = String(iot->getUDPLocalPort());
	udp_remote_host = iot->getUDPRemoteHost();
	udp_remote_port = String(iot->getUDPRemotePort());

	firmware_url = iot->getFirmwareUpdateUrl();
	local_ip = WiFi.localIP().toString();
	mac_address = WiFi.macAddress();
	wifi_status = iot->getWiFiStatus();

	page.replace(F("{{wifi_local_ip}}"), htmlEncode(wifi_local_ip));
	page.replace(F("{{wifi_local_mask}}"), htmlEncode(wifi_local_mask));
	page.replace(F("{{wifi_local_gateway}}"), htmlEncode(wifi_local_gateway));
	page.replace(F("{{wifi_local_ssid}}"), htmlEncode(wifi_local_ssid));
	page.replace(F("{{wifi_local_password}}"), htmlEncode(wifi_local_password));
	page.replace(F("{{wifi_remote_ssid}}"), htmlEncode(wifi_remote_ssid));
	page.replace(F("{{wifi_remote_password}}"), htmlEncode(wifi_remote_password));

	page.replace(F("{{tcp_local_ip}}"), htmlEncode(tcp_local_ip));
	page.replace(F("{{tcp_local_port}}"), htmlEncode(tcp_local_port));
	page.replace(F("{{tcp_remote_host}}"), htmlEncode(tcp_remote_host));
	page.replace(F("{{tcp_remote_port}}"), htmlEncode(tcp_remote_port));

	page.replace(F("{{udp_local_ip}}"), htmlEncode(udp_local_ip));
	page.replace(F("{{udp_local_port}}"), htmlEncode(udp_local_port));
	page.replace(F("{{udp_remote_host}}"), htmlEncode(udp_remote_host));
	page.replace(F("{{udp_remote_port}}"), htmlEncode(udp_remote_port));

	page.replace(F("{{firmware_url}}"), htmlEncode(firmware_url));
	page.replace(F("{{coogleiot_version}}"), htmlEncode(COOGLEIOT_VERSION));
	page.replace(F("{{coogleiot_ap_ssid}}"), htmlEncode(wifi_local_ssid));
	page.replace(F("{{mac_address}}"), htmlEncode(mac_address));
	page.replace(F("{{wifi_status}}"), htmlEncode(wifi_status));
	page.replace(F("{{ntp_status}}"), iot->ntpActive() ? "Active" : "Not Connected");
	page.replace(F("{{dns_status}}"), iot->dnsActive() ? "Active" : "Disabled");
	page.replace(F("{{firmware_update_status}}"), iot->firmwareClientActive() ? "Active" : "Disabled");
	page.replace(F("{{coogleiot_ap_status}}"), iot->apStatus() ? "Active" : "Disabled");

	webServer->send(200, "text/html", page.c_str());
}

void CoogleIOTWebserver::handleJS()
{
	webServer->sendHeader("Content-Encoding", "gzip", true);
	webServer->send_P(200, "application/javascript", jquery_3_2_1_min_js_gz, jquery_3_2_1_min_js_gz_len);
}

void CoogleIOTWebserver::handleCSS()
{
	webServer->send_P(200, "text/css", WEBPAGE_CSS, mini_default_min_css_len);
}

void CoogleIOTWebserver::handle404()
{
	webServer->send_P(404, "text/html", WEBPAGE_NOTFOUND);
}

void CoogleIOTWebserver::handleFirmwareUploadResponse()
{
	if (_manualFirmwareUpdateSuccess)
	{
		webServer->send_P(200, "text/html", WEBPAGE_Restart);
		return;
	}

	webServer->send(200, "text/html", "There was an error uploading the firmware");
}

void CoogleIOTWebserver::handleFirmwareUpload()
{
	HTTPUpload &upload = webServer->upload();
	uint32_t maxSketchSpace;

	switch (upload.status)
	{
	case UPLOAD_FILE_START:
		WiFiUDP::stopAll();

		iot->info("Receiving Firmware Upload...");

		maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;

		if (!Update.begin(maxSketchSpace))
		{
			iot->error("Failed to begin Firmware Upload!");

			if (iot->serialEnabled())
			{
				Update.printError(Serial);
			}

			_manualFirmwareUpdateSuccess = false;
		}

		break;
	case UPLOAD_FILE_WRITE:

		if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
		{

			iot->error("Failed to write Firmware Upload!");

			if (iot->serialEnabled())
			{
				Update.printError(Serial);
			}

			_manualFirmwareUpdateSuccess = false;
		}
		break;

	case UPLOAD_FILE_END:

		if (Update.end(true))
		{

			iot->info("Firmware updated!");

			_manualFirmwareUpdateSuccess = true;
		}
		else
		{
			iot->error("Failed to update Firmware!");

			if (iot->serialEnabled())
			{
				Update.printError(Serial);
			}

			_manualFirmwareUpdateSuccess = false;
		}

		break;

	case UPLOAD_FILE_ABORTED:
		Update.end();

		iot->info("Firmware upload aborted!");

		_manualFirmwareUpdateSuccess = false;

		break;
	}

	yield();
}

void CoogleIOTWebserver::handleSubmit()
{
	StaticJsonBuffer<400> jsonBuffer;
	WiFiClientPrint<> p(webServer->client());

	JsonObject &retval = jsonBuffer.createObject();
	JsonArray &errors = retval.createNestedArray("errors");

	String wifi_local_ssid, wifi_local_password, wifi_remote_ssid, wifi_remote_password,
		tcp_local_ip, tcp_local_port, tcp_remote_host, tcp_remote_port,
		udp_local_ip, udp_local_port, udp_remote_host, udp_remote_port,
		firmware_url;

	bool success = true;

	wifi_local_ssid = webServer->arg("wifi_local_ssid");
	wifi_local_password = webServer->arg("wifi_local_password");
	wifi_remote_ssid = webServer->arg("wifi_remote_ssid");
	wifi_remote_password = webServer->arg("wifi_remote_password");

	tcp_local_ip = webServer->arg("tcp_local_ip");
	tcp_local_port = webServer->arg("tcp_local_port");
	tcp_remote_host = webServer->arg("tcp_remote_host");
	tcp_remote_port = webServer->arg("tcp_remote_port");

	udp_local_ip = webServer->arg("udp_local_ip");
	udp_local_port = webServer->arg("udp_local_port");
	udp_remote_host = webServer->arg("udp_remote_host");
	udp_remote_port = webServer->arg("udp_remote_port");

	firmware_url = webServer->arg("firmware_url");

	if (wifi_local_ssid.length() > 0)
	{
		if (wifi_local_ssid.length() < WIFI_LOCAL_IP_ADDR_END - WIFI_LOCAL_IP_ADDR_START)
		{
			iot->setWiFiLocalSSID(wifi_local_ssid);
		}
		else
		{
			errors.add("AP Name was too long");
			success = false;
		}
	}

	if (wifi_local_password.length() < WIFI_LOCAL_PASSWORD_ADDR_END - WIFI_LOCAL_PASSWORD_ADDR_START)
	{
		iot->setWiFiLocalPassword(wifi_local_password);
	}
	else
	{
		errors.add("AP Password is too long!");
		success = false;
	}

	if (wifi_remote_ssid.length() > 0)
	{
		if (wifi_remote_ssid.length() < WIFI_REMOTE_SSID_ADDR_END - WIFI_REMOTE_SSID_ADDR_START)
		{
			iot->setWiFiRemoteSSID(wifi_remote_ssid);
		}
		else
		{
			errors.add("Remote AP Name is too long!");
			success = false;
		}
	}

	if (wifi_remote_password.length() < WIFI_REMOTE_PASSWORD_ADDR_END - WIFI_REMOTE_PASSWORD_ADDR_START)
	{
		iot->setWiFiRemotePassword(wifi_remote_password);
	}
	else
	{
		errors.add("Remote AP Password was too long!");
		success = false;
	}

	if (tcp_local_ip.length() > 0)
	{
		iot->setTCPLocalIP(atoi(tcp_local_ip.c_str()));
	}

	if (tcp_local_port.length() > 0)
	{
		iot->setTCPLocalPort(atoi(tcp_local_port.c_str()));
	}

	if (tcp_remote_host.length() > 0)
	{
		if (tcp_remote_host.length() < TCP_REMOTE_HOST_ADDR_END - TCP_REMOTE_HOST_ADDR_START)
		{
			iot->setTCPRemoteHost(tcp_remote_host);
		}
		else
		{
			errors.add("TCP Remote Host Name is too long!");
			success = false;
		}
	}

	if (tcp_remote_port.length() > 0)
	{
		iot->setTCPRemotePort(atoi(tcp_remote_port.c_str()));
	}

	if (udp_local_ip.length() > 0)
	{
		iot->setUDPLocalIP(atoi(udp_local_ip.c_str()));
	}

	if (udp_local_port.length() > 0)
	{
		iot->setUDPLocalPort(atoi(udp_local_port.c_str()));
	}

	if (udp_remote_host.length() > 0)
	{
		if (udp_remote_host.length() < UDP_REMOTE_HOST_ADDR_END - UDP_REMOTE_HOST_ADDR_START)
		{
			iot->setUDPRemoteHost(udp_remote_host);
		}
		else
		{
			errors.add("UDP Remote Host Name is too long!");
			success = false;
		}
	}

	if (udp_remote_port.length() > 0)
	{
		iot->setUDPRemotePort(atoi(udp_remote_port.c_str()));
	}

	if (firmware_url.length() > 0)
	{
		if (firmware_url.length() < COOGLEIOT_FIRMWARE_UPDATE_URL_MAXLEN)
		{
			iot->setFirmwareUpdateUrl(firmware_url);
		}
		else
		{
			errors.add("The Firmware Update URL was too long");
			success = false;
		}
	}

	retval["status"] = success;

	webServer->setContentLength(retval.measureLength());
	webServer->send(200, "application/json", "");

	retval.printTo(p);
	p.stop();
}

void CoogleIOTWebserver::handleReset()
{
	webServer->send_P(200, "text/html", WEBPAGE_Restart);
	iot->resetEEProm();
}

void CoogleIOTWebserver::handleRestart()
{
	webServer->send_P(200, "text/html", WEBPAGE_Restart);
}

void CoogleIOTWebserver::handleApiReset()
{
	iot->resetEEProm();
}

void CoogleIOTWebserver::handleApiRestart()
{
	iot->restartDevice();
}

void CoogleIOTWebserver::handleApiStatus()
{
	StaticJsonBuffer<200> jsonBuffer;
	WiFiClientPrint<> p(webServer->client());

	JsonObject &retval = jsonBuffer.createObject();

	retval["status"] = !iot->_restarting;

	webServer->setContentLength(retval.measureLength());
	webServer->send(200, "application/json", "");
	retval.printTo(p);
	p.stop();
}
