/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:34:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/12 14:34:02 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int i, char *str)
{
	if (i == 1)
		exit(0);
	else if (i == -1)
		ft_putstr("No such file or directory\n");
	else if (i == -2)
		ft_printf("shell: command not found : %s\n", str);
	else if (i == -3)
		ft_printf("shell error\n");
	else if (i == -4)
		ft_printf("shell: exec format error: %s\n", str);
	else if (i == -5)
		ft_printf("shell: permission denied: %s\n", str);
	else if(i == - 6)
	{
		ft_putstr("exit\n");
		exit(0);
	}
}
