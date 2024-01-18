# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 20:42:24 by sebasnadu         #+#    #+#              #
#    Updated: 2024/01/18 15:40:18 by sebasnadu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME				:= philo
CC					:= cc
RM 					:= rm -rf

DEFAULT				:= \033[0;39m
GRAY 				:= \033[0;90m
RED 				:= \033[0;91m
GREEN	 			:= \033[0;92m
YELLOW 				:= \033[0;93m
BLUE 				:= \033[0;94m
MAGENTA				:= \033[0;95m
CYAN				:= \033[0;96m
WHITE	 			:= \033[0;97m

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR				:= obj
INC_DIR				:= include
SRC_DIR				:= src

vpath %.h $(INC_DIR)
vpath %.c $(SRC_DIR)

HEADERS				:= philo.h

SOURCES				:= main.c

OBJECTS				:= $(addprefix $(OBJ_DIR)/, $SOURCES:.c=.o)

################################################################################
##                                   FLAGS                                    ##
################################################################################

ifeq ($(DEBUG), 1)
	CFLAGS			:= -Wall -Wextra -Werror -g -fsanitize=address,threads
else
	CFLAGS			:= -Wall -Wextra -Werror -g
endif
PFLAGS				:= -lrt -lpthread
INCLUDES			:= -I $(INC_DIR)

################################################################################
##                                PROGRESS_BAR                                ##
################################################################################

SRC_COUNT_TOT		:= $(shell expr $(shell echo -n $(SOURCES) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l))
ifeq ($(shell test $(SRC_COUNT) -le 0; echo $$?), 0)
	SRC_COUNT_TOT	:= $(shell echo -n $(SOURCES) | wc -W)
endif

SRC_COUNT			:= 0
SRC_PCT				= $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

################################################################################
##                                COMPILATION                                 ##
################################################################################

all:			$(NAME)


$(NAME):		$(OBJECTS)
	@printf "$(YELLOW) Linking $(WHITE)$(NAME)$(YELLOW)...$(DEFAULT)\n"
	@$(CC) $(PFLAGS) $^ -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(NAME): Compilation success 🎉!$(DEFAULT)\n"

$(OBJ_DIR):
	@printf "$(YELLOW)Creating objects directory: $(WHITE)$(OBJ_DIR)$(YELLOW)...$(DEFAULT)\n"
	@mkdir -p $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@printf "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT) 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(RED)Cleaning up objects files in $(WHITE)$(OBJ_DIR)$(RED)...$(DEFAULT)\n"
	@$(RM) $(OBJ_DIR)

fclean:			clean
	@printf "$(RED)Cleaning up $(WHITE)$(NAME)$(RED)...$(DEFAULT)\n"
	@$(RM) $(NAME)

re:				fclean all

# drd: $(NAME)
# 	valgrind --tool=drd ./$(EXECUTABLE) 5 800 200 200 5

# hell: $(NAME)
# 	valgrind --tool=helgrind ./$(EXECUTABLE) 5 800 200 200 5

# check: $(NAME)
# 	valgrind -q --leak-check=full --show-leak-kinds=all \
# 		--track-origins=yes ./$(EXECUTABLE) 5 800 200 200 5

.PHONY:			all clean fclean re
