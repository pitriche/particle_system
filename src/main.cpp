/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/23 17:19:15 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "All.hpp"
#include "Defines.hpp"

All	all;

static void	loop(void)
{
	std::string	tmp;

	all.event.update();
	all.disp.update();
	all.time.update();

	if (all.time.elapsed_frame() % 10 == 0)
	{
		tmp = WIN_TITLE " - ";
		tmp += all.time.fps_average();
		SDL_SetWindowTitle(all.disp.window, tmp.c_str());
		// std::cout << "  " << all.time.fps_average() << std::endl;
	}
}

int			main(void)
{
	all.init();
	while (1)
		loop();
	return (0);
}
