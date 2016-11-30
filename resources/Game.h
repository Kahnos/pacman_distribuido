/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: libny
 *
 * Created on November 21, 2016, 8:59 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define COL 29 //Cantidad de columnas
#define ROW 32 //Cantidad de filas
#define SPRITESIZE 18 //Tamaño de los sprites

using namespace character;

namespace game {
    class Game {
    public:
        enum Status{
            not_started,
            running,
            win,
            lose,
            character_selection
        };
        
        enum ActivePower{
            none,
            inverse
        };
        
        Game();
        virtual ~Game();
        unsigned char getLives();
        unsigned short getScore();
        unsigned char getPowerbar();
        char getMazeCell(int row, int col);
        string getStatus();
        string getActivePower();
        void setLives(unsigned char lives);
        void setScore(unsigned short score);
        void setPowerbar(unsigned char powerbar);
        void setStatus(string status);
        void setActivePower(string activePower);
        void setMazeCell(int row, int col, char value);
        void setFruit(int row, int col, char f);
        void drawMaze();
        void drawCharacter(unsigned short posX,unsigned short posY, ALLEGRO_BITMAP *sprite);
        bool verifyPosition(unsigned char dir, unsigned short posX, unsigned short posY);
        void verifyMaze(unsigned char dir, unsigned short posX, unsigned short posY);
        void eatableGhosts();
        
        
    private:
        ALLEGRO_BITMAP *block;
        ALLEGRO_BITMAP *cherry;
        ALLEGRO_BITMAP *orange;
        ALLEGRO_BITMAP *apple;
        ALLEGRO_BITMAP *strawberry;
        unsigned char lives;
        unsigned short score;
        unsigned char powerbar;
        Status status;
        ActivePower activePower;
        Character characters[5];
        char maze[ROW][COL]= {
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"X............XX............X",
	"X.XXXX.XXXXX.XX.XXXXX.XXXX.X",
	"XpXXXX.XXXXX.XX.XXXXX.XXXXpX",
	"X.XXXX.XXXXX.XX.XXXXX.XXXX.X",
	"X..........................X",
	"X.XXXX.XX.XXXXXXXX.XX.XXXX.X",
	"X.XXXX.XX.XXXXXXXX.XX.XXXX.X",
	"X......XX....XX....XX......X",
	"XXXXXX.XXXXX XX XXXXX.XXXXXX",
	"     X.XXXXX XX XXXXX.X     ",
	"     X.XX          XX.X     ",
	"     X.XX XXX__XXX XX.X     ",
	"XXXXXX.XX X      X XX.XXXXXX",
	"      .   X      X   .      ",
	"XXXXXX.XX X      X XX.XXXXXX",
	"     X.XX XXXXXXXX XX.X     ",
	"     X.XX          XX.X     ",
	"     X.XX XXXXXXXX XX.X     ",
	"XXXXXX.XX XXXXXXXX XX.XXXXXX",
	"X............XX............X",
	"X.XXXX.XXXXX.XX.XXXXX.XXXX.X",
	"X.XXXX.XXXXX.XX.XXXXX.XXXX.X",
	"Xp..XX................XX..pX",
	"XXX.XX.XX XXXXXXXX.XX.XX.XXX",
	"XXX.XX.XX XXXXXXXX.XX.XX.XXX",
	"X......XX....XX....XX......X",
	"X.XXXXXXXXXX.XX.XXXXXXXXXX.X",
	"X.XXXXXXXXXX.XX.XXXXXXXXXX.X",
	"X..........................X",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

    };
}

#endif /* GAME_H */

