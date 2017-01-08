/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/08 17:40:29 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_read(char *buf, t_env *env)
{
	int		ret;
	int		size;

	size = 0;
	env->input = malloc(INPUT_SIZE);
	ret = read(0, buf, 500);
	if (ret < 0)
		return (-1);
	buf[ret] = '\0';
	ft_strlcat(env->input, buf, INPUT_SIZE);
	size += ret;
	if (size == 0)
		return(-1);
	if (size >= INPUT_SIZE)
	{
		size = INPUT_SIZE - 1;
		env->input[size-1] = '\n';
	}
	if (env->input[size-1] != '\n')
		return (0);
	ft_reco_cmd(env->input, env); 
	env->input[0] = '\0';
	size = 0;
	ft_putstr(PROMPT);
	return (0);
}

void	ft_reco_cmd(char *input, t_env *env)
{
	// char **tab;

	// (void)input;
	(void)env;
	printf("%s", input);
	// execve("/bin/ls", NULL, env->environ);
}
