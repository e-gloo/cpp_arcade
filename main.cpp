#include <dlfcn.h>
#include <cstdlib>
#include <iostream>
#include "display/IDisplayManager.hpp"
#include "games/IGame.hpp"

int	main(int ac, char **av)
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

  std::cout << "test2" << std::endl;

  if ((dlghandle = dlopen(av[2], RTLD_LAZY)) == NULL)
    exit(1);

  std::cout << "test1" << std::endl;

  creator = reinterpret_cast<IDisplayManager * (*)()>(dlsym(dlhandle, "getInstance"));
  if (creator == NULL)
    exit(1);
  IDisplayManager *manager = creator();

  gcreator = reinterpret_cast<IGame * (*)()>(dlsym(dlghandle, "getInstance"));
  if (gcreator == NULL)
    exit(1);
  IGame *game = gcreator();

  std::cout << "test" << std::endl;

  manager->startGame(*game, "");

  delete manager;
  delete game;
  dlclose(dlhandle);
  dlclose(dlghandle);
  (void)ac;
}
