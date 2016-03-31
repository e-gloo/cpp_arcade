/*
** AGame.cpp for AGame in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 13:05:12 2016 Dylan Coodien
** Last update Thu Mar 31 13:50:08 2016 Dylqn Coodien
*/

#include "IDisplayManager.hpp"
#include "AGame.hpp"
#include "Nibbler.hpp"

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

void					AGame::startGame(IDisplayManager &dis)
{
  IGame *snake;

  srand(time(0));
  snake = new Nibbler();
  dis.setShape(*snake, 0, "map", 0xFF000000, 1);
  dis.setShape(*snake, -1, "bord", 0xFF00FF00, 1);
  dis.setShape(*snake, 1, "snake", 0xFFFFFFFF, 1);
  dis.setShape(*snake, 2, "food", 0xFF0000FF, 1);
}
