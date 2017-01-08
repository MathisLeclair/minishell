/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:16:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/08 17:39:10 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_env *env, char **environ)
{
	int i;

	i = 0;
	env->input = NULL;
	while (environ[i])
		++i;
	env->environ = malloc(sizeof(char *) * (i + 1));
	env->environ[i] = 0;
	while (i--)
		env->environ[i] = ft_strdup(environ[i]);
}

t_env		*env(void)
{
	static t_env	env;

	return (&env);
}

void	ft_hello(int i)
{
	i = 0;
}

int main(int ac, char **av, char **environ)
{
	char *buf;

	set_env(env(), environ);
	buf = malloc(512);
	signal(SIGINT, ft_hello);
	signal(SIGCONT, ft_hello);	
	(void)av;
	(void)ac;
	// (void)environ;
	ft_putstr(PROMPT);
	while (1)
	{
		if ((ft_read(buf, env())) == 0)
			continue ;
		else if(ft_read(buf, env()) == -1)
			break ;
	}
	ft_putstr("GOODBYE\n");
}
