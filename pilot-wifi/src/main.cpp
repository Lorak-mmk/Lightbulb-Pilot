#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "pilot.h"

const char* ssid = "Mieszkanie-UPC";
const char* password = "hasloD0wifi";
const int led = LED_BUILTIN;
const String html_prefix =
        "<html>\n"
        "<head>\n"
        "<title>WiFi Lightbulb Pilot</title>\n"
        "<style>\n"
        "body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n"
        "</style>\n"
        "</head>\n"
        "<body>\n";
const String html_suffix = "</body>\n"
                           "</html>\n";

ESP8266WebServer server(80);
Sender sender{};

void handleRoot() {
    digitalWrite(led, LOW);
    server.send(200, "text/plain", "hello from pilot-wifi!");
    digitalWrite(led, HIGH);
}

void handleSend_api(bool command_requested, const String& command_string, long command_value) {
    String message = "";
    if(command_requested) {
        if(command_string != "") {
            message += R"({ "command": ")" + command_string + R"(", "value": )";
            message += command_value;
            message += R"(, "status": "success"})";
            server.send(200, "application/json", message);
            return;
        } else {
            message += R"({"status": "error", "message": "Invalid value"})";
            server.send(400, "application/json", message);
            return;
        }
    }
    message += R"({"commands": [)";
    uint8_t len = (sizeof(commands_names) / sizeof(commands_names[0]));
    for(uint8_t i = 0; i < len; i++) {
        message += R"({"name": ")" + commands_names[i].name + R"(", "value": )";
        message += commands_names[i].value;
        message += R"(})";
        if(i != len - 1) {
            message += ",";
        }
    }
    message += "]}";
    server.send(200, "application/json", message);
}

void handleSend_normal(bool command_requested, const String& command_string, long command_value) {
    String message = "";
    message += html_prefix;
    if(command_requested) {
        if(command_string != "") {
            message += "<p> Received command " + command_string + " value: ";
            message += command_value;
            message += "</p>\n";
        } else {
            message += "<p> Received invalid command! </p>\n";
        }
    }
    message += "<p> Available commands: </p>\n";
    for(uint8_t i = 0; i < (sizeof(commands_names) / sizeof(commands_names[0])); i++) {
        message += "<p><a href=/send?command=";
        message += commands_names[i].value;
        message += ">" + commands_names[i].name + "</a></p>\n";
    }

    message += html_suffix;
    server.send(200, "text/html", message);
}

void handleSend() {
    digitalWrite(led, LOW);
    String command_arg = server.arg("command");
    bool command_requested = command_arg != "";
    uint32_t command_value = command_arg.toInt();
    String command_string = get_command(command_value);

    if(command_string != "") {
        sender.send(command_value);
    }

    bool is_api = server.arg("api") != "";
    if(is_api) {
        handleSend_api(command_requested, command_string, command_value);
    } else {
        handleSend_normal(command_requested, command_string, command_value);
    }
    digitalWrite(led, HIGH);
}


void handleNotFound(){
    digitalWrite(led, LOW);

    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET)?"GET":"POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i=0;  i <server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
    digitalWrite(led, HIGH);
}

void setup(void){
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("lightbulb-wifi")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.on("/send", handleSend);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop(void){
    server.handleClient();
    yield();
}