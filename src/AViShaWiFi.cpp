#include "AViShaWiFi.h"

AViShaWiFi::AViShaWiFi() {
}

void AViShaWiFi::begin(const char* ssid, const char* password) {
  _ssid = ssid;
  _password = password;
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);
  Serial.print("[WIFI] Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WIFI] Connecting to WiFi ..");
    delay(1000);
  }
  Serial.println("[WIFI] Connected to WiFi!");
  Serial.print("[WIFI] IP Address: ");
  Serial.println(WiFi.localIP());
}

String AViShaWiFi::httpsGET(const char* url) {
  String response = "";
  if ((WiFi.status() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, url)) {
      Serial.print("[HTTPS] GET to: ");
      Serial.println(url);
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTPS] GET... Response code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          response = https.getString();
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  return response;
}

String AViShaWiFi::httpsPOST(const char* url, String payload, std::vector<String> headers) {
  String response = "";
  if ((WiFi.status() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    Serial.print("[HTTPS] POST to: ");
    Serial.println(url);
    if (https.begin(*client, url)) {
      for (const String& header : headers) {
        int separatorIndex = header.indexOf(':');
        if (separatorIndex != -1) {
          String headerName = header.substring(0, separatorIndex);
          String headerValue = header.substring(separatorIndex + 1);
          Serial.printf("[HTTPS] Adding header: %s: %s\n", headerName.c_str(), headerValue.c_str());
          https.addHeader(headerName.c_str(), headerValue.c_str());
        }
      }
      Serial.println("[HTTPS] POST payload:");
      Serial.println(payload);
      int httpCode = https.POST(payload);
      if (httpCode > 0) {
        Serial.printf("[HTTPS] POST Response code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
          response = https.getString();
        }
      } else {
        Serial.printf("[HTTPS] POST Get failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  return response;
}

String AViShaWiFi::httpGET(const char* url) {
  String response = "";
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(url)) {
      Serial.print("[HTTP] GET to: ");
      Serial.println(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... Response code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          response = http.getString();
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
  }
  return response;
}

String AViShaWiFi::httpPOST(const char* url, String payload, std::vector<String> headers) {
  String response = "";
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    Serial.print("[HTTP] POST to: ");
    Serial.println(url);
    if (http.begin(url)) {
      for (const String& header : headers) {
        int separatorIndex = header.indexOf(':');
        if (separatorIndex != -1) {
          String headerName = header.substring(0, separatorIndex);
          String headerValue = header.substring(separatorIndex + 1);
          Serial.printf("[HTTP] Adding header: %s: %s\n", headerName.c_str(), headerValue.c_str());
          http.addHeader(headerName.c_str(), headerValue.c_str());
        }
      }
      Serial.println("[HTTP] POST payload:");
      Serial.println(payload);
      int httpCode = http.POST(payload);
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST Response code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
          response = http.getString();
        }
      } else {
        Serial.printf("[HTTP] POST Get failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
  }
  return response;
}