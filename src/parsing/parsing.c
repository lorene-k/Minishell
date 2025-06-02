/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:09:02 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:50:36 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_cmds(char *str, t_infos **infos)
{
	char	**cmd_tokens;

	cmd_tokens = generate_tokens_array(str, *infos);
	if (!cmd_tokens)
		return (-1);
	if (create_commands(cmd_tokens, infos) == -1)
	{
		free_cmd_tokens(cmd_tokens);
		protect_memory(*infos, NULL, NULL);
	}
	else
		free_cmd_tokens(cmd_tokens);
	modify_all_cmd_args(infos);
	return (0);
}

int	all_cmds_empty(t_infos *infos)
{
	int	i;
	int	empty;

	i = 0;
	empty = 0;
	while (i < infos->cmd_nb)
	{
		if (infos->cmd[i]->args[0] == NULL)
			empty++;
		i++;
	}
	if (empty == infos->cmd_nb)
	{
		g_sig_id = 0;
		return (1);
	}
	else
		return (0);
}

int	set_empty_cmds(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->cmd_nb)
	{
		if (infos->cmd[i]->args[0] == NULL)
		{
			infos->cmd[i]->is_empty = 1;
		}
		else
		{
			infos->cmd[i]->is_empty = 0;
		}
		i++;
	}
	return (0);
}

static int	modify_cmds(t_infos **infos)
{
	set_default_cmd_values(infos);
	set_infile_outfile(infos);
	if ((*infos)->sigint_heredoc == 1)
		return (-1);
	set_empty_cmds(*infos);
	if (all_cmds_empty(*infos))
		return (-1);
	set_in_out_pipes_and_normal(infos);
	set_all_cmd_path(infos);
	return (0);
}

int	parse(char *str, t_infos **infos, char **envp)
{
	if (ft_strlen(str) == 0)
	{
		free(str);
		return (0);
	}
	if (!(*infos))
		create_infos(infos, str, envp);
	else
		update_infos(infos, str);
	(*infos)->sigint_heredoc = 0;
	if (create_cmds(str, infos) == -1)
	{
		free_infos_syntax(infos);
		return (0);
	}
	if (modify_cmds(infos) == -1)
	{
		free_infos_while(infos);
		return (0);
	}
	return (1);
}
