# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 14:14:48 by mokariou          #+#    #+#              #
#    Updated: 2025/01/31 16:06:08 by mokariou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address 
NORM = norminette

MLX = minilibx-linux/libmlx.a -Iminilibx-linux -lXext -lX11 -lm -lbsd
OBJ_DIR = obj/
LIBFT_DIR = inc/libft/
GNL_DIR = inc/gnl/
PARSING_DIR = parsing/
RENDERING_DR = rendering/
SRC_MAIN = main.c
SRC_RENDERING = $(RENDERING_DR)init_game.c $(RENDERING_DR)init_player.c \
				$(RENDERING_DR)drawing.c $(RENDERING_DR)minimap.c \
				$(RENDERING_DR)pixel_utils.c
SRC_PARSING = $(PARSING_DIR)set_texture.c \
              $(PARSING_DIR)error_utils.c \
			  $(PARSING_DIR)cleanUp.c $(PARSING_DIR)init_text.c \
			  $(PARSING_DIR)init_map.c $(PARSING_DIR)validate_map.c $(PARSING_DIR)xpm.c
SRC_GNL = $(GNL_DIR)get_next_line.c \
          $(GNL_DIR)get_next_line_utils.c
SRC_LIBFT = $(LIBFT_DIR)ft_atoi.c $(LIBFT_DIR)ft_bzero.c $(LIBFT_DIR)ft_calloc.c \
            $(LIBFT_DIR)ft_isalnum.c $(LIBFT_DIR)ft_isalpha.c $(LIBFT_DIR)ft_isascii.c \
            $(LIBFT_DIR)ft_isdigit.c $(LIBFT_DIR)ft_isprint.c $(LIBFT_DIR)ft_itoa.c \
            $(LIBFT_DIR)ft_lstadd_back_bonus.c $(LIBFT_DIR)ft_lstadd_front_bonus.c \
            $(LIBFT_DIR)ft_lstclear_bonus.c $(LIBFT_DIR)ft_lstdelone_bonus.c \
            $(LIBFT_DIR)ft_lstiter_bonus.c $(LIBFT_DIR)ft_lstlast_bonus.c \
            $(LIBFT_DIR)ft_lstmap_bonus.c $(LIBFT_DIR)ft_lstnew_bonus.c \
            $(LIBFT_DIR)ft_lstsize_bonus.c $(LIBFT_DIR)ft_memchr.c \
            $(LIBFT_DIR)ft_memcmp.c $(LIBFT_DIR)ft_memcpy.c $(LIBFT_DIR)ft_memmove.c \
            $(LIBFT_DIR)ft_memset.c $(LIBFT_DIR)ft_putchar_fd.c $(LIBFT_DIR)ft_putendl_fd.c \
            $(LIBFT_DIR)ft_putnbr_fd.c $(LIBFT_DIR)ft_putstr_fd.c $(LIBFT_DIR)ft_split.c \
            $(LIBFT_DIR)ft_strchr.c $(LIBFT_DIR)ft_strdup.c $(LIBFT_DIR)ft_striteri.c \
            $(LIBFT_DIR)ft_strjoin.c $(LIBFT_DIR)ft_strlcat.c $(LIBFT_DIR)ft_strlcpy.c \
            $(LIBFT_DIR)ft_strlen.c $(LIBFT_DIR)ft_strmapi.c $(LIBFT_DIR)ft_strncmp.c \
            $(LIBFT_DIR)ft_strnstr.c $(LIBFT_DIR)ft_strrchr.c $(LIBFT_DIR)ft_strtrim.c \
            $(LIBFT_DIR)ft_substr.c $(LIBFT_DIR)ft_tolower.c $(LIBFT_DIR)ft_toupper.c

SRCS = $(SRC_MAIN) $(SRC_PARSING) $(SRC_GNL) $(SRC_LIBFT) $(SRC_RENDERING)
OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	$(NORM)


