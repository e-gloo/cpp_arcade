/*#include <dlfcn.h>
#include <cstdlib>
#include <iostream>
#include "display/IDisplayManager.hpp"
#include "games/IGame.hpp"
*/

#include "Launcher.hpp"

/*int	main(int ac, char **av)
{
  void	*dlhandle;
  void	*dlghandle;
  IDisplayManager* (*creator)();
  IGame		 * (*gcreator)();

  dlhandle = dlopen(av[1], RTLD_LAZY);
  if (dlhandle == NULL)
    {
      std::cout << av[1] << std::endl;
      std::cout << dlerror() << std::endl;
      exit(1);
    }

  if ((dlghandle = dlopen(av[2], RTLD_LAZY)) == NULL)
    exit(1);

  creator = reinterpret_cast<IDisplayManager * (*)()>(dlsym(dlhandle, "getInstance"));
  if (creator == NULL)
    exit(1);
  IDisplayManager *manager = creator();

  gcreator = reinterpret_cast<IGame * (*)()>(dlsym(dlghandle, "getInstance"));
  if (gcreator == NULL)
    exit(1);
  IGame *game = gcreator();

  game->startGame(*manager);

  delete manager;
  delete game;
  dlclose(dlhandle);
  dlclose(dlghandle);
  (void)ac;
}
*/

static std::string	getPlayerName()
{
  char		name[256];
  std::string	str;

  std::cout << "Please enter your name (10 char Max) : ";
  std::cin.getline(name, 256);
  str = name;
  str.erase(10);
  return (str);
}

int	main(int ac, char **av)
{

  std::string	str;

  if (ac >= 2)
    {
      str = getPlayerName();
      Launcher	launch(str, av[1]);
      launch.initGamesFolder();
      launch.displayMenu();
    }
  return (0);
}
