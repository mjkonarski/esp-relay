# LC Technology ESP8266 relay software
This is an Arduino sketch with implementation of HTTP server controlling the LC Technology ESP8266 module.

## Running

Open the sketch in Arduino IDE with ESP8266 library configured. Copy `wifi_credentials.h.example` to `wifi_credentials.h` and change its content. To program the ESP8266 module you have to remove it from the board and connect to the regular development setup with serial converter.

After uploading to the controller you can visit the main page and click the reset button or simply shot POST request to `/reset` endpoint.
