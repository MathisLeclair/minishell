/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:16:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/11 20:30:39 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(t_env *env)
{
	char 	*tmp;
	char	*tmp2;
	int 	i;
	int		t;

	i = find_param_env(env, "SHLVL");
	if (i > -1)
		t = ft_atoi(env->ev[i] + 6);
	else
		t = 0;
	++t;
	tmp2 = ft_itoa(t);
	tmp = ft_strjoin("SHLVL=", tmp2);
	add_var_to_env(env, tmp);
	free(tmp);
	free(tmp2);
}

t_env	*env(void)
{
	static t_env	*env = NULL;

	if (env == NULL)
		env = malloc(sizeof(t_env));
	return (env);
}

int		main(int ac, char **av, char **ev)
{
	t_env *envi;

	envi = env();
	set_env(env(), ev);
	signal(SIGINT, exit);
	signal(SIGQUIT, exit);
	signal(SIGTERM, exit);
	(void)av;
	(void)ac;
	shlvl(env());
	ft_printf("\e[1;32m%C\e[0;m \e[1;36m%s \e[0m%s", L'✈', envi->dir, PROMPT);
	while (1)
	{
		if ((ft_read(env())) == 0)
			continue ;
		else if (ft_read(env()) == -1)
			break ;
	}
	ft_putstr("GOODBYE\n");
}
