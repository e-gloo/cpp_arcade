CC		= g++

RM		= rm -f

CFLAGS		+= -Wall -Werror -Wextra -Wno-unused -I./includes/ --std=c++11

LDFLAGS		+= -ldl -lncurses

SRCS_FO		= ./srcs
OBJS_FO		= ./objs

LIB_FO		= ./lib/
SDL_FO		= display/sdl/
OPENGL_FO	= display/opengl/
TERM_FO		= display/term/

ARCADE_FO	= arcade/

SDL_FILES	= $(SDL_FO)SDLDisplay.cpp
OPENGL_FILES	= $(OPENGL_FO)OpenGLDisplay.cpp
TERM_FILES	= $(TERM_FO)Ncurses.cpp

SDL_SRCS	= $(SRCS_FO)/$(SDL_FILES)
OPENGL_SRCS	= $(SRCS_FO)/$(OPENGL_FILES)
TERM_SRCS	= $(SRCS_FO)/$(TERM_FILES)

SDL_OBJS	= $(OBJS_FO)/$(SDL_FILES:.cpp=.o)
OPENGL_OBJS	= $(OBJS_FO)/$(OPENGL_FILES:.cpp=.o)
TERM_OBJS	= $(OBJS_FO)/$(TERM_FILES:.cpp=.o)

SDL_FLAGS	+= -lSDL -lSDL_image
OPENGL_FLAGS	+= -lSDL -lGL -lGLU
TERM_FLAGS	+= -lncurses

SDL_LIB		= $(LIB_FO)lib_arcade_sdl.so
OPENGL_LIB	= $(LIB_FO)lib_arcade_opengl.so
TERM_LIB	= $(LIB_FO)lib_arcade_term.so

GAME_FO		= ./games/
NIBBLER_FO	= games/nibbler/
PACMAN_FO	= games/pacman/

AGAME_SRCS	= $(SRCS_FO)/games/AGame.cpp

AGAME_OBJS	= $(OBJS_FO)/games/AGame.o

NIBBLER_FILES	= $(NIBBLER_FO)Nibbler.cpp
PACMAN_FILES	= $(PACMAN_FO)Pacman.cpp

NIBBLER_SRCS	= $(SRCS_FO)/$(NIBBLER_FILES)
PACMAN_SRCS	= $(SRCS_FO)/$(PACMAN_FILES)

NIBBLER_OBJS	= $(OBJS_FO)/$(NIBBLER_FILES:.cpp=.o)
PACMAN_OBJS	= $(OBJS_FO)/$(PACMAN_FILES:.cpp=.o)

NIBBLER_LIB	= $(GAME_FO)lib_arcade_nibbler.so
PACMAN_LIB	= $(GAME_FO)lib_arcade_pacman.so

SRCS		= $(SRCS_FO)/$(ARCADE_FO)main.cpp \
		  $(SRCS_FO)/$(ARCADE_FO)Launcher.cpp

OBJS		= $(patsubst $(SRCS_FO)/%.cpp,$(OBJS_FO)/%.o, $(SRCS))

NAME		= arcade

all:		$(TERM_LIB) $(SDL_LIB) $(OPENGL_LIB) $(NIBBLER_LIB) $(PACMAN_LIB) $(NAME)

$(OBJS_FO)/%.o : $(SRCS_FO)/%.cpp
		@$(CC) $(CFLAGS) -c $< -o $@

$(SDL_LIB):
		$(CC) -c $(SDL_SRCS) -o $(SDL_OBJS) -fPIC $(CFLAGS)
		$(CC) -shared $(CFLAGS) -o $(SDL_LIB) $(SDL_OBJS) $(SDL_FLAGS)

$(TERM_LIB):
		$(CC) -c $(TERM_SRCS) -o $(TERM_OBJS) -fPIC $(CFLAGS)
		$(CC) -shared $(CFLAGS) -o $(TERM_LIB) $(TERM_OBJS) $(TERM_FLAGS)

$(OPENGL_LIB):
		$(CC) -c $(OPENGL_SRCS) -o $(OPENGL_OBJS) -fPIC $(CFLAGS)
		$(CC) -shared $(CFLAGS) -o $(OPENGL_LIB) $(OPENGL_OBJS) $(OPENGL_FLAGS)

$(NIBBLER_LIB):
		$(CC) -c $(NIBBLER_SRCS) -o $(NIBBLER_OBJS) -fPIC $(CFLAGS)
		$(CC) -c $(AGAME_SRCS) -o $(AGAME_OBJS) -fPIC $(CFLAGS)
		$(CC) $(CFLAGS) -o $(NIBBLER_LIB) $(NIBBLER_OBJS) $(AGAME_OBJS) -shared

$(PACMAN_LIB):
		$(CC) -c $(PACMAN_SRCS) -o $(PACMAN_OBJS) -fPIC $(CFLAGS) -lm
		$(CC) -c $(AGAME_SRCS) -o $(AGAME_OBJS) -fPIC $(CFLAGS)
		$(CC) $(CFLAGS) -o $(PACMAN_LIB) $(PACMAN_OBJS) $(AGAME_OBJS) -shared

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)
		$(RM) $(TERM_OBJS)
		$(RM) $(SDL_OBJS)
		$(RM) $(OPENGL_OBJS)
		$(RM) $(NIBBLER_OBJS)
		$(RM) $(PACMAN_OBJS)
		$(RM) $(AGAME_OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(TERM_LIB)
		$(RM) $(SDL_LIB)
		$(RM) $(OPENGL_LIB)
		$(RM) $(NIBBLER_LIB)
		$(RM) $(PACMAN_LIB)

re:		fclean all
