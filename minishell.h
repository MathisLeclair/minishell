/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:18:04 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 19:16:35 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# define PROMPT "$\e[0;31mms\e[0m>"
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# define INPUT_SIZE 4096

typedef struct	s_env
{
	char *input;
	char **ev;
	char *dir;
}				t_env;

/*
**getnextline
*/
# define BUFF_SIZE 32

int	get_next_line(const int fd, char **line);

/*
** ft_cmpspec.c
*/

int				ft_cmpspec(char *s1, char *str, int k);

/*
**cmd.c
*/

void			ft_reco_cmd(char *input, t_env *env);
int				ft_read(t_env *env);

/*
**error.c
*/

void			error(int i, char *str);

/*
**env_mod.c
*/

void			add_var_to_env(t_env *env, char *str);
void			suppr_var_env(t_env *env, char *str);
void			print_env(t_env *env);

#endif
