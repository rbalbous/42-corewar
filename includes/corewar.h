/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:25:48 by rbalbous          #+#    #+#             */
/*   Updated: 2018/07/28 15:30:19 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "ft_printf.h"
# include "op.h"
# include <SDL.h>
# include <SDL_ttf.h>

# define P1 0x33cc33
# define P2 0x0099ff
# define P3 0xff00ff
# define P4 0xff9933
# define NEW1 0xff0000
# define NEW2 0x0079df
# define NEW3 0xdf00df
# define NEW4 0xdf7913
# define WHITE 0xffffff
# define GREY 0x202020
# define L_GREY 0x646464
# define RED_MSG 0xff0000

# define LEN_MAX_MSG 60

# define BLACK 	"\x1B[30m"
# define RED 	"\x1B[31m"
# define GREEN 	"\x1B[32m"
# define YEL 	"\x1B[33m"
# define BLU 	"\x1B[34m"
# define MAG 	"\x1B[35m"
# define CYN 	"\x1B[36m"
# define WHT 	"\x1B[37m"
# define NOC 	"\x1B[0m"

# define CYCLE_MAX 243661

typedef struct s_player		t_player;
typedef struct s_lstprocess	t_lstprocess;
typedef	struct s_window		t_window;
typedef struct s_rect		t_rect;
typedef struct s_point		t_point;
typedef struct s_old		t_old;
typedef union u_color		t_color;

struct					s_old
{
	Uint8			mem[MEM_SIZE];
	Uint8			color[MEM_SIZE];
	Uint8			process[MEM_SIZE];
};

struct					s_rect
{
	int				x;
	int				y;
	int				width;
	int				heigth;
};

union					u_color
{
	int				color;
	unsigned char	rgb[4];
};

struct					s_point
{
	int				x;
	int				y;
};

struct					s_window
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	TTF_Font		*ttf_player;
	TTF_Font		*ttf_text;
	SDL_Event		event;
	char			game_color[MEM_SIZE];
	char			game_process[MEM_SIZE];
	int				colors[4];
	int				width;
	int				height;
	int				text_height;
	int				text_start;
};

struct					s_player
{
	t_player		*next;
	char			*name;
	char			*comment;
	char			*memory;
	int				size;
	int				start;
	int				number;
	int				live;
	int				last_live;
};

struct					s_lstprocess
{
	t_lstprocess	*next;
	int				reg[REG_NUMBER];
	short			pc;
	int				carry;
	int				player_number;
	int				id;
	int				live;
	int				last_cycle;
	char			opcode;
};

extern	t_op			g_op[17];
extern	unsigned char	*g_memory;
extern	int				g_cycle;
extern	unsigned int	g_nb_process;
extern	t_lstprocess	*g_process;
extern	int				g_cycle_to_die;
extern	unsigned int	g_nb_live;
extern	int				g_dump;
extern	int				g_flags;
extern	t_player		*g_players;

int						check_file_name(char *champ_name, int nb_champs
						, int number, int curr_number);
int						get_args(char *arg);
int						get_dump_nb(char *arg);
void					print_usage(void);
int						print_error(char *error, ...);
int						get_number(char *arg, int *number);
int						read_file(char *name_file, int number);
int						create_player(int number);
int						init_memory(t_window *win, int nb_players);
int						dump_memory(void);
void					free_all(void);
int						loop(t_window *win, int nb_players);
int						create_first_process(void);
t_lstprocess			*create_process(int reg[REG_NUMBER], int carry, int pc
							, int player_number);
void					compute_process(int (*inst[17])(), t_window *win
							, t_player **last_player_alive);
void					kill_process(t_window *win);
void					print_process(void);
t_player				*check_number(int number);

int						inst_add(int pc, t_lstprocess *process);
int						inst_aff(int pc, t_lstprocess *process, t_window *win);
int						inst_and(int pc, t_lstprocess *process);
int						inst_fork(int pc, t_lstprocess *process, t_window *win);
int						inst_ld(int pc, t_lstprocess *process);
int						inst_ldi(int pc, t_lstprocess *process);
int						inst_lfork(int pc, t_lstprocess *process
							, t_window *win);
int						inst_live(int pc, t_lstprocess *process, t_window *win
							, t_player **last_player_alive);
int						inst_lld(int pc, t_lstprocess *process);
int						inst_lldi(int pc, t_lstprocess *process);
int						inst_or(int pc, t_lstprocess *process);
int						inst_st(int pc, t_lstprocess *process, t_window *win);
int						inst_sti(int pc, t_lstprocess *process, t_window *win);
int						inst_sub(int pc, t_lstprocess *process);
int						inst_xor(int pc, t_lstprocess *process);
int						inst_zjmp(int pc, t_lstprocess *process);
int						get_all_arg(int	*pc, t_lstprocess *process, int decal);
int						get_all_arg_ldi(int *pc, t_lstprocess *process
							, int decal);
int						get_int(int	to_get);

int						init_visu(t_window *win, int nb_players);
void					get_event(t_window *win, int *pause);
void					clean_quit(t_window *win);
void					put_rect(SDL_Surface *surface, t_rect rectangle
							, Uint32 pixel);
void					put_line(SDL_Surface *surface, t_point start
							, t_point end, Uint32 pixel);
void					put_text(SDL_Surface *surface, SDL_Surface *text, int x
							, int y);
SDL_Color				argb_to_sdl(Uint32 color);
Uint32					get_color(t_window *win, int number);
void					put_byte(t_window *win, t_point p, Uint32 color
							, int process);

void					put_process(t_window *win, int pc, int process);
int						check_oc(int pc, int opcode, char octal);

void					update_visu(t_window *win, int nb_players);

void					draw_memory(t_window *win);

void					update_game_info(t_window *win, int nb_players);
void					update_player_info(t_window *win, int nb_players);
void					update_msg(t_window *win, char *str, Uint32 color);
void					update_color(t_window *win, int pc, int number);

#endif
