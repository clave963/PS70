
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x84, 0xFC, 0xE6, 0x00, 0x92, 0xA4};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  bool start;
  int speed;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
const int Pot_pin = D0;  // define pin D0 (PWM Speed)
const int Switch_pin = D2;  // define pin D2 (on/off switch) 

bool prevSwitch = false;
int prevPot = 0;
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  
  pinMode(D2, INPUT);  //This will be GND for the potentiometer
  pinMode(D0, INPUT);  //This will be switch

  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  if (digitalRead(D2) != prevSwitch)
     {
     myData.start = digitalRead(D2);
     myData.speed = map(analogRead(D0), 0, 4095, 255, 0);
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    prevSwitch = digitalRead(D2);
    prevPot = analogRead(D0);
     }
    
}