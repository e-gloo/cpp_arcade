#ifndef NCURSES_HPP
# define NCURSES_HPP

#include <curses.h>
#include <map>
#include "display/IDisplayManager.hpp"

# define WIDTH	20
# define HEIGHT	20

class Ncurses : public IDisplayManager
{
  std::string	_title;
  WINDOW	*_window;
  int		_height;
  int		_width;
  std::map<int, std::string> _shapes;

public:
  explicit Ncurses();
  virtual ~Ncurses();
  virtual int createWindow(size_t const &length, size_t const &height, std::string const &name);
  virtual std::string startGame(IGame &game);
  virtual void displayMap(char **map, int const sizeX, int const sizeY);
  virtual int setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const &textureName);
};

#endif
