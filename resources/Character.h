/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: libny
 *
 * Created on November 19, 2016, 6:01 PM
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

using namespace std;

namespace character {
    class Character {
    public:
        enum Name {
            pacman,
            clyde,
            blinky,
            pinky,
            inky
        };

        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Character();
        Character(string name);
        virtual ~Character();
        ALLEGRO_BITMAP * getSprite(int row, int col);
        string getName();
        unsigned char getActiveDirection();
        bool getDirection(Direction dir);
        unsigned char getNextDirection();
        float getSpeed();
        unsigned short getPositionX();
        unsigned short getPositionY();
        bool getAlive();
        bool getEatable();
        void loadSprites(string name);
        void setPositionX(unsigned short posX);
        void setPositionY(unsigned short posY);
        void setAlive(bool alive);
        void setEatable(bool eatable);
        void setDirection(Direction dir);
        void setSpeed(float speed);
        void setNextDirection(unsigned char nextDirection);
        

    private:
        Name name;
        bool direction[4];
        float speed;
        unsigned short positionX;
        unsigned short positionY;
        bool alive;
        bool eatable;
        ALLEGRO_BITMAP *sprites[3][6];
        unsigned char nextDirection;
    };
}

#endif /* CHARACTER_H */

