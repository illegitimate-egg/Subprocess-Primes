#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void compute_primes()
{
  int num = 1, primes = 0;

  uint limit = 4294967295;
  for (num = 1; num <= limit; num++) {
    int i = 2;
    while (i <= num) {
      if (num % i == 0)
        break;
      i++;
    }
    if (i == num)
      primes++;
  }
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);

  // This code has been obseleted :partyblob: :partying_face:
  // box(local_win, 0, 0);

  wrefresh(local_win);

  return local_win;
}

void destroy_win(WINDOW *local_win)
{
  wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wclear(local_win);
  wrefresh(local_win);
  delwin(local_win);
}

void sigint_handler(int signum)
{
  signal(SIGINT, sigint_handler);
  fflush(stdout);
}

void sigterm_handler(int signum)
{
  signal(SIGTERM, sigterm_handler);
  fflush(stdout);
}

void sigabrt_handler(int signum)
{
  signal(SIGABRT, sigabrt_handler);
  fflush(stdout);
}
