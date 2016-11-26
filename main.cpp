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

#define COL 29 //Cantidad de columnas
#define ROW 32 //Cantidad de filas
#define SPRITESIZE 18 //Tamaño de los sprites

using namespace std;
using namespace character;
using namespace game;

/*
 * 
 */


ALLEGRO_BITMAP *screen;
const float FPS = 60;
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
	int dir = 0;
   
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
 
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
   }
 

  // al_set_target_bitmap(display);
 
   //al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
 
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
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
			if(key[KEY_UP] /*&& bouncer_y >= 4.0*/) {
				dir = 0;
				pacman.setPositionY(pacman.getPositionY()-3);
//				cout << "Position Y: " << to_string(pacman.getPositionY()) << endl;
			}
 
			if(key[KEY_DOWN] /*&& bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0*/) {
				dir = 1;
				pacman.setPositionY(pacman.getPositionY()+3);
//				cout << "Position Y: " << to_string(pacman.getPositionY()) << endl;
			}

			 if(key[KEY_LEFT] /*&& bouncer_x >= 4.0*/) {
				dir = 2;
				pacman.setPositionX(pacman.getPositionX()-3);
			}

			if(key[KEY_RIGHT] /*&& bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0*/) {
				dir = 3;
				pacman.setPositionX(pacman.getPositionX()+3);
			}
			
			if(++frameCount >= frameDelay)
			{
				if(++curFrame >= maxFrame)
					curFrame = 0;

				frameCount = 0;
			}
 
			redraw = true;
		}
		
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					key[KEY_DOWN] = false;
					key[KEY_LEFT] = false;
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					key[KEY_UP] = false;
					key[KEY_LEFT] = false;
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = true;
					key[KEY_UP] = false;
					key[KEY_DOWN] = false;
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					key[KEY_UP] = false;
					key[KEY_DOWN] = false;
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
			}
		}
 
		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));

			game.setFruit(1,1,'s');

			game.drawMaze();
			game.drawCharacter(pacman.getPositionX(),pacman.getPositionY(),pacman.getSprite(curFrame,dir));

			al_flip_display();
		}
	}
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
 
	return 0;
}