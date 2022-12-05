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

NAME		:= philo

MANDATORY_DIR	:= philo/
BONUS_DIR		:= philo_bonus/

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
 
all:	
		@$(MAKE) -C $(MANDATORY_DIR)
		@cp $(MANDATORY_DIR)philo _philo
		@$(MAKE) -C $(BONUS_DIR)
		@cp $(BONUS_DIR)philo_bonus _philo_bonus

$(NAME):
		@$(MAKE) -C $(MANDATORY_DIR)
		@cp $(MANDATORY_DIR)philo _philo

bonus:		
		@$(MAKE) -C $(BONUS_DIR)
		@cp $(BONUS_DIR)philo_bonus _philo_bonus
		

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