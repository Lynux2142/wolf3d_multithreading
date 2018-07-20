# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 12:18:12 by lguiller          #+#    #+#              #
#    Updated: 2018/06/21 13:26:19 by lguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##  VARIABLES   ##
##################

OPE_SYS			= $(shell uname)
NAME			= wolf3d
SRCS1			= main.c check_and_stock_map.c minimap.c init.c \
					raycasting.c bresenham.c print_env.c \
					display.c input_device.c movements.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRCS1))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS1:.c=.o))
SRCS_DIR		= srcs/
OBJS_DIR		= objs/
LIBFT			= libft/libft.a
MINILIBX		= $(MLX_DIR)/libmlx.a
FLAGS			= -Wall -Wextra -Werror

ifeq ($(OPE_SYS), Linux)
	INCLUDES	= -I includes -I libft -I minilibx -I /usr/include
	MLX_DIR		= minilibx_x11
	FRAMEWORK	= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
else
	INCLUDES	= -I includes -I libft -I minilibx -I /usr/include
	MLX_DIR		= minilibx
	FRAMEWORK	= -framework OpenGL -framework Appkit
endif

##################
##    COLORS    ##
##################

_BLACK		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_VIOLET		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_CLEAR		= "\033[2K"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"

##################
##   TARGETS    ##
##################

.PHONY: all title libft minilibx create_dir clean fclean re

all: $(NAME)

create_dir:
	@./.check_dir.sh $(OBJS_DIR)

libft: title
	@make -sC libft

minilibx: libft
	@make -sC $(MLX_DIR) 2>/dev/null

$(NAME): minilibx create_dir $(OBJS)
	@gcc $(FLAGS) $(OBJS) $(LIBFT) $(FRAMEWORK) $(MINILIBX) -o $(NAME)
	@echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	@echo $(_GREEN)"Done."$(_END)$(_SHOW_CURS)


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@gcc $(FLAGS) $(INCLUDES) -c $^ -o $@
#	@printf $(_HIDE_CURS)$(_CLEAR)$(_YELLOW)"building - "$(_GREEN)
#	@printf $@ | cut -c6- | cut -d'.' -f1
#	@printf $(_END)
#	@printf $(_UP)$(_CUT)

clean:
	@make -sC libft clean
	@make -sC $(MLX_DIR) clean
	@/bin/rm -f $(OBJS)

fclean: clean
	@make -sC libft fclean
	@/bin/rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)

title:
	@echo $(_RED)
	@echo "𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀"
	@echo
	@echo "       :::       :::  ::::::::  :::        ::::::::::     ::::::::  :::::::::  "
	@echo "      :+:       :+: :+:    :+: :+:        :+:           :+:    :+: :+:    :+:  "
	@echo "     +:+       +:+ +:+    +:+ +:+        +:+                  +:+ +:+    +:+   "
	@echo "    +#+  +:+  +#+ +#+    +:+ +#+        :#::+::#          +#++:  +#+    +:+    "
	@echo "   +#+ +#+#+ +#+ +#+    +#+ +#+        +#+                  +#+ +#+    +#+     "
	@echo "   #+#+# #+#+#  #+#    #+# #+#        #+#           #+#    #+# #+#    #+#      "
	@echo "   ###   ###    ########  ########## ###            ########  #########        "
	@echo
	@echo "𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀𐀀"
	@printf $(_YELLOW)
	@echo "                                                       2018 © lguiller bede-fre"
	@echo $(_END)
