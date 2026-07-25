/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:51:55 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/20 10:27:47 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env   *init_env(char **envp)
{
    int     i;
    char    *eq;
    char    *key;
    char    *value;
    t_env   *head;

    head = NULL;
    i = 0;
    while (envp[i])
    {
        eq = ft_strchr(envp[i], '=');
        if (!eq)
        {
            i++;
            continue;
        }
        key = ft_substr(envp[i], 0, eq - envp[i]);
        value = ft_strdup(eq + 1);
        if (ft_strcmp(key, "_") != 0)
            env_add_back(&head, new_env_node(key, value));
        free(key);
        free(value);
        i++;
    }
    return (head);
}

void	increment_shlvl(t_env **env)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;

	shlvl_str = get_env(*env, "SHLVL");
	if (!shlvl_str)
		shlvl = 0;
	else
		shlvl = ft_atoi(shlvl_str);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	set_env(env, "SHLVL", new_shlvl);
	free(new_shlvl);
}

void	init_shell_vars(t_env **env)
{
	char	*pwd;

	if (!get_env(*env, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env(env, "PWD", pwd);
			free(pwd);
		}
	}
	if (!get_env(*env, "OLDPWD"))
		set_env(env, "OLDPWD", "");
}
