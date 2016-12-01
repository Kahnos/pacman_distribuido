/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: libny
 * 
 * Created on November 19, 2016, 6:01 PM
 */

#include "Character.h"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

using namespace character;

Character::Character() {
	al_init();
	al_init_image_addon();
}

Character::Character(string characterName) {
	al_init();
	al_init_image_addon();
	alive = true;
	eatable = false;
	nextDirection = 4; 
	loadSprites(characterName);
}

Character::~Character() {
}

ALLEGRO_BITMAP * Character::getSprite(int row, int col){
	return sprites[row][col];
}

void Character::setPositionX(unsigned short posX){
	positionX = posX;
}

void Character::setPositionY(unsigned short posY){
	positionY = posY;
}

void Character::setAlive(bool alive){
	this->alive = alive;
}

void Character::setEatable(bool eatable){
	this->eatable = eatable;
}

void Character::setDirection(Direction dir){
	for (unsigned char i = 0; i<4; i++){
		if (dir == i){
			direction[i] = true;
		}
		else
			direction[i] = false;
	}
}

void Character::setSpeed(float speed){
	this->speed = speed;
}

void Character::setNextDirection(unsigned char nextDirection){
	this->nextDirection = nextDirection;
}

string Character::getName(){
	string characterName;
	switch (name){
		case pacman:
			characterName = "pacman";
			break;
			
		case clyde:
			characterName = "clyde";
			break;
			
		case inky:
			characterName = "inky";
			break;
		
		case pinky:
			characterName = "pinky";
			break;
		
		case blinky:
			characterName = "blinky";
			break;
	}
	return characterName;
}

unsigned char Character::getActiveDirection(){
	for (unsigned char i = 0; i<4; i++){
		if (direction[i] == true){
			return i;
		}
	}
}

bool Character::getDirection(Direction dir){
	return direction[dir];
}

float Character::getSpeed(){
	return speed;
}

unsigned short Character::getPositionX(){
	return positionX;
}

unsigned short Character::getPositionY(){
	return positionY;
}

bool Character::getAlive(){
	return alive;
}

unsigned char Character::getNextDirection(){
	return nextDirection;
}

bool Character::getEatable(){
	return eatable;
}


void Character::loadSprites(string characterName){
	al_init();
	al_init_image_addon();
	if (characterName == "pacman"){
		this->name = pacman;
		speed = 6;
		positionX = 18;
		positionY = 90;
		
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
	else if (characterName == "clyde"){
		this->name = clyde;
		speed = 3;
		positionX = 252;
		positionY = 252;
		
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
	else if (characterName == "blinky"){
		this->name = blinky;
		speed = 2;
		positionX = 270;
		positionY = 270;
		
		sprites[0][0]= al_load_bitmap("resources/sprites/ghosts/blinkyUp1.png");
		sprites[1][0]= al_load_bitmap("resources/sprites/ghosts/blinkyUp2.png");
		sprites[0][1]= al_load_bitmap("resources/sprites/ghosts/blinkyDown1.png");
		sprites[1][1]= al_load_bitmap("resources/sprites/ghosts/blinkyDown2.png");
		sprites[0][2]= al_load_bitmap("resources/sprites/ghosts/blinkyLeft1.png");
		sprites[1][2]= al_load_bitmap("resources/sprites/ghosts/blinkyLeft2.png");
		sprites[0][3]= al_load_bitmap("resources/sprites/ghosts/blinkyRight1.png");
		sprites[1][3]= al_load_bitmap("resources/sprites/ghosts/blinkyRight2.png");
		
	}
	else if (characterName == "pinky"){
		this->name = pinky;
		speed = 8;
		
		sprites[0][0]= al_load_bitmap("resources/sprites/ghosts/pinkyUp1.png");
		sprites[1][0]= al_load_bitmap("resources/sprites/ghosts/pinkyUp2.png");
		sprites[0][1]= al_load_bitmap("resources/sprites/ghosts/pinkyDown1.png");
		sprites[1][1]= al_load_bitmap("resources/sprites/ghosts/pinkyDown2.png");
		sprites[0][2]= al_load_bitmap("resources/sprites/ghosts/pinkyLeft1.png");
		sprites[1][2]= al_load_bitmap("resources/sprites/ghosts/pinkyLeft2.png");
		sprites[0][3]= al_load_bitmap("resources/sprites/ghosts/pinkyRight1.png");
		sprites[1][3]= al_load_bitmap("resources/sprites/ghosts/pinkyRight2.png");
	}
	else if (characterName == "inky"){
		this->name = inky;
		speed = 7;
		
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