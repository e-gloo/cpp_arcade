/*
** Pacman.cpp for Pacman in /home/coodie_d/rendu/cpp/B4/cpp_arcade/srcs/games/pacman
** 
** Made by Dylqn Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Fri Apr  1 00:14:50 2016 Dylqn Coodien
** Last update Fri Apr  1 01:59:51 2016 Dylqn Coodien
*/

Pacman::Pacman()
  :AGame()
{
  sizeX = WIDTH;
  sizeY = HEIGHT;
  initMap();
  initPacman();
  initGhost();
  actions = new char[NB_MOVES];
  actions[0] = 'z';
  actions[1] = 'q';
  actions[2] = 's';
  actions[3] = 'd';
  lastAction = 'q';
  moves = new std::vector<methodPointer_t>;
  moves->push_back(&Pacman::moveUp);
  moves->push_back(&Pacman::moveLeft);
  moves->push_back(&Pacman::moveDown);
  moves->push_back(&Pacman::moveRight);
  lastMove = &Pacman::moveLeft;
  score = 0;
}

Pacman::~Pacman()
{
}

void			Pacman::initMap()
{
  map = new char*[sizeY];
  for (int y = 0; y < sizeY, ++y)
    {
      map[y] = new char[sizeX];
      for (int x = 0; x < sizeX; +=x)
	map[y][x] = _map[y][x];
    }
}
