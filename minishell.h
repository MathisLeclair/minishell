/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:18:04 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 17:43:06 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# define PROMPT "$\e[0;31mms\e[0m>"
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# define INPUT_SIZE 4096
# define BUFF_SIZE 32

typedef struct	s_env
{
	char	*input;
	char	**ev;
	char	*dir;
	char	**path;
	int		i;
}				t_env;

/*
**getnextline
*/

int				get_next_line(const int fd, char **line);

/*
** ft_cmpspec.c
*/

int				ft_cmpspec(char *s1, char *str);

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

int				find_param_env(t_env *env, char *str);
void			add_var_to_env(t_env *env, char *str);
void			suppr_var_env(t_env *env, char *str);

/*
**cmd_env.c
*/

void			print_env(t_env *env);
void			reco_env(t_env *env, char *input);

/*
**ft_dollar.c
*/

void			ft_dollar(t_env *env, int i);

/*
**set_env.c
*/

void			set_oldpwd(t_env *env, char *str);
void			set_env(t_env *env, char **ev);

/*
**fork.c
*/

void			ft_fork(t_env *env, char **input);

/*
**setenv.c
*/

void			getpwd(char *pwd);

char		**ft_strsplitquote(char const *s, char c);

#endif
