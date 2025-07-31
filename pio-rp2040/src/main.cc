#include <Arduino.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println("Hello, World!");
    const uint32_t* c = (uint32_t*)(0x40000000 + 0x0);
    Serial.println(*c, HEX);
    const uint32_t* p = (uint32_t*)(0x40000000 + 0x4);
    Serial.println(*p, HEX);
    const uint32_t* g = (uint32_t*)(0x40000000 + 0x40);
    Serial.println(*g, HEX);
    delay(1000);
}
