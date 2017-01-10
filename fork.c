/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:55:44 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/10 21:51:20 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_fork(t_env *env, char **input)
{
	pid_t	i;
	int		status;
	char	*tmp;
	char	*tmp2;

	i = fork();
	if (i == 0)
	{
		i = find_param_env(env, "PATH");
		env->path = ft_strsplit(env->ev[i] + 5, ':');
		i = 0;
		while (env->path[i])
		{
			tmp = ft_strjoin(env->path[i], "/");
			printf("tmp = %p\n", tmp);
			tmp2 = ft_strjoin(tmp, *input);
			printf("tmp2 = %p\n", tmp2);
			execve(tmp2, input, env->ev);
			free(tmp);
			free(tmp2);
			++i;
		}
		error(-2, *input);
		exit(0);
	}
	else
		if (wait(&status) == -1)
			error(-3, NULL);
}
