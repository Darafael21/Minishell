/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:28:56 by darafael          #+#    #+#             */
/*   Updated: 2026/07/28 12:39:29 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_brace_default(char *str, int *i, char *val, int start)
{
	int		len;

	len = 0;
	while (str[start + len] && str[start + len] != '}')
		len++;
	*i = start + len + 1;
	if (val && val[0])
		return (ft_strdup(val));
	return (ft_substr(str, start, len));
}

int	is_quoted_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			return (0);
		i++;
	}
	return (i > 0);
}

void	compact_empty_args(char **argv, int *keep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0' || keep[i])
			argv[j++] = argv[i];
		else
			free(argv[i]);
		i++;
	}
	argv[j] = NULL;
}

int	update_quote_state(char c, int *sq, int *dq)
{
	if (c == '\'' && !*dq)
	{
		*sq = !*sq;
		return (1);
	}
	if (c == '"' && !*sq)
	{
		*dq = !*dq;
		return (1);
	}
	return (0);
}
