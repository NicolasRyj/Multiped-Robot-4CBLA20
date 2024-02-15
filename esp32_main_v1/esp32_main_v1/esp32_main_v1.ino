#include <WiFi.h>
#include <WebServer.h>
#include <Servo.h>

const char* ssid = "s22nr";
const char* password = "*******";

WebServer server(80);

Servo servo1;
Servo servo2;
Servo servo3; // Continuous rotation servo
Servo servo4; // Continuous rotation servo

void setup() {
  servo1.attach(25); // Attach servo to GPIO 25
  servo2.attach(26); // Attach servo to GPIO 26
  servo3.attach(27); // Attach servo to GPIO 27
  servo4.attach(14); // Attach servo to GPIO 14

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", generateWebPage());
  });

  server.on("/servo", HTTP_GET, []() {
    if (server.hasArg("servo") && server.hasArg("position")) {
      int servoNumber = server.arg("servo").toInt();
      int position = server.arg("position").toInt();
      adjustServo(servoNumber, position);
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

String generateWebPage() {
  String html = "<!DOCTYPE html><html><body><h2>Servo Control</h2>";
  html += "<p>Control Servos:</p><form action=\"/servo\">";
  for(int i = 1; i <= 4; i++) {
    html += "Servo " + String(i) + ": <input type=\"range\" min=\"0\" max=\"180\" name=\"position\" onchange=\"updateServo(" + String(i) + ", this.value)\" /><br>";
  }
  html += "<script>function updateServo(servo, position) { var xhttp = new XMLHttpRequest(); xhttp.open(\"GET\", \"/servo?servo=\"+servo+\"&position=\"+position, true); xhttp.send(); }</script>";
  html += "</body></html>";
  return html;
}

void adjustServo(int servoNumber, int position) {
  switch (servoNumber) {
    case 1:
      servo1.write(position);
      break;
    case 2:
      servo2.write(position);
      break;
    case 3:
      servo3.write(position);
      break;
    case 4:
      servo4.write(position);
      break;
  }
}
