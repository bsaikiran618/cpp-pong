# Pong++
pong written in c++
Author: boddulus
date:	28 March 2020

![CPP_Pong_!](https://user-images.githubusercontent.com/47565414/135740569-473ab9bf-85c5-4686-abf3-6ad9992009af.png)
![CPP_Pong_2](https://user-images.githubusercontent.com/47565414/135740576-193ed148-6b9a-414c-9ba7-fa2c811c111a.png)
![CPP_Pong_3](https://user-images.githubusercontent.com/47565414/135740577-790f345b-0113-4cde-9763-6d6c8860a3c5.png)


 	Hi There!

	This project is a close clone of the popular game 'Pong' ,originally created by Alan Alcorn and
	released in 1972.
	The game is written entirely in c++ using the popular Simple DirectMedia Layer2(SDL2) library.
	No game engines were used in the making of this game.
	The motivation for this game was to explore game development from scratch.
	
	DISCLAIMER: The game is not perfect! There are glitches and bugs. Feel free to explore the source
	and possibly try to fix the bugs.


IMPORTANT!:
=========

 This game works only on Linux right now. If I find more free time, Ill try to port it to windows as well. 



RUNNING THE GAME:
================


 DEPENDENCIES:
 -------------
	To run the game, you will have to install a few dependencies first.
	These are the following.

	1)SDL2:

	command (Debian Based Distros):	sudo apt-get install libsdl2-dev
	command (Arch Based Distros):   sudo pacman -S sdl2

	2)SDL_ttf font library:
	
	command (Debian Based Distros:	sudo apt-get install libsdl2-ttf-dev
	command (Arch Based Distros):   sudo pacman -S sdl2_ttf lib32-sdl2_ttf

 BUILD:
 -----
	To build the game run the makefile by typing the following command.
	command: make

 RUN:
 ---
 	To start the game, type the following command,
	command: ./main

CONTROLS:
======== 
 	
	PLAYER 1:
		w (UP)
		s (DOWN)
	PLAYER 2:
		UP-ARROW-KEY (UP)
		DOWN-ARROW-KEY (DOWN)

HOW TO PLAY:
============

	The game is a two-player game. Player 1 controls the left paddle and Player 2 controls the right paddle.
	The ball must be hit by a player with the paddle and should be prevented from hitting the adjacent wall.
	
	The ball can be controlled in the folowing ways:
		Hitting it with the lower end of the paddle will deflect it towards the floor.
		Hitting it with the upper end of the paddle will deflect it towards the ceiling.
		Hitting it right with the center of the paddle will make it travel parallel to the floor.
	
	If the ball hits the right wall, Player 1 gets 1 point. If the ball hits the left wall, Player 2 get a 
	point. The player to score 5 points first wins the game.

Cheers! Enjoy! ;)
