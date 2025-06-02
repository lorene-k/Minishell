/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:07:16 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:33:16 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	select_builtin(t_infos **infos, int id, int fds[2])
{
	int	return_code;

	return_code = 0;
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "echo"))
		return_code = ft_echo(*infos, (*infos)->cmd[id]);
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "pwd"))
		return_code = ft_pwd(*infos, (*infos)->cmd[id]);
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "env"))
		return_code = ft_env(*infos, (*infos)->cmd[id]);
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "export"))
		return_code = ft_export(*infos, (*infos)->cmd[id]);
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "unset"))
		return_code = ft_unset(*infos, (*infos)->cmd[id]);
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "cd"))
		return_code = ft_cd(*infos, (*infos)->cmd[id]);
	if (!ft_strcmp((*infos)->cmd[id]->args[0], "exit"))
		return_code = ft_exit(*infos, (*infos)->cmd[id], fds);
	return (return_code);
}

static int	handle_child_error(t_cmd *cmd)
{
	int	exit_code;

	if (cmd->cmd_not_found != 1)
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	if (cmd->cmd_not_found == 1)
		ft_putendl_fd(": command not found", 2);
	else if (cmd->cmd_not_found == 2)
		ft_putendl_fd(": Permission denied", 2);
	else if (cmd->cmd_not_found == 3)
		ft_putendl_fd(": Is a directory", 2);
	else if (cmd->cmd_not_found == 4)
		ft_putendl_fd(": No such file or directory", 2);
	if (cmd->cmd_not_found == 1 || cmd->cmd_not_found == 4)
		exit_code = 127;
	else
		exit_code = 126;
	return (exit_code);
}

static void	check_child_error(t_infos ***infos, t_cmd *cmd)
{
	int	exit_code;

	if (cmd->is_empty)
	{
		close_all_pipe(**infos);
		free_infos_child(*infos);
		exit(0);
	}
	if (!cmd->can_access_file)
	{
		close_all_pipe(**infos);
		free_infos_child(*infos);
		exit(1);
	}
	if (cmd->cmd_not_found)
	{
		exit_code = handle_child_error(cmd);
		close_all_pipe(**infos);
		free_infos_child(*infos);
		exit(exit_code);
	}
}

static void	check_builtin(t_infos **infos, t_cmd *cmd, int id)
{
	int	return_code;

	return_code = 0;
	if (is_builtin(cmd->args[0]))
	{
		return_code = execute_one_builtin(*infos, id);
		free_infos_child(infos);
		exit(return_code);
	}
}

void	child(t_infos **infos, t_cmd *cmd, int id)
{
	(*infos)->pid[id] = fork();
	if ((*infos)->pid[id] == 0)
	{
		check_child_error(&infos, cmd);
		dup2(cmd->fd_out, 1);
		dup2(cmd->fd_in, 0);
		close_all_pipe(*infos);
		check_builtin(infos, cmd, id);
		if (cmd->can_access_file && cmd->cmd_not_found != 1)
			execve(cmd->path, cmd->args, (*infos)->new_envp);
		else
			exit(1);
	}
	else if ((*infos)->pid[id] < 0)
	{
		perror("minishell");
		free_infos_error(*infos);
	}
}
