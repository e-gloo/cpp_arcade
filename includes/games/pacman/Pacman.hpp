/*
** Pacman.hpp for Pacman in /home/coodie_d/rendu/cpp/B4/cpp_arcade
** 
** Made by Dylqn Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Fri Apr  1 00:25:45 2016 Dylqn Coodien
** Last update Sun Apr  3 18:51:43 2016 Dylqn Coodien
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
# define GHOSTS_INDEX	5
# define EYES		9

# define POINTS		10
# define MEGA_POINTS	100

# define WIDTH		32
# define HEIGHT		32

# define MIN_TIME	100
# define EFFECT_TIME	10000
# define START_TIME	1000
# define NB_GHOSTS	4

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
	UP = 3,
	DOWN,
	LEFT,
	RIGHT
      };

  private:
    GhostsMode		_mode;
    int			_mapIndex;
    GhostsDirection	_direction;
    t_coordinates	*_positions;
    int			_prevTyle;
    Pacman		*_ptr;

  public:
    Ghosts(const GhostsMode &mode, const int &mapIndex, const GhostsDirection &direction,
	   Pacman *);
    ~Ghosts();
    void		setGhostsMode(const GhostsMode &mode);
    GhostsMode		getGhostsMode() const;
    int			getMapIndex() const;
    void		setGhostsDirection(const GhostsDirection &direction);
    GhostsDirection	getGhostsDirection() const;
    void		setPositions(const int &x, const int &y);
    t_coordinates	*getPositions() const;
    int			move(char *map[32]);
    int			moveUp(char *map[32]);
    int			moveDown(char *map[32]);
    int			moveLeft(char *map[32]);
    int			moveRight(char *map[32]);
    int			leftOrRight(char *map[32]);
    int			upOrDown(char *map[32]);
    int			getPrevTyle() const;
    void		getDirections(char *map[32], t_coordinates *pacman);
    void		changeDirections(const t_coordinates *);
    void		escape(char *map[32], int const x, int const y,
			       t_coordinates &a, t_coordinates &b,
			       t_coordinates &c);
    void		findTarget(char *map[32], int const x, int const y,
				   t_coordinates &a, t_coordinates &b,
				   t_coordinates &c);
  };

  char			map_[HEIGHT][WIDTH] =
    {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,01,01,01,01,01,01,01,01,01,01,01,01,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
     {-1,-1,-1,02,-1,00,00,-1,01,-1,00,00,00,-1,01,-1,-1,01,-1,00,00,00,-1,01,-1,00,00,-1,02,-1,-1,-1},
     {-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,01,-1,-1,-1,-1,-1,01,-1,-1,-1,-1,01,-1,-1,-1},
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
  bool					_megaPacgumEffect;
  std::clock_t				_effectTime;
  std::clock_t				_startGhostsTime;

  void					setMap();
  void					setPacman();
  void					setGhosts();
  std::vector<Ghosts *>			*getGhosts() const;
  void					setActions();
  void					setMoves();
  int					whichMoves(const char move);
  int					moveGhosts(const std::clock_t time);
  int					moveUp();
  int					moveLeft();
  int					moveDown();
  int					moveRight();
  int					move(const int y, const int x);
  int					againstGhosts(const int y, const int x);
  void					removeEyes();
  void					addEyes();

public:
  Pacman();
  virtual				~Pacman();
  virtual void				startGame(IDisplayManager &, std::string const &);
  virtual int				play(char);
  virtual int				getScore() const;
};

#endif /* !PACMAN_HPP_ */
