# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 11:42:48 by agenoves          #+#    #+#              #
#    Updated: 2022/05/24 11:42:52 by agenoves         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 						philo_bonus

CC =						gcc
CFLAGS = 					-Wall -Werror -Wextra
RM =						rm -f

FILES =						ft_philo_bonus \
							ft_init_bonus \
							ft_utils_bonus \
							ft_utils_bonus2 \
							ft_check_bonus 

SRCS_DIR = 				./
SRCS = 					$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = 					${SRCS:.c=.o}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o $@ 

all: ${NAME} 
${NAME}: ${OBJS}

sanitize: ${OBJS}
	${CC} ${CFLAGS} ${SRCS} -o ${NAME} -g -fsanitize=thread

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
	
re: fclean all

.PHONY: all clean fclean re sanitize
