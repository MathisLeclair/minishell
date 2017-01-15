/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:16:47 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/15 17:56:24 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_str(char *str, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(ft_strlen(str) + 1);
	while (str[i] && i < start)
	{
		tmp[i] = str[i];
		++i;
	}
	i = end;
	while (str[i])
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

char	*pick_str(char *str, int start, int end)
{
	int		i;
	int		t;
	char	*tmp;

	i = start;
	t = 0;
	tmp = malloc(end - start + 2);
	while(str[i] && i < end)
	{
		tmp[t] = str[i];
		++i;
		++t;
	}
	tmp[t]= '\0';
	free(str);
	return (tmp);
}

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

void	reco_env(t_env *env, char **split, int j, int bool)
{
	int 	i;
	t_env	*envbis;

	envbis = malloc(sizeof(t_env));
	set_env(envbis, env->ev);
	if (split[1] && ft_cmpspec(split[1], "-i") == 1)
	{
		++j;
		envbis->ev = NULL;
	}
	envbis->input = env->input;
	while (split[++j])
	{
		bool = 0;
		i = -1;
		while (split[j][++i])
			if (split[j][i] == '=')
			{
				add_var_to_env(envbis, split[1]);
				bool = 1;
			}
		if (i == (int)ft_strlen(split[j]) && bool == 0)
		{
			envbis->input = ft_strstr(env->input, split[j - 1]) + ft_strlen(split[j - 1]);
			ft_reco_cmd(envbis);
			bool = 3;
			break ;
		}
	}
	if (bool != 3)
		print_env(envbis);
}
