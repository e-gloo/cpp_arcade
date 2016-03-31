/*
** Nibbler.cpp for Nibbler in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 14:59:35 2016 Dylan Coodien
** Last update Thu Mar 31 23:12:24 2016 Dylqn Coodien
*/

#include <unistd.h>
#include "games/nibbler/Nibbler.hpp"
#include "Protocol.hpp"

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
	    map[y][x] = EMPT;
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

  while (map[y][x] != EMPT)
    {
      x = (rand() % sizeX);
      y = (rand() % sizeY);
    }
  map[y][x] = FOOD;
}

std::vector<t_snakePosition *>		*Nibbler::getSnake() const
{
  return (this->snake);
}

void					Nibbler::startGame(IDisplayManager &dis)
{
  dis.createWindow(WIDTH, HEIGHT, "Nibbler");
  dis.setShape(0, "  map", 0xFF000000, "");
  dis.setShape(-1, "X bord", 0xFF00FF00, "");
  dis.setShape(1, "o snake", 0xFFFFFFFF, "");
  dis.setShape(2, ". food", 0xFF0000FF, "");
  dis.startGame(*this);
}

int			Nibbler::play(char move)
{
  std::clock_t		time = std::clock();
  int			timeDiff;
  int			nbMoves;
  int			index;
  int			move_index;
  char			tyle;

  if (move != -1)
    this->action = move;
  if (((time - this->previousTime) / (double)(CLOCKS_PER_SEC / 1000)) < MIN_TIME)
    return (0);
  this->previousTime = time;
  if (move == -1)
    move = action;

  move_index = 0;
  index = snake->size() - 1;
  int	save_x = snake->at(index)->coordinates->x;
  int	save_y = snake->at(index)->coordinates->y;

  while (index > 0)
    {
      snake->at(index)->coordinates->x = snake->at(index - 1)->coordinates->x;
      snake->at(index)->coordinates->y = snake->at(index - 1)->coordinates->y;
      --index;
    }

  while (actions[move_index] != move && move_index < NB_MOVES)
    ++move_index;

  if (move_index < NB_MOVES)
    (this->*(moves->at(move_index)))(save_x, save_y);
  else
    (this->*lastMove)(save_x, save_y);

  tyle = map[snake->at(0)->coordinates->y][snake->at(0)->coordinates->x];
  if (tyle == BORDER || tyle == SNAKE)
    return (1);
  map[snake->at(0)->coordinates->y][snake->at(0)->coordinates->x] = SNAKE;
  return (0);
}

void				Nibbler::moveUp(int save_x, int save_y)
{
  int	x = snake->at(0)->coordinates->x;
  int	y = snake->at(0)->coordinates->y;

  if (lastAction == 'd' || lastAction == 'q' || lastAction == 'z')
    {
      if (map[y - 1][x] == FOOD)
	{
	  snake->push_back(new t_snakePosition);
	  snake->at(snake->size() - 1)->coordinates = new t_coordinates;
	  snake->at(snake->size() - 1)->coordinates->y = save_y;
	  snake->at(snake->size() - 1)->coordinates->x = save_x;
	  snake->at(snake->size() - 1)->part = Snake::TAIL;
	  snake->at(snake->size() - 2)->part = Snake::BODY;
	  geneFood();
	}
      else
	map[save_y][save_x] = EMPT;
      snake->at(0)->coordinates->y -= 1;
      lastAction = 'z';
      lastMove = &Nibbler::moveUp;
    }
  else
    (this->*lastMove)(save_x, save_y);
}

void				Nibbler::moveLeft(int save_x, int save_y)
{
  int	x = snake->at(0)->coordinates->x;
  int	y = snake->at(0)->coordinates->y;

  if (lastAction == 'z' || lastAction == 's' || lastAction == 'q')
    {
      if (map[y][x - 1] == FOOD)
	{
	  snake->push_back(new t_snakePosition);
	  snake->at(snake->size() - 1)->coordinates = new t_coordinates;
	  snake->at(snake->size() - 1)->coordinates->y = save_y;
	  snake->at(snake->size() - 1)->coordinates->x = save_x;
	  snake->at(snake->size() - 1)->part = Snake::TAIL;
	  snake->at(snake->size() - 2)->part = Snake::BODY;
	  geneFood();
	}
      else
	map[save_y][save_x] = EMPT;
      snake->at(0)->coordinates->x -= 1;
      lastAction = 'q';
      lastMove = &Nibbler::moveLeft;
    }
  else
    (this->*lastMove)(save_x, save_y);
}

void				Nibbler::moveDown(int save_x, int save_y)
{
  int	x = snake->at(0)->coordinates->x;
  int	y = snake->at(0)->coordinates->y;

  if (lastAction == 'q' || lastAction == 'd' || lastAction == 's')
    {
      if (map[y + 1][x] == FOOD)
	{
	  snake->push_back(new t_snakePosition);
	  snake->at(snake->size() - 1)->coordinates = new t_coordinates;
	  snake->at(snake->size() - 1)->coordinates->y = save_y;
	  snake->at(snake->size() - 1)->coordinates->x = save_x;
	  snake->at(snake->size() - 1)->part = Snake::TAIL;
	  snake->at(snake->size() - 2)->part = Snake::BODY;
	  geneFood();
	}
      else
	map[save_y][save_x] = EMPT;
      snake->at(0)->coordinates->y += 1;
      lastAction = 's';
      lastMove = &Nibbler::moveDown;
    }
  else
    (this->*lastMove)(save_x, save_y);
}

void				Nibbler::moveRight(int save_x, int save_y)
{
  int	x = snake->at(0)->coordinates->x;
  int	y = snake->at(0)->coordinates->y;

  if (lastAction == 'z' || lastAction == 's' || lastAction == 'd')
    {
      if (map[y][x + 1] == FOOD)
	{
	  snake->push_back(new t_snakePosition);
	  snake->at(snake->size() - 1)->coordinates = new t_coordinates;
	  snake->at(snake->size() - 1)->coordinates->y = save_y;
	  snake->at(snake->size() - 1)->coordinates->x = save_x;
	  snake->at(snake->size() - 1)->part = Snake::TAIL;
	  snake->at(snake->size() - 2)->part = Snake::BODY;
	  geneFood();
	}
      else
	map[save_y][save_x] = EMPT;
      snake->at(0)->coordinates->x += 1;
      lastAction = 'd';
      lastMove = &Nibbler::moveRight;
    }
  else
    (this->*lastMove)(save_x, save_y);
}

extern "C"
{
  IGame			*getInstance() {return (new Nibbler()); }

  void			whereAmI(std::vector<t_snakePosition *> *snake,
				 arcade::CommandType commands)
  {
    int			size = snake->size();
    arcade::WhereAmI	*moul = new arcade::WhereAmI + size *
      sizeof(arcade::Position);

    size = snake->size();
    moul->type = commands;
    moul->lenght = size;
    for (int t = 0; t < size; ++t)
      {
	moul->position[t].x = snake->at(t)->coordinates->x;
	moul->position[t].y = snake->at(t)->coordinates->y;
      }
    write(1, moul, sizeof(arcade::WhereAmI) + size * sizeof(arcade::Position));
  }

  void			getMap(arcade::CommandType commands)
  {
    arcade::GetMap	*get_map = new arcade::GetMap +
      (WIDTH * HEIGHT) * sizeof(arcade::TileType);

    get_map->width = WIDTH;
    get_map->height = HEIGHT;
    for (int t = 0; t < get_map->width * get_map->height; ++t)
      get_map->tile[t] = arcade::TileType::EMPTY;
    get_map->type = commands;
    write(1, get_map, sizeof(arcade::GetMap) +
	  (WIDTH * HEIGHT) * sizeof(arcade::TileType));
  }

  void					Play(void)
  {
    arcade::CommandType			commands;
    Nibbler				*nibbler = new Nibbler;
    std::vector<t_snakePosition *>	*snake = nibbler->getSnake();
    arcade::CommandType			lastOne = arcade::CommandType::GO_FORWARD;
    std::map<arcade::CommandType, char>	Hmap;

    Hmap[arcade::CommandType::GO_UP] = 'z';
    Hmap[arcade::CommandType::GO_DOWN] = 's';
    Hmap[arcade::CommandType::GO_LEFT] = 'q';
    Hmap[arcade::CommandType::GO_RIGHT] = 'd';
    Hmap[arcade::CommandType::GO_FORWARD] = 'a';
    while (read(0, &commands, sizeof(arcade::CommandType)))
      {
	if (commands == arcade::CommandType::GET_MAP)
	  getMap(commands);
	else if (commands == arcade::CommandType::WHERE_AM_I)
	  whereAmI(snake, commands);
	else if (commands == arcade::CommandType::GO_UP ||
		 commands == arcade::CommandType::GO_DOWN ||
		 commands == arcade::CommandType::GO_LEFT ||
		 commands == arcade::CommandType::GO_RIGHT ||
		 commands == arcade::CommandType::GO_FORWARD)
	  lastOne = commands;
	else if (commands == arcade::CommandType::PLAY)
	  {
	    nibbler->play(Hmap[lastOne]);
	    snake = nibbler->getSnake();
	  }
      }
  }
}
