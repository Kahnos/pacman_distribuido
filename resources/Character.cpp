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

/**
 * Constructor de la clase Character
 * @param characterName
 */
Character::Character(string characterName) {
	al_init();
	al_init_image_addon();
	alive = true;
	eatable = false;
	nextDirection = 4; 
	setDirection(Character::DOWN);
	
	if (characterName == "pacman"){
		this->name = pacman;
		speed = 6;
		positionX = 18;
		positionY = 90;
		
	}
	else if (characterName == "clyde"){
		this->name = clyde;
		speed = 3;
		positionX = 252;
		positionY = 252;
	}
	else if (characterName == "blinky"){
		this->name = blinky;
		speed = 2;
		positionX = 270;
		positionY = 270;
	}
	else if (characterName == "pinky"){
		this->name = pinky;
		speed = 1.5;
		positionX = 270;
		positionY = 270;
	}
	else if (characterName == "inky"){
		this->name = inky;
		speed = 1;
		positionX = 270;
		positionY = 270;
	}
}

Character::~Character() {
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