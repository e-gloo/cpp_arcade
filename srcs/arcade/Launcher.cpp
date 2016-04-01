#include "Launcher.hpp"

Launcher::Launcher(std::string const &player) : _libHandle(NULL), _gameHandle(NULL), _graphLib(NULL), _game(NULL), _games(), _player(player), _lastScore(-1), _lastGame("")
{
}

Launcher::~Launcher()
{
  if (_libHandle != NULL)
    dlclose(_libHandle);
  if (_gameHandle != NULL)
    dlclose(_gameHandle);
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

  if ((dir = opendir(path.c_str())) == NULL)
    return ;

  while ((pdir = readdir(dir)) != NULL)
    {
      file = pdir->d_name;
      if (file.find(".so") != std::string::npos)
	{
	  _games.push_back(file);
	  std::cout << pdir->d_name << std::endl;
	}
    }
  closedir(dir);
}

void		Launcher::displayMenu()
{

}

std::vector<std::pair<std::string, int> >	Launcher::getScores(std::string const &game)
{
  std::vector<std::pair<std::string, int> >	scores;
  std::string			file;
  size_t			idx;

  file = game;
  if ((idx = game.find(".so")) != std::string::npos)
    file.replace(idx, 3, ".scores");
  file = "./scores/" + file;


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
