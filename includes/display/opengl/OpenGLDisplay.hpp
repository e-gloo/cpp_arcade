#ifndef OPENGLDISPLAY_HPP_
# define OPENGLDISPLAY_HPP_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "display/IDisplayManager.hpp"

#define SIZE_PIX 32

class OpenGLDisplay : public IDisplayManager
{
  std::string	_title;
  int		_width;
  int		_height;
  SDL_Event	_event;
  bool		_exit;
  bool		_keys[SDLK_LAST];
  std::map<int, int[3]> _shapes;

  char		readKey();
  void		catchEvent();
  void		drawCase(int, int, char**);
  void		getRGBcolors(int*, int*, int*, int);

public:
  explicit OpenGLDisplay();
  virtual ~OpenGLDisplay();
  virtual int createWindow(size_t const &length, size_t const &height, std::string const &name);
  virtual std::string startGame(IGame &game);
  virtual void displayMap(char **map, int const sizeX, int const sizeY);
  virtual int setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const &textureName);
};

#endif
