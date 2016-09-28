#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "kbio.h"
#include "configuration.h"


char* difficultyStr(void) {
	switch(difficulty) {
		case 0:
			return "    EASY    ";
		case 1:
			return "   NORMAL   ";
		case 2:
			return "    HARD    ";
	}
}

// Assumes the menu has been rendered already.
int menuMain(void) {

	int pos = 0;
	char diffStr[15];
	int cont = 0;

	while(true) {
		clearTerminal();
		setCursorPos(2, 1);
		printf("Highscore: %04d\n", highscore);
		setCursorPos(getTerminalWidth() - 11, 1);
		printf("Score: %04d\n", lastScore);
		setCursorPos((getTerminalWidth()/2) - 6, 3);
		printf("%s\n", "Snake (In C)");

		if (cont == 1) {
			setCursorPos((getTerminalWidth()/2) - 7, 14);
			printf("-- Controls --\n");
			setCursorPos((getTerminalWidth()/2) - 28, 15);
			printf("You use the arrow keys, surely you know how to play Snake??\n");
		}

		setCursorPos((getTerminalWidth()/2) - 7, 6);
		printf("   NEW GAME   \n");
		setCursorPos((getTerminalWidth()/2) - 7, 7);
		char diffStr[15];
		printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), " \n"));
		setCursorPos((getTerminalWidth()/2) - 7, 8);
		printf("   CONTROLS   \n");
		setCursorPos((getTerminalWidth()/2) - 7, 10);
		printf("     EXIT     \n");

		switch(pos) {
    		case 0:
    			setCursorPos((getTerminalWidth()/2) - 7, 6);
				printf("[  NEW GAME  ]\n");
				break;
    		case 1:
    			switch(difficulty){
    				case 0:
    					setCursorPos((getTerminalWidth()/2) - 7, 7);
						printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), ">\n"));
						break;
    				case 1:
    					setCursorPos((getTerminalWidth()/2) - 7, 7);
						printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), ">\n"));
						break;
    				case 2:
    					setCursorPos((getTerminalWidth()/2) - 7, 7);
						printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), " \n"));
						break;
    			}
	            break;
    		case 2:
    			setCursorPos((getTerminalWidth()/2) - 7, 8);
				printf("[  CONTROLS  ]\n");
				break;
    		case 3:
    			setCursorPos((getTerminalWidth()/2) - 7, 10);
				printf("[    EXIT    ]\n");
	            break;
    	}

		setCursorPos((getTerminalWidth()/2) - 21, 12);
		printf("Use the arrow keys to navigate the options.\n");

		char get = getch();
		if (get == '\033') { // if the first value is esc
		    getch(); // skip the [
		    switch( getch() ) { // the real value
		        case 'A':
		            // code for arrow up
		        	//*diffStr = "";
		        	switch(pos) {
		        		case 0:
		        			break;
		        		case 1:
		        			setCursorPos((getTerminalWidth()/2) - 7, 6);
							printf("[  NEW GAME  ]\n");
							setCursorPos((getTerminalWidth()/2) - 7, 7);
							printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), " \n"));
							pos--;
				            break;
		        		case 2:
		        			switch(difficulty){
		        				case 0:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), ">\n"));
									break;
		        				case 1:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), ">\n"));
									break;
		        				case 2:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), " \n"));
									break;
		        			}
		        			setCursorPos((getTerminalWidth()/2) - 7, 8);
							printf("   CONTROLS   \n");
							pos--;
							break;
		        		case 3:
		        			setCursorPos((getTerminalWidth()/2) - 7, 8);
							printf("[  CONTROLS  ]\n");
							setCursorPos((getTerminalWidth()/2) - 7, 10);
							printf("     EXIT     \n");
							pos--;
				            break;
		        	}
		            break;
		        case 'B':
		            // code for arrow down
		        	//*diffStr = "";
					switch(pos) {
		        		case 0:
		        			setCursorPos((getTerminalWidth()/2) - 7, 6);
							printf("   NEW GAME   \n");
							switch(difficulty){
		        				case 0:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), ">\n"));
									break;
		        				case 1:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), ">\n"));
									break;
		        				case 2:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), " \n"));
									break;
		        			}
							pos++;
		        			break;
		        		case 1:
							setCursorPos((getTerminalWidth()/2) - 7, 7);
							printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), " \n"));
							setCursorPos((getTerminalWidth()/2) - 7, 8);
							printf("[  CONTROLS  ]\n");
							pos++;
				            break;
		        		case 2:
		        			setCursorPos((getTerminalWidth()/2) - 7, 8);
							printf("   CONTROLS   \n");
							setCursorPos((getTerminalWidth()/2) - 7, 10);
							printf("[    EXIT    ]\n");
							pos++;
							break;
		        		case 3:
				            break;
		        	}
		            break;
		        case 'C':
		            // code for arrow right
		        	if (pos == 1) {
		        		//*diffStr = "";
		        		switch(++difficulty){
		        				case 0:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), ">\n"));
									break;
		        				case 1:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), ">\n"));
									break;
		        				case 2:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), " \n"));
									break;
								case 3:
									difficulty = 2;
									break;
		        			}
		        	}
		            break;
		        case 'D':
		            // code for arrow left
		        	if (pos == 1) {
		        		//*diffStr = "";
		        		switch(--difficulty){
		        				case -1:
		        					difficulty = 0;
		        					break;
		        				case 0:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, " "), difficultyStr()), ">\n"));
									break;
		        				case 1:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), ">\n"));
									break;
		        				case 2:
		        					setCursorPos((getTerminalWidth()/2) - 7, 7);
									printf(strcat(strcat(strcpy(diffStr, "<"), difficultyStr()), " \n"));
									break;
		        			}
		        	}
		            break;
		    }
		} else if (get == '\n') {	// Enter is pressed
			switch(pos) {
				case 0:
					return 0;
				case 1:
					// Enter clicked on the difficulty?
					break;
				case 2:
					// Controls Pressed.
					cont = 1;
					break;
				case 3:
					// Exit
					return 1;
			}
		}
	}
}