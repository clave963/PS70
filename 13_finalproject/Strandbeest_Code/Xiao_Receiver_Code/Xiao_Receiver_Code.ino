
#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    bool start;
    int speed;
} struct_message;

// Create a struct_message called myData
struct_message myData;

const int A1A = D0;
const int A1B = D1;

bool motorsOn = false;
int speed = 150;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(myData.start);

  // Check if start signal received
  if (myData.start) {
    motorsOn = true;
    // If start signal received, set motor speed
    
  } else {
    motorsOn = false;
    // Turn off motor
    
  }
}
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if(motorsOn){
    analogWrite(A1A, speed);
    digitalWrite(A1B, LOW);
  }
  else{
    analogWrite(A1A, 0);
    digitalWrite(A1B, LOW);
  }
}