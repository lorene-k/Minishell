/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_file_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:52:32 by imounjed          #+#    #+#             */
/*   Updated: 2024/09/19 14:52:34 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_infile_intype(t_infos **infos, char *actual_token, char *next_token,
		t_cmd *cmd)
{
	if (ft_strcmp(actual_token, "<") == 0)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(next_token);
		if (!cmd->infile)
			protect_memory(*infos, NULL, NULL);
		cmd->intype = FILE_REAL;
		return (1);
	}
	if (ft_strcmp(actual_token, "<<") == 0)
	{
		if (cmd->heredoc != NULL)
			free(cmd->heredoc);
		cmd->heredoc = ft_strdup(next_token);
		if (!cmd->heredoc)
			protect_memory(*infos, NULL, NULL);
		cmd->intype = HEREDOC;
		return (1);
	}
	return (0);
}

int	assign_outfile_outtype(t_infos **infos, char *actual_token,
		char *next_token, t_cmd *cmd)
{
	if (ft_strcmp(actual_token, ">") == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(next_token);
		if (!cmd->outfile)
			protect_memory(*infos, NULL, NULL);
		cmd->outtype = TRUNC;
		return (1);
	}
	if (ft_strcmp(actual_token, ">>") == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(next_token);
		if (!cmd->outfile)
			protect_memory(*infos, NULL, NULL);
		cmd->outtype = APPEND;
		return (1);
	}
	return (0);
}

int	check_token_and_assign(t_infos **infos, char *actual_token,
		char *next_token, t_cmd *cmd)
{
	if (assign_infile_intype(infos, actual_token, next_token, cmd) == 1)
		return (1);
	if (assign_outfile_outtype(infos, actual_token, next_token, cmd) == 1)
		return (1);
	return (0);
}

int	contains_in_out(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		if (ft_strcmp(cmd->args[i], "<") == 0 || ft_strcmp(cmd->args[i],
				"<<") == 0 || ft_strcmp(cmd->args[i], ">") == 0
			|| ft_strcmp(cmd->args[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	set_infile_outfile(t_infos **infos)
{
	int		i;
	t_cmd	*actual_cmd;

	i = 0;
	while (i < (*infos)->cmd_nb)
	{
		actual_cmd = (*infos)->cmd[i];
		actual_cmd->can_access_file = 1;
		while (contains_in_out(actual_cmd))
		{
			remove_one_inout_and_set_inout(infos, actual_cmd);
			if ((*infos)->sigint_heredoc == 1)
				return (-1);
			if (!actual_cmd->can_access_file)
				break ;
		}
		i++;
	}
	return (0);
}
