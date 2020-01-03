# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/03 11:38:07 by ivan-tey      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include source_files/lssources
include ft_printf/libft/covsources
include test_files/testsources

COVJUNK = $(shell find -E . -regex ".*\.gc(da|ov)" 2>/dev/null)
JUNK = $(shell find -E . -regex ".*(\..*~|\#.*\#|\.DS_Store)" 2>/dev/null)

MAIN := source_files/main.o
CSOURCES := $(LSSOURCES:%= source_files/%.c)
OBJECTS := $(LSSOURCES:%= source_files/%.o)
GCNOFILES += $(LSSOURCES:%= source_files/%.gcno)
TESTOBJECTS := $(TESTSOURCES:%= test_files/%.o)
COVJUNK += $(TESTSOURCES:%= test_files/%.gcno)

LIBRARY = -lftprintf
LIBPATH=-L ./ft_printf
INCLPATH=-I . -I ./ft_printf
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
	@$(CC) $(MAIN) $(OBJECTS) $(CFLAGS) $(LIBPATH) $(LIBRARY) -o $@
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@echo "$(C_LS)ft_ls has been compiled$(C_RESET)"
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"

$(LIBFT): FORCE
	@$(MAKE) -C ft_printf/

%.o: %.c
	@$(CC) -c $< $(CFLAGS) $(INCLPATH) -o $@
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@echo "$(C_OBJECTS)$@ compiled$(C_RESET)"

$(TEST): $(OBJECTS) $(NAME) $(TESTOBJECTS)
	@$(MAKE) norm
	@$(MAKE) clean
	@$(CC) $(OBJECTS) $(TESTOBJECTS) $(CFLAGS) $(LIBPATH) $(LIBRARY) \
	-lcriterion -o $@
	@echo "$(C_TEST)Test program has been compiled$(C_RESET)"

norm:
	@sh checkNorm.sh "$(CSOURCES) $(HEADER)"

gcov:
	@gcov $(CSOURCES)

clean:
	@rm -rf $(COVJUNK) $(JUNK)
	@echo "$(C_CLEAN)Junk & coverage files removed$(C_RESET)"

oclean: clean
	@rm -rf $(OBJECTS) $(TESTOBJECTS) $(GCNOFILES) $(MAIN:%.c= %.o)
	@echo "$(C_OLEAN)Object files removed$(C_RESET)"

fclean: oclean
	@rm -rf $(NAME) $(TEST)
	@echo "$(C_FCLEAN)$(NAME) & $(TEST) removed$(C_RESET)"
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@$(MAKE) fclean -C ft_printf/

re: fclean all

FORCE:

.PHONY: all norm gcov clean oclean fclean re FORCE
