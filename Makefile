# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 16:48:24 by jeguerin          #+#    #+#              #
#    Updated: 2024/01/24 14:17:34 by jeguerin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME := so_long

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -Werror -Iheaders/

#Liste des fichiers source.
SRCS := main.c handle_image.c handle_events.c
GETNEXTLINE := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
# Options de la bibliotheque MiniLibX et des bibliotheques systeme
LIBRARY := -Lminilibx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
# Liste des objets (fichiers .o) deduits des fichiers source.
OBJS = $(SRCS:.c=.o)
GETNEXTLINE_OBJ := $(GETNEXTLINE:.c=.o)

# Regle par defaut pour l'executable
all: author project $(NAME)

# Regles pour afficher l'auteur et le projet.
author:
	@echo "Author : jeguerin\n"
project:
	@echo "Project : So_long\n"

# Regle pour creer l'executable en liant les objets.
$(NAME): $(OBJS) $(GETNEXTLINE_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) $(GETNEXTLINE_OBJ) -o $(NAME)

# Regle pour nettoyer les fichiers objets.
clean:
	$(RM) $(OBJS)
	$(RM) $(GETNEXTLINE_OBJ)

# Regle pour nettoyer les fichiers objets et l'executable.
fclean: clean
	$(RM) $(NAME)

# Regle pour reconstruire le projet (clean, puis all)
re: author fclean all

# Declarer les regles comme des cibles .phony pour eviter des conflits avec
# des fichiers du meme nom.
.PHONY: all clean fclean re
