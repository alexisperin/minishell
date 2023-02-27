# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 09:50:49 by aperin            #+#    #+#              #
#    Updated: 2023/02/27 16:03:53 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_FILE	= main.c \
				input_loop/read_input.c \
				lexer/lexer.c \
				lexer/lexer_utils.c \
				lexer/prelexer.c \
				lexer/postlexer.c \
				parser/parser.c \
				parser/parser_utils.c \
				expander/expander.c \
				expander/expander_utils.c \
				executor/executor.c \
				executor/local_values.c \
				builtins/ft_pwd.c \
				builtins/ft_echo.c \
				builtins/ft_env.c \
				builtins/ft_exit.c \
				builtins/ft_cd.c \
				builtins/ft_export.c \
				builtins/ft_unset.c \
				builtins/ft_buil_utils.c \
				utils/display_header.c \
				handle_sig/handling.c \
				error/error.c
				
SRCS_DIR	= srcs
OBJSDIR		= objs
INCDIR		= includes ${LIBFT_DIR}

SRCS		= $(addprefix ${SRCS_DIR}/, ${SRC_FILE})
OBJS		= $(addprefix ${OBJSDIR}/, $(addsuffix .o, $(basename ${SRC_FILE})))
OBJS_DIR	= $(sort $(dir $(OBJS)))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
INCS		= $(foreach d, $(INCDIR), -I$d)
LDFLAGS =-L/Users/aburnott/.brew/opt/readline/lib
CPPFLAGS =-I/Users/aburnott/.brew/opt/readline/include
# libft
LIBFT_DIR	= libft
LIBFT		= ${LIBFT_DIR}/libft.a

${OBJSDIR}/%.o: ${SRCS_DIR}/%.c
			@mkdir -p ${OBJSDIR} ${OBJS_DIR}
			${CC} ${CFLAGS} ${INCS} $(CPPFLAGS) -c -o $@ $<

all:		${NAME}

${NAME}:	${OBJS}
			make -C ${LIBFT_DIR}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} $(CPPFLAGS) $(LDFLAGS) -lreadline -o ${NAME}

clean:
			make clean -C ${LIBFT_DIR}
			rm -rf ${OBJSDIR}

fclean:		clean
			make fclean -C ${LIBFT_DIR}
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re