/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/14 18:08:39 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_suppr_quotes(char *str, int i, int j)
{
	char	quote;

	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			++i;
			while (str[i] && str[i] != quote)
			{
				str[j] = str[i];
				++j;
				++i;
			}
			if (str[i] && str[i + 1])
				++i;
			else
				break ;
		}
		str[j] = str[i];
		++i;
		++j;
	}
	str[j] = 0;
}

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
		ft_suppr_quotes(a[i], 0, 0);
	return (a);
}

int		ft_read(t_env *env)
{
	char *input;
	char **inputspl;
	int i;

	i = -1;
	if(get_next_line(1, &input) == 0)
		error(-6, NULL);
	inputspl = ft_strsplitquote(input, ';');
	if (*input != '\0')
	{
		while (inputspl[++i])
		{
			env->input = inputspl[i];
			ft_dollar(env, -1);
			ft_reco_cmd(env);
		}
	}
	if (env->input)
		(env->input)[0] = '\0';
	ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', env->dir, PROMPT);
	return (0);
}

void	ft_echo(char *input)
{
	int i;

	i = 0;
	while (input[i] != 'o')
		++i;
	ft_suppr_quotes(input, 0, 0);
	if (input[i + 1])
		ft_putstr(input + i + 2);
	ft_putchar('\n');
}

void	ft_cd(char **split, t_env *env)
{
	char pwd[INPUT_SIZE + 5];
	size_t i;

	if (split[1] && split[2] && split[3])
	{
		error(-7, NULL);
		return ;
	}
	else if (split[1] && split[2])
		return ;
	else if (split[1])
	{
		if (chdir(split[1]) == -1)
		{
			error(-1, NULL);
			return ;
		}
	}
	else
	{
		if (chdir("/") == -1)
		{
			error(-1, NULL);
			return ;
		}
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

void	ft_reco_cmd2(char *input, t_env *env, char **split)
{
	if (ft_cmpspec(input, "patate") == 1)
			ft_putstr("[1]    35674 segmentation fault  ./minishell\n");
	else
		ft_fork(env, split);
}

void	ft_reco_cmd(t_env *env)
{
	char	**split;
	int		i;

	split = ft_split_input(env->input);
	i = 0;
	if (ft_cmpspec(split[0], "cd") == 1)
		ft_cd(split, env);
	else if (ft_cmpspec(split[0], "echo") == 1)
		ft_echo(env->input);
	else if (ft_cmpspec(split[0], "setenv") == 1)
		while (split[++i])
			add_var_to_env(env, split[i]);
	else if (ft_cmpspec(split[0], "unsetenv") == 1)
		while (split[++i])
			suppr_var_env(env, split[i]);
	else if (ft_cmpspec(split[0], "env") == 1)
		reco_env(env, env->input);
	else if (*env->input == '\n')
		return ;
	else
		ft_reco_cmd2(env->input, env, split);
}
