/*
** IGame.hpp for arcade in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.net>
** 
** Started on  Tue Mar 15 12:30:52 2016 Dylan Coodien
// Last update Fri Apr  1 18:24:04 2016 François Cassin
*/

#ifndef _IGAME_HPP_
#define _IGAME_HPP_

#include <map>
#include <list>
#include <string>

class IDisplayManager;

class IGame
{
public:
  virtual	~IGame() {};
  virtual int	getSizeX() const = 0;
  virtual int	getSizeY() const = 0;
  virtual int	play(char) = 0;
  virtual char	**getMap() const = 0;
  virtual void	startGame(IDisplayManager &) = 0;
  virtual std::map<int, std::list<void *> > *getEntities() const = 0;
  virtual int	getScore() const = 0;
};

#endif /* ! _IGAME_HPP_ */
