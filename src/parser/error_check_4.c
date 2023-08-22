/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21                               #+#    #+#             */
/*   Updated: 2023/08/22                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 and writes error if ratio isn't between 0 and 1
int	check_l_brightness(float ratio)
{
	if (ratio < 0 || ratio > 1)
	{
		write(2, "Error: Light brightness must be between 0 and 1\n", 48);
		return (1);
	}
	return (0);
}
