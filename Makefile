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
LIBFTA = libft/libft.a
TFDA = libTFD/libtfd.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -g

INCLUDES = -I./includes/

LIBFT_DIR = ./libft/
LIB_FLAGS = -L$(LIBFT_DIR) -lft

LIBTFD_DIR = ./libTFD/
LIB_FLAGS += -L$(LIBTFD_DIR) -ltfd

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
			opencl2.c \
			add_figures.c

OBJ = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(LIBFTA) $(TFDA) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME) $(INCLUDES) $(FRAMEWORKS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFTA): lib

lib:
	@make all -C $(LIBFT_DIR)

$(TFDA): tfd

tfd: 
	@make all -C $(LIBTFD_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBTFD_DIR)
	@/bin/rm -rf $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBTFD_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
