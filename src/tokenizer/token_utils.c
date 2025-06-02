/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <imounjed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:48:26 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/09/20 14:52:10 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	protect_memory_tokens(t_infos *i, char *line, t_token *t, char **tab)
{
	if (t)
	{
		t = get_first_node(t);
		clear_tokens(&t);
	}
	protect_memory(i, line, tab);
}

int	print_parse_error(t_infos *infos, int code, char *msg)
{
	g_sig_id = 2;
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
	infos->return_code = code;
	return (code);
}

char	*ft_strjoin_mem(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	t_len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	t_len = len1 + len2;
	str = malloc(sizeof(char) * (t_len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, (len1));
	ft_memcpy((str + len1), s2, (len2 + 1));
	str[len1 + len2] = '\0';
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (str);
}

int	ft_strchr_index(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((int)i);
		i++;
	}
	if (*s == (char)c)
		return ((int)i);
	return (-1);
}

void	clear_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}
