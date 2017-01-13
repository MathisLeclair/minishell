/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 18:20:41 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_input(char *input)
{
	int		i;
	int		j;
	char	newinp[ft_strlen(input)];
	char	**a;

	i = -1;
	j = -1;
	while (input[++i])
		if (input[i] != '\t' && ++j != -1)
			newinp[j] = input[i];
	newinp[j + 1] = 0;
	a = ft_strsplitquote(newinp, ' ');
	i = -1;
	while (a[++i])
	{
		if ((a[i][0] == '\'' && a[i][ft_strlen(a[i]) - 1] == '\'') ||
			(a[i][0] == '\"' && a[i][ft_strlen(a[i]) - 1] == '\"'))
		{
			j = 0;
			while (a[i][++j])
				a[i][j - 1] = a[i][j];
			a[i][ft_strlen(a[i]) - 2] = 0;
		}
	}
	return (a);
}

int		ft_read(t_env *env)
{
	char *input;

	if(get_next_line(1, &input) == 0)
		error(-6, NULL);
	if (*input != '\0')
	{
		env->input = input;
		ft_dollar(env, -1);
		ft_reco_cmd(env->input, env);
	}
	if (env->input)
		(env->input)[0] = '\0';
	ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', env->dir, PROMPT);
	return (0);
}

void	ft_echo(char *input)
{
	while (input[0] == ' ' || input[0] == '\t')
		++input;
	if (!input)
		ft_putchar('\n');
	ft_putstr(input);
	ft_putchar('\n');
}

void	ft_cd(char *inp, t_env *env)
{
	char pwd[INPUT_SIZE + 5];
	size_t i;

	if (!*inp)
	{
		if (chdir("/") == -1)
		{
			error(-1, NULL);
			return ;
		}
	}
	else
		if (chdir(inp + 1) == -1)
		{
			error(-1, NULL);
			return ;
		}
	set_oldpwd(env, env->ev[find_param_env(env, "PWD")]);
	getpwd(pwd);
	add_var_to_env(env, pwd);
	env->dir = ft_strdup(pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	env->dir = ft_strdup((pwd[i + 1] == 0 ?  0 : 1) + pwd + i);
}

void	ft_reco_cmd(char *input, t_env *env)
{
	char	**split;
	int		i;

	split = ft_split_input(input);
	i = 0;
	if (ft_cmpspec(input, "cd") == 1)
		ft_cd(input + 2, env);
	else if (ft_cmpspec(input, "echo") == 1)
		ft_echo(env->input + 4);
	else if (ft_cmpspec(input, "setenv") == 1)
	{
		while (split[++i])
			add_var_to_env(env, split[i]);
	}
	else if (ft_cmpspec(input, "unsetenv") == 1)
	{
		while (split[++i])
			suppr_var_env(env, split[i]);
	}
	else if (ft_cmpspec(input, "env") == 1)
		reco_env(env, input);
	else if (*input == '\n')
		return ;
	else
		ft_fork(env, split);
}
