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
#include "_precomp.h"
#include "HtmlPageParser.h"

using namespace std;

ParserAdapter::ParserAdapter(GumboTag gt, const std::string &divClass) :
tagStr_(gt),
divClass_(divClass),
beginParsing(false),
beginAtricleNode_(nullptr)
{}


// Рекурсивно обходим html-дерево, спускаемся до текстов
string
ParserAdapter::cleantext(GumboNode* node) {
	if (node->type == GUMBO_NODE_ELEMENT)
	{
		if (node->v.element.tag != GUMBO_TAG_SCRIPT && node->v.element.tag != GUMBO_TAG_STYLE && 
			node->v.element.tag != GUMBO_TAG_ASIDE)
		{
			// Ищем точку отсчета.
			if (node->v.element.tag == tagStr_)
			{
				GumboAttribute* classAttr = gumbo_get_attribute(&node->v.element.attributes, "class");
				if (classAttr && classAttr->value == divClass_)
				{
					beginParsing = true; // флажок начала вывода.
					beginAtricleNode_ = node; // Выше этой вершины не поднимаемсяю
				}
			}

			std::string contents = "";
			GumboVector* children = &node->v.element.children;
			for (unsigned int i = 0; i < children->length; ++i)
			{
				std::string &&text = cleantext((GumboNode*)children->data[i]);
				contents.append(text);
			}

			// Закончили вывод в файл, как вернулись в ту же вершину, с которой начинали.
			if (beginAtricleNode_ == node)
				beginParsing = false;

			if (beginParsing)
			{
				// Устанавливаем куда ссылка идет.
				if (node->v.element.tag == GUMBO_TAG_A) // Обрабатываем ссылки
				{
					GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href"); // предполагаем, что href должен быть всегда. TODO цементнуть
					contents.append(" [").append(href->value).append("] ");
				}

				// Теперь, если мы прошли </h1>, </h2>, </br>, <br/>, </p> тэг, то нужно перейти на другую строчку.
				if (node->v.element.tag == GUMBO_TAG_H1 || node->v.element.tag == GUMBO_TAG_H2 ||
					node->v.element.tag == GUMBO_TAG_H3 || node->v.element.tag == GUMBO_TAG_H4 ||
					node->v.element.tag == GUMBO_TAG_H5 || node->v.element.tag == GUMBO_TAG_H6 ||
					node->v.element.tag == GUMBO_TAG_BR || node->v.element.tag == GUMBO_TAG_P)
				{
					contents.append("\n\n");
				}
			}

			return contents;
		}
		return "";
	}
	else if (node->type == GUMBO_NODE_TEXT)
	{
		if (beginParsing)
			return std::string(node->v.text.text);
		else 
			return "";
	}
	else {
		return "";
	}
}

string
ParserAdapter::parse(const std::string &src)
{
	GumboOutput* output = gumbo_parse(src.c_str());
	
	if (nullptr == output)
		throw std::runtime_error("Unable to get html-root!!!");

	std::string out = cleantext(output->root);
	// Do stuff with output->root
	gumbo_destroy_output(&kGumboDefaultOptions, output);

	return std::move(out);
}