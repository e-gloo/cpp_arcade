/*
** AGame.cpp for AGame in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 13:05:12 2016 Dylan Coodien
** Last update Thu Mar 31 23:05:58 2016 Dylqn Coodien
*/

#include "games/AGame.hpp"
#include "games/nibbler/Nibbler.hpp"

AGame::AGame()
  :sizeX(0), sizeY(0), map(NULL), entities(NULL), previousTime(std::clock())
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
