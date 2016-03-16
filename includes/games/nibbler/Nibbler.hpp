/*
** Nibbler.hpp for Nibbler in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 14:53:53 2016 Dylan Coodien
** Last update Wed Mar 16 15:59:55 2016 Dylan Coodien
*/

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

# include <vector>
# include "/games/AGame.hpp"

# define NB_MOVES	4

# define BORDER		-1
# define EMPTY		0
# define SNAKE		1
# define FOOD		2

# define WIDTH		50
# define HEIGHT		50

# define POINTS		25

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
  typedef void	(Nibbler::*methodPointer_t)();

  int					score;
  std::vector<t_snakePosition *>	*snake;
  t_food				*food;
  char					*actions;
  char					lastAction;
  std::vector<methodPointer_t>		*moves;
  methodPointer_t			lastMove;

  void					initMap();
  void					initSnake();
  void					geneFood();
  void					moveUp();
  void					moveLeft();
  void					moveDown();
  void					moveRight();
  void					display();

public:
  Nibbler();
  virtual	~Nibbler();
  virtual int	play(char);
};

#endif /* !NIBBLER_HPP_ */
