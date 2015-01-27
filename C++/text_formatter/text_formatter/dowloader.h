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

#ifndef _DOWNLOADER_H_GUARD_
#define _DOWNLOADER_H_GUARD_

#include <string>
#include <curl/curl.h>

class Dowloader
{

public:
	/// Ctor
	Dowloader(){};
	/// Dtor
	~Dowloader(){};
	/// ��������� �������� � �������.
	static std::string downloadPage(const std::string& url);

private:
	/// ��� ������� ���������� ��������� ����� � ����.
	static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);
};

#endif
	// _DOWNLOADER_H_GUARD_

