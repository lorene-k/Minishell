/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:07:54 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/20 14:11:07 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_id = 0;

char	*get_input(t_infos **infos)
{
	char	*input;

	input = readline("\033[1;32mminishell$\033[0m ");
	if (!input)
	{
		free_infos(infos);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_infos	*infos;

	infos = NULL;
	(void)argc;
	(void)argv;
	while (1)
	{
		signals_init();
		input = get_input(&infos);
		if (parse(input, &infos, envp) != 0)
		{
			create_all_fd(&infos);
			execute(&infos);
			free_infos_while(&infos);
		}
	}
	return (0);
}