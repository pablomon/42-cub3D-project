/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:10:17 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 19:41:08 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr(char *s)
{
	char	c;

	if (s)
	{
		while (*s)
		{
			c = *s;
			write(1, &c, 1);
			s++;
		}
	}
}
