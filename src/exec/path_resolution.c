/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:25:38 by darafael          #+#    #+#             */
/*   Updated: 2026/07/31 13:25:38 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_in_paths(char **paths, char *command)
{
	int			i;
	char		*tmp;
	char		*slash;
	struct stat	st;

	i = 0;
	while (paths[i] != NULL)
	{
		slash = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = slash;
		tmp = ft_strjoin(paths[i], command);
		if (access(tmp, X_OK) == 0 && stat(tmp, &st) == 0
			&& !S_ISDIR(st.st_mode))
		{
			free_env_array(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_env_array(paths);
	return (NULL);
}

char	*resolve_path(char *command, t_env *lst)
{
	char	**paths;
	char	*path;

	if (!command || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) != 0)
			return (NULL);
		return (ft_strdup(command));
	}
	path = get_env(lst, "PATH");
	if (!path)
		path = "/usr/local/bin:/usr/bin:/bin";
	paths = ft_split(path, ':');
	return (search_in_paths(paths, command));
}
