/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/18 13:42:48 by mleclair         ###   ########.fr       */
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
	char	**a;

	i = -1;
	a = ft_strsplitquote(input, ' ');
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
		while (inputspl[++i])
		{
			env->input = inputspl[i];
			ft_dollar(env, -1);
			ft_reco_cmd(env);
		}
	if (env->input)
		(env->input)[0] = '\0';
	if (env->savev && (i = -1))
	{
		while(env->ev[++i])
			free(env->ev[i]);
		free(env->ev);
		env->ev = env->savev;
		env->savev = NULL;
	}
	ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', env->dir, PROMPT);
	free(input);
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

char	*ft_cd_regex(char **split, int k)
{
	char pwd[INPUT_SIZE + 5];
	char *sav;
	char *reg;

	getpwd(pwd);
	if (!(sav = ft_super_strstr(pwd + 4, split[1])))
		error(-10, split[1]);
	if (!sav)
		return (NULL);
	reg = malloc(ft_strlen(pwd + 4) + ft_strlen(split[2])
	- ft_strlen(split[1]) + 1);
	while (pwd + 4 + ++k < sav)
		reg[k] = pwd[4 + k];
	reg[k] = 0;
	ft_strcat(reg + k, split[2]);
	ft_strcat(reg + k, sav + ft_strlen(split[1]));
	return (reg);
}

void	ft_cd(char **split, t_env *env, size_t i)
{
	char pwd[INPUT_SIZE + 5];
	char *reg;

	if (split[1] && split[2] && split[3])
		return (error(-7, NULL));
	else if (split[1][0] && !split[1][1] && split[1][0] == '-')
	{
		if (chdir(env->ev[find_param(env->ev, "OLDPWD")] + 7) == -1)
			return (error(-1, NULL));
	}
	else if (split[1] && split[2] && split[1][0] != '-')
	{
		if (!(reg = ft_cd_regex(split, -1)))
			return ;
		if (chdir(reg) == -1)
			return (error(-9, reg));
		free(reg);
	}
	else if (split[1] && split[1][0] != '-')
	{
		if (chdir(split[1]) == -1)
			return (error(-1, NULL));
	}
	else
		if (chdir(env->ev[find_param(env->ev, "HOME")] + 5) == -1)
			return (error(-8, NULL));
	set_oldpwd(env, env->ev[find_param(env->ev, "PWD")]);
	getpwd(pwd);
	add_var_to_env(env, pwd);
	env->dir = ft_strdup(pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	env->dir = ft_strdup((pwd[i + 1] == 0 ?  0 : 1) + pwd + i);
}

void	ft_exit()
{
	ft_putstr("exit\n");
	exit(1);
}

void	ft_reco_cmd2(char *input, t_env *env, char **split)
{
	if (ft_strcmp(input, "Patate") == 0)
			ft_putstr("[1]    35674 segmentation fault  ./minishell\n");
	else if (ft_strcmp(split[0], "exit") == 0)
	{
		env_free(env);
		free_double_array(split);
		ft_exit();
	}
	else if (ft_strcmp(split[0], "aperture") == 0)
		ft_aperture();
	else
		ft_fork(env, split);
	free_double_array(split);
}

void	ft_reco_cmd(t_env *env)
{
	char	**split;
	int		i;

	split = ft_split_input(env->input);
	i = 0;
	if (ft_strcmp(split[0], "cd") == 0)
		ft_cd(split, env, 0);
	else if (ft_strcmp(split[0], "echo") == 0)
		ft_echo(env->input);
	else if (ft_strcmp(split[0], "setenv") == 0)
		while (split[++i])
			add_var_to_env(env, split[i]);
	else if (ft_strcmp(split[0], "unsetenv") == 0)
		while (split[++i])
			suppr_var_env(env, split[i]);
	else if (ft_strcmp(split[0], "env") == 0)
		reco_env(env, split, 0);
	else if (*env->input == '\n')
		return ;
	else
		ft_reco_cmd2(env->input, env, split);
}
