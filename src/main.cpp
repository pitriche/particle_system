/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/22 13:37:48 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "All.hpp"

All	all;

static void	loop(void)
{
	all.event.update();
	all.disp.update();
	all.time.update();
	std::cout << "  " << all.time.fps_average() << std::endl;
}

int			main(void)
{
	all.init();
	while (1)
		loop();
	return (0);
}
