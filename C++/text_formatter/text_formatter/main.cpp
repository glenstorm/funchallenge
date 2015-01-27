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

#include <iostream>
#include "options.h"
#include "dowloader.h"
#include "PrettyOut.h"
#include "HtmlPageParser.h"

using namespace std;

int main(int argc, char** argv)
{
	// Узнаем какой ресурс скачиваем
	string urlString = Options::getUrlForParsing(argc, argv);
	
	if (urlString.empty())	{
		cout << "Not write url for downloading. Please try again." << endl;
		return 0;
	}

	string res = Dowloader::downloadPage(urlString);

	ParserAdapter hp;
	string tunyHtml = hp.parse(res);

	PrettyOut po(tunyHtml, 80);
	cout << po << endl;
	return 0;
}




