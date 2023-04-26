# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 18:11:28 by agenoves          #+#    #+#              #
#    Updated: 2022/04/26 18:11:28 by agenoves         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 						philo

CC =						gcc
CFLAGS = 					-Wall -Werror -Wextra
RM =						rm -f

FILES =						ft_philo \
							ft_utils \
							ft_start \
							ft_utils2

SRCS_DIR = 				./
SRCS = 					$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = 					${SRCS:.c=.o}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o $@ 

all: ${NAME} 
${NAME}: ${OBJS}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	
re: fclean all

.PHONY: all clean fclean re
