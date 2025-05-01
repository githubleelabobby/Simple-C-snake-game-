#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

typedef struct {
    int x;
    int y;
} vec2;

int score = 0;
vec2 segments[256];//max length of snake

int main() {
    int screen_width = 40;
    int screen_height = 20;

    // Initialize screen
    WINDOW *win = initscr();

    // Take player input
    keypad(win, true);
    nodelay(win, true);
    curs_set(0);

    // Snake 
    vec2 head = {0, 0};
    vec2 dir = {1, 0};
    
    // Berry
    vec2 berry = {rand() % screen_width, rand() % screen_height};

    while (1) {
        int pressed = wgetch(win);
        
        // Update direction based on user input
        if (pressed == KEY_LEFT) {
            if (dir.x == 1) continue;
            dir.x = -1;
            dir.y = 0;
        }
        if (pressed == KEY_RIGHT) {
            if (dir.x == -1) continue;
            dir.x = 1;
            dir.y = 0;
        }
        if (pressed == KEY_UP) {
            if (dir.y == 1) continue;
            dir.x = 0;
            dir.y = -1;
        }
        if (pressed == KEY_DOWN) {
            if (dir.y == -1) continue;
            dir.x = 0;
            dir.y = 1;
        }
        if (pressed == '\e') {
            break;
        }

	//------------update-----------------
	for (int i = score ; i> 0; i--) {
	    segments[i] = segments[i - 1];
        }
	segments[0] = head;

        head.x += dir.x;
        head.y += dir.y;

        // Check if snake ate the berry
        if (head.x == berry.x && head.y == berry.y) {
            score++;
            berry.x = rand() % screen_width;
            berry.y = rand() % screen_height;
        }

        //-------------------- draw---------
        erase();

        mvaddch(berry.y, berry.x * 2, '@');
        
	//draw snake
	for (int i = 0 ;i < score ; i++){
		mvaddch(segments[i].y, segments[i].x * 2 , 'o');
        }
        mvaddch(head.y, head.x * 2 ,'O');

	mvprintw(0, 0, "Score: %d", score);

        usleep(125000);
    }

    endwin();
    return 0;
} 
