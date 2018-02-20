/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:28:26 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:46 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <regex>
#include <cfloat>
#include "VM.hpp"



FactoryMethod	VM::FM;

VM::VM()
{
	this->myMap = {
			{"push", &VM::push},
			{"assert", &VM::assert},
			{"pop", &VM::pop},
			{"dump", &VM::dump},
			{"add", &VM::add},
			{"sub", &VM::sub},
			{"mul", &VM::mul},
			{"div", &VM::div},
			{"mod", &VM::mod},
			{"print", &VM::print}
	};
	this->myOperations = {
			{"int8", eOperandType::Int8},
			{"int16", eOperandType::Int16},
			{"int32", eOperandType::Int32},
			{"float", eOperandType::Float},
			{"double", eOperandType::Double},
	};
}

VM::~VM()
{
	for (std::vector<IOperand const *>::const_iterator it = this->myStack.begin();
		it != this->myStack.end(); ++it) {
		delete (*it);
	}
}

void	VM::push(std::string const &str)
{
	std::regex re("(int8|int16|int32|float|double)[(](.*)[)](.*)");
	std::smatch sm;
	std::regex_match(str, sm, re);

	this->myStack.push_back(
		this->FM.createOperand(
			this->myOperations[sm[1].str()], sm[2].str()));
}

void VM::assert(std::string const &str)
{
	std::regex re("(int8|int16|int32|float|double)[(](.*)[)](.*)");
	std::smatch sm;
	std::regex_match(str, sm, re);
	IOperand const *a = this->FM.createOperand(
		this->myOperations[sm[1].str()], sm[2].str());

	if (this->myStack.empty())
		throw VM::assertInstruction();
	if (a->getType() != this->myStack.back()->getType() ||
		a->toString() != this->myStack.back()->toString()) {
		delete a;
		throw VM::assertInstruction();
	}
	delete a;
}

void VM::pop(std::string const &str)
{
	(void)str;
	if (this->myStack.empty())
		throw VM::emptystack();
	delete this->myStack.back();
	this->myStack.pop_back();
}

void VM::dump(std::string const &str)
{
	(void)str;
	for (auto it = this->myStack.crbegin(); it != this->myStack.crend(); ++it) {
		std::cout << (*it)->toString() <<  std::endl;
	}
}

void VM::add(std::string const &str)
{
	(void)str;
	if (this->myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = this->myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = this->myStack.end() - 2;
		auto c = (**a + **b);
		this->myStack.pop_back();
		this->myStack.pop_back();
		this->myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::sub(std::string const &str)
{
	(void)str;
	if (this->myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = this->myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = this->myStack.end() - 2;

		auto c = (**b - **a);
		this->myStack.pop_back();
		this->myStack.pop_back();
		this->myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::mul(std::string const &str)
{
	(void)str;
	if (this->myStack.size() > 1) {
		std::vector<IOperand const *>::const_iterator a = this->myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = this->myStack.end() - 2;

		auto c = (**b * **a);
		this->myStack.pop_back();
		this->myStack.pop_back();
		this->myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::div(std::string const &str)
{
	(void)str;
	if (this->myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = this->myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = this->myStack.end() - 2;
		auto aa = std::stold((*a)->toString().c_str());
		if (aa >= 0 && aa <= FLT_MIN)
			throw VM::division_modulo();
		auto c = (**b / **a);
		this->myStack.pop_back();
		this->myStack.pop_back();
		this->myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::mod(std::string const &str)
{
	(void)str;
	if (this->myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = this->myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = this->myStack.end() - 2;
		auto aa = std::stold((*a)->toString().c_str());
		if (aa == 0)
			throw VM::division_modulo();
		auto c = (**b % **a);
		this->myStack.pop_back();
		this->myStack.pop_back();
		this->myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::print(std::string const &str)
{
	(void)str;
	if (this->myStack.empty())
		throw VM::print_exception();
	if (eOperandType::Int8 == this->myStack.back()->getType()) {
		int a = atoi(this->myStack.back()->toString().c_str());
		if (isprint(a))
			std::cout << static_cast<char>(a) << std::endl;
	}
	else
		throw VM::print_exception();
}

void VM::find_command(std::vector<std::string> const &ref)
{
	std::regex re("^\\s*(push|assert|pop|dump|add|sub|mul|div|mod|print)\\s*(.*)");
	std::smatch sm;
	for (auto it = ref.begin() ; it != ref.end(); ++it) {
		if (std::regex_match((*it), sm, re)) {
			(this->*(this->myMap[sm[1].str()]))(sm[2].str());
		}
	}
}

const char *VM::emptystack::what() const throw()
{
	return ("\033[31;1mError: Instruction pop on an empty stack\033[0m");
}

const char *VM::assertInstruction::what() const throw()
{
	return ("\033[31;1mError: An assert instruction is not true\033[0m");
}

const char *VM::less_than_two_instruction::what() const throw()
{
	return ("\033[31;1mError: The stack is composed of strictly less that two values when an arithmetic instruction is executed\033[0m");
}

const char *VM::division_modulo::what() const throw()
{
	return ("\033[31;1mError: Division/modulo by 0\033[0m");
}

const char *VM::print_exception::what() const throw()
{
	return ("\033[31;1mError: An print instruction is not true\033[0m");
}
