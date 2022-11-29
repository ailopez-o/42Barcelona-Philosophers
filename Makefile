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

MANDATORY_DIR	:= mandatory/
BONUS_DIR		:= bonus/

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
		@$(MAKE) -C $(BONUS_DIR)

$(NAME):
		@$(MAKE) -C $(MANDATORY_DIR)

bonus:		
		@$(MAKE) -C $(BONUS_DIR)
		

clean:
			@make clean -sC $(MANDATORY_DIR)
			@echo "$(CYAN)Philosophers object and dependency files cleaned.$(DEF_COLOR)"
			$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)Philosophers object files cleaned!$(DEF_COLOR)"

fclean:		clean
			$(RM) -f $(MANDATORY_DIR)
			@echo "$(CYAN)Philosophers executable files cleaned!$(DEF_COLOR)"	
			$(RM) -f $(PRINTF_DIR)libftprintf.a
			@echo "$(CYAN)libftprintf.a lib cleaned!$(DEF_COLOR)"


re:			fclean 
			@$(MAKE)	
			@echo "$(GREEN)Cleaned and rebuilt everything for Philosophers!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
