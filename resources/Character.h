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
        string getName();
        unsigned char getActiveDirection();
        bool getDirection(Direction dir);
        unsigned char getNextDirection();
        float getSpeed();
        unsigned short getPositionX();
        unsigned short getPositionY();
        bool getAlive();
        bool getEatable();
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
        unsigned char nextDirection;
    };
    
    struct Sprites{
        ALLEGRO_BITMAP *sprites[3][6];
        
        void loadSprites(Character::Name characterName) {
            al_init();
            al_init_image_addon();
            if (characterName == Character::pacman){
                
                    sprites[0][0]= al_load_bitmap("resources/sprites/pacman/pacmanUp1.png");
                    sprites[0][1]= al_load_bitmap("resources/sprites/pacman/pacmanDown1.png");
                    sprites[1][0]= al_load_bitmap("resources/sprites/pacman/pacmanUp2.png");
                    sprites[1][1]= al_load_bitmap("resources/sprites/pacman/pacmanDown2.png");
                    sprites[0][2]= al_load_bitmap("resources/sprites/pacman/pacmanLeft1.png");
                    sprites[1][2]= al_load_bitmap("resources/sprites/pacman/pacmanLeft2.png");
                    sprites[0][3]= al_load_bitmap("resources/sprites/pacman/pacmanRight1.png");
                    sprites[1][3]= al_load_bitmap("resources/sprites/pacman/pacmanRight2.png");
                    sprites[2][0]= al_load_bitmap("resources/sprites/pacman/pacman.png");
                    sprites[2][1]= al_load_bitmap("resources/sprites/pacman/pacman.png");
                    sprites[2][2]= al_load_bitmap("resources/sprites/pacman/pacman.png");
                    sprites[2][3]= al_load_bitmap("resources/sprites/pacman/pacman.png");
                    
            }
            else if (characterName == Character::clyde){

                    sprites[0][0]= al_load_bitmap("resources/sprites/ghosts/clydeUp1.png");
                    sprites[1][0]= al_load_bitmap("resources/sprites/ghosts/clydeUp2.png");
                    sprites[0][1]= al_load_bitmap("resources/sprites/ghosts/clydeDown1.png");
                    sprites[1][1]= al_load_bitmap("resources/sprites/ghosts/clydeDown2.png");
                    sprites[0][2]= al_load_bitmap("resources/sprites/ghosts/clydeLeft1.png");
                    sprites[1][2]= al_load_bitmap("resources/sprites/ghosts/clydeLeft2.png");
                    sprites[0][3]= al_load_bitmap("resources/sprites/ghosts/clydeRight1.png");
                    sprites[1][3]= al_load_bitmap("resources/sprites/ghosts/clydeRight2.png");
                    sprites[0][4]= al_load_bitmap("resources/sprites/death/eatableGhost1.png");
                    sprites[1][4]= al_load_bitmap("resources/sprites/death/eatableGhost2.png");
                    sprites[0][5]= al_load_bitmap("resources/sprites/death/ghost1.png");
                    sprites[1][5]= al_load_bitmap("resources/sprites/death/ghost2.png");

            }
            else if (characterName == Character::blinky){

                    sprites[0][0]= al_load_bitmap("resources/sprites/ghosts/blinkyUp1.png");
                    sprites[1][0]= al_load_bitmap("resources/sprites/ghosts/blinkyUp2.png");
                    sprites[0][1]= al_load_bitmap("resources/sprites/ghosts/blinkyDown1.png");
                    sprites[1][1]= al_load_bitmap("resources/sprites/ghosts/blinkyDown2.png");
                    sprites[0][2]= al_load_bitmap("resources/sprites/ghosts/blinkyLeft1.png");
                    sprites[1][2]= al_load_bitmap("resources/sprites/ghosts/blinkyLeft2.png");
                    sprites[0][3]= al_load_bitmap("resources/sprites/ghosts/blinkyRight1.png");
                    sprites[1][3]= al_load_bitmap("resources/sprites/ghosts/blinkyRight2.png");

            }
            else if (characterName == Character::pinky){

                    sprites[0][0]= al_load_bitmap("resources/sprites/ghosts/pinkyUp1.png");
                    sprites[1][0]= al_load_bitmap("resources/sprites/ghosts/pinkyUp2.png");
                    sprites[0][1]= al_load_bitmap("resources/sprites/ghosts/pinkyDown1.png");
                    sprites[1][1]= al_load_bitmap("resources/sprites/ghosts/pinkyDown2.png");
                    sprites[0][2]= al_load_bitmap("resources/sprites/ghosts/pinkyLeft1.png");
                    sprites[1][2]= al_load_bitmap("resources/sprites/ghosts/pinkyLeft2.png");
                    sprites[0][3]= al_load_bitmap("resources/sprites/ghosts/pinkyRight1.png");
                    sprites[1][3]= al_load_bitmap("resources/sprites/ghosts/pinkyRight2.png");
            }
            else if (characterName == Character::inky){

                    sprites[0][0]= al_load_bitmap("resources/sprites/ghosts/inkyUp1.png");
                    sprites[1][0]= al_load_bitmap("resources/sprites/ghosts/inkyUp2.png");
                    sprites[0][1]= al_load_bitmap("resources/sprites/ghosts/inkyDown1.png");
                    sprites[1][1]= al_load_bitmap("resources/sprites/ghosts/inkyDown2.png");
                    sprites[0][2]= al_load_bitmap("resources/sprites/ghosts/inkyLeft1.png");
                    sprites[1][2]= al_load_bitmap("resources/sprites/ghosts/inkyLeft2.png");
                    sprites[0][3]= al_load_bitmap("resources/sprites/ghosts/inkyRight1.png");
                    sprites[1][3]= al_load_bitmap("resources/sprites/ghosts/inkyRight2.png");
                    
            }
        }
        
        ALLEGRO_BITMAP * getSprite(int row, int col){
            return sprites[row][col];
        }
    };
}

#endif /* CHARACTER_H */

