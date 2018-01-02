#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/30 18:43:03 by ahrytsen          #+#    #+#              #
#    Updated: 2018/01/02 15:12:35 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_ls
DIRSRC		=	./src/
DIROBJ		=	./obj/
INCLUDE		=	-I./includes/ -I./libftprintf/
SUB_MAKE	=	./libftprintf/
INC_LIB		=	-L./libftprintf -lftprintf
SRC			=	ft_ls.c

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)%)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	gcc
RM			=	rm -f
ECHO		=	echo


$(NAME)	:		$(OBJ)
ifdef SUB_MAKE
				@(cd $(SUB_MAKE) && $(MAKE))
endif
				@$(CC) $(INCLUDE) $(INC_LIB) $(CFLAGS) -o $(NAME) $(OBJS)
				@$(ECHO) "\033[31m> \033[32mft_ls: Compiled\033[0m"

clean	:
				@(cd $(DIROBJ) && $(RM) $(OBJ))
ifdef SUB_MAKE
				@(cd $(SUB_MAKE) && $(MAKE) clean)
endif
				@$(ECHO) "\033[31m> \033[33mft_ls: Directory cleaned\033[0m"

all		:		$(NAME)

fclean	:		clean
ifdef SUB_MAKE
				@(cd $(SUB_MAKE) && $(MAKE) fclean)
endif
				-@$(RM) $(NAME)
				@$(ECHO) "\033[31m> \033[33mft_ls: Remove executable\033[0m"

re		:		fclean all

.PHONY	:		all clean re

%.o		:		$(DIRSRC)/%.c
				@$(CC) $(INCLUDE) $(CFLAGS) -o $(DIROBJ)/$@ -c $<
