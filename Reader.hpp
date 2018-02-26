/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:51:06 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/26 12:41:50 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_CLASSREADER_HPP
#define ABSTRACTVM_CLASSREADER_HPP


#include <string>
#include <vector>
#include <regex>
#include "IOperand.hpp"

class Reader {
	private:
		bool _exitFlag;
		bool _progressFlag;
		std::vector<std::string> 	inputData;
		Reader& operator= (Reader const & rhs);
		Reader(Reader const & rhs);
	public:
		Reader();
		~Reader();

		void 	read_from_file(std::string);
		void 	read_from_stdin();
		bool 	getProgressFlag() const;
		std::vector<std::string> const &getVector() const;
		void 	error_manager(std::string &);
		void	validation(std::string & , int &, bool file);

		class ExitException: public std::exception {
			public:
				const char* what() const throw();
		};
		class lex_syn_error: public std::exception {
			public:
				const char* what() const throw();
		};
		class unknown_ins: public std::exception {
			public:
				const char* what() const throw();
		};
};


#endif
