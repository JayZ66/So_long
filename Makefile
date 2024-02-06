# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 16:48:24 by jeguerin          #+#    #+#              #
#    Updated: 2024/02/05 19:50:42 by jeza             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME := so_long

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -Werror -Iheaders/

#Liste des fichiers source.
SRCS := main.c handle_image.c handle_events.c check_map.c handle_errors.c utils.c
GETNEXTLINE := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
LIBFT = Libft/libft.a
# Options de la bibliotheque MiniLibX et des bibliotheques systeme
LIBRARY := -Lminilibx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
OBJS = $(SRCS:.c=.o)
GETNEXTLINE_OBJ := $(GETNEXTLINE:.c=.o)

# Regle par defaut pour l'executable
all: author project $(NAME)

# Regles pour afficher l'auteur et le projet.
author:
	@echo "Author : jeguerin\n"
project:
	@echo "Project : So_long\n"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C Libft
	
# Regle pour creer l'executable en liant les objets.
$(NAME): $(OBJS) $(LIBFT) $(GETNEXTLINE_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) $(LIBFT) $(GETNEXTLINE_OBJ) -o $(NAME)

# Regle pour nettoyer les fichiers objets.
clean:
	$(RM) $(OBJS) 
	$(RM) $(GETNEXTLINE_OBJ)
	make clean -C Libft

# Regle pour nettoyer les fichiers objets et l'executable.
fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft

# Regle pour reconstruire le projet (clean, puis all)
re: author fclean all

# Declarer les regles comme des cibles .phony pour eviter des conflits avec
# des fichiers du meme nom.
.PHONY: all clean fclean re
