/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:28:13 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 16:15:34 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_normal(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->cmd_nb)
	{
		if (infos->cmd[i]->outtype == NORMAL)
			infos->cmd[i]->fd_out = 1;
		if (infos->cmd[i]->intype == NORMAL)
			infos->cmd[i]->fd_in = 0;
		i++;
	}
}

static void	create_file(t_infos **infos)
{
	int	i;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		if ((*infos)->cmd[i]->outtype == TRUNC)
		{
			(*infos)->cmd[i]->fd_out = open((*infos)->cmd[i]->outfile,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		if ((*infos)->cmd[i]->intype == FILE_REAL)
		{
			(*infos)->cmd[i]->fd_in = open((*infos)->cmd[i]->infile, O_RDONLY);
		}
		i++;
	}
}

static void	create_heredoc(t_infos **infos)
{
	int	i;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		if ((*infos)->cmd[i]->intype == HEREDOC)
		{
			(*infos)->cmd[i]->fd_in = open((*infos)->cmd[i]->heredoc_file_name,
					O_RDONLY);
		}
		i++;
	}
}

static void	create_append(t_infos **infos)
{
	int	i;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		if ((*infos)->cmd[i]->outtype == APPEND)
		{
			(*infos)->cmd[i]->fd_out = open((*infos)->cmd[i]->outfile,
					O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		i++;
	}
}

void	create_all_fd(t_infos **infos)
{
	create_pipes(infos);
	create_normal(*infos);
	create_file(infos);
	create_heredoc(infos);
	create_append(infos);
}
