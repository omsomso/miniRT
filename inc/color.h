/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:53:06 by zaphod           #+#    #+#             */
/*   Updated: 2023/09/26 15:19:27 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "types.h"

t_color	add_colors(t_color color1, t_color color2);
t_color	mult_col(t_color color1, t_color color2);
t_color	mult_cs(t_color color, float s);
void	set_pixel_color(t_data *data, int x, int y, int color);
int		convert_tcolor_to_int(t_color color);

#endif
