/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:16:47 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/19 19:06:33 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
	{
		ft_putstr(split[i]);
		ft_putchar('\n');
	}
}

void	reco_env_options(t_env *env, char **split, int *i)
{
	char	c;
	int		j;

	while (split[++*i] && split[*i][0] == '-')
	{
		j = 0;
		while (split[*i][++j])
			if (split[*i][j] == 'i')
				c = 1;
			else
			{
				ft_putstr("BAD OPTION. I ONLY TAKE -i YOU ARSEHOLE!\n");
				return ;
			}
	}
	if (c == 1 && (c = -1))
	{
		env->savev = env->ev;
		env->ev = malloc(sizeof(char **));
		env->ev[0] = 0;
	}
}

void	reco_env(t_env *env, char **split, int j, int i)
{
	int k;

	reco_env_options(env, split, &i);
	while (split[i] && (j = -1))
	{
		while (split[i][++j] && split[i][j] != '=')
			;
		if (split[i][j] == '=')
			add_var_to_env(env, split[i]);
		else
		{
			k = 0;
			while (env->input[k] != 'v')
				++k;
			free(env->input);
			env->input = ft_strdup((*(ft_strstr(env->input + k, split[i]) - 1) == '\'' || *(ft_strstr(env->input + k, split[i]) - 1) == '"') ? ft_strstr(env->input + k, split[i]) - 1 : ft_strstr(env->input + k, split[i]));
			ft_reco_cmd(env);
			break ;
		}
		++i;
	}
	if (!split[i])
		print_split(env->ev);
}
