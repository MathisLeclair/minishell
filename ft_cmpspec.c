/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:49:00 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 19:10:03 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmpspec(char *s1, char *str, int p)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (!s1[i])
			return (-1);
		if (str[i] == s1[i])
			++k;
		++i;
	}
	if (k == (int)ft_strlen(str))
		if (s1[ft_strlen(str)] == ' ' || s1[ft_strlen(str)] == '\t' || p == 0)
			return (1);
	return (0);
}
