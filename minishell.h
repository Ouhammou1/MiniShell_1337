/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/28 21:44:53 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

typedef struct s_idx
{
	int					i;
	int					len;
	int					start;
	int					state;
	int					in_s_quote;
	int					in_d_quote;
}						t_idx;

typedef enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}						t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	GENERAL,
	NUL,
}						t_state;
typedef struct s_command
{
	char				*str_input;
	int					len;
	enum e_token		type;
	enum e_state		state;
	struct s_command	*next;
}						t_command;

// IT IS IMPORTANT TO REMOVE THE LIBRARIES WE USED
# include <string.h>

// call all the libriries we need in the project
# include "./includes/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// function we use
int						ft_search(char *s, char *d);
int						ft_isspace(char c);
void					print_str_input(void *str_input);
void					print_t_command(t_command *cmd);
t_token					ft_get_token(char str_input);
int 					ft_check_input(char str_input);
t_state					ft_get_state(t_idx *var, char str_input);
void					ft_lexer(char *input, t_command **x);




void  	ft_exute( t_command *list , char **env);
int 	ft_strcmp(char *s1, char *s2);


///////            Commands         ///////
void 	ft_cd(t_command *list);
void 	ft_pwd(t_command *va_list);

#endif