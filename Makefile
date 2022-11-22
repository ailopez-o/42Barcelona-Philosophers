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

SRC_DIR		:= src/
OBJ_DIR		:= obj/
CC			:= gcc
CFLAGS		:= -g -O3 -Wall -Werror -Wextra
#FSANITIZE	:= -fsanitize=address -g3
FSANITIZE	:= 
NOFLAGS		:= -g
RM			:= rm -f

INC		 		:= inc/
LIB				:= lib/
PRINTF_DIR		:= $(LIB)ft_printf/
PRINTF			:= $(PRINTF_DIR)libftprintf.a
HEADER 			:= -I$(INC) -I$(PRINTF_DIR)

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

SRC_FILES	=	main

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS		= 	$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))
###

OBJF		=	.cache_exists

all:	makelibs
		@$(MAKE) $(NAME)

makelibs:	
	@$(MAKE) -C $(PRINTF_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) -MMD -c $< -o $@	

-include 	${DEPS}
$(NAME):	$(OBJ) Makefile
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) -o $(NAME)		
			@echo "👉 $(BLUE)$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) -o $(NAME)$(DEF_COLOR)"
			@echo "$(GREEN)✨ Philosophers compiled!$(DEF_COLOR)"

bonus:		
			@$(MAKE) all
			
$(OBJF):
			@mkdir -p $(OBJ_DIR)
		

clean:
			@make clean -sC $(PRINTF_DIR)
			@echo "$(CYAN)ft_printf object and dependency files cleaned.$(DEF_COLOR)"
			$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)Philosophers object files cleaned!$(DEF_COLOR)"

fclean:		clean
			$(RM) -f $(NAME)
			@echo "$(CYAN)Philosophers executable files cleaned!$(DEF_COLOR)"	
			$(RM) -f $(PRINTF_DIR)libftprintf.a
			@echo "$(CYAN)libftprintf.a lib cleaned!$(DEF_COLOR)"


re:			fclean 
			@$(MAKE)	
			@echo "$(GREEN)Cleaned and rebuilt everything for Fdf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
