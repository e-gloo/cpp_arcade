#include "display/term/Ncurses.hpp"

#include <iostream>
#include <unistd.h>

Ncurses::Ncurses() : _title(""), _window(NULL), _height(HEIGHT), _width(WIDTH)
{
  initscr();
}

Ncurses::~Ncurses()
{
  if (this->_window)
    {
      wrefresh(_window);
      nodelay(_window, 0);
      echo();
      delwin(_window);
    }
  endwin();
}

int		Ncurses::createWindow(size_t const &length, size_t const &height, std::string const &name)
{
  _width = length;
  _height = height;
  int xstart = (COLS - _width) / 2;
  int ystart = (LINES - _height) / 2;

  _title = name;
  if ((_window = newwin(_height, _width, ystart, xstart)) == NULL)
    {
      std::cout << "error" << std::endl;
      return (-1);
    }
  curs_set(0);
  noecho();
  nodelay(_window, 1);
  keypad(_window, TRUE);
  wrefresh(_window);
  return (0);
}

std::string	Ncurses::startGame(IGame &game)
{
  bool		running = true;
  char		**map;
  int		key;

  while (running)
    {
      map = game.getMap();
      this->displayMap(map, _width, _height);
      if ((key = wgetch(_window)) == 27)
	running = false;
      if (game.play(key) == 1)
	running = false;
    }
  return ("");
}

void		Ncurses::displayMap(char **map, int const sizeX, int const sizeY)
{
  for (int i = 0; i < sizeY; ++i)
    for (int j = 0; j < sizeX; ++j)
      mvwprintw(_window, i, j, "%c", _shapes[map[i][j]][0]);
  wrefresh(_window);
}

int		Ncurses::setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const &textureName)
{
  (void)color;
  (void)textureName;
  _shapes[tileType] = shape;
  return (0);
}

extern "C"
{
  IDisplayManager		*getInstance() {return (new Ncurses()); }
}
