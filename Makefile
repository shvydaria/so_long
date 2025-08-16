GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

NAME	= so_long

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -I$(LIB_PATH) -I$(PRINTF_PATH)

LIB_NAME = libft
PRINTF = ft_printf
MLX42_DIR = MLX42
MLX42_LIB = $(MLX42_DIR)/build/libMLX42.a

LDFLAGS =  -L$(MLX42_DIR)/build MLX42/build/libmlx42.a -ldl -lglfw -lm -pthread

SRCS = src/so_long.c src/map_utils.c src/map_validation.c src/texture_manager.c \
       src/image_handler.c src/render.c src/player.c \
       get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ := $(SRCS:%.c=%.o)

LIB_PATH = ./$(LIB_NAME)
PRINTF_PATH = ./$(PRINTF)

$(NAME): $(OBJ) $(LIB_PATH)/$(LIB_NAME).a $(PRINTF_PATH)/libftprintf.a $(MLX42_LIB)
	@echo "$(GREEN)$(NAME) has started running $(RESET)"
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) -L$(LIB_PATH) -lft -L$(PRINTF_PATH) -lftprintf
	@echo "$(GREEN)$(NAME) has ran $(RESET)"

$(LIB_PATH)/$(LIB_NAME).a:
	make -C $(LIB_PATH)

$(PRINTF_PATH)/libftprintf.a:
	make -C $(PRINTF_PATH)

$(MLX42_LIB):
	cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	cmake --build $(MLX42_DIR)/build

%.o:	%.c
		$(CC) $(CFLAGS) -I$(LIB_PATH) -I$(PRINTF_PATH) -I$(MLX42_DIR)/include -c $< -o $@

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

re:			fclean all

.PHONY: all clean fclean re libft ft_printf
