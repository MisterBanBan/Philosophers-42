NAME := philo
SRC_DIR := src
BUILD_DIR := .build
DEPS_DIR := .deps
INC := inc/philosopher.h


SRC_FILES =	$(SRC_DIR)/main.c		\
			$(SRC_DIR)/ft_atol.c	\
			$(SRC_DIR)/init_philo.c	\
			$(SRC_DIR)/time.c		\
			$(SRC_DIR)/thread.c		\
			$(SRC_DIR)/action.c		\
			$(SRC_DIR)/monitor.c	\
			$(SRC_DIR)/taken_fork.c \
			$(SRC_DIR)/ft_calloc.c \
			$(SRC_DIR)/ft_isdigit.c


SRC := $(SRC_FILES)

OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEPS    := $(patsubst %.o, %.d,$(OBJS))

CC := cc -g3
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -MMD -MP

RM := rm -f

all: $(NAME) 

FORCE:


$(LIBS_TARGET): FORCE
	$(MAKE) -C $(LIBS_DIR) all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
			$(CC) $(IFLAGS) $(OBJS) -o $(NAME)


-include $(DEPS)

# **************************************************************************** #

clean:
	$(RM) -r $(BUILD_DIR) $(DEPS_DIR)

# **************************************************************************** #

fclean: clean
	$(RM) -r $(NAME)

# **************************************************************************** #

re: fclean all

# **************************************************************************** # # .PHONY #

.PHONY: all clean fclean re

# *****************************