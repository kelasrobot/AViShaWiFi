```
### AViShaWiFi Library

AViShaWiFi is a simple library for connecting ESP8266 devices to WiFi networks and making HTTP/HTTPS requests. This library provides functions for initiating WiFi connection, making GET and POST requests over both HTTP and HTTPS protocols.

---

## Installation

To use AViShaWiFi library in your Arduino projects, follow these steps:

1. Download the AViShaWiFi-main.zip file from this repository.
2. Open the Arduino IDE.
3. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library`.
4. Select the downloaded AViShaWiFi-main.zip file.
5. The library will be added to your Arduino IDE.

---

## Usage

### Initializing AViShaWiFi

To begin using the AViShaWiFi library, you first need to initialize it with your WiFi credentials. Use the `begin()` function to connect to your WiFi network.

```cpp
#include "AViShaWiFi.h"

AViShaWiFi avishaWiFi;

void setup() {
  avishaWiFi.begin("YourWiFiSSID", "YourWiFiPassword");
}
```

### Making HTTP Requests

AViShaWiFi supports making both HTTP GET and POST requests. Use the `httpGET()` and `httpPOST()` functions respectively.

```cpp
String response = avishaWiFi.httpGET("http://example.com/api/data");
```

```cpp
String payload = "{\"key\":\"value\"}";
std::vector<String> headers = {"Content-Type: application/json"};
String response = avishaWiFi.httpPOST("http://example.com/api/post", payload, headers);
```

### Making HTTPS Requests

For HTTPS requests, use the `httpsGET()` and `httpsPOST()` functions. Ensure that the server's SSL certificate is valid.

```cpp
String response = avishaWiFi.httpsGET("https://example.com/api/data");
```

```cpp
String payload = "{\"key\":\"value\"}";
std::vector<String> headers = {"Content-Type: application/json"};
String response = avishaWiFi.httpsPOST("https://example.com/api/post", payload, headers);
```

---

## Dependencies

- Arduino
- ESP8266WiFi
- ESP8266HTTPClient
- WiFiClientSecureBearSSL

---

## Contributing

If you find any issues or have suggestions for improvement, please feel free to open an issue or create a pull request on GitHub.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```
