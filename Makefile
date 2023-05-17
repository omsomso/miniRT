NAME		:= minirt
CC			:= gcc 
FLAGS		:= -g3 -fsanitize=address #-Wall -Wextra -Werror 
RM			:= rm -rf

SRCDIR		:= src
INCDIR		:= inc
OBJDIR		:= obj
LIBMLXDIR	:= mlx
LIBDIR		:= libft/
LIBFT		:= libft.a
SRC			:= $(shell find $(SRCDIR) -name '*.c')
OBJ			:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

define HEADER
                                     __      
           __          __           /\ \__   
  ___ ___ /\_\    ___ /\_\      _ __\ \ ,_\  
/' __` __`\/\ \ /' _ `\/\ \    /\`'__\ \ \/  
/\ \/\ \/\ \ \ \/\ \/\ \ \ \   \ \ \/ \ \ \_ 
\ \_\ \_\ \_\ \_\ \_\ \_\ \_\   \ \_\  \ \__\ 
 \/_/\/_/\/_/\/_/\/_/\/_/\/_/    \/_/   \/__/

endef
export HEADER

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p '$(@D)'
			@$(CC) -c $(FLAGS) $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@$(CC) $(FLAGS) -o $@ $^ -L$(LIBDIR) -lft -I$(INCDIR) -I$(LIBMLXDIR) -L$(LIBMLXDIR) -lmlx -framework OpenGL -framework AppKit
#			@$(CC) $(FLAGS) -o $@ $^ -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -L$(LIBDIR) -lft -I$(INCDIR)

#On school computers run :
# curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# brew install readline
#Use the second compile command

run:		all
			@echo "$$HEADER"
			@./minirt

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
