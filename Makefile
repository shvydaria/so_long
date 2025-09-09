GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

NAME	= so_long

CC		= clang
RM		= rm -f

LIB_NAME = libft
PRINTF = ft_printf
MLX42_DIR = MLX42
MLX42_REPO = https://github.com/codam-coding-college/MLX42
MLX42_LIB = $(MLX42_DIR)/build/libMLX42.a

LIB_PATH = ./$(LIB_NAME)
PRINTF_PATH = ./$(PRINTF)
INCLUDE_PATH = ./include

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE_PATH) -I./get_next_line -I$(LIB_PATH) -I$(PRINTF_PATH) -I$(MLX42_DIR)/include

OS := $(shell uname)
# LDFLAGS =  -L$(MLX42_DIR)/build MLX42/build/libmlx42.a -ldl -lglfw -lm -pthread -fsanitize=address
# LDFLAGS =  -L$(MLX42_DIR)/build -lmlx42 -ldl -lglfw -lm -pthread -fsanitize=address

ifeq ($(OS), Linux)
	LDFLAGS = -L$(MLX42_DIR)/build -lmlx42 -ldl -lglfw -lm -pthread -fsanitize=address
else ifeq ($(OS), Darwin)
	LDFLAGS = -L$(MLX42_DIR)/build -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit -fsanitize=address
endif

SRCS = src/so_long.c src/map_utils.c src/map_validation.c src/texture_manager.c \
		src/image_handler.c src/render.c src/player.c src/path_validation.c \
		src/moves.c src/collectibles.c src/init.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ := $(SRCS:%.c=%.o)

$(NAME): $(OBJ) $(LIB_PATH)/$(LIB_NAME).a $(PRINTF_PATH)/libftprintf.a $(MLX42_LIB)
	@echo "$(GREEN)$(NAME) has started running $(RESET)"
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) -L$(PRINTF_PATH) -lftprintf -L$(LIB_PATH) -lft
	@echo "$(GREEN)$(NAME) has ran $(RESET)"

$(OBJ): $(MLX42_LIB)

$(LIB_PATH)/$(LIB_NAME).a:
	make -C $(LIB_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

$(PRINTF_PATH)/libftprintf.a:
	make -C $(PRINTF_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

# $(MLX42_LIB):
# 	cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
# 	cmake --build $(MLX42_DIR)/build

$(MLX42_LIB):
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	fi
	cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	cmake --build $(MLX42_DIR)/build

%.o:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

libft:
		make -C libft

ft_printf:
		make -C ft_printf

clean:
	make clean -C $(LIB_PATH)
	make clean -C $(PRINTF_PATH)
	${RM} ${OBJ}

fclean: clean
	${RM} $(NAME)
	make fclean -C $(LIB_PATH)
	make fclean -C $(PRINTF_PATH)
	${RM} -rf $(MLX42_DIR)

cln:
	make clean -C $(LIB_PATH)
	make clean -C $(PRINTF_PATH)
	${RM} ${OBJ}
	${RM} $(NAME)
	make fclean -C $(LIB_PATH)
	make fclean -C $(PRINTF_PATH)

re:			fclean all

.PHONY: all clean fclean re libft ft_printf
