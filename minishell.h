/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:18:04 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/18 12:16:15 by mleclair         ###   ########.fr       */
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
	char	**savev;
	char	*dir;
	char	**path;
	int		i;
}				t_env;

/*
** main.c
*/

t_env			*env(void);

/*
** getnextline
*/

int				get_next_line(const int fd, char **line);

/*
** ft_cmpspec.c
*/

int				ft_cmpspec(char *s1, char *str);
char			*ft_super_strstr(const char *str1, const char *str2);

/*
**cmd.c
*/

void			ft_reco_cmd(t_env *env);
int				ft_read(t_env *env);

/*
**error.c
*/

void			error(int i, char *str);

/*
**env_mod.c
*/

int				find_param(char **split, char *str);
void			add_var_to_env(t_env *env, char *str);
void			suppr_var_env(t_env *env, char *str);

/*
**cmd_env.c
*/

void			print_split(char **split);
void			reco_env(t_env *env, char **input, int i);

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

/*
**ft_strsplitquote.c
*/

char		**ft_strsplitquote(char const *s, char c);

/*
** free.c
*/

void			env_free(t_env *env);
void			free_double_array(char **tab);

void	ft_aperture(void);

#endif
