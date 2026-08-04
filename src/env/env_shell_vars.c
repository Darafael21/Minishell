/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shell_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:24:48 by darafael          #+#    #+#             */
/*   Updated: 2026/08/04 08:56:24 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
