# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2019/12/09 21:21:01 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include source_files/lssources
include libft/covsources
include Test_files/testsources

JUNK := **/*~ **/\#*\# **/.DS_Store
COVJUNK := **/*.gcov **/*.gcda *.gcov *.gcda

CSOURCES := $(LSSOURCES:%= source_files/%.c)
OBJECTS := $(LSSOURCES:%= source_files/%.o)
GCNOFILES += $(LSSOURCES:%= *.gcno)
TESTOBJECTS := $(TESTSOURCES:%= test_files/%.o)
COVJUNK += $(TESTSOURCES:%= test_files/%.gcno)

LIBRARIES = -lftprintf
export LIBRARY_PATH += :$(PWD)/ft_printf
export CPATH += :$(PWD)/ft_printf
HEADER := ft_ls.h

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -g
ifdef COV
	CFLAGS += -coverage
endif

LIBFT := ft_printf/libftprinft.a

NAME := ft_ls

TEST := test

C_RESET = \033[0;00m
C_CLEAN = \033[38;5;194m
C_FCLEAN = \033[38;5;156m
C_LS = \033[38;5;34m
C_TEST = \033[38;5;28m
C_OBJECTS = \033[38;5;220m
C_LINES = \033[38;5;250m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS) $(HEADER)
	@$(MAKE) norm
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@$(CC) $(OBJECTS) $(CFLAGS) $(LIBRARIES) -o $@
	@echo "$(C_LS)ft_ls has been compiled$(C_RESET)\n"

$(LIBFT):
	 @$(MAKE) -C ft_printf/


%.o: %.c
	@$(CC) -c $< $(CFLAGS) -o $@
	@echo "$(C_OBJECTS)$@ compiled$(C_RESET)"

$(TEST): $(OBJECTS) $(NAME) $(TESTOBJECTS)
	@$(MAKE) norm
	@$(MAKE) clean
	@LIBRARIES +=  -lcriterion
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@$(CC) $(TESTOBJECTS) $(CFLAGS) $(LIBRARIES) -o $@
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
	@echo "$(C_CLEAN)Object files removed$(C_RESET)"

fclean: oclean
	@rm -rf $(NAME) $(TEST)
	@echo "$(C_FCLEAN)$(NAME) & $(TEST) removed$(C_RESET)"
	@echo "$(C_LINES)- - - - - - - - - -$(C_RESET)"
	@$(MAKE) fclean -C ft_printf/

re: fclean all

.PHONY: all norm gcov clean oclean fclean re
