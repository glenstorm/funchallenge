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

#include "PrettyOut.h"
#include "convert_utf8_unicode_helper.h"
#include <string>
#include <sstream>


using namespace std;


PrettyOut::PrettyOut(const string &wrapStr, int width) :
		str_(wrapStr),
		width_(width) 
{};

ostream& 
operator<<(ostream& out, const PrettyOut& obj)
{
	// Считаем текст в поток
	// По одному слову делаем вывод в стандартный поток, пока у нас не будет переполения по ширине.
	// иначе начнаем новую строчку.

	// create a read/write stream object
	std::wistringstream in(utf8_to_wstring(obj.str_));

	std::wstring line;
	while (!in.eof()) {
		getline(in, line);

		// wrap string
		// алгоритм
		// 1) Переходим сразу на 80(n) символов вперед.
		// 2) Движемся посимвольно назад пока не наткнемся на пробел |_|
		// 3) Выводим строчку от начальной позиции до найденной.
		// 4) Устанавливаем найденную страницу как текущую.
		// 5) Пока не конец строки п.1 и т.д.
		size_t beginPos = 0, curPos = obj.width_;
		while (curPos <= line.size())
		{
			curPos = line.find_last_of(' ', curPos);
			wstring temp = line.substr(beginPos, curPos - beginPos);

			cout << wstring_to_utf8(temp) << endl;
			beginPos = curPos;
			curPos = beginPos + obj.width_;
		}

		// выводим остаток строки.
		cout << wstring_to_utf8(line.substr(beginPos, curPos)) << endl;
	}
	
	// Построчно считаем файл. Каждую строчку далее разбиваем на подстрочки определенной длины.
	return out;
}

