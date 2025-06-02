/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:59:45 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:30:46 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_infos *infos)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		add_env_var(infos, "OLDPWD", buffer);
	else
		return (print_cmd_error("getcwd: error updating OLDPWD", infos, 1));
	return (0);
}

static int	goto_home(t_infos *infos)
{
	if (env_var_exists(infos, "HOME") == 1)
	{
		update_pwd(infos);
		if (chdir(get_env_var(infos, "HOME")) < 0)
			return (print_cmd_error("cd: error accessing HOME", infos, 1));
	}
	else
		return (print_cmd_error("cd: HOME variable not set", infos, 1));
	return (0);
}

static int	goto_oldpwd(t_infos *infos)
{
	char	*old_tmp;

	if (env_var_exists(infos, "OLDPWD") == 1)
	{
		old_tmp = get_env_var(infos, "OLDPWD");
		if (!old_tmp)
			protect_memory(infos, 0, 0);
		ft_putendl_fd(old_tmp, 1);
		update_pwd(infos);
		if (chdir(old_tmp) < 0)
			return (print_cmd_error("cd: error accessing OLDPWD", infos, 1));
		free(old_tmp);
	}
	else
		return (print_cmd_error("cd: OLDPWD variable not set", infos, 1));
	return (0);
}

static int	goto_path(t_infos *infos, char *path)
{
	update_pwd(infos);
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_infos *infos, t_cmd *cmd)
{
	int		code;
	char	buffer[PATH_MAX];

	code = 0;
	if (cmd->args_indexes == 2)
		code = goto_home(infos);
	else if (cmd->args_indexes == 3 && cmd->args[1][0] == '~')
		code = goto_home(infos);
	else if (cmd->args_indexes == 3 && cmd->args[1][0] == '-')
		code = goto_oldpwd(infos);
	else if (cmd->args_indexes == 3)
		code = goto_path(infos, cmd->args[1]);
	else
		return (print_cmd_error("cd: too many arguments", infos, 1));
	getcwd(buffer, sizeof(buffer));
	add_env_var(infos, "PWD", buffer);
	return (code);
}
