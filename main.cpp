#include <dlfcn.h>
#include <cstdlib>
#include "display/IDisplayManager.hpp"

int	main(int ac, char **av)
{
  void	*dlhandle;
  void	*dlghandle;
  IDisplayManager* (*creator)();
  IGame		 * (*gcreator)();

  dlhandle = dlopen(av[1], RTLD_NOW);
  if (dlhandle == NULL)
    exit(1);

  if ((dlghandle = dlopen(av[2], RTLD_NOW)) == NULL)
    exit(1);

  creator = reinterpret_cast<IDisplayManager * (*)()>(dlsym(dlhandle, "getInstance"));
  if (creator == NULL)
    exit(1);
  IDisplayManager *manager = creator();

  gcreator = reinterpret_cast<IGame * (*)()>(dlsym(dlghandle, "getInstance"));
  if (gcreator == NULL)
    exit(1);
  IGame *game = gcreator();

  delete manager;
  (void)ac;
}
