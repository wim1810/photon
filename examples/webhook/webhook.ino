// Photon webhook example (Particle Device OS, Wiring/Arduino-style).
// Button on D3 (to GND) publishes "temp-alert"; the Particle cloud then
// forwards it to your URL as defined in webhook.json.
// Also listens for a "hook-response/temp-alert" reply from the server.

const int BUTTON_PIN = D3;
const int LED_PIN = D7;
unsigned long lastPublish = 0;

void hookResponse(const char *event, const char *data) {
  Serial.printlnf("Response: %s", data);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Particle.subscribe("hook-response/temp-alert", hookResponse, MY_DEVICES);
}

void loop() {
  // Debounce + rate limit (Particle allows ~1 publish/sec sustained)
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastPublish > 2000) {
    lastPublish = millis();
    // Replace with a real sensor read
    float value = analogRead(A0) * 3.3 / 4095.0;
    Particle.publish("temp-alert", String::format("{\"value\":%.2f}", value), PRIVATE);
  }
}
