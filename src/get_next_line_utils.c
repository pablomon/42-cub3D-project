/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:55:20 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 09:55:25 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlentoc(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!(str))
		return (0);
	while (str[i] && (str[i] != c))
		i++;
	return (i);
}

char	*ft_strmerge(char **s1, char *s2)
{
	char	*ptr;
	size_t	t1;
	size_t	t2;

	if (!s1 || !s2)
		return (NULL);
	t1 = ft_strlen(*s1);
	t2 = ft_strlen(s2);
	ptr = malloc(t1 + t2 + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, *s1, t1);
	ft_memcpy((ptr + t1), s2, t2);
	ptr[(t1 + t2)] = '\0';
	ft_strdel(s1);
	*s1 = ptr;
	return (ptr);
}
