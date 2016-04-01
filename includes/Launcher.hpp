#ifndef LAUNCHER_HPP_
# define LAUNCHER_HPP_

#include <string>
#include <vector>
#include <dlfcn.h>
#include <cstdlib>
#include <dirent.h>
#include <iostream>
#include "display/IDisplayManager.hpp"
#include "games/IGame.hpp"

class Launcher
{
  void				*_libHandle;
  void				*_gameHandle;
  IDisplayManager		*_graphLib;
  IGame				*_game;
  std::vector<std::string>	_games;
  std::string			_player;
  int				_lastScore;
  std::string			_lastGame;

  std::vector<std::pair<std::string, int> >	getScores(std::string const &game);
  std::string			getShortName(std::string const &name) const;

public:
  Launcher(std::string const&player);
  virtual ~Launcher();

  void		loadGraphLibrary(std::string const &path);
  void		loadGame(std::string const &path);
  void		initGamesFolder();
  void		displayMenu();
};

#endif
