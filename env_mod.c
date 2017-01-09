/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:10:15 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 15:17:33 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var_to_env(t_env *env, char *str)
{
	int i;
	char **new;

	i = 0;
	while (env->ev[i])
		++i;
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = 0;
	i = 0;
	while (env->ev[i])
	{
		new[i] = env->ev[i];
		++i;
	}
	new[i] = ft_strdup(str);
	free(env->ev);
	env->ev = new;
}

void	suppr_var_env(t_env *env, char *str)
{
	int i;
	int j;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (env->ev[i])
	{
		j = 0;
		while (str[j] && str[j] == env->ev[i][j])
			j++;
		if (j == len && env->ev[i][j + 1] == '=')
		{
			free(env->ev[i]);
			break ;
		}
		++i;
	}
	while (env->ev[i] && ++i)
		env->ev[i - 1] = env->ev[i];
}
