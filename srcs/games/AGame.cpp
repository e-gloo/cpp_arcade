/*
** AGame.cpp for AGame in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 13:05:12 2016 Dylan Coodien
** Last update Wed Mar 16 15:57:43 2016 Dylan Coodien
*/

#include "games/AGame.hpp"

AGame::AGame()
  :sizeX(0), sizeY(0), map(NULL), entities(NULL), previousTime(std::time(0) * 1000)
{
}

int					AGame::getSizeX() const
{
  return (this->sizeX);
}

int					AGame::getSizeY() const
{
  return (this->sizeY);
}

char					**AGame::getMap() const
{
  return (this->map);
}

std::map<int, std::list<void *> >	*AGame::getEntities() const
{
  return (this->entities);
}

/*
void					AGame::startGame(IDisplayManager &dis)
{
  (void)dis;
}
*/
