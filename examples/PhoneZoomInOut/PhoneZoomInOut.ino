#include <DigiCombo.h>

void setup() {
  DigiCombo.begin();

  DigiCombo.write('b');
  DigiCombo.delay(2000);
  DigiCombo.sendKeyStroke(KEYCODE_BACKSPACE);

  DigiCombo.pressKey(KEYCODE_D, MOD_LEFT_SHIFT);
  DigiCombo.release();
  DigiCombo.print("igispark"); 

  DigiCombo.write(' ');
  DigiCombo.pressKey(KEYCODE_A, MOD_LEFT_SHIFT);
  DigiCombo.release();
  DigiCombo.println("ttiny 85");

  DigiCombo.delay(4000);
}

void loop() {  
  // Zoom in
  for (int i = 0; i < 1000; i += 10) {
    DigiCombo.moveFinger(5000, 4000 - i, CONTACT_ONE);
    DigiCombo.moveFinger(5000, 6000 + i, CONTACT_TWO);   
  }
  DigiCombo.release(CONTACT_ONE);
  DigiCombo.release(CONTACT_TWO);

  // Zoom out
  for (int i = 0; i < 1000; i += 10) {
    DigiCombo.moveFinger(5000, 3000 + i, CONTACT_ONE);
    DigiCombo.moveFinger(5000, 7000 - i, CONTACT_TWO);   
  }
  DigiCombo.release(CONTACT_ONE);
  DigiCombo.release(CONTACT_TWO);

  DigiCombo.delay(2000);
}
