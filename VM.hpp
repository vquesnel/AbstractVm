/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:52:36 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/21 13:36:07 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_CLASSVM_HPP
#define ABSTRACTVM_CLASSVM_HPP

#include <iostream>
#include <vector>
#include <map>
#include "IOperand.hpp"
#include "FactoryMethod.hpp"


class VM {
	private:
		std::vector<IOperand const *> _myStack;
		static FactoryMethod _FM;
		std::map<std::string, void (VM::*)(std::string const &)> _myMap;
		std::map<std::string, eOperandType> _myOperations;
		VM(VM const &rhs);
		VM& operator=(VM const &rhs);
	public:
		VM();
		~VM();

		void	push(std::string const &);
		void	assert(std::string const &);
		void	pop(std::string const &);
		void 	dump(std::string const &);
		void 	add(std::string const &);
		void 	sub(std::string const &);
		void 	mul(std::string const &);
		void 	div(std::string const &);
		void 	mod(std::string const &);
		void 	print(std::string const &);
		void 	avmSin(std::string const &);
		void 	avmCos(std::string const &);
		void 	avmTan(std::string const &);
		void 	avmSqrt(std::string const &);
		void	total(std::string const &);
		void	average(std::string const &);
		void	dispatcher(std::vector<std::string> const &);
		class VM_Exceptions : public std::exception {};
		class emptystack: public VM_Exceptions {
			public:
				const char* what() const throw();
		};
		class assertInstruction: public VM_Exceptions {
			public:
				const char* what() const throw();
		};
		class less_than_two_instruction: public VM_Exceptions {
			public:
				const char* what() const throw();
		};
		class division_modulo: public VM_Exceptions {
			public:
				const char* what() const throw();
		};
		class print_exception: public VM_Exceptions {
			public:
				const char* what() const throw();
		};
		class negativesqrt: public VM_Exceptions {
			public:
				const char* what() const throw();
		};
};

#endif
