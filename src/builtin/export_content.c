/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:59:45 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 15:30:46 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TEST*/
char	**dup_env(t_infos *infos)
{
	int		i;
	char	**new;

	i = 0;
	while (infos->new_envp[i] != NULL)
		i++;
	new = ft_calloc(sizeof(char *), (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (infos->new_envp[i] != NULL)
	{
		new[i] = infos->new_envp[i];
		i++;
	}
	return (new);
}

/*TEST*/
void	show_one_line_export(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (ft_strchr(str, '=') == NULL)
	{
		ft_putendl_fd(str, 1);
		return ;
	}
	while (i < len)
	{
		write(1, &str[i], 1);
		if (str[i] == '=')
			break ;
		i++;
	}
	write(1, "\"", 1);
	if (i < len)
		ft_putstr_fd(ft_strchr(str, '=') + 1, 1);
	write(1, "\"\n", 2);
}

void	sort_env(char **env)
{
	int		i;
	int		sorted;
	char	*tmp;

	i = 0;
	sorted = 0;
	while (env[i] != NULL && sorted == 0)
	{
		i = 0;
		sorted = 1;
		while (env[i + 1] != NULL)
		{
			if (env[i + 1] != NULL && ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

void	print_sorted_export_env(t_infos *infos)
{
	int		i;
	char	**env;

	env = dup_env(infos);
	if (!env)
		protect_memory(infos, NULL, NULL);
	sort_env(env);
	i = 0;
	while (env[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		show_one_line_export(env[i++]);
	}
	free(env);
}

char	*get_var_content(t_infos *infos, char *str)
{
	char	*var_content;

	var_content = NULL;
	var_content = ft_strchr(str, '=') + 1;
	var_content = replace_str_var_new(infos, var_content);
	if (!var_content)
		protect_memory(infos, 0, 0);
	return (var_content);
}
