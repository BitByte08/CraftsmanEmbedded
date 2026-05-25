#include <stdbool.h>

#define SW1 0
#define SW2 1
#define SW3 2

#define LED_R 3
#define LED_G 4
#define LED_B 5

#define FND_L 6
#define FND_R 7

#define FND_A 8
#define FND_B 9
#define FND_C 10
#define FND_D 11

bool fndShow = false;

bool ready1 = false;
bool ready2 = false;

uint8_t workState = 3;
uint8_t count = 0;

void input();
void led(uint8_t color);
void fnd();
void reset();

void work1();
void work2();
void work3();

void setup() {
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(FND_L, OUTPUT);
  pinMode(FND_R, OUTPUT);

  pinMode(FND_A, OUTPUT);
  pinMode(FND_B, OUTPUT);
  pinMode(FND_C, OUTPUT);
  pinMode(FND_D, OUTPUT);
}

void loop() {
  reset();
  input();
  work1();
  work2();
  fnd();
}

void work1() {
  static uint32_t currentMillis = millis();
  if(workState == 1 && !ready1) {
    uint32_t wCurrentMillis = millis();
    count = 88;
    fndShow = true;
    while((millis() - wCurrentMillis) < 2000){
      if((millis() - wCurrentMillis)/500 == 0) led('G');
      else if((millis() - wCurrentMillis)/500 == 1) led('R');
      else led(0);
      fnd();
    }
    count = 0;
    ready1 = true;
    workState = 0;
    currentMillis = millis();
  } else if(workState == 1 && ready1) {
    work3();
  } else if(ready1) {
    if(millis() - currentMillis > 500){
      count = (count + 1) % 100;
      digitalWrite(LED_B, !digitalRead(LED_B));
      currentMillis = millis();
    }
  }
}
void work2() {
  static uint32_t currentMillis = millis();
  if(workState == 2 && !ready2) {
    uint32_t wCurrentMillis = millis();
    count = 88;
    fndShow = true;
    while((millis() - wCurrentMillis) < 2000){
      if((millis() - wCurrentMillis)/500 == 0) led('B');
      else if((millis() - wCurrentMillis)/500 == 1) led('R');
      else led(0);
      fnd();
    }
    count = 99;
    ready2 = true;
    workState = 0;
    currentMillis = millis();
  } else if(workState == 2 && ready2) {
    work3();
  } else if(ready2) {
    if(millis() - currentMillis > 500){
      count = (count + 99) % 100;
      digitalWrite(LED_G, !digitalRead(LED_G));
      currentMillis = millis();
    }
  }
}
void work3(){
  uint32_t currentMillis = millis();
  while(millis() - currentMillis < 8000){
    if(((millis() - currentMillis) / 2000)%2) {
      fndShow = false;
      led(0);
    }else{
      fndShow = true;
      led('R');
    }
    fnd();
  }
  workState = 0;
}

void reset() {
  if(workState == 3){
    uint32_t currentMillis = millis();
    while(millis() - currentMillis < 4000) {
      if(((millis() - currentMillis) / 1000) % 2) {
        fndShow = false;
      }else{
        fndShow = true;
      }
      if((millis() - currentMillis) / 1000 == 0) {
        led('R');
      } else if ((millis() - currentMillis) / 1000 == 1) {
        led('G');
      } else if ((millis() - currentMillis) / 1000 == 2) {
        led('B');
      } else if ((millis() - currentMillis) / 1000 == 3) {
        led(0);
      }
      fnd();
    }
    count = 0;
    ready1 = false;
    ready2 = false;
    led('R');
    workState = 0;
  }
}

void fnd() {
  static bool pos = false;
  uint8_t num = 0;
  if(!fndShow){
    digitalWrite(FND_L, LOW);
    digitalWrite(FND_R, LOW);
  }else if(pos){
    num = count / 10;
    digitalWrite(FND_L, HIGH);
    digitalWrite(FND_R, LOW); 
  }else{
    num = count % 10;
    digitalWrite(FND_L, LOW);
    digitalWrite(FND_R, HIGH); 
  }
  digitalWrite(FND_A, num & 1);
  digitalWrite(FND_B, num & 2);
  digitalWrite(FND_C, num & 4);
  digitalWrite(FND_D, num & 8);
  pos = !pos;
}

void led(uint8_t color) {
  if(color == 'R') {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }else if(color == 'G'){
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  }else if(color == 'B'){
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
  }else{
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }
}

void input() {
  static bool currentSW1 = digitalRead(SW1);
  static bool currentSW2 = digitalRead(SW2);
  static bool currentSW3 = digitalRead(SW3);

  if(!currentSW1 && digitalRead(SW1)) workState = 1;
  if(!currentSW2 && digitalRead(SW2)) workState = 2;
  if(!currentSW3 && digitalRead(SW3)) workState = 3;

  currentSW1 = digitalRead(SW1);
  currentSW2 = digitalRead(SW2);
  currentSW3 = digitalRead(SW3);
}

