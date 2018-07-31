# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/26 15:48:11 by mstorcha          #+#    #+#              #
#    Updated: 2018/07/24 19:24:01 by mstorcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt
LIBFTA = libft/libft.a
TFDA = libTFD/libtfd.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror
#CFLAGS += -g

INCLUDES = -I./includes/

LIBFT_DIR = ./libft/
LIB_FLAGS = -L$(LIBFT_DIR) -lft

LIBTFD_DIR = ./libTFD/
LIB_FLAGS += -L$(LIBTFD_DIR) -ltfd

INCLUDES	+=	-I./frameworks/SDL2.framework/Headers
INCLUDES	+=  -I./frameworks/SDL2_image.framework/Headers
INCLUDES	+=  -I./frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h
INCLUDES	+=  -F./frameworks 

FRAMEWORKS	=	-framework OpenGL -framework AppKit -framework OpenCL \
					-framework SDL2 -framework SDL2_image -framework SDL2_ttf -rpath ./frameworks 

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SOURCES = main.c \
			handlers.c \
			color_vector.c \
			ft_makelist.c \
			opencl1.c \
			opencl2.c \
			add_figures.c \
			json_parser.c \
			write_in_file.c \
			user_interface.c \
			init_interface.c \
			sidebar.c \
			printer.c \
			button_manipulator.c \
			button_drawer.c \
			crutches.c

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
