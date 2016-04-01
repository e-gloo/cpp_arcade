#ifndef SDLDISPLAY_HPP_
# define SDLDISPLAY_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include "display/IDisplayManager.hpp"

#define SIZE_PIX 32

class SDLDisplay : public IDisplayManager
{
  std::string	_title;
  SDL_Surface	*_screen;
  int		_width;
  int		_height;
  std::map<int, std::pair<Uint32, SDL_Surface*> > _shapes;
  SDL_Event	_event;
  bool		_exit;
  bool		_keys[SDLK_LAST];

  void		drawCase(int, int, char**);
  void		catchEvent();
  char		readKey();

public:
  explicit SDLDisplay();
  virtual ~SDLDisplay();
  virtual int createWindow(size_t const &length, size_t const &height, std::string const &name);
  virtual std::string startGame(IGame &game);
  virtual void displayMap(char **map, int const sizeX, int const sizeY);
  virtual int setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const&textureName);
};

#endif
