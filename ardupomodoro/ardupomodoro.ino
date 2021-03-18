#include <Arduboy2.h>
#define POMODORO_LENGTH 1500000
Arduboy2 arduboy;
BeepPin1 beep;
unsigned long start = 0;
unsigned long elapsed = 0;
unsigned long breakTime = 0;
unsigned long last_mod = 0;
bool running = false;
bool onBreak = false;

void setup() {
  arduboy.begin();
  beep.begin();
  arduboy.clear();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long curTime = millis();
  unsigned long mod = elapsed % POMODORO_LENGTH;
  beep.timer();
  // press a to stop/start
  arduboy.pollButtons();

  if (arduboy.justPressed(A_BUTTON)) {
    running = !running;
    start = curTime;
    if (onBreak) {
      elapsed += 1;
      onBreak = false;
    }
  }
  if (arduboy.justPressed(B_BUTTON)) {
    elapsed = 0;
    running = false;
  }
  if (mod < last_mod) {
    beep.tone(beep.freq(880), 30);
    running = false;
    last_mod = mod;
  }
  if (running) {
    elapsed += curTime - start;
    start = curTime;
    last_mod = mod;
  }

  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print(F("Elapsed: "));
  render_time(elapsed);
  arduboy.print(F("Pomodoros: "));
  render_pomodoros(elapsed);
  arduboy.display();
}

void render_time(unsigned long duration) {
  int hours = duration / 1000 / 60 / 60;
  int minutes = (duration - hours * 3600000) / 1000 / 60;
  float seconds = (duration - (hours * 3600000) - (minutes * 60000)) / 1000.0;
  arduboy.print(hours);
  arduboy.print(F(":"));
  arduboy.print(minutes);
  arduboy.print(F(":"));
  arduboy.println(seconds, 3);
}

void render_pomodoros(unsigned long duration) {
  int pomodoros = duration / POMODORO_LENGTH;
  for (int i = 0; i < pomodoros; i++) {
    arduboy.print(F("*"));
    if (arduboy.getCursorX() >= 122) {
      arduboy.println();
    }
  }
}
