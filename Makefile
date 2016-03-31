CC		= g++

RM		= rm -f

CFLAGS		+= -Wall -Werror -Wextra -Wno-unused -I./includes/ --std=c++11

LDFLAGS		+= -ldl

SRCS_FO		= ./srcs
OBJS_FO		= ./objs

LIB_FO		= ./lib/
SFML_FO		= display/sfml/
OPENGL_FO	= display/opengl/
TERM_FO		= display/term/

SFML_FILES	= $(SFML_FO)SFMLDisplay.cpp
OPENGL_FILES	= $(OPENGL_FO)*.cpp
TERM_FILES	= $(TERM_FO)Ncurses.cpp

SFML_SRCS	= $(SRCS_FO)/$(SFML_FILES)
OPENGL_SRCS	= $(SRCS_FO)/$(OPENGL_FILES)
TERM_SRCS	= $(SRCS_FO)/$(TERM_FILES)

SFML_OBJS	= $(OBJS_FO)/$(SFML_FILES:.cpp=.o)
OPENGL_OBJS	= $(OBJS_FO)/$(OPENGL_FILES:.cpp=.o)
TERM_OBJS	= $(OBJS_FO)/$(TERM_FILES:.cpp=.o)

SFML_FLAGS	+= -L./libs/SFML-2.3.2/lib/ -lsfml-graphics -lsfml-window -lsfml-system
##SFML_FLAGS	+= ./libs/SFML-2.3.2/lib/libsfml-graphics.so
OPENGL_FLAGS	+= -L./libs/
TERM_FLAGS	+= -lncurses

SFML_LIB	= $(LIB_FO)lib_arcade_sfml.so
OPENGL_LIB	= $(LIB_FO)lib_arcade_opengl.so
TERM_LIB	= $(LIB_FO)lib_arcade_term.so

GAME_FO		= ./games/
NIBBLER_FO	= games/nibbler/

AGAME_SRCS	= $(SRCS_FO)/games/AGame.cpp

AGAME_OBJS	= $(OBJS_FO)/games/AGame.o

NIBBLER_FILES	= $(NIBBLER_FO)Nibbler.cpp

NIBBLER_SRCS	= $(SRCS_FO)/$(NIBBLER_FILES)

NIBBLER_OBJS	= $(OBJS_FO)/$(NIBBLER_FILES:.cpp=.o)

NIBBLER_LIB	= $(GAME_FO)lib_arcade_nibbler.so

SRCS		= main.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= arcade

all:		$(TERM_LIB) $(NIBBLER_LIB) $(NAME)

$(SFML_LIB):
		$(CC) -c $(SFML_SRCS) -o $(SFML_OBJS) -fPIC $(CFLAGS)
		$(CC) -shared $(CFLAGS) -o $(SFML_LIB) $(SFML_OBJS) $(SFML_FLAGS)

$(TERM_LIB):
		$(CC) -c $(TERM_SRCS) -o $(TERM_OBJS) -fPIC $(CFLAGS)
		$(CC) -shared $(CFLAGS) -o $(TERM_LIB) $(TERM_OBJS) $(TERM_FLAGS)

$(NIBBLER_LIB):
		$(CC) -c $(NIBBLER_SRCS) -o $(NIBBLER_OBJS) -fPIC $(CFLAGS)
		$(CC) -c $(AGAME_SRCS) -o $(AGAME_OBJS) -fPIC $(CFLAGS)
		$(CC) $(CFLAGS) -o $(NIBBLER_LIB) $(NIBBLER_OBJS) $(AGAME_OBJS) -shared

$(NAME):
		$(CC) -c $(SRCS) -o $(OBJS) $(CFLAGS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS) $(SFML_FLAGS)

clean:
		$(RM) $(OBJS)
		$(RM) $(TERM_OBJS)
		$(RM) $(NIBBLER_OBJS)
		$(RM) $(AGAME_OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(TERM_LIB)
		$(RM) $(NIBBLER_LIB)

re:		fclean all
