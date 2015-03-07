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

#ifndef _PRETTY_OUT_H_GUARD_
#define _PRETTY_OUT_H_GUARD_

class PrettyOut
{
public:
	explicit PrettyOut(const std::string &wrapStr, int width = 120);
	~PrettyOut(){}
	// Вывод в поток с ограничением длины.
	friend std::ostream& operator<<(std::ostream& out, const PrettyOut& obj);
private:
	/// Максимальная ширина вывода.
	int width_;
	/// Строка, которую будем выводить.
	std::string str_;
};



#endif
	// _PRETTY_OUT_H_GUARD_

