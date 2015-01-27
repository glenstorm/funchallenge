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
#include <string>
#include <sstream>
#include <iomanip>
#include <codecvt>

using namespace std;


// convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

// convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

PrettyOut::PrettyOut(const string &wrapStr, int width) :
		str_(wrapStr),
		width_(width) 
{};

ostream& 
operator<<(ostream& out, const PrettyOut& obj)
{
	// ������� ����� � �����
	// �� ������ ����� ������ ����� � ����������� �����, ���� � ��� �� ����� ����������� �� ������.
	// ����� ������� ����� �������.

	// create a read/write stream object
	std::wistringstream in(utf8_to_wstring(obj.str_));

	std::wstring line;
	while (!in.eof()) {
		getline(in, line);

		// wrap string
		// ��������
		// 1) ��������� ����� �� 80(n) �������� ������.
		// 2) �������� ����������� ����� ���� �� ��������� �� ������ |_|
		// 3) ������� ������� �� ��������� ������� �� ���������.
		// 4) ������������� ��������� �������� ��� �������.
		// 5) ���� �� ����� ������ �.1 � �.�.
		size_t beginPos = 0, curPos = obj.width_;
		while (curPos <= line.size())
		{
			curPos = line.find_last_of(' ', curPos);
			wstring temp = line.substr(beginPos, curPos - beginPos);

			cout << wstring_to_utf8(temp) << endl;
			beginPos = curPos;
			curPos = beginPos + obj.width_;
		}

		// ������� ������� ������.
		cout << wstring_to_utf8(line.substr(beginPos, curPos)) << endl;
	}
	
	// ��������� ������� ����. ������ ������� ����� ��������� �� ���������� ������������ �����.
	return out;
}

