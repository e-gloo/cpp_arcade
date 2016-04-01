/*
** Pacman.cpp for Pacman in /home/coodie_d/rendu/cpp/B4/cpp_arcade/srcs/games/pacman
** 
** Made by Dylqn Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Fri Apr  1 00:14:50 2016 Dylqn Coodien
** Last update Fri Apr  1 20:30:47 2016 Dylqn Coodien
*/

#include "games/pacman/Pacman.hpp"
#include <iostream>
#include <fstream>
Pacman::Pacman()
  :AGame()
{
  
  sizeX = WIDTH;
  sizeY = HEIGHT;
  setMap();
  //setPacman();
  //setGhosts();
  //setActions();
  _score = 0;
}

Pacman::~Pacman()
{
}

void				Pacman::setMap()
{
  map = new char*[sizeY];
  for (int y = 0; y < sizeY; ++y)
    {
      map[y] = new char[sizeX];
      for (int x = 0; x < sizeX; ++x)
	map[y][x] = map_[y][x];
    }
}

void				Pacman::setPacman()
{
  _pacman = new t_coordinates;
  _pacman->y = 15;
  _pacman->x = 15;
  map[_pacman->y][_pacman->x] = PACMAN;
}

void				Pacman::setGhosts()
{
  _ghosts = new std::vector<Pacman::Ghosts *>;
  for (int index = 0; index < NB_GHOSTS; ++index)
    _ghosts->push_back(new Ghosts(Pacman::Ghosts::GhostsMode::BASIC, GHOST_INDEX
				  + index, Pacman::Ghosts::GhostsDirection::START));
}

void				Pacman::setActions()
{
  _actions = new char[NB_MOVES];
  _actions[0] = 'z';
  _actions[1] = 'q';
  _actions[2] = 's';
  _actions[3] = 'd';
  _lastAction = 'q';
  _action = 'q';
}

void				Pacman::setMoves()
{
  _moves = new std::vector<methodPointer_t>;
  _moves->push_back(&Pacman::moveUp);
  _moves->push_back(&Pacman::moveLeft);
  _moves->push_back(&Pacman::moveDown);
  _moves->push_back(&Pacman::moveRight);
  _lastMove = &Pacman::moveLeft;
}

void				Pacman::startGame(IDisplayManager &dis, std::string const &player)
{
  (void)player;
  dis.createWindow(WIDTH, HEIGHT, "Pacman");
  dis.setShape(0, "  map", 0xFF000000, "");
  dis.setShape(-1, "x bord", 0xFF00FF00, "");
  dis.setShape(1, ". pacgum", 0xFF000000, "");
  dis.setShape(2, "o megafood", 0xFF0000FF, "./resources/snake/food.png");
  dis.setShape(3, "  portal", 0xFF0000FF, "");
  dis.setShape(4, "  pacman", 0xFFFFFFFF, "");
  dis.startGame(*this);
}

int				Pacman::play(char move)
{
  return (0);
  std::clock_t		time = std::clock();
  int			move_index;

  if (move != -1)
    this->_action = move;
  if (((time - this->previousTime) / (double)(CLOCKS_PER_SEC / 1000)) < MIN_TIME)
    return (0);
  if (move == -1)
    move = _action;

  move_index = 0;

  while (_actions[move_index] != move && move_index < NB_MOVES)
    ++move_index;

  if (move_index < NB_MOVES)
    (this->*(_moves->at(move_index)))();
  else
    (this->*_lastMove)();

  for (int index = 0; index < NB_GHOSTS; ++index)
    _ghosts->at(index)->move(map);

  this->previousTime = time;
  return (0);
}

int				Pacman::getScore() const
{
  return (_score);
}

int				Pacman::moveUp()
{
  int			returnVal = 0;

  if ((returnVal = move('d', 'q', 'z', _pacman->y - 1, _pacman->x)) < 0)
    return ((this->*_lastMove)());
  _lastMove = &Pacman::moveUp;
  if (returnVal == 0)
    {
      map[_pacman->y][_pacman->x] = EMPTY_SPACE;
      _pacman->y -= 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  return (returnVal);
}

int				Pacman::moveLeft()
{
  int			returnVal = 0;

  if ((returnVal = move('z', 's', 'q', _pacman->y, _pacman->x - 1)) < 0)
    return ((this->*_lastMove)());
  _lastMove = &Pacman::moveLeft;
  if (returnVal == 0)
    {
      map[_pacman->y][_pacman->x] = EMPTY_SPACE;
      _pacman->x -= 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  return (returnVal);
}

int				Pacman::moveDown()
{
  int			returnVal = 0;

  if ((returnVal = move('q', 'd', 's', _pacman->y + 1, _pacman->x)) < 0)
    return ((this->*_lastMove)());
  _lastMove = &Pacman::moveDown;
  if (returnVal == 0)
    {
      map[_pacman->y][_pacman->x] = EMPTY_SPACE;
      _pacman->y += 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  return (returnVal);
}

int				Pacman::moveRight()
{
  int			returnVal = 0;

  if ((returnVal = move('z', 's', 'd', _pacman->y, _pacman->x + 1)) < 0)
    return ((this->*_lastMove)());
  _lastMove = &Pacman::moveRight;
  if (returnVal == 0)
    {
      map[_pacman->y][_pacman->x] = EMPTY_SPACE;
      _pacman->x += 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  return (returnVal);
}

int				Pacman::move(const char lastact1, const char lastact2,
					     const char lastact3, const int y, const int x)
{
  if (_lastAction == lastact1 || _lastAction == lastact2 || _lastAction == lastact3)
    {
      if (map[y][x] == PACGUM)
	_score += POINTS;
      else if (map[y][x] == MEGA_PACGUM)
	{
	  for (int index = 0; index < NB_GHOSTS; ++index)
	    _ghosts->at(index)->setGhostsMode(Pacman::Ghosts::GhostsMode::RUNAWAY);
	  _score += MEGA_POINTS;
	}
      else if (map[y][x] == BORDER)
	return (1);
      _lastAction = lastact3;
      return (0);
    }
  return (-1);
}

Pacman::Ghosts::Ghosts(const GhostsMode &mode, const int &mapIndex,
		       const GhostsDirection &direction)
  :_mode(mode), _mapIndex(mapIndex), _direction(direction), _positions(NULL)
{
}

Pacman::Ghosts::~Ghosts()
{
}

void				Pacman::Ghosts::setGhostsMode(const GhostsMode &mode)
{
  _mode = mode;
}

Pacman::Ghosts::GhostsMode	Pacman::Ghosts::getGhostsMode() const
{
  return (_mode);
}

int				Pacman::Ghosts::getMapIndex() const
{
  return (_mapIndex);
}

void				Pacman::Ghosts::setGhostsDirection(const GhostsDirection &direction)
{
  _direction = direction;
}

Pacman::Ghosts::GhostsDirection	Pacman::Ghosts::getGhostsDirection() const
{
  return (_direction);
}

void				Pacman::Ghosts::setPositions(const int &x, const int &y)
{
  if (_positions == NULL)
    _positions = new t_coordinates;
  _positions->x = x;
  _positions->y = y;
}

t_coordinates			*Pacman::Ghosts::getPositions() const
{
  return (_positions);
}

void				Pacman::Ghosts::move(char *map[32])
{
  (void)map;
}

extern "C"
{
  IGame			*getInstance() {return (new Pacman()); }
}
