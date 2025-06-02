/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:18:44 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 16:06:04 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	commands_nb(char **cmd_array)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (cmd_array[i] != NULL)
	{
		if (cmd_array[i + 1] == NULL)
			nb++;
		else if (ft_strcmp(cmd_array[i], "|") == 0)
			nb++;
		i++;
	}
	return (nb);
}

static int	create_infos_array(t_infos **infos, char **cmd_array)
{
	t_cmd	**tab;

	(*infos)->cmd = NULL;
	(*infos)->cmd_nb = commands_nb(cmd_array);
	tab = ft_calloc(commands_nb(cmd_array) + 1, (sizeof(t_cmd *)));
	if (!tab)
		return (-1);
	(*infos)->cmd = tab;
	return (0);
}

static int	get_cmd_array(char **cmd_array, t_infos **infos)
{
	int	nb_words;

	nb_words = 0;
	if (create_infos_array(infos, cmd_array) == -1)
		return (-1);
	while (cmd_array[nb_words] != NULL)
		nb_words++;
	return (nb_words);
}

static void	init_vars(int *i, int *args_nb, int *last_index, int *id_cmd)
{
	*i = 0;
	*args_nb = 0;
	*last_index = 0;
	*id_cmd = 0;
}

static void	update_vars(int *args_nb, int *last_index, int *id_cmd, int i)
{
	*args_nb = 0;
	*last_index = i + 1;
	*id_cmd += 1;
}

int	create_commands(char **cmd_array, t_infos **infos)
{
	int	i;
	int	args_nb;
	int	last_index;
	int	id_cmd;
	int	nb_words;

	init_vars(&i, &args_nb, &last_index, &id_cmd);
	nb_words = get_cmd_array(cmd_array, infos);
	if (nb_words == -1)
		return (-1);
	while (i < nb_words)
	{
		if (ft_strcmp(cmd_array[i], "|") != 0)
			args_nb++;
		if (ft_strcmp(cmd_array[i], "|") == 0 || i + 1 == nb_words)
		{
			(*infos)->cmd[id_cmd] = get_cmd(args_nb, cmd_array, last_index,
					infos);
			if ((*infos)->cmd[id_cmd] == NULL)
				return (-1);
			update_vars(&args_nb, &last_index, &id_cmd, i);
		}
		i++;
	}
	return (0);
}
