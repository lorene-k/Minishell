/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:12:55 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 14:22:07 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	protect_cmd_memory(int i, int z, t_cmd **cmd)
{
	while (i < z)
	{
		free((*cmd)->args[i]);
		i++;
	}
	free(*cmd);
	ft_putendl_fd("malloc: memory allocation failed", 2);
}

void	free_cmd_args(t_cmd *cmd)
{
	int	id;

	id = 0;
	while (id < cmd->args_indexes)
	{
		if (cmd->args[id] != NULL)
		{
			free(cmd->args[id]);
		}
		id++;
	}
	free(cmd->args);
	cmd->args = NULL;
	cmd->args_indexes = 0;
}

void	free_two_tokens(char *a_token, char *next_token, t_cmd *a_cmd, int id)
{
	free(a_token);
	free(next_token);
	a_cmd->args[id] = NULL;
	a_cmd->args[id + 1] = NULL;
}

void	free_cmd_tokens(char **cmd_array)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (cmd_array[nb_words] != NULL)
	{
		nb_words++;
	}
	while (i < nb_words)
	{
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

void	free_infos_syntax(t_infos **infos)
{
	if (*infos != NULL)
	{
		if ((*infos)->pid != NULL)
		{
			free((*infos)->pid);
			(*infos)->pid = NULL;
		}
		if ((*infos)->input != NULL)
		{
			free((*infos)->input);
			(*infos)->input = NULL;
		}
		if ((*infos)->tube != NULL)
		{
			free((*infos)->tube);
			(*infos)->tube = NULL;
		}
	}
}
