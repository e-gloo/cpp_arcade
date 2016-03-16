/*
** Nibbler.cpp for Nibbler in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 14:59:35 2016 Dylan Coodien
** Last update Wed Mar 16 15:56:56 2016 Dylan Coodien
*/

#include <iostream>
#include "games/nibbler/Nibbler.hpp"

Nibbler::Nibbler()
  :AGame()
{
  sizeX = WIDTH;
  sizeY = HEIGHT;
  initMap();
  initSnake();
  food = new t_food;
  food->coordinates = new t_coordinates;
  food->points = POINTS;
  geneFood();
  actions = new char[NB_MOVES];
  actions[0] = 'z';
  actions[1] = 'q';
  actions[2] = 's';
  actions[3] = 'd';
  lastAction = 'd';
  moves = new std::vector<methodPointer_t>;
  moves->push_back(&Nibbler::moveUp);
  moves->push_back(&Nibbler::moveLeft);
  moves->push_back(&Nibbler::moveDown);
  moves->push_back(&Nibbler::moveRight);
  lastMove = &Nibbler::moveRight;
  display();
  score = 0;
}

Nibbler::~Nibbler()
{
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
  t_snakePosition	*body;

  snake = new std::vector<t_snakePosition *>;
  for (int it = 0; it < 4; ++it)
    {
      body = new t_snakePosition;
      body->coordinates = new t_coordinates;
      body->coordinates->y = (sizeY / 2) + 1;
      body->coordinates->x = ((sizeX / 2) + 1) - it;
      if (it == 0)
	body->part = Snake::HEAD;
      else if (it == 3)
	body->part = Snake::TAIL;
      else
	body->part = Snake::BODY;
      map[body->coordinates->y][body->coordinates->x] = SNAKE;
      snake->push_back(body);
    }
}

void			Nibbler::geneFood()
{
  int			y = 0;
  int			x = 0;

  while (map[y][x] != EMPTY)
    {
      x = (rand() % sizeX);
      y = (rand() % sizeY);
    }
  map[y][x] = FOOD;
}

int			Nibbler::play(char move)
{
  long int		time = std::time(0) * 1000;
  int			timeDiff;
  int			nbMoves;
  int			index;
  int			move_index;
  char			tyle;

  if ((time - this->previousTime) < 250)
    return (score);
  timeDiff = time - this->previousTime;
  this->previousTime = time;
  move_index = 0;
  index = snake->size() - 1;
  map[snake->at(index)->coordinates->y][snake->at(index)->coordinates->x] = EMPTY;

  delete snake->at(index)->coordinates;
  while (index > 0)
    {
      snake->at(index)->coordinates = snake->at(index - 1)->coordinates;
      --index;
    }

  snake->at(index)->coordinates = new t_coordinates;
  snake->at(index)->coordinates->x = snake->at(index + 1)->coordinates->x;
  snake->at(index)->coordinates->y = snake->at(index + 1)->coordinates->y;

  while (actions[move_index] != move && move_index < NB_MOVES)
    ++move_index;

  if (move_index < NB_MOVES)
    (this->*(moves->at(move_index)))();
  else
    (this->*lastMove)();

  tyle = map[snake->at(0)->coordinates->y][snake->at(0)->coordinates->x];
  if (tyle == BORDER || tyle == SNAKE)
    return (1);
  map[snake->at(0)->coordinates->y][snake->at(0)->coordinates->x] = SNAKE;
  display();
  return (0);
}

void				Nibbler::moveUp()
{
  if (lastAction == 'd' || lastAction == 'q' || lastAction == 'z')
    {
      snake->at(0)->coordinates->y -= 1;
      lastAction = 'z';
      lastMove = &Nibbler::moveUp;
    }
  else
    (this->*lastMove)();
}

void				Nibbler::moveLeft()
{
  if (lastAction == 'z' || lastAction == 's' || lastAction == 'q')
    {
      snake->at(0)->coordinates->x -= 1;
      lastAction = 'q';
      lastMove = &Nibbler::moveLeft;
    }
  else
    (this->*lastMove)();
}

void				Nibbler::moveDown()
{
  if (lastAction == 'q' || lastAction == 'd' || lastAction == 's')
    {
      snake->at(0)->coordinates->y += 1;
      lastAction = 's';
      lastMove = &Nibbler::moveDown;
    }
  else
    (this->*lastMove)();
}

void				Nibbler::moveRight()
{
  if (lastAction == 'z' || lastAction == 's' || lastAction == 'd')
    {
      snake->at(0)->coordinates->x += 1;
      lastAction = 'd';
      lastMove = &Nibbler::moveRight;
    }
  else
    (this->*lastMove)();
}

void				Nibbler::display()
{
  for (int i = 0; i < sizeY; ++i)
    {
      for (int n = 0; n < sizeX; ++n)
	{
	  if (map[i][n] == BORDER)
	    std::cout << '|';
	  else if (map[i][n] == EMPTY)
	    std::cout << ' ';
	  else if (map[i][n] == FOOD)
	    std::cout << 'x';
	  else
	    std::cout << 'o';
	}
      std::cout << std::endl;
    }
  for (unsigned int i = 0; i < snake->size(); i++)
    {
      std::cout << snake->at(i)->coordinates->y << ", "
		<< snake->at(i)->coordinates->x << std::endl;
    }
}


extern "C"
{
  IGame			*getInstance() {return (new Nibbler); }
}

