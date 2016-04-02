/*
** Pacman.cpp for Pacman in /home/coodie_d/rendu/cpp/B4/cpp_arcade/srcs/games/pacman
** 
** Made by Dylqn Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Fri Apr  1 00:14:50 2016 Dylqn Coodien
** Last update Sat Apr  2 03:53:15 2016 Dylqn Coodien
*/

#include <unistd.h>
#include "games/pacman/Pacman.hpp"

Pacman::Pacman()
  :AGame()
{
  sizeX = WIDTH;
  sizeY = HEIGHT;
  setMap();
  setPacman();
  setGhosts();
  setActions();
  setMoves();
  _score = 0;
  _megaPacgumEffect = false;
  _startGhostsTime = std::clock();
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
  _pacman->y = 18;
  _pacman->x = 16;
  map[_pacman->y][_pacman->x] = PACMAN;
}

void				Pacman::setGhosts()
{
  _ghosts = new std::vector<Pacman::Ghosts *>;
  for (int index = 0; index < NB_GHOSTS; ++index)
    {
    _ghosts->push_back(new Ghosts(Pacman::Ghosts::GhostsMode::BASIC, GHOSTS_INDEX
				  + index, Pacman::Ghosts::GhostsDirection::UP));
    _ghosts->at(index)->setPositions(14 + index, 16);
    map[16][14 + index] = GHOSTS_INDEX + index;
    }
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
  dis.setShape(0, "  map", 0xFFFFFFFF, "");
  dis.setShape(-1, "x bord", 0xFF00FF00, "");
  dis.setShape(1, ". pacgum", 0xFF000000, "./resources/pacman/coins.png");
  dis.setShape(2, "o megafood", 0xFF0000FF, "./resources/snake/food.png");
  dis.setShape(3, "  portal", 0xFFFFFFFF, "");
  dis.setShape(4, "C  pacman", 0xFF000000, "");
  dis.setShape(5, "T  ghost", 0xFFFF0000, "");
  dis.setShape(6, "T  ghost", 0xFF002EFF, "");
  dis.setShape(7, "T  ghost", 0xFFFF96E0, "");
  dis.setShape(8, "T  ghost", 0xFFFF8000, "");
  dis.startGame(*this);
}

int				Pacman::whichMoves(const char move)
{
  int			move_index;
  int			val;

 move_index = 0;

  while (_actions[move_index] != move && move_index < NB_MOVES)
    ++move_index;

  if (move_index < NB_MOVES)
    val = (this->*(_moves->at(move_index)))();
  else
    val = (this->*_lastMove)();

  if (val == 3)
    return (1);
  return (0);
}

int				Pacman::moveGhosts(const std::clock_t time)
{
  if (((time - _startGhostsTime) / (double)(CLOCKS_PER_SEC / 1000)) >= EFFECT_TIME)
    {
      for (int index = 0; index < NB_GHOSTS; ++index)
	{
	  if (_ghosts->at(index)->move(map) != 0)
	    return (1);
	}
    }

  if (_megaPacgumEffect &&
      ((time - _effectTime) / (double)(CLOCKS_PER_SEC / 1000)) >= EFFECT_TIME)
    {
      _megaPacgumEffect = false;
      for (int index = 0; index < NB_GHOSTS; ++index)
	{
	  if (_ghosts->at(index)->getGhostsMode() == Ghosts::GhostsMode::RUNAWAY)
	    _ghosts->at(index)->setGhostsMode(Ghosts::GhostsMode::BASIC);
	}
    }
  return (0);
}

int				Pacman::play(char move)
{
  std::clock_t		time = std::clock();

  if (move != -1)
    this->_action = move;
  if (((time - this->previousTime) / (double)(CLOCKS_PER_SEC / 1000)) < MIN_TIME)
    return (0);
  if (move == -1)
    move = _action;

  if (whichMoves(move) == 1)
    return (1);

  if (moveGhosts(time) != 0)
    return (1);

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

  if ((returnVal = move(_pacman->y -1, _pacman->x)) == 1
      && _lastMove != &Pacman::moveUp)
    return ((this->*_lastMove)());
  else if (returnVal == 1 && _lastMove == &Pacman::moveUp)
    return (returnVal);
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

  if ((returnVal = move(_pacman->y, _pacman->x - 1)) == 1
      && _lastMove != &Pacman::moveLeft)
    return ((this->*_lastMove)());
  else if (returnVal == 1 && _lastMove == &Pacman::moveLeft)
    return (returnVal);
  _lastMove = &Pacman::moveLeft;
  if (returnVal == 0)
    {
      if (_pacman->x == 0 || _pacman->x == WIDTH - 1)
	map[_pacman->y][_pacman->x] = PORTAL;
      else
	map[_pacman->y][_pacman->x] = EMPTY_SPACE;
      _pacman->x -= 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  else if (returnVal == 2)
    {
      map[_pacman->y][_pacman->x] = PORTAL;
      _pacman->x = WIDTH - 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  return (returnVal);
}

int				Pacman::moveDown()
{
  int			returnVal = 0;

  if ((returnVal = move(_pacman->y + 1, _pacman->x)) == 1
      && _lastMove != &Pacman::moveDown)
    return ((this->*_lastMove)());
  else if (returnVal == 1 && _lastMove == &Pacman::moveDown)
    return (returnVal);
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

  if ((returnVal = move(_pacman->y, _pacman->x + 1)) == 1
      && _lastMove != &Pacman::moveRight)
    return ((this->*_lastMove)());
  else if (returnVal == 1 && _lastMove == &Pacman::moveRight)
    return (returnVal);
  _lastMove = &Pacman::moveRight;
  if (returnVal == 0)
    {
      if (_pacman->x == 0 || _pacman->x == WIDTH - 1)
	map[_pacman->y][_pacman->x] = PORTAL;
      else
	map[_pacman->y][_pacman->x] = EMPTY_SPACE;
      _pacman->x += 1;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  else if (returnVal == 2)
    {
      map[_pacman->y][_pacman->x] = PORTAL;
      _pacman->x = 0;
      map[_pacman->y][_pacman->x] = PACMAN;
    }
  return (returnVal);
}

int				Pacman::move(const int y, const int x)
{
  if (map[y][x] == PACGUM)
    _score += POINTS;
  else if (map[y][x] == MEGA_PACGUM)
    {
      _megaPacgumEffect = true;
      _effectTime = std::clock();
      for (int index = 0; index < NB_GHOSTS; ++index)
	_ghosts->at(index)->setGhostsMode(Pacman::Ghosts::GhostsMode::RUNAWAY);
      _score += MEGA_POINTS;
    }
  else if (map[y][x] == BORDER)
    return (1);
  else if (map[y][x] >= GHOSTS_INDEX)
    return (againstGhosts(y, x));
  else if (x == WIDTH || x == -1)
    return (2);
  return (0);
}

int				Pacman::againstGhosts(const int y, const int x)
{
  int	index = 0;
  while (_ghosts->at(index)->getMapIndex() != map[y][x])
    ++index;
  if (_ghosts->at(index)->getGhostsMode() == Ghosts::GhostsMode::BASIC)
    return (3);
  else if (_ghosts->at(index)->getGhostsMode() == Ghosts::GhostsMode::RUNAWAY)
    {
      _ghosts->at(index)->setGhostsMode(Ghosts::GhostsMode::EYESREMAINING);
      _score += MEGA_PACGUM;
    }
  return (1);
}

Pacman::Ghosts::Ghosts(const GhostsMode &mode, const int &mapIndex,
		       const GhostsDirection &direction)
  :_mode(mode), _mapIndex(mapIndex), _direction(direction), _positions(NULL),
   _prevTyle(EMPTY_SPACE)
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

int				Pacman::Ghosts::move(char *map[32])
{
  int			val = 0;

  if (_direction == GhostsDirection::UP)
    {
      if ((val = moveUp(map)) == 1)
	val = leftOrRight(map);
    }
  else if (_direction == GhostsDirection::DOWN)
    {
      if ((val = moveDown(map)) == 1)
	val = leftOrRight(map);
    }
  else if (_direction == GhostsDirection::LEFT)
    {
      if ((val = moveLeft(map)) == 1)
	val = upOrDown(map);
    }
  else if (_direction == GhostsDirection::RIGHT)
    {
      if ((val = moveRight(map)) == 1)
	val = upOrDown(map);
    }
  if (_prevTyle == PACMAN)
    return (-1);
  if (_prevTyle >= GHOSTS_INDEX)
    _prevTyle = EMPTY_SPACE;
  return (val);
}

int				Pacman::Ghosts::moveUp(char *map[32])
{
  if (map[_positions->y - 1][_positions->x] != BORDER)
    {
      map[_positions->y][_positions->x] = _prevTyle;
      _prevTyle = map[_positions->y - 1][_positions->x];
      map[_positions->y - 1][_positions->x] = _mapIndex;
      _positions->y -= 1;
      _direction = GhostsDirection::UP;
      return (0);
    }
  return (1);
 }

int				Pacman::Ghosts::moveDown(char *map[32])
{
  if (map[_positions->y + 1][_positions->x] != BORDER)
    {
      map[_positions->y][_positions->x] = _prevTyle;
      _prevTyle = map[_positions->y + 1][_positions->x];
      map[_positions->y + 1][_positions->x] = _mapIndex;
      _positions->y += 1;
      _direction = GhostsDirection::DOWN;
      return (0);
    }
  return (1);
}

int				Pacman::Ghosts::moveLeft(char *map[32])
{
  if (map[_positions->y][_positions->x - 1] != BORDER)
    {
      map[_positions->y][_positions->x] = _prevTyle;
      _prevTyle = map[_positions->y][_positions->x - 1];
      map[_positions->y + 1][_positions->x - 1] = _mapIndex;
      _positions->x -= 1;
      _direction = GhostsDirection::LEFT;
      return (0);
    }
  return (1);
}

int				Pacman::Ghosts::moveRight(char *map[32])
{
  if (map[_positions->y][_positions->x + 1] != BORDER)
    {
      map[_positions->y][_positions->x] = _prevTyle;
      _prevTyle = map[_positions->y][_positions->x + 1];
      map[_positions->y + 1][_positions->x + 1] = _mapIndex;
      _positions->x += 1;
      _direction = GhostsDirection::RIGHT;
      return (0);
    }
  return (1);
}

int				Pacman::Ghosts::leftOrRight(char *map[32])
{
  int			random = rand() % 2;
  int			val = 0;

  if (random == 0 && (val = moveLeft(map)) != 0)
    val = moveRight(map);
  return (val);
}

int				Pacman::Ghosts::upOrDown(char *map[32])
{
  int			random = rand() % 2;
  int			val = 0;

  if (random == 0 && (val = moveUp(map)) != 0)
    val = moveDown(map);
  return (val);
}

extern "C"
{
  IGame			*getInstance() {return (new Pacman()); }
}
