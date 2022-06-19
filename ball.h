#pragma once
#include <U8g2lib.h>
#include "racket.h"
#include "vector2.h"
#include "position2.h"
#include "gameController.h"


class ball {
public:
  const static int width=2;
  const static int height=2;
  Vector2 speed = Vector2(-1.2, 1);
  Position2 position = Position2(63, 31);

  ball() {
    
  }

  void draw(U8G2_SSD1306_128X64_NONAME_F_HW_I2C& display) {
    display.drawBox(position.x, position.y, width, height);
  }

  void tick(gameController& game) {
    position.move(speed);
    if (position.y <= 0 && speed.y < 0) speed.reflectV();
    if (position.y + height >= 63 && speed.y > 0) speed.reflectV();

    if (position.x <= 0 && speed.x < 0) { 
        game.gameOverEvent();
        while (1) {} // game over
    }
    if (position.x + width >= 129 && speed.x > 0) { 
        game.gameOverEvent();
        while (1) {} // game over
    }
  }

  void checkCollisionRight(const racket& collider, gameController& game) {
    if (position.x + width >= 127 && speed.x > 0)
        if (position.y + height - 1 >= collider.y && position.y <= collider.y + collider.height) {
            speed.reflectH();
            game.addScore();
        }
  }

  void checkCollisionLeft(const racket& collider, gameController& game) {
    if (position.x <= collider.x + 1 && speed.x < 0)
        if (position.y + height - 1 >= collider.y && position.y <= collider.y + collider.height)
            speed.reflectH();
  }
};