#include "display/sfml/SFMLDisplay.hpp"

SFMLDisplay::SFMLDisplay() : _window(NULL)
{
}

SFMLDisplay::~SFMLDisplay()
{
  if (this->_window)
    delete this->_window;
}

int		SFMLDisplay::createWindow(size_t const &length, size_t const &height, std::string const &name)
{
  this->_window = new sf::RenderWindow(sf::VideoMode(length, height), name);
  return (0);
}

std::string	SFMLDisplay::startGame(IGame &game, std::string const &musicName)
{
  (void)game;
  (void)musicName;
  while (this->_window->isOpen())
    {
      sf::Event event;
      while (this->_window->pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    this->_window->close();
	}
    }

  this->_window->clear();
  this->_window->display();
  return ("");
}

void		SFMLDisplay::displayMap(char **map, int const sizeX, int const sizeY)
{
  (void)map;
  (void)sizeX;
  (void)sizeY;
}

int		SFMLDisplay::setShape(IGame &game, int const tileType, std::string const &shape, unsigned int const color, unsigned int const size, std::string const &textureName)
{
  (void)game;
  (void)tileType;
  (void)shape;
  (void)color;
  (void)size;
  (void)textureName;
  return (0);
}

void		SFMLDisplay::displayEntities(std::map<int, std::list<void *> > *entities, int const sizeX, int const sizeY)
{
  (void) entities;
  (void) sizeX;
  (void) sizeY;
}

std::string	SFMLDisplay::replay(int const score)
{
  (void) score;
  return ("");
}

extern "C"
{
IDisplayManager		*getInstance() {return (new SFMLDisplay); }
}
