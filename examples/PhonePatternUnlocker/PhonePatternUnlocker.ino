#include <DigiCombo.h>

int repeat = 5;
int phonePattern[4] = {0, 3, 6, 7};

void setup() {
  DigiCombo.begin();

  //Touch to awake the phone
  DigiCombo.tapSingle(5000, 5000);
  DigiCombo.tapSingle(5000, 5000);
  //
  
  DigiCombo.delay(2000);
  
  // Swipe up for going to draw pattern any 1 percent in 25ms  
  for (int i = 0; i < 4000; i += 100) {
    DigiCombo.moveFinger(5000, 7000 - i);   
  }
  
  DigiCombo.release();
  DigiCombo.delay(2000);
}

void loop() {
  if (repeat == 0) {
    DigiCombo.delay(1000);
    return;
  }
  
  // Place of point in lockscreen
  // y = 1: 4100, 2: 5300, 3: 6500
  // x = 1: 2500, 2: 5000, 3: 7500
  int selectedPointIndex[4] = {0, 0, 0, 0};

  for (int i = 0; i < 4; i++) {
    // Select unique point
    while (true) {      
      int pointIndex = repeat != 1 ? (random() % 9) : phonePattern[i];
      selectedPointIndex[i] = pointIndex;
      
      int count = 0;    
      for (int j = 0; j <= i; j++) {
        if (selectedPointIndex[j] == pointIndex) count++;
      }

      if (count == 1) break;
    }
    
    DigiCombo.moveFinger(2500 + (selectedPointIndex[i] % 3) * 2500, 4100 + (selectedPointIndex[i] / 3) * 1200);
  }

  DigiCombo.release();
  DigiCombo.delay(1000);

  repeat--;
}
