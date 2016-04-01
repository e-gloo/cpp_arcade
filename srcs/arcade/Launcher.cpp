#include "Launcher.hpp"

bool	orderScores(std::pair<std::string, int> a, std::pair<std::string, int> b)
{
  return (a.second > b.second);
}

Launcher::Launcher(std::string const &player, std::string const &lib) : _lib(lib), _libHandle(NULL), _gameHandle(NULL), _graphLib(NULL), _game(NULL), _games(), _player(player), _lastScore(-1), _lastGame("")
{
}

Launcher::~Launcher()
{
}

void		Launcher::loadGraphLibrary(std::string const &path)
{
  IDisplayManager*	(*creator)();

  if ((_libHandle = dlopen(path.c_str(), RTLD_LAZY)) == NULL)
    {
      std::cerr << path << std::endl;
      std::cerr << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }

  creator = reinterpret_cast<IDisplayManager * (*)()>(dlsym(_libHandle, "getInstance"));
  if (creator == NULL)
    exit(1);
  _graphLib = creator();
}

void		Launcher::loadGame(std::string const &path)
{
  IGame*		(*creator)();

  if ((_gameHandle = dlopen(path.c_str(), RTLD_LAZY)) == NULL)
    {
      std::cerr << path << std::endl;
      std::cerr << dlerror() << std::endl;
      exit(EXIT_FAILURE);
    }

  creator = reinterpret_cast<IGame * (*)()>(dlsym(_gameHandle, "getInstance"));
  _game = creator();
}

void		Launcher::initGamesFolder()
{
  std::string path = "./games/";
  DIR		*dir;
  dirent*	pdir;
  std::string file;
  std::pair<std::string, bool>	pair;

  if ((dir = opendir(path.c_str())) == NULL)
    return ;

  while ((pdir = readdir(dir)) != NULL)
    {
      file = pdir->d_name;
      if (file.find(".so") != std::string::npos)
	{
	  pair.first = file;
	  if (_games.empty())
	    pair.second = true;
	  else
	    pair.second = false;
	  _games.push_back(pair);
	}
    }
  closedir(dir);
}

void		Launcher::display(WINDOW *win)
{
  int		line;
  int		col;
  std::string	str;
  std::vector<std::pair<std::string, int> > scores;
  
  wattroff(win, A_STANDOUT);
  str = "Welcome to Arcade, " + _player + " !";
  mvwprintw(win, 0, 0, "%s", str.c_str());

  if (_lastScore != -1)
    {
      str = "Last game : " + getShortName(_lastGame) + " => Score : " + std::to_string(_lastScore) + "        ";;
      mvwprintw(win, 1, 0, "%s", str.c_str());
    }
  col = 0;
  for (std::vector<std::pair<std::string,bool> >::iterator it = _games.begin(); it != _games.end(); ++it)
    {
      line = 2;
      if (it->second == true)
	wattron(win, A_STANDOUT);
      else
	wattroff(win, A_STANDOUT);
      str = getShortName(it->first);
      mvwprintw(win, line, col, "%s", str.c_str());
      wattroff(win, A_STANDOUT);
      scores = getScores(it->first);
      line++;
      mvwprintw(win, line, col, "%s", "Best scores :");
      line++;
      for (unsigned int i = 0; i < 5; ++i)
	{
	  if (i < scores.size())
	    {
	      str = std::to_string(i+1) + ") " + scores.at(i).first + " " + std::to_string(scores.at(i).second);
	      mvwprintw(win, line, col, "%s", str.c_str());
	      ++line;
	    }
	}
      col += 30;
    }

  wrefresh(win);
}

void		Launcher::changeCursor(int i)
{
  int		j;

  j = 0;
  while (j < (int)_games.size())
    {
      if (_games.at(j).second == true && (j + i) >= 0 && (j + i) < (int)_games.size())
	{
	  _games.at(j).second = false;
	  _games.at(j+i).second = true;
	}
      ++j;
    }
}

void		Launcher::launchGame()
{
  std::string	game;

  for (std::vector<std::pair<std::string, bool> >::iterator it = _games.begin(); it != _games.end() ; ++it)
    {
      if (it->second == true)
	{
	  loadGame("./games/" + it->first);
	  _lastGame = it->first;
	}
    }
  loadGraphLibrary(_lib);
  _game->startGame(*_graphLib);
  _lastScore = _game->getScore();
  delete _game;
  delete _graphLib;
  dlclose(_libHandle);
  dlclose(_gameHandle);
  _libHandle = NULL;
  _gameHandle = NULL;
  noecho();
  clear();
}

void		Launcher::displayMenu()
{
  WINDOW	*win;
  int		key;

  initscr();

  if ((win = newwin(30, 30 * _games.size(), 0, 0)) == NULL)
    exit(EXIT_FAILURE);

  noecho();
  nodelay(win, 1);
  keypad(win, TRUE);
  curs_set(0);

  while ((key = wgetch(win)) != 27)
    {
      if (key == 'q')
	changeCursor(-1);
      else if (key == 'd')
	changeCursor(1);
      else if (key == ' ')
	launchGame();
      display(win);
    }

  nodelay(win, 0);
  echo();
  delwin(win);
  endwin();
}

std::vector<std::pair<std::string, int> >	Launcher::getScores(std::string const &game)
{
  std::vector<std::pair<std::string, int> >	scores;
  std::string			file;
  size_t			idx;
  std::ifstream			filestream;
  std::string			str;

  file = game;
  if ((idx = game.find(".so")) != std::string::npos)
    file.replace(idx, 3, ".scores");
  file = "./scores/" + file;

  filestream.open(file);
  while (std::getline(filestream, str))
    {
      std::pair<std::string, int> pair;
      idx = str.find(":");
      pair.first = str.substr(0, idx);
      pair.second = std::stoi(str.substr(idx + 1));
      scores.push_back(pair);
    }

  std::sort(scores.begin(), scores.end(), orderScores);

  return (scores);
}

std::string			Launcher::getShortName(std::string const &game) const
{
  std::string			name;

  name = game.substr(11);
  std::string::size_type i = name.find(".so");

  if (i != std::string::npos)
    name.erase(i, 3);
  return (name);
}
