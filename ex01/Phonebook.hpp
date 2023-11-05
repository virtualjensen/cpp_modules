/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:22:26 by jebucoy           #+#    #+#             */
/*   Updated: 2023/11/05 19:03:44 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
#include "Contact.hpp"

#include <iostream>

class Phonebook{
	private:
	Contact contactList[8];
	public:
	void	setContactFirstName(int index, std::string contactFirstName);
	void	setContactLastName(int index, std::string contactLastName);
	void	setContactNickName(int index, std::string contactNickName);
	void	setContactPhoneNum(int index, std::string contactPhoneNum);
	void	setDarkSecret(int index, std::string contactDarkSecret);
	std::string	 getContactFirstName();
	std::string	 getContactLastName();
	std::string	 getContactNickName();
	std::string	 getContactPhoneNum();
	std::string	 getContactDarkSecret();
};



#endif





