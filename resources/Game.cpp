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

using namespace game;

Game::Game(){
	al_init();
	al_init_image_addon();
	
	block = al_load_bitmap("resources/sprites/roca.bmp");
	cherry = al_load_bitmap("resources/sprites/fruits/cherry.png");
	apple = al_load_bitmap("resources/sprites/fruits/apple.png");
	orange = al_load_bitmap("resources/sprites/fruits/orange.png");
	strawberry = al_load_bitmap("resources/sprites/fruits/strawberry.png");
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

void Game::drawCharacter(unsigned short posX, unsigned short posY, ALLEGRO_BITMAP *sprite){
	al_draw_scaled_bitmap(sprite, 0, 0, 24, 24, posX, posY, SPRITESIZE, SPRITESIZE, 0);
}

void Game::setFruit(int row, int col, char f){
	if ((maze[row][col] != 'X') && (maze[row][col] != '.')){
		maze[row][col] = f;
	}
}

bool Game::verifyPosition(unsigned char dir, unsigned short posX, unsigned short posY/*, unsigned char nextDirection*/){
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