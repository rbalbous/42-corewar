#!/bin/bash

printf "\033[1;31mCheck headers\033[0m\n"
cat *.c srcs/*c srcs/**/*c srcs/**/**/*c libft/*.c libft/**/*.c includes/ *.h | grep "By:"

printf "\033[1;31mCheck malloc\033[0m\n"
cat *.c srcs/*c srcs/**/*c srcs/**/**/*c libft/*.c libft/**/*.c includes/ *.h | grep "malloc"

printf "\033[1;31mNorm check\033[0m\n"
norminette | grep Error -B 1
norminette | grep Warning -B 1
