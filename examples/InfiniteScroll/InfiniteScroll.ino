#include <DigiCombo.h>

void setup() {
  DigiCombo.begin();
}

void loop() {
  for (int i = 0; i < 4000; i += 25) {
    DigiCombo.moveFinger(5000, 7000 - i);
  }
  DigiCombo.release();
}
