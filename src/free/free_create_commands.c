/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_create_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:54:59 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 16:11:29 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_files(t_infos ***infos, int i)
{
	if ((**infos)->cmd[i]->infile != NULL)
		free((**infos)->cmd[i]->infile);
	if ((**infos)->cmd[i]->outfile != NULL)
		free((**infos)->cmd[i]->outfile);
	if ((**infos)->cmd[i]->heredoc != NULL)
	{
		free((**infos)->cmd[i]->heredoc);
		(**infos)->cmd[i]->heredoc = NULL;
	}
	if ((**infos)->cmd[i]->heredoc_file_name != NULL)
	{
		unlink((**infos)->cmd[i]->heredoc_file_name);
		free((**infos)->cmd[i]->heredoc_file_name);
		(**infos)->cmd[i]->heredoc_file_name = NULL;
	}
}

void	free_create_commands(t_infos **infos)
{
	int	i;

	if (*infos != NULL)
	{
		if ((*infos)->cmd != NULL)
		{
			i = 0;
			while ((*infos)->cmd[i] != NULL)
			{
				clear_tab((*infos)->cmd[i]->args);
				if ((*infos)->cmd[i]->is_empty)
					free((*infos)->cmd[i]->args);
				if ((*infos)->cmd[i]->path != NULL)
					free((*infos)->cmd[i]->path);
				clear_files(&infos, i);
				free((*infos)->cmd[i]);
				i++;
			}
			free((*infos)->cmd);
		}
	}
}

static void	clear_files_error(t_infos *infos, int i)
{
	if ((infos)->cmd[i]->infile != NULL)
		free((infos)->cmd[i]->infile);
	if ((infos)->cmd[i]->outfile != NULL)
		free((infos)->cmd[i]->outfile);
	if ((infos)->cmd[i]->heredoc != NULL)
	{
		free((infos)->cmd[i]->heredoc);
		(infos)->cmd[i]->heredoc = NULL;
	}
	if ((infos)->cmd[i]->heredoc_file_name != NULL)
	{
		unlink((infos)->cmd[i]->heredoc_file_name);
		free((infos)->cmd[i]->heredoc_file_name);
		(infos)->cmd[i]->heredoc_file_name = NULL;
	}
}

static void	free_fd_commands_error(t_infos *infos, int i)
{
	t_cmd	*cmd;

	cmd = (infos)->cmd[i];
	if (cmd->fd_in != -1 && cmd->fd_in != 0 && cmd->fd_in != 1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1 && cmd->fd_out != 0 && cmd->fd_out != 1)
		close(cmd->fd_out);
}

void	free_create_commands_error(t_infos *infos)
{
	int	i;

	i = 0;
	if (infos != NULL)
	{
		if ((infos)->cmd != NULL)
		{
			while ((infos)->cmd[i] != NULL)
			{
				clear_tab((infos)->cmd[i]->args);
				if ((infos)->cmd[i]->is_empty)
					free((infos)->cmd[i]->args);
				if ((infos)->cmd[i]->path != NULL)
					free((infos)->cmd[i]->path);
				free_fd_commands_error(infos, i);
				clear_files_error(infos, i);
				free((infos)->cmd[i]);
				i++;
			}
			free((infos)->cmd);
		}
	}
}
