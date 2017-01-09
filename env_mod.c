/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:10:15 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 16:48:42 by bfrochot         ###   ########.fr       */
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

void	add_var_to_env(t_env *env, char *str)
{
	int		i;
	char	**new;

	while (*str == ' ' || *str == '\t')
		++str;
	str[ft_strlen(str) - 1] = '\0';
	i = 0;
	while (env->ev[i])
		++i;
	new = malloc(sizeof(char *) * (i + 2));
	new[i + 1] = 0;
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

	while (*str == ' ' || *str == '\t')
		++str;
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
