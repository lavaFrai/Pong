#pragma once
#include <U8g2lib.h>


class gameController {
public:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* u8g2;
    unsigned int score=0;

    gameController(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* _u8g2) { 
        u8g2 = _u8g2;
        u8g2->setFont(u8g2_font_helvR08_tr);
    }

    void gameOverEvent() {
        u8g2->drawStr((127 - u8g2->getStrWidth("Game Over!")) / 2, 40, "Game Over!");
        u8g2->sendBuffer();
        delay(3000);
    }

    void preparationScreen(int time=3) {
        for (; time > 0; time--) {
            u8g2->clearBuffer();
            u8g2->setFont(u8g2_font_helvR10_tr);
            u8g2->drawStr((127 - u8g2->getStrWidth("Get ready for game")) / 2, 20, "Get ready for game");
            u8g2->setFont(u8g2_font_helvR14_tr);
            u8g2->drawStr((127 - u8g2->getStrWidth(String(time).c_str())) / 2, 40, String(time).c_str());
            u8g2->setFont(u8g2_font_helvR08_tr);
            u8g2->drawStr((127 - u8g2->getStrWidth("Pong by. lava_frai")) / 2, 60, "Pong by. lava_frai");
            u8g2->sendBuffer();
            delay(1000);
        }
        u8g2->setFont(u8g2_font_helvR08_tr);
    }

    void drawScore() {
        String tempText = "Score: " + String(score);
        u8g2->drawStr((120 - u8g2->getStrWidth(tempText.c_str())), 14, tempText.c_str());
    }

    void drawFrame() {
        u8g2->drawPixel(0, 0);
        u8g2->drawPixel(1, 0);
        u8g2->drawPixel(0, 1);
        
        u8g2->drawPixel(0, 63);
        u8g2->drawPixel(1, 63);
        u8g2->drawPixel(1, 62);
        
        u8g2->drawPixel(126, 0);
        u8g2->drawPixel(127, 0);
        u8g2->drawPixel(127, 1);
        
        u8g2->drawPixel(126, 63);
        u8g2->drawPixel(127, 63);
        u8g2->drawPixel(127, 62);
    }

    void addScore() {
        score++;
    }
};