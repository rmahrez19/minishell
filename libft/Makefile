# Nom de la bibliothèque
NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
      ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c ft_memcpy.c \
      ft_memmove.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strdup.c \
      ft_strlcat.c ft_strlcpy.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
      ft_substr.c ft_itoa.c ft_split.c ft_putnbr_fd.c ft_putstr_fd.c \
      ft_putendl_fd.c ft_putchar_fd.c ft_putstr.c ft_lstnew_bonus.c \
      ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
      ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
      ft_lstsize_bonus.c ft_split_remove_ws.c ft_memchr.c ft_memcmp.c \
      ft_strjoin.c ft_strmapi.c ft_striteri.c ./printf/base.c ./printf/hexa.c \
      ./printf/libft.c ft_strncmp.c ft_strndup.c ./garbage.c \
	  get_next_line.c get_next_line_utils.c

OBJ_DIR = objs

OBJ = $(SRC:.c=.o)
OBJF = $(addprefix $(OBJ_DIR)/,$(OBJ))

AR = ar rcs

all: $(NAME)

$(NAME): $(OBJF)
	@$(AR) $(NAME) $(OBJF) \
	&& echo "\033[32m✔ Libft compilée avec succès\033[0m" \
	|| echo "\033[31m✘ Erreur compilation de libft\033[0m"

# Compile rule
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ \
	&& echo "\033[32m✔ Compilé : $<\033[0m" \
	|| echo "\033[31m✘ Erreur compilation : $<\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[33m🧹 Clean libft terminé\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33m🧼 Fclean libft terminé\033[0m"

re: fclean all

.PHONY: all clean fclean re
