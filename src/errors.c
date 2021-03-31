/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:54:42 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 19:34:07 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	prt_err3(int err)
{
	if (err == 22)
		ft_putstr_fd("Missing .cub file\n", 2);
	if (err == 23)
		ft_putstr_fd("Too many arguments\n", 2);
	return (ERROR);
}

int	prt_err2(int err)
{
	if (err == 11)
		ft_putstr_fd("Read file error\n", 2);
	if (err == 12)
		ft_putstr_fd("Not allowed character in map\n", 2);
	if (err == 13)
		ft_putstr_fd("Map not surrounded by walls\n", 2);
	if (err == 14)
		ft_putstr_fd("More than 1 spawn position\n", 2);
	if (err == 15)
		ft_putstr_fd("Only .cub files allowed\n", 2);
	if (err == 16)
		ft_putstr_fd("MLX error\n", 2);
	if (err == 17)
		ft_putstr_fd("Couldn't load texture \
		wrong path?\n", 2);
	if (err == 18)
		ft_putstr_fd("Missing spawning point\n", 2);
	if (err == 19)
		ft_putstr_fd("Invalid map\n", 2);
	if (err == 20)
		ft_putstr_fd("Map surrounds not squared\n", 2);
	if (err == 21)
		ft_putstr_fd("File must be a .cub file\n", 2);
	return (prt_err3(err));
}

int	prt_err(int err)
{
	ft_putstr_fd("Error\n", 2);
	if (err == 1)
		ft_putstr_fd("Undefined error\n", 2);
	if (err == 2)
		ft_putstr_fd("Wrong arguments\n", 2);
	if (err == 3)
		ft_putstr_fd("Repeated identifier\n", 2);
	if (err == 4)
		ft_putstr_fd("Wrong resolution\n", 2);
	if (err == 5)
		ft_putstr_fd("Wrong color (ceiling)\n", 2);
	if (err == 6)
		ft_putstr_fd("Malloc failure\n", 2);
	if (err == 7)
		ft_putstr_fd("Wrong color (floor)\n", 2);
	if (err == 8)
	{
		ft_putstr_fd("Expected a valid identifier :", 2);
		ft_putstr_fd("R, NO, SO, WE, EA, S, F or C\n", 2);
	}
	if (err == 9)
		ft_putstr_fd("Wrong texture in file\n", 2);
	if (err == 10)
		ft_putstr_fd("Unknown identifier\n", 2);
	return (prt_err2(err));
}
