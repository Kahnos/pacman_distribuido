/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kahnos
 *
 * Created on November 13, 2016, 5:54 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "resources/Character.h"
#include "resources/Game.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define COL 29 //Cantidad de columnas
#define ROW 32 //Cantidad de filas
#define SPRITESIZE 18 //Tamaño de los sprites

using namespace std;
using namespace character;
using namespace game;

ALLEGRO_BITMAP *screen;
const float FPS = 30;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
 
int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
   
	//Animation
	const int maxFrame = 3;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 1;
	unsigned char dir = 0;
	unsigned char mazeCell = 0;
   
	Character pacman = Character("pacman");
   
	Game game = Game();
   
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
			return -1;
	}
 
	timer = al_create_timer(1.0 / FPS);
	
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	
	//Inicialización de la biblioteca para imágenes
	al_init_image_addon();
 
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
   }
 
	al_set_target_bitmap(al_get_backbuffer(display));
 
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	
	ALLEGRO_FONT *font = al_load_ttf_font("resources/8bitOperatorPlus8-Bold.ttf",20,0 );
 
   if (!font){
      fprintf(stderr, "Could not load '8bitOperatorPlus8-Bold.ttf'.\n");
      return -1;
   }
 
	
 
	al_register_event_source(event_queue, al_get_display_event_source(display));
 
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
	al_register_event_source(event_queue, al_get_keyboard_event_source());
 
	al_start_timer(timer);
 
	while(!doexit){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
 
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			
			if (pacman.getNextDirection() != dir){
				switch (pacman.getNextDirection()){
					case KEY_UP:
						if ( (pacman.getPositionX() % SPRITESIZE) == 0){
							if(game.verifyPosition( pacman.getNextDirection(), pacman.getPositionX(), pacman.getPositionY() ) ){
								pacman.setPositionY(pacman.getPositionY() - pacman.getSpeed());
								key[KEY_UP] = true;
								key[KEY_DOWN] = false;
								key[KEY_LEFT] = false;
								key[KEY_RIGHT] = false;
								pacman.setNextDirection(4);
							}
						}
						break;
					
					case KEY_DOWN:
						if ( (pacman.getPositionX() % SPRITESIZE) == 0){
							if(game.verifyPosition( pacman.getNextDirection(), pacman.getPositionX(), pacman.getPositionY() ) ){
								pacman.setPositionY(pacman.getPositionY() + pacman.getSpeed());
								key[KEY_UP] = false;
								key[KEY_DOWN] = true;
								key[KEY_LEFT] = false;
								key[KEY_RIGHT] = false;
								pacman.setNextDirection(4);
							}
						}
						break;
					
					case KEY_LEFT:
						
						if ( (pacman.getPositionY() % SPRITESIZE) == 0){
							if(game.verifyPosition( pacman.getNextDirection(), pacman.getPositionX(), pacman.getPositionY() ) ){
								pacman.setPositionX(pacman.getPositionX() - pacman.getSpeed());
								key[KEY_UP] = false;
								key[KEY_DOWN] = false;
								key[KEY_LEFT] = true;
								key[KEY_RIGHT] = false;
								pacman.setNextDirection(4);
							}
						}
						break;
					
					case KEY_RIGHT:
						if ( (pacman.getPositionY() % SPRITESIZE) == 0){
							if(game.verifyPosition( pacman.getNextDirection(), pacman.getPositionX(), pacman.getPositionY() ) ){
								pacman.setPositionX(pacman.getPositionX() + pacman.getSpeed());
								key[KEY_UP] = false;
								key[KEY_DOWN] = false;
								key[KEY_LEFT] = false;
								key[KEY_RIGHT] = true;
								pacman.setNextDirection(4);
							}
						}
						break;
				}
			}
			
			if(key[KEY_UP]) {
				dir = KEY_UP;
				
				if ( (pacman.getPositionX() % SPRITESIZE) == 0){
					if(game.verifyPosition( dir, pacman.getPositionX(), pacman.getPositionY() ) ){
						pacman.setPositionY(pacman.getPositionY() - pacman.getSpeed());
					}
				}
				
			}
 
			if(key[KEY_DOWN]) {
				dir = KEY_DOWN;
				
				if ( (pacman.getPositionX() % SPRITESIZE) == 0){
					if(game.verifyPosition(dir, pacman.getPositionX(), pacman.getPositionY())){
						pacman.setPositionY(pacman.getPositionY() + pacman.getSpeed());
					}
				}
				
			}

			 if(key[KEY_LEFT]) {
				dir = KEY_LEFT;
				
				if ( (pacman.getPositionY() == 252) && (pacman.getPositionX() <= 0 ) ){
					pacman.setPositionX(486);
				}
				else if ( (pacman.getPositionY() % SPRITESIZE) == 0){
					if(game.verifyPosition(dir, pacman.getPositionX(), pacman.getPositionY())){
						pacman.setPositionX(pacman.getPositionX() - pacman.getSpeed());	
					}
				}
			}

			if(key[KEY_RIGHT]) {
				dir = KEY_RIGHT;
				
				if ( (pacman.getPositionY() == 252) && (pacman.getPositionX() >= 486 ) ){
					pacman.setPositionX(0);
				}
				if ( (pacman.getPositionY() % SPRITESIZE) == 0){
					if (game.verifyPosition(dir, pacman.getPositionX(), pacman.getPositionY())){
						pacman.setPositionX(pacman.getPositionX() + pacman.getSpeed());
					}
				}
				
			}
			
			if(++frameCount >= frameDelay)
			{
				if(++curFrame >= maxFrame)
					curFrame = 0;

				frameCount = 0;
			}
			
			game.verifyMaze(dir, pacman.getPositionX(), pacman.getPositionY());
 
			redraw = true;
		}
		
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					if ( !(key[KEY_LEFT]) && !(key[KEY_RIGHT]) ){
						key[KEY_UP] = true;
						key[KEY_DOWN] = false;
						key[KEY_LEFT] = false;
						key[KEY_RIGHT] = false;
					}
					pacman.setNextDirection(KEY_UP);
					break;

				case ALLEGRO_KEY_DOWN:
					if ( !(key[KEY_LEFT]) && !(key[KEY_RIGHT]) ){
						key[KEY_DOWN] = true;
						key[KEY_UP] = false;
						key[KEY_LEFT] = false;
						key[KEY_RIGHT] = false;
					}
					pacman.setNextDirection(KEY_DOWN);
					break;

				case ALLEGRO_KEY_LEFT: 
					if ( !(key[KEY_UP]) && !(key[KEY_DOWN]) ){
						key[KEY_LEFT] = true;
						key[KEY_UP] = false;
						key[KEY_DOWN] = false;
						key[KEY_RIGHT] = false;
					}
					pacman.setNextDirection(KEY_LEFT);
					break;

				case ALLEGRO_KEY_RIGHT:
					if ( !(key[KEY_UP]) && !(key[KEY_DOWN]) ){
						key[KEY_RIGHT] = true;
						key[KEY_UP] = false;
						key[KEY_DOWN] = false;
						key[KEY_LEFT] = false;
					}
					pacman.setNextDirection(KEY_RIGHT);
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
			}
		}
 
		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));

			game.drawMaze();
			game.drawCharacter(pacman.getPositionX(),pacman.getPositionY(),pacman.getSprite(curFrame,dir));
			al_draw_text(font, al_map_rgb(255,255,255), 620, 54, ALLEGRO_ALIGN_CENTRE, "SCORE");
			al_draw_text(font, al_map_rgb(255,255,255), 620, 92, ALLEGRO_ALIGN_CENTRE, to_string(game.getScore()).c_str());
			al_flip_display();
		}
	}
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
 
	return 0;
}