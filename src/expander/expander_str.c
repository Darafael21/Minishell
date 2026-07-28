/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:28:51 by darafael          #+#    #+#             */
/*   Updated: 2026/07/28 11:28:51 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var(char *str, int *skip)
{
	int		len;
	char	*name;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = ft_substr(str, 0, len);
	*skip = len;
	return (name);
}

char	*expand_brace_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		skip;

	var_name = get_var(&str[*i + 2], &skip);
	if (!var_name)
		return (NULL);
	if (str[*i + 2 + skip] == ':' && str[*i + 2 + skip + 1] == '-')
	{
		var_value = get_env(shell->env, var_name);
		return (free(var_name),
			expand_brace_default(str, i, var_value, *i + 2 + skip + 2));
	}
	if (skip == 0 || str[*i + 2 + skip] != '}')
		return (free(var_name), (*i)++, ft_strdup("$"));
	var_value = get_env(shell->env, var_name);
	free(var_name);
	*i += skip + 3;
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

static char	*handle_dollar(char *str, char *result, int *i, t_shell *shell)
{
	char	*expanded;
	char	*tmp;

	expanded = expand_var(str, i, shell);
	if (!expanded)
	{
		free(result);
		return (NULL);
	}
	tmp = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	return (tmp);
}

static char	*append_str_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	int		i;
	int		sq;
	int		dq;

	result = ft_strdup("");
	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] && result)
	{
		if (update_quote_state(str[i], &sq, &dq))
			i++;
		else if (str[i] == '\\' && dq && str[i + 1]
			&& escapable_quote(str[i + 1]))
			result = (i++, append_str_char(result, str[i++]));
		else if (str[i] == '$' && !sq && str[i + 1]
			&& !(dq && str[i + 1] == '"'))
			result = handle_dollar(str, result, &i, shell);
		else
			result = append_str_char(result, str[i++]);
	}
	return (result);
}
