/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:39:33 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/10 13:39:52 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar(t_env *env)
{
	int		i;
	int		k;
	char	*str;

	str = malloc(INPUT_SIZE);
	i = 0;
	k = 0;
	while (env->input[i])
	{
		if (env->input[i] == '$')
		{
			while (ft_isalpha(env->input[i]))
			{
				str[k] = env->input[i];
				++i;
				++k;
			}
		}
		++i;
	}
}
