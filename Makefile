# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afoures <afoures@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 18:09:37 by afoures           #+#    #+#              #
#    Updated: 2018/06/30 15:32:18 by afoures          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

ASM = asm

CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast

OBJ_PATH = obj

VM_SRCS =	main.c \
			settings.c \
			init.c \
			read_file.c \
			create_player.c \
			get_champs.c \
			print_msg.c \
			memory.c \
			op.c \
			cycles.c \
			process.c \
			colors.c \
			visu.c \
			update_visu.c \
			sdl_utils.c \
			exit.c

VM_PATH = srcs/vm
VM_OBJ = $(addprefix $(OBJ_PATH)/, $(VM_SRCS:.c=.o))

INST_SRCS = add.c \
			lfork.c \
			live.c \
			sub.c \
			zjmp.c \
			fork.c \
			aff.c \
			and.c \
			ld.c \
			lld.c \
			or.c \
			xor.c \
			st.c \
			sti.c \
			ldi.c \
			lldi.c \
			check_oc.c
 
INST_PATH = srcs/vm/instructions
VM_OBJ += $(addprefix $(OBJ_PATH)/, $(INST_SRCS:.c=.o))

ASM_SRCS =	asm_main.c \
			get_next_line_asm.c \
			print.c \
			line.c \
			assemble.c \
			lst.c \
			lst2.c \
			op.c \
			get_file.c \
			get_name.c \
			get_comment.c \
			errors.c \
			label.c \
			free_asm.c

ASM_PATH = srcs/asm
ASM_OBJ = $(addprefix $(OBJ_PATH)/, $(ASM_SRCS:.c=.o))

INCLUDES = includes

LIB_PATH = srcs/libft
LIB = $(LIB_PATH)/libft.a

all : 
	@make $(LIB)
	@make $(ASM)
	@make $(NAME)

$(NAME) :	$(LIB) $(VM_OBJ)
			$(CC) -o $(NAME) $^ $(FLAGS) -L ~/.brew/lib/ -lsdl2 -lsdl2_ttf -I ~/.brew/include/SDL2
			@echo "\033[32mvm done\033[m"

$(ASM) :	$(LIB) $(ASM_OBJ) 
			$(CC) -o $(ASM) $^ $(FLAGS)
			@echo "\033[32masm done\033[m"

$(LIB) :
			make -j -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(ASM_PATH)/%.c $(INCLUDES)/asm.h $(INCLUDES)/op.h
			@mkdir -p $(OBJ_PATH)
			$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes $(FLAGS)

$(OBJ_PATH)/%.o: $(VM_PATH)/%.c $(INCLUDES)/corewar.h $(INCLUDES)/op.h
			@mkdir -p $(OBJ_PATH)
			$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes $(FLAGS) -I ~/.brew/include/SDL2

$(OBJ_PATH)/%.o: $(INST_PATH)/%.c $(INCLUDES)/corewar.h $(INCLUDES)/op.h
			@mkdir -p $(OBJ_PATH)
			$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes $(FLAGS) -I ~/.brew/include/SDL2

norme:
	@norminette srcs/**/*.c srcs/**/**/*.c includes | grep Error -B 1 > norm.out
	@echo "--" >> norm.out
	@norminette srcs/**/*.c srcs/**/**/*.c includes | grep Warning -B 1 >> norm.out

clean :
			make -C $(LIB_PATH) clean
			rm -f $(ASM_OBJ)
			rm -f $(VM_OBJ)

fclean :	clean
			rm -f $(ASM)
			rm -f $(NAME)
			rm -f $(LIB)

re : 	
			make fclean 
			make all

.PHONY : all clean fclean re
