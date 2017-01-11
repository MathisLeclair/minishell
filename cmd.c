/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:28:38 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/11 19:34:31 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_input(char *input)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			++i;
		else
		{
			if (i == 0)
				input[++j] = input[i];
			else if (input[i - 1] == ' ' || input[i - 1] == '\t')
			{
				input[++j] = ' ';
				input[++j] = input[i];
			}
			else
				input[++j] = input[i];
			++i;
		}
	}
	input[j + 1] = 0;
	return(ft_strsplit(input, ' '));
}

int		ft_read(t_env *env)
{
	char *input;

	if(get_next_line(1, &input) == 0)
		error(1, NULL);
	if (*input != '\0')
	{
		env->input = input;
		ft_dollar(env);
		ft_reco_cmd(input, env);
	}
	(env->input)[0] = '\0';
	ft_printf("%s%s %s%s", "\e[0;32m", env->dir, PROMPT, "\e[0m");
	return (0);
}

void	ft_echo(char *input)
{
	int		i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		++input;
	if (!input)
		ft_putchar('\n');
	ft_putstr(input);
	ft_putchar('\n');
}

void	ft_cd(char *inp, t_env *env)
{
	int		i;
	char	pwd[INPUT_SIZE + 4];

	i = 0;
	while (inp[i] && (inp[i] == ' ' || inp[i] == '\t' || inp[i] == '\n'))
		++inp;
	if (!inp[i])
	{
		if (chdir("/") == -1)
			error(-1, NULL);
		getcwd(env->dir, INPUT_SIZE);
		return ;
	}
	if (inp[ft_strlen(inp) - 1] == '\n')
		inp[ft_strlen(inp) - 1] = '\0';
	if (chdir(inp) == -1)
		error(-1, NULL);
	set_oldpwd(env);
	getcwd(env->dir, INPUT_SIZE);
	getpwd(pwd);
	add_var_to_env(env, pwd);

}

void	ft_reco_cmd(char *input, t_env *env)
{
	char	**split;
	int		i;

	split = ft_split_input(input);
	i = 0;
	if (ft_cmpspec(input, "cd", 0) == 1)
		ft_cd(input + 2, env);
	else if (ft_cmpspec(input, "echo", 0) == 1)
		ft_echo(input + 4);
	else if (ft_cmpspec(input, "setenv", 1) == 1)
	{
		while (split[++i])
			add_var_to_env(env, split[i]);
	}
	else if (ft_cmpspec(input, "unsetenv", 1) == 1)
	{
		while (split[++i])
			suppr_var_env(env, split[i]);
	}
	else if (ft_cmpspec(input, "env", 0) == 1)
		print_env(env);
	else if (*input == '\n')
		return ;
	else
		ft_fork(env, split);
}
