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

# ----------------------------- VAR DECLARATION ------------------------------ #

NAME		:= philo

MANDATORY_DIR	:= philo/
BONUS_DIR		:= philo_bonus/


# Git submodule update
GSU =			git submodule update

# Flags for GSU
GSU_FLAGS =		--remote --merge --recursive

# Flags to compile with gcc
FLAGS =			-Werror -Wextra -Wall

# Variable to compile .c files
CC = 			gcc

# Colors 
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;5;94m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
RANDM =			\033[38;5;95m
DARK_GREEN =	\033[38;5;64m
DARK_YELLOW =	\033[38;5;143m

# --------------------------------- ACTIONS ---------------------------------- #
 
all:	
		@$(MAKE) -C $(MANDATORY_DIR)
		@$(MAKE) -C $(BONUS_DIR)

# Action to update the git submodules
update:
				@echo "$(YELLOW)Updating submodules"
				@$(GSU) $(GSU_FLAGS)
				@echo "$(YELLOW)DONE"		

$(NAME):
		@$(MAKE) -C $(MANDATORY_DIR)

bonus:		
		@$(MAKE) -C $(BONUS_DIR)
		
clean:
			@make clean -sC $(MANDATORY_DIR)
			@make clean -sC $(BONUS_DIR)

fclean:		
			@make fclean -sC $(MANDATORY_DIR)
			@make fclean -sC $(BONUS_DIR)


re:			fclean 
			@$(MAKE)	
			@echo "$(GREEN)Cleaned and rebuilt everything for Philosophers!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm