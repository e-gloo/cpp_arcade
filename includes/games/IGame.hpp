#ifndef _IGAME_HPP_
#define _IGAME_HPP_

#include <map>
#include <list>
#include <string>

struct Part
{
  float x;
  float y;
  float speed;
};


class IDisplayManager;

class IGame
{
public:
  virtual	~IGame() {};
  virtual int	getSizeX() const = 0;
  virtual int   getSizeY() const = 0;
  virtual int	play(char, int const) = 0;
  virtual char	**getMap() const = 0;
  virtual void startGame(IDisplayManager &) = 0;
  virtual std::map<int, std::list<void *>> *getEntities() = 0;
};

#endif /* ! _IGAME_HPP_ */
