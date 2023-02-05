.PHONY: all re clean fclean

#Program name
NAME	= cub3d

# Compiler
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -MMD -g3 #-fsanitize=address

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

# Sources
SRC_PATH	=	sources/
SRC			= 	main.c 						\
				init_data.c					\
				init_mlx.c					\
			  	parsing/check_args.c		\
				parsing/parse_data.c		\
				parsing/get_file_data.c		\
				parsing/create_game_map.c	\
				parsing/check_textures.c	\
				parsing/check_map.c 		\
				parsing/check_map_borders.c	\
				raycasting_utils.c          \
				raycasting.c				\
				utils.c						\
				render/render.c				\
				render/image_utils.c		\
				render/minimap_render.c		\
				render/minimap_image.c		\
			  	input/input_handler.c		\
			  	exit.c 						\
				free_data.c					\
				debug/debug.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/input
	@mkdir $(OBJ_PATH)/debug
	@mkdir $(OBJ_PATH)/render

$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MLX_PATH)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJS)
	@echo "Compiling cub3d..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm
	@echo "cub3d ready."

bonus: all

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing cub3d..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all
