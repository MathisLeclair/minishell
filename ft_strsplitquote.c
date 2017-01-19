/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:58:49 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/19 16:39:47 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cnt_parts(const char *s, char c)
{
	int i;
	int nw;
	int	done;

	i = 0;
	nw = 0;
	done = 0;
	while (s[i])
	{
		if (i != 0 && (s[i - 1] == '\'' || s[i - 1] == '"') && done == s[i - 1])
			done = 0;
		else if (i != 0 && (s[i - 1] == '\'' || s[i - 1] == '"') && done == 0)
			done = s[i - 1];
		if (s[i] != c && (i == 0 || s[i - 1] == c) && done == 0)
			nw++;
		++i;
	}
	return (nw);
}

static int	ft_wlen(const char *s, char c)
{
	int	l;
	int	done;

	l = 0;
	done = 0;
	while ((*s != c || (*s == c && done != 0)) && *s)
	{
		if ((*s == '\'' || *s == '"') && done == *s)
			done = 0;
		else if ((*s == '\'' || *s == '"') && done == 0)
			done = *s;
		l++;
		s++;
	}
	return (l);
}

char		**ft_strsplitquote(char const *s, char c)
{
	char	**a;
	int		nbw;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	nbw = ft_cnt_parts((const char *)s, c);
	a = malloc(sizeof(char *) * nbw + 1);
	if (a == NULL)
		return (NULL);
	while (nbw--)
	{
		while (*s == c && *s != '\0')
			s++;
		a[i] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
		if (a[i] == NULL)
			return (NULL);
		s = s + ft_wlen(s, c);
		i++;
	}
	a[i] = NULL;
	return (a);
}
