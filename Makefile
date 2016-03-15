CC		= g++

RM		= rm -f

CFLAGS		+= -Wall -Werror -Wextra -I./includes/

SRCS_FO		= ./srcs
OBJS_FO		= ./objs

LIB_FO		= ./lib/
SFML_FO		= display/sfml/
OPENGL_FO	= display/opengl/
TERM_FO		= display/term/

SFML_FILES	= $(SFML_FO)*.cpp
OPENGL_FILES	= $(OPENGL_FO)*.cpp
TERM_FILES	= $(TERM_FO)*.cpp

SFML_SRCS	= $(SRCS_FO)/$(SFML_FILES)
OPENGL_SRCS	= $(SRCS_FO)/$(OPENGL_FILES)
TERM_SRCS	= $(SRCS_FO)/$(TERM_FILES)

SFML_OBJS	= $(OBJS_FO)/$(SFML_FILES:.cpp=.o)
OPENGL_OBJS	= $(OBJS_FO)/$(OPENGL_FILES:.cpp=.o)
TERM_OBJS	= $(OBJS_FO)/$(TERM_FILES:.cpp=.o)

SFML_FLAGS	+= -L./libs/SFML-2.3.2/lib/ -lsfml-graphics -lsfml-window -lsfml-system
OPENGL_FLAGS	+= -L./libs/
TERM_FLAGS	+= -L./libs/

SFML_LIB	= $(LIB_FO)libsfml.so
OPENGL_LIB	= $(LIB_FO)libopengl.so
TERM_LIB	= $(LIB_FO)libterm.so

GAME_FO		= ./games/

SRCS		= main.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= arcade

all:		$(NAME) $(SFML_LIB)

$(SFML_LIB):
		$(CC) -c $(SFML_SRCS) -o $(SFML_OBJS) -fPIC
		$(CC) $(CFLAGS) $(SFML_FLAGS) -o $(SFML_LIB) $(SFML_OBJS) -shared

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		$(RM) $(OBJS)
		$(RM) $(SFML_OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(SFML_LIB)

re:		fclean all
