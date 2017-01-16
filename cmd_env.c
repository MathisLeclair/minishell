/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:16:47 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/16 17:26:11 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*remove_str(char *str, int start, int end)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = malloc(ft_strlen(str) + 1);
// 	while (str[i] && i < start)
// 	{
// 		tmp[i] = str[i];
// 		++i;
// 	}
// 	i = end;
// 	while (str[i])
// 	{
// 		tmp[i] = str[i];
// 		++i;
// 	}
// 	tmp[i] = '\0';
// 	free(str);
// 	return (tmp);
// }

// char	*pick_str(char *str, int start, int end)
// {
// 	int		i;
// 	int		t;
// 	char	*tmp;

// 	i = start;
// 	t = 0;
// 	tmp = malloc(end - start + 2);
// 	while(str[i] && i < end)
// 	{
// 		tmp[t] = str[i];
// 		++i;
// 		++t;
// 	}
// 	tmp[t]= '\0';
// 	free(str);
// 	return (tmp);
// }

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

void	reco_env(t_env *env, char **split, int j)
{
	int 	i;
	char	c;
	t_env	*envbis;

	i = 0;
	c = 0;
	while (split[++i] && split[i][0] == '-')
	{
		j = 0;
		while (split[i][++j])
			if (split[i][j] == 'i')
				c = 1;
			else
			{
				ft_putstr("MAUVAISE OPTION. JE NE COMPRENDS QUE -i !\n");
				return ;
			}
	}
	envbis = malloc(sizeof(t_env));
	if (c == 1)
	{
		envbis->ev = malloc(sizeof(char **));
		envbis->ev[0] = 0;
	}
	else
		set_env(envbis, env->ev);
	while (split[i])
	{
		j = -1;
		while (split[i][++j] && split[i][j] != '=')
			;
		if (split[i][j] == '=')
			add_var_to_env(envbis, split[i]);
		else
		{
			envbis->input = ft_strdup((*(ft_strstr(env->input, split[i]) - 1) == '\'' || *(ft_strstr(env->input, split[i]) - 1) == '"') ? ft_strstr(env->input, split[i]) - 1 : ft_strstr(env->input, split[i]));
			ft_reco_cmd(envbis);
			break ;
		}
		++i;
	}
	if (!split[i])
		print_split(envbis->ev);
}
