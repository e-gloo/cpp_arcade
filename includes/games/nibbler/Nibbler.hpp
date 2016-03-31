/*
** Nibbler.hpp for Nibbler in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 14:53:53 2016 Dylan Coodien
** Last update Thu Mar 31 23:09:29 2016 Dylqn Coodien
*/

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

# include <vector>
# include "games/AGame.hpp"
# include "display/IDisplayManager.hpp"

# define NB_MOVES	4

# define BORDER		-1
# define EMPT		0
# define SNAKE		1
# define FOOD		2

# define WIDTH		20
# define HEIGHT		20

# define POINTS		25

# define MIN_TIME	100

typedef enum	Snake
  {
    HEAD = 0,
    BODY,
    TAIL
  }		Snake;

typedef struct	s_coordinates
{
  int		x;
  int		y;
}		t_coordinates;

typedef struct	s_snakePosition
{
  t_coordinates	*coordinates;
  Snake		part;
}		t_snakePosition;

typedef struct	s_food
{
  t_coordinates	*coordinates;
  int		points;
}		t_food;


class Nibbler: public AGame
{
  typedef void	(Nibbler::*methodPointer_t)(int, int);

  int					score;
  std::vector<t_snakePosition *>	*snake;
  t_food				*food;
  char					*actions;
  char					action;
  char					lastAction;
  std::vector<methodPointer_t>		*moves;
  methodPointer_t			lastMove;

  void					initMap();
  void					initSnake();
  void					geneFood();
  void					moveUp(int, int);
  void					moveLeft(int, int);
  void					moveDown(int, int);
  void					moveRight(int, int);

public:
  Nibbler();
  virtual				~Nibbler();
  virtual void				startGame(IDisplayManager &);
  virtual int				play(char);
  std::vector<t_snakePosition *>	*getSnake() const;
};

#endif /* !NIBBLER_HPP_ */
