# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/26 15:48:11 by mstorcha          #+#    #+#              #
#    Updated: 2018/03/02 20:59:40 by mstorcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt
LIBA = libft/libft.a
MLXA = minilibx_macos/libmlx.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -g

INCLUDES = -I./includes/

LIB_DIR = ./libft/
LIB_FLAGS = -L$(LIB_DIR) -lft

MLX_DIR = ./frameworks/minilibx_macos/
LIB_FLAGS += -L$(MLX_DIR) -lmlx

INCLUDES	+=	-I./frameworks/SDL2.framework/Headers -F./frameworks

FRAMEWORKS	=	-framework OpenGL -framework AppKit -framework OpenCL \
					-framework SDL2 -rpath ./frameworks

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SOURCES = main.c \
			handlers.c \
			color_vector.c \
			ft_makelist.c \
			readf.c \
			read_help.c \
			get_obj.c \
			opencl1.c \
			opencl2.c

OBJ = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(LIBA) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME) $(INCLUDES) $(FRAMEWORKS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBA): lib

lib:
	@make all -C $(LIB_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@/bin/rm -rf $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
