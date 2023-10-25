/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21                               #+#    #+#             */
/*   Updated: 2023/10/25                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 and writes error if ratio isn't between 0 and 1
int	check_l_brightness(float ratio)
{
	if (ratio < 0 || ratio > 1)
	{
		write(2, "Error\nLight brightness must be between 0 and 1\n", 48);
		exit(1);
	}
	return (0);
}
