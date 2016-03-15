#include <dlfcn.h>
#include <cstdlib>
#include "display/IDisplayManager.hpp"

int	main(int ac, char **av)
{
  void	*dlhandle;
  IDisplayManager* (*creator)();

  dlhandle = dlopen(av[1], RTLD_NOW);
  if (dlhandle == NULL)
    exit(1);

  creator = reinterpret_cast<IDisplayManager * (*)()>(dlsym(dlhandle, "getInstance"));
  if (creator == NULL)
    exit(1);
  IDisplayManager *manager = creator();
  delete manager;
  (void)ac;
}
