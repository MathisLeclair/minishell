/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:14:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/24 16:14:33 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	env_free2(t_env *env)
{
	int i;

	i = 0;
	if (env->savev && (i = -1))
	{
		while (env->savev[++i])
			free(env->savev[i]);
		free(env->savev);
	}
	if (env->path && (i = -1))
	{
		while (env->path[++i])
			free(env->path[i]);
		free(env->path);
	}
}

void	env_free(t_env *env)
{
	int i;

	i = -1;
	if (env)
	{
		if (env->input)
		{
			free(env->input);
			env->input = NULL;
		}
		if (env->dir)
			free(env->dir);
		if (env->ev)
		{
			while (env->ev[++i])
				free(env->ev[i]);
			free(env->ev);
		}
		env_free2(env);
	}
}

int		free_double_array(char **tab)
{
	int i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
	return (1);
}
