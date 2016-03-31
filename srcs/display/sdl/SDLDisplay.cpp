#include "display/sdl/SDLDisplay.hpp"

#include <iostream>
#include <unistd.h>

SDLDisplay::SDLDisplay() : _title(""), _screen(NULL), _width(0), _height(0), _shapes(), _event(), _exit(false), _keys()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL_Init : " << SDL_GetError() << std::endl;
      exit(1);
    }
}

SDLDisplay::~SDLDisplay()
{
  std::map<int, std::pair<Uint32, SDL_Surface*> >::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
    SDL_FreeSurface(it->second.second);
  SDL_Quit();
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
  return (0);
}

std::string	SDLDisplay::startGame(IGame &game)
{
  bool		running = true;
  char		**map;
  char		key;

  while (running)
    {
      map = game.getMap();
      this->displayMap(map, _width, _height);
      if ((key = readKey()) == 27)
	running = false;
      if (game.play(key) == 1)
	running = false;
    }
  return ("");
}

void		SDLDisplay::drawCase(int i, int j, char **map)
{
  SDL_Surface	*Case;
  SDL_Rect	rect;

  rect.x = j * SIZE_PIX;
  rect.y = i * SIZE_PIX;

  if (_shapes[map[i][j]].second != NULL)
    SDL_BlitSurface(_shapes[map[i][j]].second, NULL, _screen, &rect);
  else
    {
      Case = SDL_CreateRGBSurface(SDL_HWSURFACE, SIZE_PIX, SIZE_PIX, 32, 0, 0, 0, 0);
      if (Case == NULL)
	{
	  std::cerr << "SDL_CreateRGBSurface : " << SDL_GetError() << std::endl;
	  return;
	}
      SDL_FillRect(Case, NULL, _shapes[map[i][j]].first);
      SDL_BlitSurface(Case, NULL, _screen, &rect);
      SDL_FreeSurface(Case);
    }
}

char		SDLDisplay::readKey()
{
  catchEvent();
  if (_keys[SDLK_z])
    {
      _keys[SDLK_z] = false;
      return 'z';
    }
  else if (_keys[SDLK_q])
    {
      _keys[SDLK_q] = false;
      return 'q';
    }
  else if (_keys[SDLK_s])
    {
      _keys[SDLK_s] = false;
      return 's';
    }
  else if (_keys[SDLK_d])
    {
      _keys[SDLK_d] = false;
      return 'd';
    }
  else if (_exit)
    return (27);
  return (-1);
}

void		SDLDisplay::catchEvent()
{
  SDL_PollEvent(&_event);

  if (_event.type == SDL_KEYDOWN)
    _keys[_event.key.keysym.sym] = true;
  else if (_event.type == SDL_KEYUP)
    _keys[_event.key.keysym.sym] = false;
  else if (_event.type == SDL_QUIT)
    _exit = true;
  _event.type = 0;
}

void		SDLDisplay::displayMap(char **map, int const sizeX, int const sizeY)
{
  SDL_Rect	rect;

  for (int i = 0; i < sizeY; ++i)
    for (int j = 0; j < sizeX; ++j)
      drawCase(i, j, map);
  
  SDL_Flip(_screen);
}

int		SDLDisplay::setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const &textureName)
{
  SDL_Surface *img;

  (void)shape;
  img = NULL;
  _shapes[tileType].first = color;
  if (!textureName.empty())
    if ((img = IMG_Load(textureName.c_str())) == NULL)
      std::cerr << "IMG_Load : " << SDL_GetError() << std::endl;
  _shapes[tileType].second = img;
  return (0);
}

extern "C"
{
  IDisplayManager		*getInstance() {return (new SDLDisplay()); }
}
