/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:10:15 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 18:17:01 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	int i;

	i = 0;
	while (env->ev[i])
	{
		ft_putstr(env->ev[i]);
		ft_putchar('\n');
		++i;
	}
}

int		find_param_env(t_env *env, char *str)
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
			break ;
		++i;
	}
	if (env->ev[i])
		return (i);
	else
		return(-1);
}

void	add_var_to_env(t_env *env, char *str)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;
	char	*new_para;

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
	{
		j = 0;
		while (env->ev[i][j] != '=')
			++j;
		new_para = malloc(ft_strlen(str) + j + 2);
		j = -1;
		while (env->ev[i][++j] != '=')
			new_para[j] = env->ev[i][j];
		new_para[j] = '=';
		k = -1;
		while (str[++k])
			new_para[j + k + 1] = str[k];
		new_para[j + k + 1] = 0;
		free(env->ev[i]);
		env->ev[i] = new_para;
	}
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
