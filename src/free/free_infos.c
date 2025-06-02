/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:49:41 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 13:46:23 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_infos_exit(t_infos *infos)
{
	if (infos != NULL)
	{
		free_create_commands(&infos);
		if ((infos)->new_envp != NULL)
			clear_tab((infos)->new_envp);
		if ((infos)->paths != NULL)
			clear_tab((infos)->paths);
		if ((infos)->pid != NULL)
			free((infos)->pid);
		if ((infos)->input != NULL)
			free((infos)->input);
		if ((infos)->tube != NULL)
			free((infos)->tube);
		free(infos);
	}
}

void	free_infos_error(t_infos *infos)
{
	if (infos != NULL)
	{
		if ((infos)->new_envp != NULL)
			clear_tab((infos)->new_envp);
		if ((infos)->paths != NULL)
			clear_tab((infos)->paths);
		if ((infos)->pid != NULL)
			free((infos)->pid);
		if ((infos)->input != NULL)
			free((infos)->input);
		if ((infos)->tube != NULL)
			free((infos)->tube);
		free_create_commands_error(infos);
		free(infos);
	}
	exit(123);
}

void	free_infos(t_infos **infos)
{
	if (*infos != NULL)
	{
		if ((*infos)->new_envp != NULL)
			clear_tab((*infos)->new_envp);
		if ((*infos)->paths != NULL)
			clear_tab((*infos)->paths);
		if ((*infos)->pid != NULL)
			free((*infos)->pid);
		if ((*infos)->input != NULL)
			free((*infos)->input);
		if ((*infos)->tube != NULL)
			free((*infos)->tube);
		free(*infos);
		*infos = NULL;
	}
}

void	free_infos_child(t_infos **infos)
{
	if (*infos != NULL)
	{
		if ((*infos)->new_envp != NULL)
			clear_tab((*infos)->new_envp);
		if ((*infos)->paths != NULL)
			clear_tab((*infos)->paths);
		if ((*infos)->pid != NULL)
			free((*infos)->pid);
		if ((*infos)->input != NULL)
			free((*infos)->input);
		if ((*infos)->tube != NULL)
			free((*infos)->tube);
		free_create_commands(infos);
		free(*infos);
		*infos = NULL;
	}
}

void	free_infos_while(t_infos **infos)
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
		free_create_commands(infos);
	}
}
