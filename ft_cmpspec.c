/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:49:00 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 14:58:18 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmpspec(char *s1, char *str)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while(str[i])
	{
		if (!s1[i])
			return (-1);
		if (str[i] == s1[i])
			++k;
		++i;
	}
	if (k == (int)ft_strlen(str))
		if (s1[ft_strlen(str)] == ' ' || s1[ft_strlen(str)] == '\t')
			return (1);
	return (0);
}
