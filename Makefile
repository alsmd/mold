
SRC_DIR = ./Srcs/

CLASSES_DIR = $(SRC_DIR)Classes/


# SRC FILES
SRC_TMP = $(addprefix $(SRC_DIR), main)

# CLASSES FILES

SRC_TMP += $(addprefix $(CLASSES_DIR), BST)


# ADDSUFIX
SRC = $(addsuffix .cpp, $(SRC_TMP))

OBJS = $(SRC:.cpp=.o)

NAME = bst

LIB_PATH = /libs/

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SFML_PATH = $(LIB_PATH)SFML/

CC = g++

CFLAGS = 

RM = rm -rf


all: $(NAME)


.cpp.o:
	${CC} ${CFLAGS} -I./Includes -c $< -o ${<:.cpp=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I./Includes -I$(SFML_PATH)includes -o $(NAME) $(OBJS) -L$(SFML_PATH)lib  $(SFML_FLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all