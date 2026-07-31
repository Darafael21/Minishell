/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:24:59 by darafael          #+#    #+#             */
/*   Updated: 2026/07/31 13:25:01 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	sort_env_array(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

char	**env_to_declare_array(t_env *lst)
{
	char	**res;
	char	*tmp;
	int		i;

	res = malloc(sizeof(char *) * (count_env_size(lst) + 1));
	i = 0;
	while (lst)
	{
		tmp = ft_strjoin("declare -x ", lst->key);
		if (!lst->value)
			res[i++] = tmp;
		else
		{
			res[i] = ft_strjoin(tmp, "=\"");
			free(tmp);
			tmp = ft_strjoin(res[i], lst->value);
			free(res[i]);
			res[i++] = ft_strjoin(tmp, "\"");
			free(tmp);
		}
		lst = lst->next;
	}
	res[i] = NULL;
	return (res);
}

void	print_export_err(char *name, t_shell *shell)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	shell->exit_status = 1;
}
