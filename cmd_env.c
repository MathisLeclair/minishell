/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:16:47 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/12 11:47:05 by mleclair         ###   ########.fr       */
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
	// free(str);
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
	// free(str);
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


void	reco_env(t_env *env, char *input)
{
	int i;
	int t;
	char *str;

	i = 0;
	t = 0;
	input += 4;
	while (input[i])
	{
		if (input[i] == '=')
		{
			while (input[i] && input[i] != ' ' && input[i] != '\t')
				--i;
			++i;
			t = i + 1;
			while (input[t] && input[t] != ' ' && input[t] != '\t')
				++t;
			str = pick_str(input, i, t);
			input = remove_str(input, i, t);
			add_var_to_env(env, str);
			free(str);
		}
		++i;
	}
	print_env(env);
}
