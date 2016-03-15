#ifndef SFMLDISPLAY_HPP
# define SFMLDISPLAY_HPP

#include "extern/SFML/Window.hpp"
#include "extern/SFML/Graphics.hpp"
#include "display/IDisplayManager.hpp"

class	SFMLDisplay : public IDisplayManager
{
private:
  sf::RenderWindow	*_window;
public:
  explicit SFMLDisplay();
  virtual ~SFMLDisplay();
  virtual int createWindow(size_t const &length, size_t const &height, std::string const &name);
  virtual std::string startGame(IGame &game, std::string const &musicName);
  virtual void displayMap(char **map, int const sizeX, int const sizeY);
  virtual int setShape(IGame &game, int const tileType, std::string const &shape, unsigned int const color, unsigned int const size, std::string const &textureName);
  virtual void displayEntities(std::map<int, std::list<void *> > *entities, int const sizeX, int const sizeY);
  virtual std::string replay(int const score);
};

#endif
