#include <DigiCombo.h>

void setup() {
  DigiCombo.begin();
}

void loop() {
  DigiCombo.tapSingle(5000, 5000);
  DigiCombo.delay(752); // + 50
}
