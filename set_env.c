/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:47:40 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/11 19:33:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getpwd(char *pwd)
{
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	getcwd(pwd + 4, INPUT_SIZE);
}

void	set_oldpwd(t_env *env)
{
	char	oldpwd[INPUT_SIZE + 7];

	oldpwd[0] = 'O';
	oldpwd[1] = 'L';
	oldpwd[2] = 'D';
	oldpwd[3] = 'P';
	oldpwd[4] = 'W';
	oldpwd[5] = 'D';
	oldpwd[6] = '=';
	getcwd(oldpwd + 7, INPUT_SIZE);
	add_var_to_env(env, oldpwd);
}

void	set_env(t_env *env, char **ev)
{
	int		i;
	char	pwd[INPUT_SIZE + 4];

	i = 0;
	env->input = NULL;
	env->path = NULL;
	while (ev[i])
		++i;
	env->ev = malloc(sizeof(char *) * (i + 1));
	env->ev[i] = 0;
	while (i--)
		env->ev[i] = ft_strdup(ev[i]);
	env->dir = malloc(INPUT_SIZE);
	getcwd(env->dir, INPUT_SIZE);
	if (find_param_env(env, "PWD") == -1)
	{
		getpwd(pwd);
		add_var_to_env(env, pwd);
	}
}
