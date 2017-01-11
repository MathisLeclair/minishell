/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:10:15 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/11 11:16:55 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_param_env(t_env *env, char *str)
{
	int i;
	int j;

	i = 0;
	while (env->ev[i])
	{
		j = 0;
		while (str[j] && str[j] != '=' && str[j] == env->ev[i][j])
			j++;
		if (env->ev[i][j] == '=')
			break ;
		++i;
	}
	if (env->ev[i])
		return (i);
	return(-1);
}

void	modif_var_env(t_env *env, char *str, int i)
{
	char	*new_para;

	new_para = ft_strdup(str);
	free(env->ev[i]);
	env->ev[i] = new_para;
}

void	add_var_to_env(t_env *env, char *str)
{
	int		i;
	char	**new_env;

	i = find_param_env(env, str);
	if (i == -1)
	{
		i = 0;
		while (env->ev[i])
			++i;
		new_env = malloc(sizeof(char *) * (i + 2));
		new_env[i + 1] = 0;
		i = -1;
		while (env->ev[++i])
			new_env[i] = env->ev[i];
		new_env[i] = ft_strdup(str);
		free(env->ev);
		env->ev = new_env;
	}
	else
		modif_var_env(env, str, i);
}

void	suppr_var_env(t_env *env, char *str)
{
	int i;

	i = find_param_env(env, str);
	if (i != -1)
	{
		free(env->ev[i]);
		while (env->ev[i] && ++i)
			env->ev[i - 1] = env->ev[i];
	}
}
