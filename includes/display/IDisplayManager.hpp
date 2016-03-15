#ifndef IDISPLAYMANAGER_HPP
#define IDISPLAYMANAGER_HPP

#include <cstdlib>
#include <string>
#include <map>
#include "games/IGame.hpp"

class IDisplayManager
{
  public:
    virtual ~IDisplayManager(void) { };
    virtual int createWindow(size_t const & length, size_t const &height, std::string const &name) = 0;
    virtual std::string startGame(IGame &game, std::string const &musicName) = 0;
    virtual void displayMap(char **map, int const sizeX, int const sizeY) = 0;
    virtual int setShape(IGame &game, int const tileType, std::string const &shape, unsigned int const color, unsigned int const size = 0,  std::string const &textureName = "") = 0;
    virtual void displayEntities(std::map<int, std::list<void *>> *entities, int const sizeX, int const sizeY) = 0;
    virtual std::string replay(int const score) = 0;
};

#endif
