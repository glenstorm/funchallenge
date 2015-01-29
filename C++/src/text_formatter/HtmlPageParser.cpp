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

#include "HtmlPageParser.h"
#include <iostream>
#include <sstream>

using namespace std;

ParserAdapter::ParserAdapter(GumboTag gt, const std::string &divClass) :
tagStr_(gt),
divClass_(divClass),
beginParsing(false),
beginAtricleNode_(nullptr)
{}


// ���������� ������� html-������, ���������� �� �������
string
ParserAdapter::cleantext(GumboNode* node) {
	if (node->type == GUMBO_NODE_ELEMENT)
	{
		if (node->v.element.tag != GUMBO_TAG_SCRIPT && node->v.element.tag != GUMBO_TAG_STYLE && 
			node->v.element.tag != GUMBO_TAG_ASIDE)
		{
			// ���� ����� �������.
			if (node->v.element.tag == tagStr_)
			{
				GumboAttribute* classAttr = gumbo_get_attribute(&node->v.element.attributes, "class");
				if (classAttr && classAttr->value == divClass_)
				{
					beginParsing = true; // ������ ������ ������.
					beginAtricleNode_ = node; // ���� ���� ������� �� ������������
				}
			}

			std::string contents = "";
			GumboVector* children = &node->v.element.children;
			for (unsigned int i = 0; i < children->length; ++i)
			{
				const std::string text = cleantext((GumboNode*)children->data[i]);
				contents.append(text);
			}

			// ��������� ����� � ����, ��� ��������� � �� �� �������, � ������� ��������.
			if (beginAtricleNode_ == node)
				beginParsing = false;

			// ������������� ���� ������ ����.
			if (node->v.element.tag == GUMBO_TAG_A) // ������������ ������
			{
				GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href"); // ������������, ��� href ������ ���� ������. TODO ����������

				if (beginParsing)
				{
					ostringstream is;
					is << " [" << href->value << "]";
					contents.append(is.str());
				}
			}

			// ������, ���� �� ������ </h1>, </h2>, </br>, <br/>, </p> ���, �� ����� ������� �� ������ �������.
			if (node->v.element.tag == GUMBO_TAG_H1 || node->v.element.tag == GUMBO_TAG_H2 ||
				node->v.element.tag == GUMBO_TAG_H3 || node->v.element.tag == GUMBO_TAG_H4 ||
				node->v.element.tag == GUMBO_TAG_H5 || node->v.element.tag == GUMBO_TAG_H6 ||
				node->v.element.tag == GUMBO_TAG_BR || node->v.element.tag == GUMBO_TAG_P)
			{
				contents.append("\n\n");
			}

			return contents;
		}
		return "";
	}
	else if (node->type == GUMBO_NODE_TEXT)
	{
		if (beginParsing)
			return std::string(node->v.text.text);
		else return "";
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

	std::string out = "";
	// ���������������.
	try
	{
		out = cleantext(output->root);
	}
	catch (std::exception &e)
	{
		cout << "Exception: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "�������������� ����������!!!";
	}
	// Do stuff with output->root
	gumbo_destroy_output(&kGumboDefaultOptions, output);

	return std::move(out);
}