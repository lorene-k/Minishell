/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:26 by imounjed          #+#    #+#             */
/*   Updated: 2024/09/19 15:48:24 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_new_args(t_infos **infos, int old_nb_indexes,
		t_cmd *actual_cmd)
{
	char	**new_args;
	int		j;
	int		i;

	new_args = malloc(sizeof(char *) * (old_nb_indexes - 2));
	if (!new_args)
		protect_memory(*infos, NULL, NULL);
	i = 0;
	j = 0;
	while (i < old_nb_indexes - 1)
	{
		if (actual_cmd->args[i] != NULL)
			new_args[j++] = ft_strdup(actual_cmd->args[i]);
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

int	is_valid_token(char *actual_token)
{
	if (ft_strcmp(actual_token, "<") == 0 || ft_strcmp(actual_token, "<<") == 0
		|| ft_strcmp(actual_token, ">") == 0 || ft_strcmp(actual_token,
			">>") == 0)
		return (1);
	else
		return (0);
}

void	delete_redirect_args(t_infos **infos, t_cmd *actual_cmd)
{
	char	*actual_token;
	int		arg_id;
	int		i;
	char	**new_args;

	arg_id = 0;
	while (actual_cmd->args[arg_id] != NULL)
	{
		actual_token = actual_cmd->args[arg_id];
		if (is_valid_token(actual_token) == 1)
		{
			free_two_tokens(actual_token, actual_cmd->args[arg_id + 1],
				actual_cmd, arg_id);
			new_args = create_new_args(infos, actual_cmd->args_indexes,
					actual_cmd);
			free_cmd_args(actual_cmd);
			actual_cmd->args = new_args;
			i = 0;
			while (actual_cmd->args[i] != NULL)
				i++;
			actual_cmd->args_indexes = i + 1;
			return ;
		}
		arg_id++;
	}
}
