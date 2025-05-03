/*
 Copyright (c) 2025 Mateusz Stadnik

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.

 */
// based on
// https://labex.io/tutorials/c-creating-terminal-code-rain-with-c-and-ncurses-298826

#include "rain.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#define MAX_RAINDROPS 100
typedef struct {
  int x;
  int y;
  char ch;
  int color;
  int speed;
} Raindrop;

void init_colors(void) {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
}

void rain(void) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  nodelay(stdscr, true);
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);
  init_colors();
  srand(time(NULL));
  Raindrop raindrops[MAX_RAINDROPS] = {};
  for (int i = 0; i < MAX_RAINDROPS; i++) {
    raindrops[i].x = rand() % max_x;
    raindrops[i].y = rand() % max_y;
    raindrops[i].ch = rand() % 94 + 33; // ASCII range from 33 to 126
    raindrops[i].color = rand() % 6 + 1;
    raindrops[i].speed = rand() % 3 + 1;
  }

  while (1) {
    int ch = getch();
    if (ch == 'q') {
      break; // Exit on 'q' key press
    }
    for (int i = 0; i < MAX_RAINDROPS; i++) {
      attron(COLOR_PAIR(raindrops[i].color));
      mvaddch(raindrops[i].y, raindrops[i].x, ' ');
      raindrops[i].y += raindrops[i].speed;
      if (raindrops[i].y >= max_y) {
        raindrops[i].y = 0;
        raindrops[i].x = rand() % max_x;
      }
      mvaddch(raindrops[i].y, raindrops[i].x, raindrops[i].ch);
      attroff(COLOR_PAIR(raindrops[i].color));
    }
    refresh();
    napms(50);
  }
  endwin();
}