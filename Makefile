# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/20 13:28:00 by vquesnel          #+#    #+#              #
#    Updated: 2018/02/20 13:28:00 by vquesnel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

SRC = main.cpp Reader.cpp Operand.cpp FactoryMethod.cpp VM.cpp

OBJ = $(SRC:.cpp=.o)

CFLAGS = -std=c++11 -Wall -Wextra -Werror

CC = clang++

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c  -o $@ $<

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
