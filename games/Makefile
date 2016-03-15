##
## Makefile for arcade in /home/coodie_d/rendu/cpp/B4/cpp_arcade/games
## 
## Made by Dylan Coodien
## Login   <coodie_d@epitech.net>
## 
## Started on  Tue Mar 15 14:40:51 2016 Dylan Coodien
## Last update Tue Mar 15 18:35:52 2016 Dylan Coodien
##

CC	= g++

NAME	= nibbler

SRC	= main.cpp \
	  AGame.cpp \
	  Nibbler.cpp

CFLAGS	= -Wall -Wextra -Werror -Wno-unused --std=c++11

all:	$(NAME)

$(NAME):
	$(CC) $(SRC) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
