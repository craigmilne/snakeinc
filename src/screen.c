#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "screen.h"
#include "menu.h"
#include "game.h"
#include "kbio.h"
#include "configuration.h"

struct winsize wz;
char version[10];

// Draws the splash screen, and waits 2 seconds.
int drawSplashScreen(void) {
	clearTerminal();

	setCursorPos((getTerminalWidth()/2) - 6, 7);
	printf("%s\n", "Snake (In C)");
	setCursorPos((getTerminalWidth()/2) - 2, 8);
	printf("%s\n", version);
	setCursorPos((getTerminalWidth()/2) - 12, 12);
	printf("%s\n", "Craig Milne - enlim.co");
	setCursorPos((getTerminalWidth()/2) - 13, 13);
	printf("%s\n", "github.com/enlim/snakeinc");
	setCursorPos((getTerminalWidth()/2) - 15, getTerminalHeight() - 1);
	printf("%s\n", "Copyright (c) 2016 Craig Milne");
	sleep(2);
	return 0;
}

// Draws the game over screen
int drawEndScreen(void) {
	clearTerminal();
	setCursorPos(2, 1);
	printf("Highscore: %04d\n", highscore);
	setCursorPos(getTerminalWidth() - 11, 1);
	printf("Score: %04d\n", lastScore);
	setCursorPos((getTerminalWidth()/2) - 4, 3);
	printf("%s\n", "Game Over");
	
	if (lastScore > highscore) {
		highscore = lastScore;
		setCursorPos((getTerminalWidth()/2) - 12, 5);
		printf("%s\n", "You set a new highscore!");
	}

	sleep(1);

	setCursorPos((getTerminalWidth()/2) - 18, 7);
	printf("%s\n", "Press Enter to return to the menu.");
	while( getchar() != '\n' );

	return 0;
}

// Draws the menu etc.
int drawMenuScreen(void) {
	//sleep(2);	// Debuging only
	return menuMain();
}

// Draws Screen whilst in game.
int drawGameScreen(void) {
	clearTerminal();
	return playGame();
}


// Sets Cursor Position to x, y
void setCursorPos(int x, int y) {
	printf("\033[%d;%dH", y, x);
	return;
}

// Clears Terminal Screen and resets position to 1,1
void clearTerminal(void) {
	printf("\033[2J\033[1;1H");
}

int getTerminalWidth(void) {
	ioctl(0, TIOCGWINSZ, &wz);
	return wz.ws_col;
}

int getTerminalHeight(void) {
	ioctl(0, TIOCGWINSZ, &wz);
	return wz.ws_row;
}
