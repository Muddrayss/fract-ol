# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudio <claudio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 15:53:22 by egualand          #+#    #+#              #
#    Updated: 2023/12/10 01:30:09 by claudio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), fract-ol.c general_utils.c formulas.c rendering.c hooks.c color.c)
OBJS = $(SRCS:.c=.o)
INCLUDES = .
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = fract-ol
MLX_DIR = minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

all: $(MLX_DIR) $(NAME)

$(MLX_DIR):
		@git clone $(MLX_REPO) $(MLX_DIR)
		@cd $(MLX_DIR) && ./configure

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -lmlx_Linux -I$(MLX_DIR) -lXext -lX11 -lm -lz -lpthread -o $(NAME)
		@echo compiled $(NAME)

%.o: %.c
		@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
		@$(RM) $(OBJS)
		@echo removed object files

fclean: clean
		@$(RM) $(NAME)
		@echo removed $(NAME)

re: fclean all

.PHONY: all clean fclean re
