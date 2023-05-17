# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 06:13:39 by kpawlows          #+#    #+#              #
#    Updated: 2023/05/17 19:29:19 by kpawlows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC 		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
AR 		=	ar -rcs
RM		=	rm -r
SRCDIR	=	src
OBJDIR	=	obj

SRC		=	$(shell find $(SRCDIR) -name '*.c')
OBJ		=	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
END=\033[0m

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			mkdir -p '$(@D)'
			$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	@printf "[libft]$(GREEN) \t re successful $(END)\n"