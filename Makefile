NAME		:= miniRT
CC			:= gcc 
FLAGS		:= -g3 -Wall -Wextra -Werror #-fsanitize=address
RM			:= rm -rf

SRCDIR		:= src
INCDIR		:= inc
OBJDIR		:= obj
LIBMLXDIR	:= mlx
LIBDIR		:= libft/
LIBFT		:= libft.a
SRC 		:= $(shell find $(SRCDIR) -name '*.c' ! -name '*_bonus.c')
OBJ 		:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
BONUS_SRC 	:= $(filter-out src/parser/parse_spc.c src/transformations_2.c,$(SRC)) \
             src/parser/parse_spc_bonus.c \
             src/transformations_2_bonus.c
BONUS_OBJ 	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(BONUS_SRC))



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

bonus: 		fclean
			@$(MAKE) all FLAGS="$(FLAGS) -DBONUS" SRC="$(BONUS_SRC)" OBJ="$(BONUS_OBJ)"
			@echo "Compiled with bonus files"
			./miniRT scenes/cone.rt


run:		re
			@./minirt scenes/test06-complex.rt

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
