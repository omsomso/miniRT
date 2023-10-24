/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/24 14:54:27 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 and writes error if ratio isn't between 0 and 1
int	check_l_brightness(float ratio)
{
	if (ratio < 0 || ratio > 1)
	{
		write(2, "Error\nLight brightness must be between 0 and 1\n", 48);
		return (1);
	}
	return (0);
}
