/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:25:56 by darafael          #+#    #+#             */
/*   Updated: 2026/07/31 13:25:58 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_prepared_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->fd != -1)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	prepare_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*head;
	t_redir	*redir;

	head = cmd;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				redir->fd = handle_heredoc(redir->filename, shell,
						redir->quoted);
				if (redir->fd == -1)
					return (close_prepared_heredocs(head), -1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
