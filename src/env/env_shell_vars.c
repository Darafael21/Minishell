/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shell_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:24:48 by darafael          #+#    #+#             */
/*   Updated: 2026/07/31 13:24:49 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
