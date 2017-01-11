/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:55:44 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/11 19:25:10 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_fork(t_env *env, char **input)
{
	pid_t	i;
	int		status;
	char	*tmp;
	char	*tmp2;
	int		t;
	struct stat buf[INPUT_SIZE];
	char	pwd[INPUT_SIZE + 4];

	getpwd(pwd);
	t = 0;
	i = fork();
	if (i == 0)
	{
		if ((i = find_param_env(env, "PATH")) == -1)
		{
			error(-2, *input);
			exit(0);
		}
		env->path = ft_strsplit(env->ev[i] + 5, ':');
		i = 0;
		while (env->path[i])
		{
			tmp = ft_strjoin(env->path[i], "/");
			tmp2 = ft_strjoin(tmp, *input);
			execve(tmp2, input, env->ev);
			free(tmp);
			free(tmp2);
			++i;
		}
		if (ft_cmpspec(*input, "./", 0) == 1)
		{
			tmp = ft_strjoin(pwd + 4, *input + 1);
			i = execve(tmp, input, env->ev);
			if (lstat(tmp, buf) == -1)
				error(-1, NULL);
			else if (!(buf->st_mode & S_IXUSR) || !(buf->st_mode & S_IROTH))
				error(-5, *input);
			else
				error(-4, *input);
			free(tmp);
			exit(0);
		}
		error(-2, *input);
		exit(0);
	}
	else
		if (wait(&status) == -1)
			error(-3, NULL);
}