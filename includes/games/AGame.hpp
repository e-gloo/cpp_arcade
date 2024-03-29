/*
** AGame.hpp for AGame in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 12:42:18 2016 Dylan Coodien
** Last update Fri Apr  1 19:13:51 2016 Dylqn Coodien
*/

#ifndef AGAME_HPP_
# define AGAME_HPP_

# include <ctime>
# include "IGame.hpp"

class AGame: public IGame
{
protected:
  int					sizeX;
  int					sizeY;
  char					**map;
  std::map<int, std::list<void *> >	*entities;
  std::clock_t				previousTime;

public:
  AGame();
  virtual	~AGame() {};
  virtual int	getSizeX() const;
  virtual int	getSizeY() const;
  virtual char	**getMap() const;
  virtual void	startGame(IDisplayManager &, std::string const &) = 0;
  virtual std::map<int, std::list<void *> > *getEntities() const;
  virtual int	play(char) = 0;
};

#endif /* !AGAME_HPP_ */
