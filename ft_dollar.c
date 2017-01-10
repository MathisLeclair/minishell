/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:39:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/10 14:53:47 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replacestr(t_env *env, int ret, int sav)
{
	char	*rez;
	int		i;
	int		u;

	i = 0;
	u = 0;
	rez = malloc(INPUT_SIZE * 2);
	ft_bzero(rez, INPUT_SIZE * 2);
	while (i < sav)
	{
		rez[i] = env->input[i];
		++i;
	}
	while (env->ev[ret][u] != '=')
		++u;
	if (env->ev[ret][u + 1])
		++u;
	while (env->ev[ret][sav] != ' ' && env->ev[ret][sav] != '\t')
		++sav;
	ft_strcat(rez, env->ev[ret] + u);
	ft_strcat(rez, env->input + sav);
	free(env->input);
	env->input = rez;
}

void	ft_dollar(t_env *env)
{
	int		i;
	int		k;
	int		sav;
	char	*str;

	str = malloc(INPUT_SIZE);
	i = 0;
	k = 0;
	while (env->input[i])
	{
		if (env->input[i] == '$')
		{
			sav = i;
			++i;
			while (env->input[i] && env->input[i] != ' ' && env->input[i] != '\t')
			{
				str[k] = env->input[i];
				++i;
				++k;
			}
			str[k] = '\0';
			ft_replacestr(env, find_param_env(env, str), sav);
		}
		++i;
	}
}
