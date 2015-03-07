/*
@author: Dmitry Borisov 2015

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "options.h"

#include <iostream>
#include <boost/property_tree/ini_parser.hpp>

#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

using namespace boost;
using namespace std;

namespace po = boost::program_options;

Options::Options(const std::string& fn) :
fn_(fn)
{
	property_tree::ptree config;

	try
	{
		property_tree::ini_parser::read_ini(fn_, config);
	}
	catch (property_tree::ini_parser_error& error)
	{
		cout	<< error.message() << ": " << error.filename() << ", line " << error.line() << std::endl;
	}
}

string 
Options::getUrlForParsing(int argc, char** argv)
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("url", po::value<string>(), "set URL for dowloading")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
	}

	if (vm.count("url")) {
		return vm["url"].as<string>();
	}

	return "";
}




