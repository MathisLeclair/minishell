/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:14:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/18 17:51:51 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

void	free_double_array(char **tab)
{
	int i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}
