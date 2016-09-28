#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "screen.h"
#include "logging.h"

// Variable Declarations
bool gameLoop = true;
enum gameState {MENU, PLAYING, GAMEOVER};
enum gameState currentState = MENU;

// Function Declarations
int isNoSplash(int argc, char **argv);

// Main Function, contains the Game Loop, although probably shouldn't :|
int main(int argc, char **argv) {

	if (!isNoSplash(argc, argv)) {
		// Draw the splash screen
		drawSplashScreen();
	}

	// Actual Game Loop
	while(gameLoop) {
		if (currentState == MENU) {
			// Currently on the menu, hands control to "screen.c"
			// then to "menu.c" when it is time to leave.
			// returns 0 if going to play, -1 if no change or 1 if exit.
			int menuResponse = drawMenuScreen();
			switch(menuResponse) {
				case -1 :
					break;
				case  0 :
					currentState = PLAYING;
					break;
				case  1 :
					gameLoop = false;
					break;
				default :
					logsExit("Unexpected Menu Response - Exiting...");
					return 0;
			}
		} else if (currentState == PLAYING) {
			// Currently playing game
			int gameResp = drawGameScreen();
			if (gameResp == 0) {
				currentState = GAMEOVER;
			} else {
				logsExit("Unexpected Game Response - Exiting...");
				return 0;
			}
		} else if (currentState == GAMEOVER) {
			// Game has ended
			int endResp = drawEndScreen();
			if (endResp == 0) {
				currentState = MENU;
			} else {
				logsExit("Unexpected Game Response - Exiting...");
				return 0;
			}
		} else {
			// Shoudln't happen? RIP
			logsExit("Unexpected Game State - Exiting...");
			return 0;
		}
		// Cancel after 1 loop, for debug - don't keep in final
		//gameLoop = false;
	}

	// Reset system console on exit.
	system("reset");
	return 0;
}

int isNoSplash(int argc, char **argv) {
	int k;
	for (k=0; k < argc; k++) {
		if (strcmp(argv[k], "-novid") == 0) {
			return true;
		}
	}
	return false;
}
