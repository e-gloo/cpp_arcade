/*
** Nibbler.cpp for Nibbler in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 14:59:35 2016 Dylan Coodien
** Last update Tue Mar 15 18:35:23 2016 Dylan Coodien
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
  :AGame()
{
  sizeX = 50;
  sizeY = 50;
  initMap();
  initSnake();
  food = new t_food;
  food->coordinates = new t_coordinates;
  food->coordinates->x = 0;
  food->coordinates->y = 0;
  food->points = 0;
}

void			Nibbler::initMap()
{
  map = new char*[sizeY];
  for (int y = 0; y < sizeY; ++y)
    {
      map[y] = new char[sizeX];
      for (int x = 0; x < sizeX; ++x)
	{
	  if (y == 0 || y == sizeY - 1
	      || x == 0 || x == sizeX - 1)
	    map[y][x] = BORDER;
	  else
	    map[y][x] = EMPTY;
	}
    }
}

void			Nibbler::initSnake()
{
  t_snakePosition	*head = new t_snakePosition;
  t_snakePosition	*body = new t_snakePosition;
  t_snakePosition	*tail = new t_snakePosition;

  snake = new std::vector<t_snakePosition *>;
  head->part = Snake::HEAD;
  head->coordinates = new t_coordinates;
  head->coordinates->y = (sizeY / 2) + 1;
  head->coordinates->x = (sizeX / 2) + 1;
  snake->push_back(head);
  for (int it = 0; it < 2; ++it)
    {
      body = new t_snakePosition;
      body->part = Snake::BODY;
      body->coordinates = new t_coordinates;
      head->coordinates->y = (sizeY / 2) + 1;
      head->coordinates->x = ((sizeX / 2) + 1) - (it + 1);
    }
}

int			Nibbler::play(char move)
{
  (void)move;
  long int		time = std::time(0);
  int			timeDiff = time - this->previousTime;

  this->previousTime = time;
  return (0);
}
