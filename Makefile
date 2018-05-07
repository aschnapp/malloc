# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/22 09:20:40 by pjha              #+#    #+#              #
#    Updated: 2018/05/06 20:19:21 by aschnapp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so

BINDIR := bin
SRCDIR := src
SRCS := $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*/*.c $(SRCDIR)/*/*/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))
DEPS := $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.d, $(SRCS))

CC := gcc
CCFLAGS := -Wall -Wextra -Werror -fPIC -DDEBUG_MODE
LD := gcc
LDFLAGS := -shared

RESET := $(shell echo "\033[0m")
WHITE := $(shell echo "\033[1;37m")
YELLOW := $(shell echo "\033[1;33m")
GREEN := $(shell echo "\033[1;32m")
CYAN := $(shell echo "\033[1;36m")

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)[$(CYAN)LD$(GREEN)] $(WHITE)$(BINDIR)/$(NAME)$(RESET)"
	@$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)
	@rm -f libft_malloc.so test/libft_malloc.so test/$(NAME)
	@ln -s $(NAME) libft_malloc.so

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(GREEN)[$(YELLOW)CC$(GREEN)] $(WHITE)$<$(RESET)"
	@mkdir -p $(shell dirname $@)
	@$(CC) -MM -MP -MT $@ -I$(SRCDIR) $(CCFLAGS) $< > $(patsubst %.o,%.d,$@)
	@$(CC) -I$(SRCDIR) -c $< $(CCFLAGS) -o $@

-include $(DEPS)

clean:
	@echo "$(CYAN)Cleaning object files"
	@rm -rf $(BINDIR)
	@rm $(NAME) libft_malloc.so

fclean: clean
	@echo "$(CYAN)Cleaning generated binary"
	@rm -rf $(NAME)

re: fclean all

test:
	$(MAKE) -C test

.PHONY: all clean fclean re test
