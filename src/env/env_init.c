/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:27:08 by darafael          #+#    #+#             */
/*   Updated: 2026/07/28 11:27:11 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_shlvl(t_env **head)
{
	char	*val;
	int		lvl;
	char	*new_val;

	val = get_env(*head, "SHLVL");
	lvl = 1;
	if (val)
		lvl = ft_atoi(val) + 1;
	new_val = ft_itoa(lvl);
	set_env(head, "SHLVL", new_val);
	free(new_val);
}

static void	init_pwd(t_env **head)
{
	char	*pwd;

	if (get_env(*head, "PWD"))
		return ;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		set_env(head, "PWD", pwd);
		free(pwd);
	}
}

static void	init_oldpwd(t_env **head)
{
	t_env	*cur;

	cur = *head;
	while (cur)
	{
		if (ft_strcmp(cur->key, "OLDPWD") == 0)
			return ;
		cur = cur->next;
	}
	env_add_back(head, new_env_node("OLDPWD", NULL));
}

static void	setup_default_env(t_env **head)
{
	init_shlvl(head);
	init_pwd(head);
	init_oldpwd(head);
}

t_env	*init_env(char **envp)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;
	t_env	*head;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		key = ft_substr(envp[i], 0, eq - envp[i]);
		value = ft_strdup(eq + 1);
		if (ft_strcmp(key, "_") != 0)
			env_add_back(&head, new_env_node(key, value));
		free(key);
		free(value);
		i++;
	}
	setup_default_env(&head);
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