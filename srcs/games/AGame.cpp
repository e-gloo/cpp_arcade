/*
** AGame.cpp for AGame in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 13:05:12 2016 Dylan Coodien
// Last update Thu Mar 31 15:23:29 2016 François Cassin
*/

#include "display/IDisplayManager.hpp"
#include "games/AGame.hpp"
#include "games/nibbler/Nibbler.hpp"

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
  dis.createWindow(0, 0, "Nibbler");
  dis.setShape(*snake, 0, "  map", 0xFF000000, 1);
  dis.setShape(*snake, -1, "X bord", 0xFF00FF00, 1);
  dis.setShape(*snake, 1, "o snake", 0xFFFFFFFF, 1);
  dis.setShape(*snake, 2, "x food", 0xFF0000FF, 1);
  dis.startGame(*snake, "");
}
