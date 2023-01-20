#include "util.cpp"
#include <thread>
#include <iostream>

#define win_title "Would you like to proceed?"

#define win_footer_left "F1 to exit"
#define win_footer_right "Release Note: Multithreading eats the CPU"

unsigned int nthreads = std::thread::hardware_concurrency();

int main(int argc, char *argv[])
{
  WINDOW *my_win;
  WINDOW *my_win_padded;
  int ch;

  signal(SIGINT, sigint_handler);
  signal(SIGTERM, sigterm_handler);
  signal(SIGABRT, sigabrt_handler);

  initscr();
  keypad(stdscr, TRUE);
  raw();
  noecho();
  cbreak();
  curs_set(0);

  start_color();
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_RED);
  init_pair(5, COLOR_RED, COLOR_WHITE);
  clear();

  attron(COLOR_PAIR(2));

  for (int i = 0; i < COLS; i++)
  {
    printw(" ");
  }

  move(0, (COLS / 2) - (strlen(win_title) / 2));
  printw(win_title);

  attroff(COLOR_PAIR(2));
  attron(COLOR_PAIR(1));

  move(LINES - 2, 0);

  for (int i = 0; i < COLS; i++)
  {
    printw(" ");
  }

  move(LINES - 2, 1);
  printw(win_footer_left);

  move(LINES - 2, COLS - strlen(win_footer_right) - 1);
  printw(win_footer_right);

  attroff(COLOR_PAIR(1));

  refresh();
  my_win = create_newwin(10, COLS, (LINES / 2) - 5, 0);
  wbkgd(my_win, COLOR_PAIR(3));
  wrefresh(my_win);
  my_win_padded = create_newwin(8, COLS - 2, (LINES / 2) - 4, 1);
  wbkgd(my_win_padded, COLOR_PAIR(3));
  wattron(my_win_padded, COLOR_PAIR(3));
  wprintw(my_win_padded, "Proceeding to the next stage.");
  wattroff(my_win_padded, COLOR_PAIR(3));

  wmove(my_win_padded, 7, COLS / 2 - 4);
  wattron(my_win_padded, COLOR_PAIR(4));
  wprintw(my_win_padded, "  ");
  wattroff(my_win_padded, COLOR_PAIR(4));
  wattron(my_win_padded, COLOR_PAIR(5));
  wprintw(my_win_padded, "OK");
  wattroff(my_win_padded, COLOR_PAIR(5));
  wattron(my_win_padded, COLOR_PAIR(4));
  wprintw(my_win_padded, "  ");
  wattroff(my_win_padded, COLOR_PAIR(4));

  wrefresh(my_win_padded);

  while ((ch = getch()) != KEY_F(1))
  {
    switch (ch) {
    case 10:
    case 32:
      wclear(my_win_padded);
      wmove(my_win_padded, 0, 0);
      wprintw(
          my_win_padded,
          "Congratulations! You're now computing prime numbers up to the "
          "unsigned 32-bit integer limit (4,294,967,295)! What are we "
          "doing with them? Absolutely nothing! This will likely use a lot "
          "of processing power and take a while to complete. You have a "
          "few options. 1. Wait for it to complete (this will take a long "
          "time). 2. Reboot your computer. 3. Find a way to exit the "
          "program, ^C will not work as the program handles SIGINT and "
          "prevents it from ending runtime. If you hadn't pressed ok you could "
          "have pressed F1 to save yourself. Remember this for next "
          "time.\nChange da world, my final message, goodbye.");
      wrefresh(my_win_padded);
      for (int i = 0; i <= nthreads; i++)
      {
        std::thread j(compute_primes);
        j.detach();
      }
    }
  }

  endwin();
  return 0;
}
