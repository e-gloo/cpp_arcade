/*
** Nibbler.hpp for Nibbler in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
** 
** Made by Dylan Coodien
** Login   <coodie_d@epitech.eu>
** 
** Started on  Tue Mar 15 14:53:53 2016 Dylan Coodien
** Last update Tue Mar 15 18:22:40 2016 Dylan Coodien
*/

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

# include <vector>
# include "AGame.hpp"

# define BORDER	-1
# define EMPTY	0

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
  int					score;
  std::vector<t_snakePosition *>	*snake;
  t_food				*food;

  void					initMap();
  void					initSnake();
public:
  Nibbler();
  virtual	~Nibbler() {}
  virtual int	play(char);
};

#endif /* !NIBBLER_HPP_ */
