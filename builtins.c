/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:40:58 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/19 18:55:24 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	env_free(env());
	ft_putstr("exit\n");
	exit(1);
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

void	ft_newpwd(t_env *env)
{
	char	pwd[INPUT_SIZE + 5];
	size_t	i;

	set_oldpwd(env, env->ev[find_param(env->ev, "PWD")]);
	getpwd(pwd);
	add_var_to_env(env, pwd);
	i = ft_strlen(pwd);
	while (pwd[i] != '/' && pwd[i] != '=')
		--i;
	if (env->dir)
		free(env->dir);
	env->dir = ft_strdup((pwd[i + 1] == 0 ? 0 : 1) + pwd + i);
}

void	ft_cd(char **split, t_env *env, size_t i)
{
	char *reg;

	if (split[1] && split[2] && split[3])
		return (error(-7, NULL));
	else if (split[1] && split[1][0] == '-' && !split[1][1])
	{
		if (chdir(env->ev[find_param(env->ev, "OLDPWD")] + 7) == -1)
			return (error(-1, NULL));
	}
	else if (split[1] && split[2])
	{
		if (!(reg = ft_cd_regex(split, -1)))
			return ;
		if (chdir(reg) == -1)
			return (error(-9, reg));
		free(reg);
	}
	else if (split[1])
	{
		if (chdir(split[1]) == -1)
			return (error(-1, NULL));
	}
	else if (chdir(env->ev[find_param(env->ev, "HOME")] + 5) == -1)
		return (error(-8, NULL));
	ft_newpwd(env);
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
