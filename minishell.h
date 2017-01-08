/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:18:04 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/08 13:17:57 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# define PROMPT "$\e[0;31mminishell\e[0m>"
# include <signal.h>
# include <unistd.h>
# define INPUT_SIZE 4096

typedef struct	s_env
{
	char *input;
	char **environ;
}				t_env;

/*
cmd.c
*/
void	ft_reco_cmd();
int		ft_read(char *buf, t_env *env);

/*
error.c
*/
void	error(int i);

#endif