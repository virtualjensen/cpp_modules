/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:26:34 by jebucoy           #+#    #+#             */
/*   Updated: 2023/11/06 15:52:09 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <cstring>

int main(int ac, char **av)
{
	char	convert;
	size_t	len;

	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for(int s = 1; s < ac; s++){ 
		len = strlen(av[s]);
		for(size_t i = 0; i < len; i++){
			convert = toupper(av[s][i]);

			std::cout << convert;
		}
		if (s + 1 != ac)
			std::cout << " ";
	}
	std::cout << std::endl;
}