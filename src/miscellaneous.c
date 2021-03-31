/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:04 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 10:24:02 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_endtrails(char *str)
{
	int	i;

	i = ft_strlen(str);
	while ((ft_isspace(*(str + i)) || *(str + i) == '\0') && i > 0)
	{
		*(str + i) = '\0';
		i--;
	}
	if (ft_isspace(*(str + i)))
		*(str + i) = '\0';
}

int	ext_chk(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (SUCCESS);
	return (ERROR);
}

int	is_spaces_line(char *str)
{
	char	*ptr;

	ptr = str;
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr == '\0')
		return (1);
	return (0);
}

t_list	*get_node(size_t pos, t_list *first)
{
	size_t		i;
	t_list		*node;

	if (first == NULL)
		return (NULL);
	node = first;
	i = 0;
	while (i < pos)
	{
		node = node->next;
		if (node == NULL)
			return (NULL);
		i++;
	}
	return (node);
}

void	empty_function(void)
{
}
