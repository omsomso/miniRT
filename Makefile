NAME		:= minirt
CC			:= gcc 
FLAGS		:= #-fsanitize=address #-g3 -Wall -Wextra -Werror
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
			@echo "$$HEADER"
			
run:		all
			@echo "$$HEADER"
			@./minirt scenes/test01-sphere.rt

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
