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

#ifndef _OPTIONS_H_GUARD_
#define _OPTIONS_H_GUARD_

/**
@class Options 
@brief Класс, ответственный за считывание настроек для данной программы.
*/
class Options
{
public:
	Options(const std::string& fn = "rulez.ini");
	~Options(){};

	// Разбор и заполнение структуры 
	static std::string getUrlForParsing(int argc, char** argv);
private:
	// Имя файла с настройками.
	std::string fn_;



};

#endif
	// _OPTIONS_H_GUARD_