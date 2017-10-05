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

#ifndef COOGLEIOT_WEBPAGES_HOME_H_
#define COOGLEIOT_WEBPAGES_HOME_H_

const char WEBPAGE_Home[] PROGMEM = R"=====(
<html>
  <head>
    <title>ldos Firmware</title>
    <link href="/css" type="text/css" rel="stylesheet">
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
    <h3>ldos Device Setup</h3>
    <div class="tabs" style="margin-top: 5px; margin-bottom: 5px;">
      <input type="radio" name="navtabs" id="tab1" checked="" aria-hidden="true">
      <label for="tab1" aria-hidden="true">WiFi</label>
        <div style="height: 600px">
         <fieldset>
           <legend>Device Wireless Setup</legend>
             <p>Settings for the device WiFi (as AP)</p>
             <div class="input-group fluid">
               <label aria-hidden="true" for="wifi_local_ssid">Device AP SSID</label>
               <input aria-hidden="true" type="text" value="{{wifi_local_ssid}}" id="wifi_local_ssid" placeholder="Device AP Name">
             </div>
             <div class="input-group fluid">
               <label aria-hidden="true" for="wifi_local_password">Device AP Password</label>
               <input aria-hidden="true" type="password" value="{{wifi_local_password}}" id="wifi_local_password">
             </div>
               <div class="input-group fluid">
                 <label aria-hidden="true" for="wifi_local_ip">Device IP</label>
                 <input aria-hidden="true" value="{{wifi_local_ip}}" id="wifi_local_ip" placeholder="Device IP" type="text">
               </div>
               <div class="input-group fluid">
                 <label aria-hidden="true" for="wifi_local_mask">Device Mask</label>
                 <input aria-hidden="true" value="{{wifi_local_mask}}" id="wifi_local_mask" placeholder="Device Mask" type="text">
               </div>
               <div class="input-group fluid">
                 <label aria-hidden="true" for="wifi_local_gateway">Device Gateway</label>
                 <input aria-hidden="true" value="{{wifi_local_gateway}}" id="wifi_local_gateway" placeholder="Device Gateway" type="text">
               </div>
         </fieldset>
         <fieldset>
           <legend>Client WiFi Setup</legend>
           <p>Settings for WiFi (as Client)</p>
           <div class="input-group fluid">
             <label aria-hidden="true" for="wifi_remote_ssid">Remote SSID</label>
             <input aria-hidden="true" type="text" value="{{wifi_remote_ssid}}" id="wifi_remote_ssid" placeholder="Remote AP Name">
           </div>
           <div class="input-group fluid">
              <label aria-hidden="true" for="wifi_remote_password">Remote SSID Password</label>
              <input aria-hidden="true" type="password" value="{{wifi_remote_password}}" id="wifi_remote_password">
           </div>
         </fieldset>
      </div>
      <input type="radio" name="navtabs" id="tab2" aria-hidden="true">
      <label for="tab2" aria-hidden="true">TCP&UDP</label>
      <div style="height: 600px">
        <fieldset>
          <legend>Server TCP Setup</legend>
            <p>Settings for the device TCP (as Server)</p>
          <div class="input-group fluid">
            <label aria-hidden="true" for="tcp_local_ip">TCP Server IP</label>
            <input aria-hidden="true" type="text" value="{{tcp_local_ip}}" id="tcp_local_ip" placeholder="IP">
          </div>
          <div class="input-group fluid">
            <label aria-hidden="true" for="tcp_local_port">TCP Server Port</label>
            <input aria-hidden="true" type="text" value="{{tcp_local_port}}" id="tcp_local_port">
          </div>
        </fieldset>
           <fieldset>
             <legend>Client TCP Setup</legend>
             <p>Settings for TCP (as Client)</p>
             <div class="input-group fluid">
               <label aria-hidden="true" for="tcp_remote_host">Remote Host</label>
               <input aria-hidden="true" value="{{tcp_remote_host}}" id="tcp_remote_host" placeholder="Remote Host" type="text">
             </div>
             <div class="input-group fluid">
                <label aria-hidden="true" for="tcp_remote_port">Remote Port</label>
                <input aria-hidden="true" value="{{tcp_remote_port}}" id="tcp_remote_port" type="text">
             </div>
           </fieldset>
		   <fieldset>
             <legend>Server UDP Setup</legend>
               <p>Settings for the device UDP (as server)</p>
               <div class="input-group fluid">
                 <label aria-hidden="true" for="udp_local_ip">Device IP</label>
                 <input aria-hidden="true" value="{{udp_local_ip}}" id="udp_local_ip" placeholder="Device IP" type="text">
               </div>
               <div class="input-group fluid">
                 <label aria-hidden="true" for="udp_local_port">Device Port</label>
                 <input aria-hidden="true" value="{{udp_local_port}}" id="udp_local_port" type="text">
               </div>
           </fieldset>
           <fieldset>
             <legend>Client UDP Setup</legend>
             <p>Settings for UDP (as Client)</p>
             <div class="input-group fluid">
               <label aria-hidden="true" for="udp_remote_host">Remote IP</label>
               <input aria-hidden="true" value="{{udp_remote_host}}" id="udp_remote_host" placeholder="Remote Host" type="text">
             </div>
             <div class="input-group fluid">
                <label aria-hidden="true" for="udp_remote_port">Remote Port</label>
                <input aria-hidden="true" value="{{udp_remote_port}}" id="udp_remote_port" type="text">
             </div>
           </fieldset>
      </div>
      <input type="radio" name="navtabs" id="tab3" aria-hidden="true">
      <label for="tab3" aria-hidden="true">System</label>
      <div style="height: 600px">
        <h3>System Commands</h3>
        <button class="secondary large" id="resetEEPROMBtn">Reset EEPROM (factory reset)</button>
        <button class="primary large" id="reloadBtn">Reboot</button>
        <fieldset>
          <legend>Firmware Updates</legend>
            <p>Device will check for updates every 30 minutes at this URL. See:<br><br>
            <a href="http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html#http-server">http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html#http-server</a><br><br>
            For details on the server-side implementation.</p>
          <div class="input-group fluid">
            <label aria-hidden="true" for="firmware_url">Firmware Update URL</label>
            <input aria-hidden="true" type="text" value="{{firmware_url}}" id="firmware_url" placeholder="http://example.com/updateEndpoint.php">
          </div>
          <p>Alternatively, you can directly upload a new .bin firmware file below:</p>
          <div class="input-group fluid">
            <form action="/firmware-upload" method="POST" enctype="multipart/form-data">
              <input type="file" id="firmware_file" name="update" accept=".bin">
              <label aria-hidden="true" for="firmware_file" class="button">Step 1: Select Firmware</label>
              <input type="submit" value="Step 2: Begin Upload">
            </form>
          </div>
        </fieldset>
      </div>
      <input type="radio" name="navtabs" id="tab4" aria-hidden="true">
      <label for="tab4" aria-hidden="true">Status</label>
      <div style="height: 600px">
        <table class="horizontal">
          <caption>ldos Status</caption>
          <thead>
            <tr>
              <th>ldos Version</th>
              <th>ldos AP Status</th>
              <th>ldos AP SSID</th>
              <th>WiFi Status</th>
              <th>WiFi SSID</th>
              <th>LAN IP Address</th>
              <th>NTP Status</th>
              <th>DNS Status</th>
              <th>Firmware Updates</th>
            </tr>
         </thead>
         <tbody>
           <tr>
             <td data-label="ldos Version">{{coogleiot_version}}</td>
             <td data-label="ldos AP Status">{{coogleiot_ap_status}}</td>
             <td data-label="ldos AP SSID">{{coogleiot_ap_ssid}}</td>
             <td data-label="WiFi Status">{{wifi_status}}</td>
             <td data-label="WiFi SSID">{{remote_ap_name}}</td>
             <td data-label="LAN IP Address">{{wifi_ip_address}}</td>
             <td data-label="NTP Status">{{ntp_status}}</td>
             <td data-label="DNS Status">{{dns_status}}</td>
             <td data-label="Firmware Updates">{{firmware_update_status}}</td>
           </tr>
         </tbody>
        </table>
      </div>
    </div>
    <button class="primary bordered" style="width: 100%" id="saveBtn">Save and Restart</button>
	<script src="/jquery"></script>
    <script>
      $(document).ready(function() {
        
        $('#saveBtn').on('click', function(e) {
          e.preventDefault();
          
          var postData = {
            'ap_name' : $('#ap_name').val(),
            'ap_password' : $('#ap_password').val(),
            'remote_ap_name' : $('#ap_remote_name').val(),
            'remote_ap_password' : $('#ap_remote_password').val(),
            'firmware_url' : $('#firmware_url').val()
          }
          
          console.log(postData);
          
          $.post('/api/save', postData, function(result) {
            
            if(!result.status) {
              alert("Failed to save settings");
              return;
            }
            
            alert("Settings Saved!");
            
          });
        });
      });
    </script>
  </body>
</html>
)=====";


#endif /* COOGLEIOT_WEBPAGES_HOME_H_ */
