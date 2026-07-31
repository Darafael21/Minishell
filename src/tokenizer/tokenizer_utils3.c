/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:27:30 by darafael          #+#    #+#             */
/*   Updated: 2026/07/31 13:27:31 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_op(const char *s, size_t *i)
{
	char	*res;

	if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
	{
		res = dup_str(s + *i, 2);
		*i += 2;
	}
	else
	{
		res = dup_str(s + *i, 1);
		(*i)++;
	}
	return (res);
}
