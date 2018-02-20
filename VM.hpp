/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:52:36 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 13:28:42 by vquesnel         ###   ########.fr       */
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
		std::vector<IOperand const *> myStack;
		static FactoryMethod FM;
		std::map<std::string, void (VM::*)(std::string const &)> myMap;
		std::map<std::string, eOperandType> myOperations;
		VM(VM const & rhs);
		VM& operator= (VM const & rhs);
	public:
		VM();
		~VM();

		void	push(std::string const & );
		void	assert(std::string const & );
		void	pop(std::string const & );
		void 	dump(std::string const &);
		void 	add(std::string const &);
		void 	sub(std::string const &);
		void 	mul(std::string const &);
		void 	div(std::string const &);
		void 	mod(std::string const &);
		void 	print(std::string const &);
		void	find_command(std::vector<std::string> const & );
		class emptystack: public std::exception {
			public:
				const char* what() const throw();
		};
		class assertInstruction: public std::exception {
			public:
				const char* what() const throw();
		};
		class less_than_two_instruction: public std::exception {
			public:
				const char* what() const throw();
		};
		class division_modulo: public std::exception {
			public:
				const char* what() const throw();
		};
		class print_exception: public std::exception {
			public:
				const char* what() const throw();
		};
};

#endif
