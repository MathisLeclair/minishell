/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:34:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/19 16:53:54 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int i, char *str)
{
	if (i == -1)
		ft_putstr("No such file or directory\n");
	else if (i == -2)
		ft_printf("shell: command not found : %s\n", str);
	else if (i == -3)
		ft_printf("shell error\n");
	else if (i == -4)
		ft_printf("shell: exec format error: %s\n", str);
	else if (i == -5)
		ft_printf("shell: permission denied: %s\n", str);
	else if (i == -6)
	{
		ft_putstr("\n");
		exit(0);
	}
	else if (i == -7)
		ft_putstr("shell: error too many arguments.\n");
	else if (i == -8)
		ft_putstr("shell: cd: HOME not set\n");
	else if (i == -9)
		ft_printf("shell: cd: no such file or directory: %s\n", str);
	else if (i == -10)
		ft_printf("shell: cd: string not in pwd: %s\n", str);
}
