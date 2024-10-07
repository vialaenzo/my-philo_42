# Nom du programme
NAME = philo

# Dossier de sortie pour les fichiers objets
OBJ_DIR = obj/
SRCS_DIR = srcs/
# Les différentes bibliothèques

# Headers et includes
HEADER = -I./includes

# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Commandes
CC = cc
RM = rm -rf
#-fsanitize=thread
# Rechercher tous les fichiers .c dans le répertoire courant
SRCS = main.c \
	utils/ft_atoi.c \
	utils/ft_error.c \
	utils/ft_free.c \
	utils/utils.c \
	threads/routine.c \
	utils/inits.c

MAKEFLAGS += --no-print-directory
TOTAL_FILES := $(words $(SRCS))
CURRENT_INDEX := 0

# Conversion des fichiers source en fichiers objets
OBJS = $(addprefix ${OBJ_DIR}, $(SRCS:.c=.o))

# Cibles
all: $(NAME)

# Compilation de la bibliothèque
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(HEADER) $(LIBS)
	@echo "\n┗▷${BOLD}$(GREEN)『./$(NAME) Successfully created [✅]$(RESET)"

${OBJ_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
	@printf "\r🔧 $(BLUE)$(BOLD)%3d%% $(WHITE)$(BOLD)Compiling:$(WHITE)$(BOLD) ${NAME}${RESET} $(RED)$(BOLD)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX) $(TOTAL_FILES)
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "$(BOLD) [ 🗑️ ] $(YELLOW)$(REVERSED)Cleaning up$(RESET)"
	@$(RM) -r $(OBJ_DIR) > /dev/null 2>&1
	@echo "┗▷$(YELLOW)『$(ITALIC)./$(SRCS_DIR)'s$(RESET)$(YELLOW) object files cleaned』$(RESET)"

# Nettoyage complet
fclean: clean
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "┗▷$(YELLOW)『$(ITALIC)./$(NAME)'s$(RESET)$(YELLOW) cleaned』$(RESET)"

# Recompiler entièrement
re: fclean
	$(MAKE) all

.PHONY: all clean fclean re

.SILENT:
# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m
RESET := \033[0m
BOLD := \033[1m
UNDERLINE := \033[4m
REVERSED := \033[7m
ITALIC := \033[3m
