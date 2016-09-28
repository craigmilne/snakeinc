#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "screen.h"
#include "kbio.h"
#include "configuration.h"

struct snakepos {
	int x;
	int y;
};

bool isvalueinhistory(struct snakepos val, struct snakepos* history, int size);

unsigned int rand_interval(unsigned int min, unsigned int max);

int playGame(void) {

	bool playing = true;
	int direction = 0; // left = 0, up = 1, right = 2, down = 3
	int newscore = 0;
	long wait;
	switch(difficulty) {
		case 0:
			wait = 200L;
			break;
		case 1:
			wait = 75L;
			break;
		case 2:
			wait = 20L;
			break;
	}
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = wait * 1000000L;

	struct snakepos blank;
	blank.x = 0;
	blank.y = 0;

	struct snakepos history[2*300*200] = {blank};		// max game size?

	history[0].x = getTerminalWidth()/2;
	history[0].y = getTerminalHeight()/2;
	history[1].x = history[0].x + 1;
	history[1].y = history[0].y;
	history[2].x = history[1].x + 1;
	history[2].y = history[0].y;

	struct snakepos munch;
	unsigned int x_munch = rand_interval(1, getTerminalWidth() - 1);
	unsigned int y_munch = rand_interval(1, getTerminalHeight() - 1);


	while(playing){ 
		clearTerminal();
		setCursorPos(2, 1);
		printf("Highscore: %04d\n", highscore);
		setCursorPos(getTerminalWidth() - 11, 1);
		printf("Score: %04d\n", newscore);

        if(kbhit()){  //is true when a key was pressed
	        char c = getch();   //capture the key code and insert into c
	        if (c == '\033') {
	        	getch();		// Skip [
	        	switch(getch()) {
	        		case 'A':
	        			// Arrow up
	        			if (direction == 3) {
	        				playing = false;
	        			} else {
	        				direction = 1;
	        			}
	        			break;
	        		case 'B':
	        			// Arrow down
	        			if (direction == 1) {
	        				playing = false;
	        			} else {
	        				direction = 3;
	        			}
	        			break;
	        		case 'C':
	        			// Arrow right
	        			if (direction == 0) {
	        				playing = false;
	        			} else {
	        				direction = 2;
	        			}
	        			break;
	        		case 'D':
	        			// Arrow left
	        			if (direction == 2) {
	        				playing = false;
	        			} else {
	        				direction = 0;
	        			}
	        			break;
	        	}
	        }
	    }
	    // draw snek
	    for (int i = 0; i < sizeof(history)/sizeof(* history); i++) {
	    	if (history[i].x != 0) {
	    		setCursorPos(history[i].x, history[i].y);
	    		if (i == 0) {
	    			printf("@");
	    		} else {
	    			printf("#");
	    		}
	    	} else {
	    		break;
	    	}
	    }
	    setCursorPos(3,5);
	    printf("\n", history[0].x, history[0].y);
	    //sleep(5);

	    munch.x = x_munch;
	    munch.y = y_munch;

	    struct snakepos temp;
	    struct snakepos temp1;
   		for (int c = 0; c < sizeof(history)/sizeof(* history); c++) {
   			if (history[c].x == 0) {
   				if (history[0].x == munch.x && history[0].y == munch.y) {
					newscore++;
   					history[c] = temp;
   				}
   				break;
   			} else {
   				// calc next pos and arrange 'history'
   				if (c == 0) {
   					temp = history[0];
				    struct snakepos nextpos;
				    switch(direction) {
				    	case 0:
				    		if (history[c].x == 1) {
				    			nextpos.x = getTerminalWidth() - 1;
				    			nextpos.y = history[c].y;
				    		} else {
				    			nextpos.x = history[c].x - 1;
				    			nextpos.y = history[c].y;
				    		}
				    		break;
				    	case 1:
				    		if (history[c].y == 1) {
				    			nextpos.x = history[c].x;
				    			nextpos.y = getTerminalHeight() - 1;
				    		} else {
				    			nextpos.x = history[c].x;
				    			nextpos.y = history[c].y - 1;
				    		}
				    		break;
				    	case 2:
				    		if (history[c].x == getTerminalWidth() - 1) {
				    			nextpos.x = 1;
				    			nextpos.y = history[c].y;
				    		} else {
				    			nextpos.x = history[c].x + 1;
				    			nextpos.y = history[c].y;

				    		}
				    		break;
				    	case 3:
				    		if (history[c].y == getTerminalHeight() - 1) {
				    			nextpos.x = history[c].x;
				    			nextpos.y = 1;
				    		} else {
				    			nextpos.x = history[c].x;
				    			nextpos.y = history[c].y + 1;
				    		}
				    		break;
				    }
				    if (!isvalueinhistory(nextpos, history, sizeof(history)/sizeof(*history))) {
				    	history[c] = nextpos;
				    } else {
				    	playing = false;
				    }
				} else {
					temp1 = history[c];
					history[c] = temp;
					temp = temp1;
				}
   			}
   		}

	    while (isvalueinhistory(munch, history, sizeof(history)/sizeof(* history))) {
	    	x_munch = rand_interval(2, getTerminalWidth() - 2);
	    	y_munch = rand_interval(2, getTerminalHeight() - 2);

	    	munch.x = x_munch;
	    	munch.y = y_munch;
	    }

	    setCursorPos(munch.x, munch.y);
	    printf("o\n");

	    // Sleep based on difficulty
	    setCursorPos(getTerminalWidth() - 1, getTerminalHeight() - 2);
	    printf("\n");
	    nanosleep(&tim, NULL);

    }

    lastScore = newscore;
    return 0;

}

bool isvalueinhistory(struct snakepos val, struct snakepos* history, int size) {
    int i;
    for (i=0; i < size; i++) {
    	if (history[i].x == 0) {
			return false;
    	}
        if (history[i].x == val.x && history[i].y == val.y) {
            return true;
        }
    }
    return false;
}

unsigned int rand_interval(unsigned int min, unsigned int max) {
	srand(time(NULL));
	return rand() % (max + 1 - min) + min;
}
