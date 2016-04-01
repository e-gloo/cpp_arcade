#include "display/opengl/OpenGLDisplay.hpp"

#include <iostream>
#include <unistd.h>

OpenGLDisplay::OpenGLDisplay() : _title(""), _width(0), _height(0), _event(), _exit(false), _keys()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL_Init : " << SDL_GetError() << std::endl;
      exit(1);
    }
}

OpenGLDisplay::~OpenGLDisplay()
{
  SDL_Quit();
}

int		OpenGLDisplay::createWindow(size_t const &length, size_t const &height, std::string const &name)
{
  _width = length;
  _height = height;
  _title = name;
  SDL_WM_SetCaption(_title.c_str(), NULL);
  SDL_SetVideoMode(_width * SIZE_PIX, _height * SIZE_PIX, 32, SDL_OPENGL);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, _width * SIZE_PIX, 0, _height * SIZE_PIX);
  return (0);
}

std::string		OpenGLDisplay::startGame(IGame &game)
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

char            OpenGLDisplay::readKey()
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
  else if (_keys[SDLK_ESCAPE] || _exit)
    return (27);
  return (-1);
}

void            OpenGLDisplay::catchEvent()
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

void		OpenGLDisplay::getRGBcolors(int *r, int *g, int *b, int color)
{
  int		mask = 0x00FF0000;
  *r = mask & color;
  *r = *r >> 16;
  mask = mask >> 8;
  *g = mask & color;
  *g = *g >> 8;
  mask = mask >> 8;
  *b = mask & color;
}

void		OpenGLDisplay::drawCase(int i, int j, char **map)
{
  int		y = i - (_width / 2);
  int		x = j - (_height / 2);

  glBegin(GL_QUADS);

  glColor3ub(_shapes[map[i][j]][0], _shapes[map[i][j]][1], _shapes[map[i][j]][2]);
  glVertex2d((double)x / (_width / 2), (double)(-y) / (_height / 2));
  glVertex2d((double)x / (_width / 2), (double)(-(y+1)) / (_height / 2));
  glVertex2d((double)(x + 1) / (_width / 2), (double)(-(y+1)) / (_height / 2));
  glVertex2d((double)(x + 1) / (_width / 2), (double)(-y) / (_height / 2));

  glEnd();
}

void		OpenGLDisplay::displayMap(char **map, int const sizeX, int const sizeY)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glBegin(GL_QUADS);
  glColor3ub(255, 255, 255);
  glVertex2d(-1, -1);
  glVertex2d(-1, 1);
  glVertex2d(1, 1);
  glVertex2d(1, -1);
  glEnd();

  for (int i = 0; i < sizeY; ++i)
    for (int j = 0; j < sizeX; ++j)
      {
	if (map[i][j] != 0)
	  this->drawCase(i, j, map);
      }
  //equivalent de SDL_Flip() :
  glFlush();
  SDL_GL_SwapBuffers();
}

int		OpenGLDisplay::setShape(int const tileType, std::string const &shape, unsigned int const color, std::string const &textureName)
{
  int	r;
  int	g;
  int	b;

  (void)shape;
  (void)textureName;
  getRGBcolors(&r ,&g, &b, color);
  _shapes[tileType][0] = r;
  _shapes[tileType][1] = g;
  _shapes[tileType][2] = b;
  return (0);
}

extern "C"
{
  IDisplayManager		*getInstance() {return (new OpenGLDisplay()); }
}
