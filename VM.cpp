/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:26 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/21 14:30:46 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <regex>
#include <cfloat>
#include <math.h>
#include "VM.hpp"

FactoryMethod	VM::_FM;

VM::VM() :
	_myMap({
		{"push", &VM::push},
		{"assert", &VM::assert},
		{"pop", &VM::pop},
		{"dump", &VM::dump},
		{"add", &VM::add},
		{"sub", &VM::sub},
		{"mul", &VM::mul},
		{"div", &VM::div},
		{"mod", &VM::mod},
		{"print", &VM::print},
		{"sin", &VM::avmSin},
		{"cos", &VM::avmCos},
		{"tan", &VM::avmTan},
		{"sqrt", &VM::avmSqrt},
		{"total", &VM::total},
		{"average", &VM::average},
	}),
	_myOperations({
		{"int8", eOperandType::Int8},
		{"int16", eOperandType::Int16},
		{"int32", eOperandType::Int32},
		{"float", eOperandType::Float},
		{"double", eOperandType::Double},
	})
{
	return;
}

VM::~VM()
{
	for (std::vector<IOperand const *>::iterator it =
		this->_myStack.begin(); it != this->_myStack.end(); ++it) {
		delete (*it);
	}
}

void	VM::push(std::string const &str)
{
	std::regex re("(int8|int16|int32|float|double)[(](.*)[)](.*)");
	std::smatch sm;
	std::regex_match(str, sm, re);

	this->_myStack.push_back(
		this->_FM.createOperand(this->_myOperations[sm[1].str()], sm[2].str()));
}

void VM::assert(std::string const &str)
{
	std::regex re("(int8|int16|int32|float|double)[(](.*)[)](.*)");
	std::smatch sm;
	std::regex_match(str, sm, re);
	if (this->_myStack.empty())
		throw VM::assertInstruction();
	IOperand const *a = this->_FM.createOperand(
		this->_myOperations[sm[1].str()], sm[2].str());
	if (a->getType() != this->_myStack.back()->getType() ||
		a->toString() != this->_myStack.back()->toString()) {
		delete a;
		throw VM::assertInstruction();
	}
	delete a;
}

void VM::pop(std::string const &)
{
	if (this->_myStack.empty())
		throw VM::emptystack();
	delete this->_myStack.back();
	this->_myStack.pop_back();
}

void VM::dump(std::string const &)
{
	for (auto it = this->_myStack.crbegin(); it != this->_myStack.crend(); ++it) {
		std::cout << (*it)->toString() <<  std::endl;
	}
}

void VM::add(std::string const &)
{
	if (this->_myStack.size() <= 1)
		throw VM::less_than_two_instruction();
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	std::vector<IOperand const *>::iterator b = this->_myStack.end() - 2;
	auto c = (**a + **b);
	this->_myStack.pop_back();
	this->_myStack.pop_back();
	this->_myStack.push_back(c);
}

void VM::sub(std::string const &)
{
	if (this->_myStack.size() <= 1)
		throw VM::less_than_two_instruction();
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	std::vector<IOperand const *>::iterator b = this->_myStack.end() - 2;

	auto c = (**b - **a);
	this->_myStack.pop_back();
	this->_myStack.pop_back();
	this->_myStack.push_back(c);
}

void VM::mul(std::string const &)
{
	if (this->_myStack.size() <= 1)
		throw VM::less_than_two_instruction();
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	std::vector<IOperand const *>::iterator b = this->_myStack.end() - 2;
	auto c = (**b * **a);
	this->_myStack.pop_back();
	this->_myStack.pop_back();
	this->_myStack.push_back(c);
}

void VM::div(std::string const &)
{
	if (this->_myStack.size() <= 1)
		throw VM::less_than_two_instruction();
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	std::vector<IOperand const *>::iterator b = this->_myStack.end() - 2;
	auto aa = std::stold((*a)->toString().c_str());
	if (aa >= 0 && aa <= FLT_MIN)
		throw VM::division_modulo();
	auto c = (**b / **a);
	this->_myStack.pop_back();
	this->_myStack.pop_back();
	this->_myStack.push_back(c);

}

void VM::mod(std::string const &)
{
	if (this->_myStack.size() <= 1)
		throw VM::less_than_two_instruction();
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	std::vector<IOperand const *>::iterator b = this->_myStack.end() - 2;
	auto aa = std::stold((*a)->toString().c_str());
	if (aa == 0)
		throw VM::division_modulo();
	auto c = (**b % **a);
	this->_myStack.pop_back();
	this->_myStack.pop_back();
	this->_myStack.push_back(c);
}

void 	VM::print(std::string const &)
{
	if (this->_myStack.empty())
		throw VM::print_exception();
	if (eOperandType::Int8 == this->_myStack.back()->getType()) {
		int a = atoi(this->_myStack.back()->toString().c_str());
		if (isprint(a))
			std::cout << static_cast<char>(a) << std::endl;
	}
	else
		throw VM::print_exception();
}

void	VM::avmSin(std::string const &)
{
	if (this->_myStack.empty()) {
		throw VM::emptystack();
	}
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	auto aa = std::to_string(sin(std::stod((*a)->toString().c_str())));
	this->_myStack.pop_back();
	this->_myStack.push_back(
		this->_FM.createOperand(eOperandType::Double, aa));
}
void	VM::avmCos(std::string const &)
{
	if (this->_myStack.empty()) {
		throw VM::emptystack();
	}
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	auto aa = std::to_string(cos(std::stod((*a)->toString().c_str())));
	this->_myStack.pop_back();
	this->_myStack.push_back(
		this->_FM.createOperand(eOperandType::Double, aa));
}

void	VM::avmTan(std::string const &)
{
	if (this->_myStack.empty()) {
		throw VM::emptystack();
	}
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	auto aa = std::to_string(tan(std::stod((*a)->toString().c_str())));
	this->_myStack.pop_back();
	this->_myStack.push_back(
		this->_FM.createOperand(eOperandType::Double, aa));
}

void	VM::avmSqrt(std::string const &)
{
	if (this->_myStack.empty()) {
		throw VM::emptystack();
	}
	std::vector<IOperand const *>::iterator a = this->_myStack.end() - 1;
	if (std::stod((*a)->toString().c_str()) < 0) {
		throw VM::negativesqrt();
	}
	auto aa = std::to_string(sqrt(std::stod((*a)->toString().c_str())));
	this->_myStack.pop_back();
	this->_myStack.push_back(
		this->_FM.createOperand(eOperandType::Double, aa));
}
void 	VM::total(std::string const &)
{
	int i = 0;
	int size = this->_myStack.size();
	while ( i < size - 1 ) {
  		this->add("");
  		i++;
	}
}

void	VM::average(std::string const &)
{
	if (this->_myStack.empty())
		throw VM::emptystack();
	int size = this->_myStack.size();
	this->total("");
	this->_myStack.push_back(
		this->_FM.createOperand(eOperandType::Double, std::to_string(size)));
	this->div("");
}

void	VM::dispatcher(std::vector<std::string> const &ref)
{
	std::regex re("^\\s*(push|assert|pop|dump|add|sub|mul|div|mod|print|sin|tan|cos|sqrt|total|average)\\s*(.*)");
	std::smatch sm;
	for (auto it = ref.begin() ; it != ref.end(); ++it) {
		if (std::regex_match((*it), sm, re)) {
			(this->*(this->_myMap[sm[1].str()]))(sm[2].str());
		}
	}
}

const char *VM::emptystack::what() const throw()
{
	return ("\033[31;1mError: Instruction pop on an empty stack\033[0m");
}

const char *VM::assertInstruction::what() const throw()
{
	return ("\033[31;1mError: Instruction assert is false\033[0m");
}

const char *VM::less_than_two_instruction::what() const throw()
{
	return ("\033[31;1mError: The stack is too small when an arithmetic instruction is executed\033[0m");
}

const char *VM::division_modulo::what() const throw()
{
	return ("\033[31;1mError: Division/modulo by 0\033[0m");
}
const char *VM::negativesqrt::what() const throw()
{
	return ("\033[31;1mError: Square root on a negative number\033[0m");
}

const char *VM::print_exception::what() const throw()
{
	return ("\033[31;1mError: Instruction print is false\033[0m");
}
