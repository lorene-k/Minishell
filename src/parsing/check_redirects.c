/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:38:34 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:38:30 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_appendfile(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_file_error(cmd, file);
	else
		close(fd);
}

static void	handle_outfile(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_file_error(cmd, file);
	else
		close(fd);
}

static void	handle_infile(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_file_error(cmd, file);
	else
		close(fd);
}

static void	check_redirect(t_infos **infos, t_cmd *cmd, int arg_id)
{
	char	*actual_token;
	char	*next_token;

	actual_token = cmd->args[arg_id];
	next_token = cmd->args[arg_id + 1];
	if (!ft_strcmp(actual_token, "<"))
		handle_infile(cmd, next_token);
	else if (ft_strcmp(actual_token, ">") == 0)
		handle_outfile(cmd, next_token);
	else if (!ft_strcmp(actual_token, ">>"))
		handle_appendfile(cmd, next_token);
	else if (ft_strcmp(actual_token, "<<") == 0)
		handle_heredoc(cmd, arg_id, *infos, get_cmd_id(*infos, cmd));
}

void	remove_one_inout_and_set_inout(t_infos **infos, t_cmd *cmd)
{
	int		arg_id;
	char	*actual_token;
	char	*next_token;

	arg_id = 0;
	cmd->can_access_file = 1;
	while (arg_id < cmd->args_indexes - 2)
	{
		actual_token = cmd->args[arg_id];
		next_token = cmd->args[arg_id + 1];
		if (check_token_and_assign(infos, actual_token, next_token, cmd) == 1)
		{
			check_redirect(infos, cmd, arg_id);
			if ((*infos)->sigint_heredoc == 1 || cmd->can_access_file == 0)
				break ;
			delete_redirect_args(infos, cmd);
		}
		else
			arg_id++;
	}
	return ;
}
