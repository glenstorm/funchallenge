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

#ifndef _HTML_PAGE_PARSER_H_GUARD_
#define _HTML_PAGE_PARSER_H_GUARD_

#include <gumbo.h>
#include <string>

class ParserAdapter
{
private:
	/// Процедура вычистки html страницы от всякого мусора.
	std::string cleantext(GumboNode* node);

	// Координаты начала вывода. Используемая библиотека не поддерживает xpath, поэтому пока жестко закодируем координату для lenta.ru
	GumboTag tagStr_;
	std::string divClass_;

	bool beginParsing;
	GumboNode* beginAtricleNode_;

public:
	ParserAdapter(GumboTag gt = GUMBO_TAG_DIV, const std::string &divClass = "b-topic__content");
	/// Возвращаем распарсенный и урезанную страничку html.
	std::string parse(const std::string &src);
};



#endif
// _HTML_PAGE_PARSER_H_GUARD_





