# **************************************************************************** #
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 12:18:12 by lguiller          #+#    #+#              #
#    Updated: 2018/11/08 12:51:00 by lguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################
##  DOWNLOAD SDL  ##
####################

SDL_FOLDER				= $(HOME)/goinfre/sdl/
SDL_MAIN_DOWNLOAD		= https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
SDL_MAIN_VERSION		= SDL2-2.0.8.tar.gz
SDL_MAIN_FOLDER			= $(SDL_MAIN_VERSION:.tar.gz=)
eDL_IMAGE_DOWNLOAD		= https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz
SDL_IMAGE_VERSION		= SDL2_image-2.0.3.tar.gz
SDL_IMAGE_FOLDER		= $(SDL_IMAGE_VERSION:.tar.gz=)
SDL_MIXER_DOWNLOAD		= https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.2.tar.gz
SDL_MIXER_VERSION		= SDL2_mixer-2.0.2.tar.gz
SDL_MIXER_FOLDER		= $(SDL_MIXER_VERSION:.tar.gz=)
SDL_TTF_DOWNLOAD		= https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
SDL_TTF_VERSION			= SDL2_ttf-2.0.14.tar.gz
SDL_TTF_FOLDER			= $(SDL_TTF_VERSION:.tar.gz=)
FREETYPE_DOWNLOAD		= https://download.savannah.gnu.org/releases/freetype/freetype-2.8.1.tar.gz
FREETYPE_VERSION		= freetype-2.8.1.tar.gz
FREETYPE_FOLDER			= $(FREETYPE_VERSION:.tar.gz=)
SDL_MAIN_HEADER			= $(addsuffix .h, SDL SDL_assert SDL_atomic SDL_audio SDL_bits \
							 SDL_blendmode SDL_cpuinfo SDL_egl SDL_endian SDL_error SDL_events \
							 SDL_filesystem SDL_gamecontroller SDL_gesture SDL_haptic SDL_hints \
							 SDL_joystick SDL_keyboard SDL_keycode SDL_loadso SDL_log \
							 SDL_main SDL_messagebox SDL_mouse SDL_mutex SDL_name SDL_opengl \
							 SDL_opengl_glext SDL_opengles SDL_opengles2_gl2ext SDL_opengles2_gl2 \
							 SDL_opengles2_gl2platform SDL_opengles2 SDL_opengles2_khrplatform \
							 SDL_pixels SDL_platform SDL_power SDL_quit SDL_rect SDL_render \
							 SDL_rwops SDL_scancode SDL_shape SDL_stdinc SDL_surface SDL_system \
							 SDL_syswm SDL_thread SDL_timer SDL_touch SDL_types SDL_version \
							 SDL_video SDL_vulkan begin_code close_code)
SDL_IMAGE_HEADER		= SDL_image.h
SDL_MAIN_OBJ_LIBS		= libSDL2.a
SDL_IMAGE_OBJ_LIBS		= libSDL2_image.a
SDL_MAIN_LIBS_PATH		= $(SDL_FOLDER)$(SDL_MAIN_FOLDER)/
SDL_MAIN_INCLUDE_PATH	= $(SDL_FOLDER)$(SDL_MAIN_FOLDER)/include/
SDL_IMAGE_LIBS_PATH		= $(SDL_FOLDER)$(SDL_MAIN_FOLDER)/
SDL_IMAGE_INCLUDE_PATH	= $(SDL_FOLDER)$(SDL_IMAGE_FOLDER)/
SDL_MAIN_INCLUDE		= $(addprefix $(SDL_MAIN_INCLUDE_PATH), $(SDL_MAIN_HEADER))
SDL_MAIN_LIBS			= $(SDL_FOLDER)lib/
SDL_MAIN				= $(addprefix $(SDL_MAIN_LIBS), $(SDL_MAIN_OBJ_LIBS))
SDL_IMAGE_LIBSD2		= $(SDL_FOLDER)lib/
SDL_IMAGE				= $(addprefix $(SDL_IMAGE_LIBS), $(SDL_IMAGE_OBJ_LIBS))
SDL_IMAGE_INCLUDE		= $(addprefix $(SDL_IMAGE_INCLUDE_PATH), $(SDL_IMAGE_HEADER))
CURL_PATH				= curl -L

#####################
##  SDL VARIABLES  ##
#####################

SDL_MAIN_OBJ_LIBS		= libSDL2.a
SDL_IMAGE_OBJ_LIBS		= libSDL2_image.a
SDL_MAIN_FOLDER			= $(SDL_MAIN_VERSION:.tar.gz=)
SDL_MAIN_LIBS			= $(SDL_FOLDER)lib/
SDL_IMAGE_LIBS			= $(SDL_FOLDER)lib/
SDL_IMAGE_FOLDER		= $(SDL_IMAGE_VERSION:.tar.gz=)
SDL_IMAGE_INCLUDE_PATH	= $(SDL_FOLDER)$(SDL_IMAGE_FOLDER)/
SDL_MAIN_INCLUDE_PATH	= $(SDL_FOLDER)$(SDL_MAIN_FOLDER)/include/
SDL_IMAGE				= $(addprefix $(SDL_IMAGE_LIBS), $(SDL_IMAGE_OBJ_LIBS))
SDL_MAIN				= $(addprefix $(SDL_MAIN_LIBS), $(SDL_MAIN_OBJ_LIBS))

######################
##  GAME VARIABLES  ##
######################

OPE_SYS			= $(shell uname)
NAME			= wolf3d
SRCS1			= $(addsuffix .c, main check_and_stock_map minimap init \
				  raycasting bresenham print_env display input_device \
				  movements copy_struct to_map)
SRCS			= $(addprefix $(SRCS_DIR), $(SRCS1))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS1:.c=.o))
SRCS_DIR		= srcs/
OBJS_DIR		= objs/
LIBFT			= libft/libft.a
MINILIBX		= $(MLX_DIR)/libmlx.a
FLAGS			= -Wall -Wextra -Werror -O2

ifeq ($(OPE_SYS), Linux)
	MLX_DIR		= minilibx_x11
	INCLUDES	= -I includes -I libft -I $(MLX_DIR) -I /usr/include -I ./ -pthread
	FRAMEWORK	= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
else
	MLX_DIR		= minilibx
	INCLUDES	= -I includes -I libft -I $(MLX_DIR) -I ./ -pthread
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

#################
##   TARGETS   ##
#################

.PHONY: all title libft minilibx create_dir clean fclean re install cleansdl sdl_image sdl_main reall

all: create_dir install
	@$(MAKE) $(NAME)

libft:
	@$(MAKE) -sC libft

minilibx: libft
	@$(MAKE) -sC $(MLX_DIR) 2>/dev/null

$(NAME): minilibx $(OBJS)
	@gcc $(FLAGS) $(OBJS) $(LIBFT) $(FRAMEWORK) $(MINILIBX) -I $(SDL_MAIN_INCLUDE_PATH) \
		-L $(SDL_MAIN_LIBS) -lSDL2 -I $(SDL_IMAGE_INCLUDE_PATH) -L $(SDL_IMAGE_LIBS) \
		-lSDL2_image -o $(NAME)
	@echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	@echo $(_GREEN)"Done."$(_END)$(_SHOW_CURS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@gcc $(FLAGS) $(INCLUDES) -c $^ -o $@

create_dir:
	@mkdir -p objs/

clean:
	@$(MAKE) -sC libft clean
	@$(MAKE) -sC $(MLX_DIR) clean
	@/bin/rm -rf $(OBJS_DIR)
	@/bin/rm -rf ./SDL

fclean: clean
	@$(MAKE) -sC libft fclean
	@/bin/rm -f $(NAME)

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all

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
	@echo "                                                   2018 © lguiller bede-fre"
	@echo $(_END)

########################
##   COMPILATION SDL  ##
########################

install:
	@echo "\x1b[44m\x1b[1mVerifing sdl_main ... $(HGLSS) \033[0m"
	@$(MAKE) sdl_main
	@echo "\x1b[42m\x1b[1m Done $(CHECK) \033[0m"
	@echo "\x1b[44m\x1b[1mVerifing sdl_image ... $(HGLSS) \033[0m"
	@$(MAKE) sdl_image
	@echo "\x1b[42m\x1b[1m Done $(CHECK) \033[0m"

sdl_main:
	@if [ ! -d "$(SDL_FOLDER)" ] ; then mkdir $(SDL_FOLDER); fi
	@if [ ! -e "$(SDL_FOLDER)$(SDL_MAIN_VERSION)" ] ; then cd $(SDL_FOLDER) && \
		$(CURL_PATH) $(SDL_MAIN_DOWNLOAD) > $(SDL_MAIN_VERSION); fi
	@if [ ! -d "$(SDL_FOLDER)$(SDL_MAIN_FOLDER)" ] ; then cd $(SDL_FOLDER) && \
		tar -xvzf $(SDL_MAIN_VERSION); fi
	@$(foreach file, $(SDL_MAIN), test -e $(file) || \
		(echo "\x1b[41m\x1b[1mUhhh.... Missing file $(file) in $@\033[0m" ; \
		cd $(SDL_FOLDER)$(SDL_MAIN_FOLDER) ; ./configure --prefix=$$PWD/../ ; \
		make && make install);)
	@$(foreach file, $(SDL_MAIN_INCLUDE), test -e $(file) || \
		(echo "\x1b[41m\x1b[1mUhhh.... Missing file $(file) in $@\033[0m" ; \
		cd $(SDL_FOLDER)$(SDL_MAIN_FOLDER) ; ./configure --prefix=$$PWD/../ ; \
		make && make install);)
	@mkdir -p ./SDL
	@cp -r $(SDL_MAIN_INCLUDE_PATH) ./SDL

sdl_image:
	@if [ ! -d "$(SDL_FOLDER)" ] ; then make sdl_main; fi
	@if [ ! -e "$(SDL_FOLDER)$(SDL_IMAGE_VERSION)" ] ; then cd $(SDL_FOLDER) && \
		$(CURL_PATH) $(SDL_IMAGE_DOWNLOAD) > $(SDL_IMAGE_VERSION); fi
	@if [ ! -d "$(SDL_FOLDER)$(SDL_IMAGE_FOLDER)" ] ; then cd $(SDL_FOLDER) && \
		tar -xvzf $(SDL_IMAGE_VERSION); fi
	@$(foreach file, $(SDL_IMAGE), test -e $(file) || \
		(echo "\x1b[41m\x1b[1mUhhh.... Missing file $(file)\033[0m" ; \
		cd $(SDL_FOLDER)$(SDL_IMAGE_FOLDER) ; ./configure --prefix=$$PWD/../ \
		--with-sdl-prefix=$$PWD/../../sdl ; make && make install);)
	@$(foreach file, $(SDL_IMAGE_LIBS), test -e $(file) || \
		(echo "\x1b[41m\x1b[1mUhhh.... Missing file $(file)\033[0m" ; \
		cd $(SDL_FOLDER)$(SDL_IMAGE_FOLDER) ; ./configure --prefix=$$PWD/../ \
		--with-sdl-prefix=$$PWD/../../sdl ; make && make install);)
	@cp $(SDL_FOLDER)SDL2_image-2.0.3/SDL_image.h ./SDL/SDL_image.h

cleansdl:
	@rm -rf $(SDL_FOLDER)
	@rm -rf SDL

reall: cleansdl re
