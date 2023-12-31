/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:53:52 by jebucoy           #+#    #+#             */
/*   Updated: 2023/12/20 19:38:52 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150){
     if (_grade < 1)
        throw GradeTooHighException();
    if (_grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name), _grade(grade){
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &copy){
    _grade = copy._grade;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &copy){
    if (this != &copy)
        this->_grade = copy._grade;
    return (*this);
}

Bureaucrat::~Bureaucrat(){};

int Bureaucrat::getGrade() const{
    return (this->_grade);
}

const std::string Bureaucrat::getName() const{
    return (this->_name);
}

void Bureaucrat::incrementGrade(){
    if (_grade <= 1)
        throw GradeTooHighException();
    _grade--;
    std::cout << this->_name << ", bureaucrat grade incremented" << std::endl;
}

void Bureaucrat::decrementGrade(){
    if (_grade >= 150)
        throw GradeTooLowException();
    _grade++;
    std::cout << this->_name << ", bureaucrat grade decremented" << std::endl;

}

void    Bureaucrat::signForm(Form &f){
    try {
        f.beSigned(*this);
        std::cout << this->_name << " signed " << f.getName() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << this->_name << " couldn't sign " << f.getName()
            << " because " << e.what() << std::endl;
    }
}

std::ostream &operator<<(std::ostream& os, const Bureaucrat& b){
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
    return (os);
}

