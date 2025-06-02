/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:58:41 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/19 16:15:55 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_filename(int id, int cmd_id, char **file_name,
		char **cmd_id_str)
{
	char	*id_str;
	size_t	i;

	i = 0;
	id_str = ft_itoa(id);
	if (!id_str)
		return (-1);
	*cmd_id_str = ft_itoa(cmd_id);
	if (!*cmd_id_str)
		return (free(id_str), -1);
	*file_name = ft_calloc(ft_strlen(id_str) + 1 + ft_strlen(*cmd_id_str) + 4
			+ 1, sizeof(char));
	if (!*file_name)
		return (free(id_str), free(*cmd_id_str), -1);
	while (i < ft_strlen(id_str))
	{
		*file_name[i] = id_str[i];
		i++;
	}
	free(id_str);
	ft_strlcat(*file_name, "_", ft_strlen(*file_name) + 2);
	return (i + 1);
}

static char	*create_filename_heredoc(int id, int cmd_id)
{
	char	*cmd_id_str;
	char	*file_name;
	int		i;
	size_t	z;

	z = 0;
	i = get_filename(id, cmd_id, &file_name, &cmd_id_str);
	if (i == -1)
		return (NULL);
	while (z < ft_strlen(cmd_id_str))
	{
		file_name[i] = cmd_id_str[z];
		i++;
		z++;
	}
	free(cmd_id_str);
	ft_strlcat(file_name, ".tmp", ft_strlen(file_name) + 5);
	return (file_name);
}

static int	get_heredoc_fd(t_cmd *cmd, int i, int cmd_id, t_infos *infos)
{
	int	file;

	signals_init_heredoc();
	infos->g_sig_id_heredoc = g_sig_id;
	g_sig_id = 0;
	if (cmd->heredoc_file_name != NULL)
	{
		unlink(cmd->heredoc_file_name);
		free(cmd->heredoc_file_name);
		cmd->heredoc_file_name = NULL;
	}
	cmd->heredoc_file_name = create_filename_heredoc(i, cmd_id);
	if (!cmd->heredoc_file_name)
		protect_memory(infos, NULL, NULL);
	file = open(cmd->heredoc_file_name, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (file < 0)
		print_file_error(cmd, cmd->heredoc_file_name);
	return (file);
}

static int	check_heredoc_input(char *buf, t_cmd *cmd, t_infos *infos)
{
	if (!buf)
	{
		ft_putstr_fd("bash: warning: ", 2);
		ft_putstr_fd("here-document delimited by end-of-file ", 2);
		ft_putendl_fd("(wanted `EOF')", 2);
		return (1);
	}
	if (g_sig_id == 128 + SIGINT)
	{
		infos->sigint_heredoc = 1;
		free(buf);
		return (1);
	}
	if (ft_strcmp(buf, cmd->heredoc) == 0)
	{
		free(buf);
		return (1);
	}
	return (0);
}

void	handle_heredoc(t_cmd *cmd, int i, t_infos *infos, int cmd_id)
{
	int		file;
	char	*buf;
	char	*tmp;

	tmp = NULL;
	file = get_heredoc_fd(cmd, i, cmd_id, infos);
	if (file < 0)
		return ;
	while (1)
	{
		buf = readline("> ");
		if (check_heredoc_input(buf, cmd, infos))
			break ;
		tmp = replace_str_var_heredoc_new(infos, buf);
		if (!tmp)
			protect_memory(infos, NULL, NULL);
		write(file, tmp, ft_strlen(tmp));
		write(file, "\n", 1);
		free(tmp);
		free(buf);
	}
	close(file);
	signals_init();
}
