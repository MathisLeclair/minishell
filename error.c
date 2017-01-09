/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:34:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/09 18:18:01 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int i, char *str)
{
	if (i == 1)
		exit(0);
	if (i == -1)
		ft_putstr("No such file or directory\n");
	if (i == -2)
		ft_printf("shell: command not found : %s\n", str);
}
