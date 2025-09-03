NAME                =   minishell

CC                  =   gcc

UNAME_S             := $(shell uname -s)

INCLUDES            =   ./includes
CFLAGS              =   -Wall -Wextra -Werror -g -I$(INCLUDES)

ifeq ($(UNAME_S),Darwin)
	CFLAGS  += -I/opt/homebrew/opt/readline/include
	LDFLAGS += -L/opt/homebrew/opt/readline/lib
else
	LDFLAGS += -lreadline
endif

LIBFT_PATH          =   ./libft
LIBFT_FILE          =   libft.a
LIBFT_LIB           =   $(LIBFT_PATH)/$(LIBFT_FILE)

SRC_DIR             =   ./srcs
OBJ_DIR             =   $(SRC_DIR)/objs

SRCS                =  $(SRC_DIR)/main_program.c           	\
					    $(SRC_DIR)/parsing/parsing.c  	    	\
					    $(SRC_DIR)/parsing/quote.c	  	    	\
						$(SRC_DIR)/parsing/handle_args.c		\
						$(SRC_DIR)/parsing/tokenizing.c	  	   	\
						$(SRC_DIR)/utils/program_utils.c    	\
						$(SRC_DIR)/utils/listes_utils.c     	\
						$(SRC_DIR)/utils/signal_utils.c     	\
						$(SRC_DIR)/execv/env_util.c         	\
						$(SRC_DIR)/execv/env_util2.c         	\
						$(SRC_DIR)/builtin/ft_echo.c        	\
						$(SRC_DIR)/builtin/ft_pwd.c         	\
						$(SRC_DIR)/builtin/ft_unset.c       	\
						$(SRC_DIR)/parsing/token.c				\
						$(SRC_DIR)/execv/exec_parsing.c			\
						$(SRC_DIR)/execv/exec_parsing_utils1.c	\
						$(SRC_DIR)/execv/exec_parsing_utils2.c	\
						$(SRC_DIR)/execv/exec_pipes.c			\
						$(SRC_DIR)/utils/fd_management.c		\
						$(SRC_DIR)/utils/dup2_utils.c			\
						$(SRC_DIR)/execv/exec_builtin.c 		\
						$(SRC_DIR)/execv/exec_heredoc1.c		\
						$(SRC_DIR)/execv/exec_heredoc2.c 		\
						$(SRC_DIR)/execv/exec_heredoc3.c 		\
						$(SRC_DIR)/execv/exec_heredoc4.c 		\
						$(SRC_DIR)/execv/exec_heredoc5.c 		\
						$(SRC_DIR)/utils/end_line_utils.c 		\
						$(SRC_DIR)/execv/exec_command1.c		\
						$(SRC_DIR)/execv/exec_command2.c		\
						$(SRC_DIR)/execv/exec_command3.c		\
						$(SRC_DIR)/builtin/ft_cd.c 				\
						$(SRC_DIR)/builtin/ft_env.c        		\
						$(SRC_DIR)/builtin/ft_env_utils.c  		\
						$(SRC_DIR)/utils/check_utils1.c 		\
						$(SRC_DIR)/utils/check_utils2.c 		\
						$(SRC_DIR)/utils/heredoc_utils.c 		\
						$(SRC_DIR)/builtin/ft_export.c 			\
						$(SRC_DIR)/builtin/ft_exit.c			\
						$(SRC_DIR)/builtin/ft_exit_utils.c 		\
						$(SRC_DIR)/builtin/ft_echo_utils1.c 	\
						$(SRC_DIR)/builtin/ft_echo_utils2.c 	\
						$(SRC_DIR)/builtin/ft_echo_dollarutils.c \
						$(SRC_DIR)/builtin/ft_cd_utils1.c 		\
						$(SRC_DIR)/builtin/ft_cd_utils2.c 		\
						$(SRC_DIR)/utils/bad_input_utils.c		\
						$(SRC_DIR)/utils/token_utils.c			\
						$(SRC_DIR)/builtin/ft_export_utils1.c 	\
						$(SRC_DIR)/builtin/ft_export_utils2.c 	\
						$(SRC_DIR)/builtin/ft_unset_utils.c 	\
						$(SRC_DIR)/builtin/ft_export_utils3.c 	\
						$(SRC_DIR)/builtin/ft_export_utils4.c 	\
						$(SRC_DIR)/builtin/ft_export_utils5.c 	\
						$(SRC_DIR)/utils/expanding_variables.c 	\
						$(SRC_DIR)/utils/expanding_variables_utils.c 	\
						$(SRC_DIR)/utils/building_args.c 		\
						$(SRC_DIR)/utils/open_files.c 			\
						$(SRC_DIR)/utils/tab_entry_utils.c 		\
						$(SRC_DIR)/utils/manage_cat_input.c 	\
						$(SRC_DIR)/utils/singleton.c 			\
						$(SRC_DIR)/utils/parsing_utils.c 		\
						$(SRC_DIR)/utils/expand_utils_pid.c		\


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

################################## COMMANDES ##################################

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME) \

# Compilation de la libft
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH)

# Création du dossier des .o et sous-dossiers nécessaires
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/builtin
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/execv
	mkdir -p $(OBJ_DIR)/parsing

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ \

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
