#include "display/sdl/SDLDisplay.h"

#include <iostream>

SDLDisplay::SDLDisplay() : _title(""), _screen(NULL), _width(0), _height(0)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL_Init : " << SDL_GetError() << std::endl;
      exit(1);
    }
}

SDLDisplay::~SDLDisplay()
{

}

int		SDLDisplay::createWindow(size_t const &length, size_t const &height, std::string const &name)
{
  _width = length;
  _height = height;
  _title = name;
  _screen = SDL_SetVideoMode(_width * SIZE_PIX, _height * SIZE_PIX, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (_screen == NULL)
    {
      std::cerr << "SDL_SetVideoMode : " << SDL_GetError() << std::endl;
      exit(1);
    }
  SDL_WM_SetCaption(_title.c_str(), NULL);
}

std::string	SDLDisplay::startGame(IGame &game)
{
  bool		running = true;

  while (running)
    {
      running = false;
    }
  return ("");
}

void		SDLDisplay::displayMap(char **map, int const sizeX, int const sizeY)
{

}

int		SDLDisplay::setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const &textureName)
{

}

extern "C"
{
  IDisplayManager		*getInstance() {return (new SDLDisplay(); }
}
