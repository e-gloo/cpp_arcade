#ifndef LAUNCHER_HPP_
# define LAUNCHER_HPP_

#include <string>
#include <vector>
#include <dlfcn.h>
#include <cstdlib>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <curses.h>
#include "display/IDisplayManager.hpp"
#include "games/IGame.hpp"

class Launcher
{
  std::string			_lib;
  void				*_libHandle;
  void				*_gameHandle;
  IDisplayManager		*_graphLib;
  IGame				*_game;
  std::vector<std::pair<std::string, bool> >	_games;
  std::string			_player;
  int				_lastScore;
  std::string			_lastGame;

  std::vector<std::pair<std::string, int> >	getScores(std::string const &game);
  std::string			getShortName(std::string const &name) const;
  void		loadGame(std::string const &path);
  void		display(WINDOW *);
  void		changeCursor(int);
  void		launchGame();
  void		loadGraphLibrary(std::string const &path);

public:
  Launcher(std::string const&player, std::string const &lib);
  virtual ~Launcher();

  void		initGamesFolder();
  void		displayMenu();
};

#endif
