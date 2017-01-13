/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:49:00 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/13 18:32:13 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmpspec(char *input, char *tofind)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (input[i] == ' ' || input[i] == '\t')
		++i;
	while (tofind[k] && input[i + k] == tofind[k])
		++k;
	if (k == ft_strlen(tofind))
		return (1);
	return (0);
}
