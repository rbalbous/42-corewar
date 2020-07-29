/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:12:36 by afoures           #+#    #+#             */
/*   Updated: 2018/06/30 15:16:04 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "ft_printf.h"
# include "op.h"
# include <time.h>

# define BLACK	"\x1B[30m"
# define RED	"\x1B[31m"
# define GREEN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define GREY	"\x1B[90m"
# define NOC	"\x1B[0m"

/*
** Error messages
*/

# define W_SIZE "Warning: champ size exceed the actual corewar's limit (%d/%d)"
# define STARTING_COMPILATION "Starting %s's asm compilation"
# define DONE "\x1B[32mCompilation done (%d bytes written)\x1B[m"
# define SYNTAX "error: syntax [l.%d] : {%s}"

typedef struct s_file		t_file;
typedef struct s_lstlabel	t_lstlabel;
typedef struct s_lsttmp		t_lsttmp;
typedef struct s_addresses	t_addresses;
typedef struct s_args		t_args;

/*
**	Notre file avec son nom pour le creer la taille de la memoire du champion et
**		le bytecode = buffer a ecrire dans notre fichier
**
**	Taille buffer = PROG_NAME_LENGTH + COMMENT_LENGTH + file.champ_size
*/

extern	t_op		g_op[17];
extern	t_file		*g_file;
extern	int			g_nb_line;

struct				s_addresses
{
	int				instruction_address;
	int				address;
	int				size;
};

struct				s_file
{
	char			*name;
	unsigned char	*bytecode;
	int				champ_size;
};

struct				s_args
{
	char			*line;
	int				size;
	int				skip;
	int				data;
	int				i;
};

/*
**	Liste pour contenir tous les labels et leur addresse
*/

struct				s_lstlabel
{
	t_lstlabel		*next;
	char			*name;
	int				address;
};

struct				s_lsttmp
{
	t_lsttmp		*next;
	char			*name;
	t_addresses		address;
};

int					assemble(char *file_name, int dump);

int					get_file_name(char *file_name);

int					get_next_line_asm(const int fd, char **line);

int					read_label_inst(int fd
						, t_lsttmp **instructions, t_lstlabel **labels);
int					read_name_comment(int fd, int name
						, int comment);
int					add_champ_name(char **line, int fd, int name);
int					add_comment(char **line, int fd, int comment);

int					empty_line(char *line);
int					empty_gnl(int fd);
int					skip_comment(char *line);
int					only_space(char *line, char end);

int					is_label(char *line, int c);

int					print_error(char *error, ...);
void				print_usage(void);
void				print_custom(char *s, ...);
int					print_error_free(char **line);
int					skip_comment(char *line);
int					skip_end_comment(char *line, int *line_index);
int					check_valid(char *line, int	inst);
t_lstlabel			*existing_label(t_lstlabel **labels, char *str);
int					compute_label(t_lsttmp **instructions
						, t_lstlabel **labels);
int					create_label(t_lstlabel **first, char *line, int address
						, int c);
int					create_tmp(t_lsttmp **first, char *line, t_addresses address
						, int c);
int					add_args(char *line, char *data, t_lsttmp **first
						, char type);

int					free_all(t_lsttmp **instructions
						, t_lstlabel **labels);

#endif
