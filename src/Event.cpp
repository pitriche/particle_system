/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/01 09:26:03 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"
#include "All.hpp"

Event::Event(void) { }
Event::Event(const Event &) { }
Event::~Event(void) { }

void	Event::_keychange(SDL_Keycode kc)
{
	switch (kc)
	{
		case (SDLK_w):
			std::cout << "W pressed" << std::endl;
			break;
		case (SDLK_a):
			std::cout << "A pressed" << std::endl;
			break;
		case (SDLK_s):
			std::cout << "S pressed" << std::endl;
			break;
		case (SDLK_d):
			std::cout << "D pressed" << std::endl;
			break;
		case (SDLK_t):
			std::cout << "T pressed" << std::endl;
			break;
		case (SDLK_ESCAPE):
			exit(0);
			break;
		default:
			std::cout << "other pressed" << std::endl;
			break;
	}
}

void	Event::update(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		// if (event.type == SDL_KEYDOWN && !event.key.repeat)
		if (event.type == SDL_KEYDOWN)
			this->_keychange(event.key.keysym.sym);
	}
}

void	Event::operator=(const Event &) { }
