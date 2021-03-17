#include <Arduboy2.h>
#define POMODORO_LENGTH 1500000
Arduboy2 arduboy;
unsigned long start = 0;
unsigned long elapsed = 0;
unsigned long elapsed_last = 0;
unsigned long elapsed_delta = 0;
bool running = false;
bool onBreak = false;

void setup() {
  arduboy.begin();
  arduboy.clear();
  // put your setup code here, to run once:

}

void loop() {
  unsigned long curTime = millis();
  int hours = elapsed / 1000 / 60 / 60;
  int minutes = (elapsed - hours * 3600000) /1000/60;
  float seconds = (elapsed - (hours *3600000) - (minutes*60000))/1000.0;
  // press a to stop/start
  arduboy.pollButtons();

  if(arduboy.justPressed(A_BUTTON)){
    running = !running;
    start = curTime;
    if(onBreak){
      elapsed+=1;
      onBreak=false;
    }

  }
  if(arduboy.justPressed(B_BUTTON)){
    elapsed =0;
    hours=0;
    minutes=0;
    seconds=0.0;
    running=false;
  }
  if(running){
    elapsed += curTime - start;
    start = curTime;
  }
  
  
  arduboy.clear();
  arduboy.setCursor(0,0);
  arduboy.print(F("Elapsed: "));
  arduboy.print(hours);
  arduboy.print(F(":"));
  arduboy.print(minutes);
  arduboy.print(F(":"));
  arduboy.println(seconds,3);
  arduboy.print(F("Pomodoros: "));
  render_pomodoros(elapsed);
  arduboy.display();
  // put your main code here, to run repeatedly:
}

void render_pomodoros(unsigned long duration){
  int pomodoros = duration / POMODORO_LENGTH;
  for(int i = 0; i < pomodoros; i++){
    arduboy.print(F("*"));
  }
}
