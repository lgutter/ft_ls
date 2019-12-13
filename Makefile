# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2019/12/13 16:56:18 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include source_files/lssources
include ft_printf/libft/covsources
include test_files/testsources

JUNK := **/*~ **/\#*\# **/.DS_Store
COVJUNK := **/*.gcov **/*.gcda *.gcov *.gcda

MAIN := source_files/main.o
CSOURCES := $(LSSOURCES:%= source_files/%.c)
OBJECTS := $(LSSOURCES:%= source_files/%.o)
GCNOFILES += $(LSSOURCES:%= *.gcno)
TESTOBJECTS := $(TESTSOURCES:%= test_files/%.o)
COVJUNK += $(TESTSOURCES:%= test_files/%.gcno)

LIBRARY = -lftprintf
export LIBRARY_PATH=$(HOME)/.brew/lib:$(PWD)/ft_printf
export CPATH=$(HOME)/.brew/include:$(PWD):$(PWD)/ft_printf
HEADER := ft_ls.h

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -g
ifdef COV
	CFLAGS += -coverage
endif

LIBFT := ft_printf/libftprintf.a

NAME := ft_ls

TEST := test

C_RESET = \033[0;00m
C_CLEAN = \033[38;5;189m
C_OLEAN = \033[38;5;183m
C_FCLEAN = \033[38;5;140m
C_LS = \033[38;5;98m
C_TEST = \033[38;5;134m
C_OBJECTS = \033[38;5;224m
C_LINES = \033[38;5;250m

all: $(NAME)

$(NAME): $(MAIN) $(OBJECTS) $(HEADER) $(LIBFT)
	@#$(MAKE) norm
	@$(CC) $(MAIN) $(OBJECTS) $(CFLAGS) $(LIBRARY) -o $@
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@echo "$(C_LS)ft_ls has been compiled$(C_RESET)"
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"

$(LIBFT): FORCE
	@$(MAKE) -C ft_printf/

%.o: %.c
	@$(CC) -c $< $(CFLAGS) -o $@
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@echo "$(C_OBJECTS)$@ compiled$(C_RESET)"
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"

$(TEST): $(OBJECTS) $(NAME) $(TESTOBJECTS)
	@$(MAKE) norm
	@$(MAKE) clean
	@$(CC) $(OBJECTS) $(TESTOBJECTS) $(CFLAGS) $(LIBRARY) -lcriterion -o $@
	@echo "$(C_TEST)Test program has been compiled$(C_RESET)"

norm:
	@sh checkNorm.sh "$(CSOURCES) $(HEADER)"

gcov:
	@gcov $(CSOURCES)

clean:
	@rm -rf $(COVJUNK) $(JUNK)
	@echo "$(C_CLEAN)Junk & coverage files removed$(C_RESET)"

oclean: clean
	@rm -rf $(OBJECTS) $(TESTOBJECTS) $(GCNOFILES)
	@echo "$(C_OLEAN)Object files removed$(C_RESET)"

fclean: oclean
	@rm -rf $(NAME) $(TEST)
	@echo "$(C_FCLEAN)$(NAME) & $(TEST) removed$(C_RESET)"
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@$(MAKE) fclean -C ft_printf/

re: fclean all

FORCE:

.PHONY: all norm gcov clean oclean fclean re FORCE
