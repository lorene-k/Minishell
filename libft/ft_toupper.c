/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imounjed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:00:07 by imounjed          #+#    #+#             */
/*   Updated: 2024/05/21 20:00:45 by imounjed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int character)
{
	if ((character >= 'a' && character <= 'z'))
	{
		return (character - 'a' + 'A');
	}
	else
	{
		return (character);
	}
}
