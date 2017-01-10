/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:16:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/10 21:39:21 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*env(void)
{
	static t_env	env;

	return (&env);
}

int main(int ac, char **av, char **ev)
{
	t_env *envi;

	envi = env();
	set_env(env(), ev);
	signal(SIGINT, exit);
	signal(SIGQUIT, exit);
	signal(SIGTERM, exit);
	(void)av;
	(void)ac;
	ft_printf("%s%s %s%s", "\e[0;32m",envi->dir, PROMPT, "\e[0m");
	while (1)
	{
		if ((ft_read(env())) == 0)
			continue ;
		else if(ft_read(env()) == -1)
			break ;
	}
	ft_putstr("GOODBYE\n");
}
