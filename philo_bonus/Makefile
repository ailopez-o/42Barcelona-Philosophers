# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:48:38 by ailopez-          #+#    #+#              #
#    Updated: 2022/06/03 13:50:22 by aitoraudi        ###   ########.fr        #
#    Updated: 2022/05/24 00:35:24 by aitorlope        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#Variables

NAME		:= philo_bonus

SRC_DIR		:= src/
OBJ_DIR		:= obj/
CC			:= gcc
CFLAGS		:= -g -Wall -Werror -Wextra
#CFLAGS		:= -g -Werror
#FSANITIZE	:= -fsanitize=thread
FSANITIZE	:= 
NOFLAGS		:= -g
RM			:= rm -f

HEADER 			:= -I$(INC)
PTHREAD			= -pthread

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRC_FILES	=	main \
				utils \
				forking \
				parsing

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS		= 	$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))
###

OBJF		=	.cache_exists

all:	
		@$(MAKE) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) $(PTHREAD) -MMD -c $< -o $@	

-include 	${DEPS}
$(NAME):	$(OBJ) Makefile
			@$(CC) $(CFLAGS) $(PTHREAD) $(FSANITIZE) $(OBJ) $(PRINTF) -o $(NAME)		
			@echo "👉 $(BLUE)$(CC) $(CFLAGS) $(PTHREAD) $(FSANITIZE) $(OBJ) -o $(NAME)$(DEF_COLOR)"
			@echo "$(GREEN)✨ Philosophers Bonus compiled!$(DEF_COLOR)"

bonus:		
			@$(MAKE) all
			
$(OBJF):
			@mkdir -p $(OBJ_DIR)
		

clean:
			$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)Philosophers Bonus object files cleaned!$(DEF_COLOR)"

fclean:		clean
			$(RM) -f $(NAME)
			@echo "$(CYAN)Philosophers Bonus executable files cleaned!$(DEF_COLOR)"	

re:			fclean 
			@$(MAKE)	
			@echo "$(GREEN)Cleaned and rebuilt everything for Philosophers Bonus!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
