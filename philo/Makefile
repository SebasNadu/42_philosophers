# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 20:42:24 by sebasnadu         #+#    #+#              #
#    Updated: 2024/02/01 14:57:32 by johnavar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME				:= philo
CC					:= cc
RM 					:= rm -rf

################################################################################
##                                   COLORS                                   ##
################################################################################

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

HEADERS				:= philo.h colors.h structs.h
SOURCE				:= main.c parser.c error_handler.c utils.c controllers.c \
					   init.c free_data.c setters.c getters.c print.c dinner.c \
					   supervisor.c states.c
OBJECTS				:= $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

################################################################################
##                                   FLAGS                                    ##
################################################################################

ifeq ($(DEBUG_MODE), 1)
	CFLAGS			:= -Wall -Wextra -Werror -fsanitize=address
else ifeq ($(DEBUG_MODE), 2)
	CFLAGS			:= -Wall -Wextra -Werror -fsanitize=thread
else
	CFLAGS			:= -Wall -Wextra -Werror
endif

PFLAGS				:= -pthread

INCLUDES			:= -I$(INC_DIR)

ifdef DEBUG_MODE
	CFLAGS 			+= -DDEBUG_MODE=$(DEBUG_MODE)
endif

################################################################################
##                                PROGRESS_BAR                                ##
################################################################################

SRC_WORD_COUNT		:= $(shell echo -n $(SOURCE) | wc -w)
OBJ_FILE_COUNT		:= $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l)
SRC_COUNT_TOT		:= $(shell expr $(SRC_WORD_COUNT) - $(OBJ_FILE_COUNT))

ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?), 0)
	SRC_COUNT_TOT	:= $(shell expr $(shell echo -n $(SOURCE) | wc -w))
endif

SRC_COUNT			= 0
SRC_PCT				= $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

################################################################################
##                                COMPILATION                                 ##
################################################################################

all:			$(NAME)


$(NAME):		$(OBJECTS)
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Linking "
	@printf "($(BLUE)$(NAME)$(DEFAULT))...\n"
	@$(CC) $(CFLAGS) -O3 $(PFLAGS) $(INCLUDES) $^ -o $@
	@printf "\r%100s\r$(MAGENTA)[$(NAME)] $(GREEN)Compilation success "
	@printf "🎉!$(DEFAULT)\n"

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@printf "$(MAGENTA)\r%100s\r[$(NAME)] $(GREEN)[ %d/%d (%d%%) ]" \
			"" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT) 
	@printf " $(DEFAULT)Compiling ($(BLUE)$<$(DEFAULT))...\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Creating objects directory "
	@printf "($(BLUE)$(OBJ_DIR)$(DEFAULT))...\n"
	@mkdir -p $@

clean:
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Cleaning up objects files in "
	@printf "($(RED)$(OBJ_DIR)$(DEFAULT))...\n"
	@$(RM) $(OBJ_DIR)

fclean:			clean
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Cleaning up "
	@printf "($(RED)$(NAME)$(DEFAULT))...\n"
	@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
