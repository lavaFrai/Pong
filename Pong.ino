#include <U8g2lib.h>

#include <Wire.h>
#include "racket.h"
#include "ball.h"
#include "gameController.h"


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
int i = 0;
int direction = 1;
racket leftRacket;
racket rightRacket;
ball mainBall;
gameController game = gameController(&u8g2);

const int UP_BUTTON_PIN = 4;    // Attention! Pins are pulled up
const int DOWN_BUTTON_PIN = 5;

const int GAME_SPEED = 1; // from 1 up to infinity
                          // more is faster
const bool SHOW_SCREEN_FRAME = true;  // show or hide frame around the screen
const bool SHOW_SCORE = true;  // show number of successfully hit balls


void setup() {
  u8g2.begin();
  rightRacket.x = 127;
  rightRacket.y = 31 - rightRacket.height / 2;

  leftRacket.y = 31 - rightRacket.height / 2;

  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);

  game.preparationScreen();
}

void loop() {
  // Ui contols handling
  if (!digitalRead(UP_BUTTON_PIN)) rightRacket.stepUp(3);
  if (!digitalRead(DOWN_BUTTON_PIN)) rightRacket.stepDown(3);

  // Physical rendering
  for (int i = 0; i < GAME_SPEED; i++)
  { // one physical engine cycle
    mainBall.tick(game);
    mainBall.checkCollisionRight(rightRacket, game);
    mainBall.checkCollisionLeft(leftRacket, game);
  }

  // Autopilot for lefr racket
  leftRacket.y = constrain((mainBall.position.y - leftRacket.height / 2), 0, 63 - leftRacket.height);
  // rightRacket.y = constrain((mainBall.position.y - leftRacket.height / 2), 0, 63 - leftRacket.height);

  // Graphic rendering
  u8g2.clearBuffer();

  mainBall.draw(u8g2);

  leftRacket.draw(u8g2);
  rightRacket.draw(u8g2);

  if (SHOW_SCORE) game.drawScore();
  if (SHOW_SCREEN_FRAME) game.drawFrame();

  u8g2.sendBuffer();
}
