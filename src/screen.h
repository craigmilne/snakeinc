#ifndef SCREEN_H
#define SCREEN_H


int drawSplashScreen(void);
int drawMenuScreen(void);
int drawGameScreen(void);
int drawEndScreen(void);

void setCursorPos(int x, int y);
void clearTerminal(void);

int getTerminalWidth(void);
int getTerminalHeight(void);

#endif /* SCREEN_H */
