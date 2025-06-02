/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:55:23 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/21 19:59:53 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int character)
{	
	if ((character >= 'A' && character <= 'Z'))
	{
		return (character - 'A' + 'a');
	}
	else
	{
		return (character);
	}
}
