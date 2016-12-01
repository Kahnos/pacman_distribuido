/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: libny
 * 
 * Created on November 21, 2016, 8:59 PM
 */

#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define COL 29 //Cantidad de columnas
#define ROW 32 //Cantidad de filas
#define SPRITESIZE 18 //Tamaño de los sprites
#define PACMOV 3 //Movimiento de pacman
#define PACDOTSPOINTS 10 //Puntos por comer un pacdot
#define PPPOINTS 15 //Puntos por comer una powerpellet

using namespace game;

Game::Game(){
	
	al_init();
	al_init_image_addon();
	
	block = al_load_bitmap("resources/sprites/roca.bmp");
	cherry = al_load_bitmap("resources/sprites/fruits/cherry.png");
	apple = al_load_bitmap("resources/sprites/fruits/apple.png");
	orange = al_load_bitmap("resources/sprites/fruits/orange.png");
	strawberry = al_load_bitmap("resources/sprites/fruits/strawberry.png");
	
	score = 0;
	lives = 3;
	powerbar = 0;
	
	characters[Character::pacman] = Character("pacman");
	characters[Character::clyde] = Character("clyde");
	characters[Character::blinky] = Character("blinky");
	characters[Character::pinky] = Character("pinky");
	characters[Character::inky] = Character("inky");
	
}

Game::~Game() {
}

char Game::getMazeCell(int row, int col){
	return maze[row][col];
}

unsigned char Game::getLives(){
	return lives;
}

string Game::getActivePower(){
	string activePower_str;
	
	switch(activePower){
		case none:
			activePower_str = "none";
			break;
			
		case inverse:
			activePower_str = "inverse";
			break;
	}
	return activePower_str;
}

unsigned char Game::getPowerbar(){
	return powerbar;
}

unsigned short Game::getScore(){
	return score;
}

string Game::getStatus(){
	string status_str;
	
	switch(status){
		case not_started:
			status_str = "not_started";
			break;
			
		case running:
			status_str = "running";
			break;
			
		case win:
			status_str = "win";
			break;
			
		case lose:
			status_str = "lose";
			break;
			
		case character_selection:
			status_str = "character_selection";
			break;
	}	
	return status_str;
}

void Game::setLives(unsigned char lives){
	this->lives = lives;
}

void Game::setActivePower(string activePower){
	//this->activePower = activePower;
}

void Game::setPowerbar(unsigned char powerbar){
	this->powerbar = powerbar;
}

void Game::setScore(unsigned short score){
	this->score = score;
}

void Game::setStatus(string status){
	
}

void Game::setMazeCell(int row, int col, char value){
	maze[row][col] = value;
}

void Game::drawMaze(){
	
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			if (maze[i][j] == 'X'){
				al_draw_scaled_bitmap(block, 0, 0, 24, 24,
					(j*SPRITESIZE), (i*SPRITESIZE), SPRITESIZE, SPRITESIZE, 0);
			}
			if (maze[i][j] == '.'){
				al_draw_filled_circle((j*SPRITESIZE)+SPRITESIZE/2, (i*SPRITESIZE)+SPRITESIZE/2, 1.5, al_map_rgb(255,255,255));
			}
			if (maze[i][j] == 'p'){
				al_draw_filled_circle((j*SPRITESIZE)+SPRITESIZE/2, (i*SPRITESIZE)+SPRITESIZE/2, 4, al_map_rgb(255,255,255));
			}
			if (maze[i][j] == 's'){
				al_draw_scaled_bitmap(strawberry, 0, 0, 24, 24,
					(j*SPRITESIZE), (i*SPRITESIZE), SPRITESIZE, SPRITESIZE, 0);
			}
			if (maze[i][j] == 'o'){
				al_draw_scaled_bitmap(orange, 0, 0, 24, 24,
					(j*SPRITESIZE), (i*SPRITESIZE), SPRITESIZE, SPRITESIZE, 0);
			}
		}
	}
	
}

void Game::drawCharacter(Character::Name name, int curFrame){
	al_draw_scaled_bitmap(characters[name].getSprite(curFrame, characters[name].getActiveDirection()),
		0, 0, 24, 24, characters[name].getPositionX(), characters[name].getPositionY(), SPRITESIZE, SPRITESIZE, 0);
}

void Game::setFruit(int row, int col, char f){
	if ((maze[row][col] != 'X') && (maze[row][col] != '.')){
		maze[row][col] = f;
	}
}

bool Game::verifyPosition(unsigned char dir, unsigned short posX, unsigned short posY){
	float base;
	unsigned short newX;
	unsigned short newY;
	
	switch(dir){
		
		//UP
		case 0: 
			if( (posY % SPRITESIZE) == 0 ){
				base = posY/SPRITESIZE;
			}
			else{
				base = (posY / SPRITESIZE) +1;
				
			}
			newX = posX/SPRITESIZE;
			newY = (short)base -1;
			break;
		
		//DOWN
		case 1:	

			base = posY/SPRITESIZE;
			newX = posX/SPRITESIZE;
			newY = (short)base +1;
			break;
		
		//LEFT	
		case 2:	
			if( (posX % SPRITESIZE) == 0 ){
				base = posX/SPRITESIZE;
			}
			else{
				base = (posX / SPRITESIZE) +1;
				
			}
			newY = posY/SPRITESIZE;
			newX = (short)base -1;
			break;
			
		//RIGHT	
		case 3:	
			base = posX/SPRITESIZE;
			newY = posY/SPRITESIZE;
			newX = (short)base +1;
			break;
	}

	if (maze[newY][newX] != 'X')
		return true;
	
	return false;
}

void Game::eatableGhosts(bool eatable){
	characters[Character::clyde].setEatable(eatable);
	characters[Character::blinky].setEatable(eatable);
	characters[Character::pinky].setEatable(eatable);
	characters[Character::inky].setEatable(eatable);
}

void Game::verifyMaze(){
	float base;
	unsigned short col;
	unsigned short row;
	
	switch(characters[Character::pacman].getActiveDirection()){
		
		//UP
		case 0: 
			if( (characters[Character::pacman].getPositionY() % SPRITESIZE) == 0 ){
				base = characters[Character::pacman].getPositionY()/SPRITESIZE;
			}
			else{
				base = (characters[Character::pacman].getPositionY() / SPRITESIZE) +1;
				
			}
			col = characters[Character::pacman].getPositionX()/SPRITESIZE;
			row = (short)base;
			break;
		
		//DOWN
		case 1:	

			base = characters[Character::pacman].getPositionY()/SPRITESIZE;
			col = characters[Character::pacman].getPositionX()/SPRITESIZE;
			row = (short)base;
			break;
		
		//LEFT	
		case 2:	
			if( (characters[Character::pacman].getPositionX() % SPRITESIZE) == 0 ){
				base = characters[Character::pacman].getPositionX()/SPRITESIZE;
			}
			else{
				base = (characters[Character::pacman].getPositionX() / SPRITESIZE);
				
			}
			row = characters[Character::pacman].getPositionY()/SPRITESIZE;
			col = (short)base;
			break;
			
		//RIGHT	
		case 3:	
			base = characters[Character::pacman].getPositionX()/SPRITESIZE;
			row = characters[Character::pacman].getPositionY()/SPRITESIZE;
			col = (short)base;
			break;
	}

	switch (maze[row][col]){
		case 'p':
			maze[row][col] = ' ';
			score = score + PPPOINTS;
			eatableGhosts(true);
			break;
		
		case '.':
			maze[row][col] = ' ';
			score = score + PACDOTSPOINTS;
			break;
	}
	
}

void Game::move(Character::Name name){
	if (characters[name].getNextDirection() != characters[name].getActiveDirection() ){
				switch (characters[name].getNextDirection()){
					case Character::UP:
						cout<<"nextDir up"<<endl;
						if ( (characters[name].getPositionX() % SPRITESIZE) == 0){
							if(verifyPosition( characters[name].getNextDirection(), characters[name].getPositionX(), characters[name].getPositionY() ) ){
								characters[name].setPositionY(characters[name].getPositionY() - characters[name].getSpeed());
								characters[name].setDirection(Character::UP);
								characters[name].setNextDirection(4);
							}
						}
						break;
				
					case Character::DOWN:
						if ( (characters[name].getPositionX() % SPRITESIZE) == 0){
							if(verifyPosition( characters[name].getNextDirection(), characters[name].getPositionX(), characters[name].getPositionY() ) ){
								characters[name].setPositionY(characters[name].getPositionY() + characters[name].getSpeed());
								characters[name].setDirection(Character::DOWN);
								characters[name].setNextDirection(4);
							}
						}
						break;
					
					case Character::LEFT:
						
						if ( (characters[name].getPositionY() % SPRITESIZE) == 0){
							if(verifyPosition( characters[name].getNextDirection(), characters[name].getPositionX(), characters[name].getPositionY() ) ){
								characters[name].setPositionX(characters[name].getPositionX() - characters[name].getSpeed());
								characters[name].setDirection(Character::LEFT);
								characters[name].setNextDirection(4);
							}
						}
						break;
					
					case Character::RIGHT:
						if ( (characters[name].getPositionY() % SPRITESIZE) == 0){
							if(verifyPosition( characters[name].getNextDirection(), characters[name].getPositionX(), characters[name].getPositionY() ) ){
								characters[name].setPositionX(characters[name].getPositionX() + characters[name].getSpeed());
								characters[name].setDirection(Character::RIGHT);
								characters[name].setNextDirection(4);
							}
						}
						break;
				}
			}
			
			if(characters[name].getDirection(Character::UP)) {
				
				
				if ( (characters[name].getPositionX() % SPRITESIZE) == 0){
					if(verifyPosition( Character::UP, characters[name].getPositionX(), characters[name].getPositionY() ) ){
						characters[name].setPositionY(characters[name].getPositionY() - characters[name].getSpeed());
					}
				}
				
			}
 
			if(characters[name].getDirection(Character::DOWN)) {
				
				if ( (characters[name].getPositionX() % SPRITESIZE) == 0){
					if(verifyPosition(Character::DOWN, characters[name].getPositionX(), characters[name].getPositionY())){
						characters[name].setPositionY(characters[name].getPositionY() + characters[name].getSpeed());
					}
				}
				
			}

			 if(characters[name].getDirection(Character::LEFT)) {
				
				if ( (characters[name].getPositionY() == 252) && (characters[name].getPositionX() <= 0 ) ){
					characters[name].setPositionX(486);
				}
				else if ( (characters[name].getPositionY() % SPRITESIZE) == 0){
					if(verifyPosition(Character::LEFT, characters[name].getPositionX(), characters[name].getPositionY())){
						characters[name].setPositionX(characters[name].getPositionX() - characters[name].getSpeed());	
					}
				}
			}

			if(characters[name].getDirection(Character::RIGHT)) {
				
				if ( (characters[name].getPositionY() == 252) && (characters[name].getPositionX() >= 486 ) ){
					characters[name].setPositionX(0);
				}
				if ( (characters[name].getPositionY() % SPRITESIZE) == 0){
					if (verifyPosition(Character::RIGHT, characters[name].getPositionX(), characters[name].getPositionY())){
						characters[name].setPositionX(characters[name].getPositionX() + characters[name].getSpeed());
					}
				}
				
			}
	
}

void Game::setCharacterDirection(Character::Name name, Character::Direction dir){
	switch(dir){
		case Character::UP:
			if ( !(characters[name].getDirection(Character::LEFT)) && !(characters[name].getDirection(Character::RIGHT)) ){
				characters[name].setDirection(Character::UP);
			}
			characters[name].setNextDirection(Character::UP);
			break;
		
		case Character::DOWN:
			if ( !(characters[name].getDirection(Character::LEFT)) && !(characters[name].getDirection(Character::RIGHT)) ){
				characters[name].setDirection(Character::DOWN);
			}
			characters[name].setNextDirection(Character::DOWN);
			break;
			
		case Character::LEFT:
			if ( !(characters[name].getDirection(Character::UP)) && !(characters[name].getDirection(Character::DOWN)) ){
				characters[name].setDirection(Character::LEFT);
			}
			characters[name].setNextDirection(Character::LEFT);
			break;
			
		case Character::RIGHT:
			if ( !(characters[name].getDirection(Character::UP)) && !(characters[name].getDirection(Character::DOWN)) ){
				characters[name].setDirection(Character::RIGHT);
			}
			characters[name].setNextDirection(Character::RIGHT);
			break;
	}
}

