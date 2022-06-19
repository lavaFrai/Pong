#pragma once
#include <U8g2lib.h>


class racket {
public:
  int x=0, y=0;
  const static int height=20;

  racket() {
    
  }

  void stepUp(int speed=1) {
    if (y > 0) y -= speed;
  }

  void stepDown(int speed=1) {
    if (y + height < 63) y += speed;
  }

  void draw(U8G2_SSD1306_128X64_NONAME_F_HW_I2C& display) {
    display.drawLine(x, y, x, y+height);
  }
};