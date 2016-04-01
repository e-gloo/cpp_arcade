/*
** Pacman.hpp for Pacman in /home/coodie_d/rendu/cpp/B4/cpp_arcade
** 
** Made by Dylqn Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Fri Apr  1 00:25:45 2016 Dylqn Coodien
** Last update Fri Apr  1 20:29:47 2016 Dylqn Coodien
*/

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include <vector>
# include <algorithm>
# include "games/AGame.hpp"
# include "display/IDisplayManager.hpp"
# include "Protocol.hpp"

# define NB_MOVES	4

# define BORDER		-1
# define EMPTY_SPACE	0
# define PACGUM		1
# define MEGA_PACGUM	2
# define PORTAL		3
# define PACMAN		4

# define POINTS		25
# define MEGA_POINTS	100

# define WIDTH		32
# define HEIGHT		32

# define MIN_TIME	100

# define NB_GHOSTS	4

# define GHOST_INDEX	5

typedef struct	s_coordinates
{
  int		x;
  int		y;
}		t_coordinates;

class Pacman: public AGame
{
  class Ghosts
  {
  public:
    enum GhostsMode
      {
	BASIC = 0,
	RUNAWAY,
	EYESREMAINING
      };

    enum GhostsDirection
      {
	START = 3,
	UP,
	DOWN,
	LEFT,
	RIGHT
      };

  private:
    GhostsMode		_mode;
    int			_mapIndex;
    GhostsDirection	_direction;
    t_coordinates	*_positions;

  public:
    Ghosts(const GhostsMode &mode, const int &mapIndex, const GhostsDirection &direction);
    ~Ghosts();
    void		setGhostsMode(const GhostsMode &mode);
    GhostsMode		getGhostsMode() const;
    int			getMapIndex() const;
    void		setGhostsDirection(const GhostsDirection &direction);
    GhostsDirection	getGhostsDirection() const;
    void		setPositions(const int &x, const int &y);
    t_coordinates	*getPositions() const;
    void		move(char *map[32]);
  };

  char			map_[HEIGHT][WIDTH] =
    {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,02,-1,00,00,-1,01,-1,00,00,00,-1,01,-1,-1,01,-1,00,00,00,-1,01,-1,00,00,-1,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,02,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,-1,-1,01,01,01,01,-1,-1,01,01,01,01,-1,-1,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,00,-1,-1,00,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1},
     {00,00,00,00,00,00,00,-1,01,-1,-1,-1,-1,-1,00,-1,-1,00,-1,-1,-1,-1,-1,01,-1,00,00,00,00,00,00,00},
     {00,00,00,00,00,00,00,-1,01,-1,-1,00,00,00,00,00,00,00,00,00,00,-1,-1,01,-1,00,00,00,00,00,00,00},
     {00,00,00,00,00,00,00,-1,01,-1,-1,00,-1,-1,-1,00,00,-1,-1,-1,00,-1,-1,01,-1,00,00,00,00,00,00,00},
     {-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,00,-1,00,00,00,00,00,00,-1,00,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1},
     {03,00,00,00,00,00,00,00,01,00,00,00,-1,00,00,00,00,00,00,-1,00,00,00,01,00,00,00,00,00,00,00,03},
     {-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,00,-1,00,00,00,00,00,00,-1,00,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1},
     {00,00,00,00,00,00,00,-1,01,-1,-1,00,-1,-1,-1,-1,-1,-1,-1,-1,00,-1,-1,01,-1,00,00,00,00,00,00,00},
     {00,00,00,00,00,00,00,-1,01,-1,-1,00,00,00,00,00,00,00,00,00,00,-1,-1,01,-1,00,00,00,00,00,00,00},
     {00,00,00,00,00,00,00,-1,01,-1,-1,00,-1,-1,-1,-1,-1,-1,-1,-1,00,-1,-1,01,-1,00,00,00,00,00,00,00},
     {-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,00,-1,-1,-1,-1,-1,-1,-1,-1,00,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,02,01,01,-1,-1,01,01,01,01,01,01,01,00,00,01,01,01,01,01,01,01,-1,-1,01,01,02,-1,-1,-1},
     {-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,-1,-1,01,01,01,01,-1,-1,01,01,01,01,-1,-1,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};

  typedef int	(Pacman::*methodPointer_t)();

  t_coordinates				*_pacman;
  std::vector<Ghosts *>			*_ghosts;
  int					_score;
  char					*_actions;
  char					_action;
  char					_lastAction;
  std::vector<methodPointer_t>		*_moves;
  methodPointer_t			_lastMove;

  void					setMap();
  void					setPacman();
  void					setGhosts();
  void					setActions();
  void					setMoves();
  int					moveUp();
  int					moveLeft();
  int					moveDown();
  int					moveRight();
  int					move(const char lastact1, const char lastact2,
					     const char lastact3, const int y, const int x);

public:
  Pacman();
  virtual				~Pacman();
  virtual void				startGame(IDisplayManager &, std::string const &);
  virtual int				play(char);
  virtual int				getScore() const;
};

#endif /* !PACMAN_HPP_ */
