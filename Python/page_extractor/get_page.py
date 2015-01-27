#!/usr/bin/python
# -*- coding: utf-8 -*- 
""" Скачиваем и парсим страницу.

Copyright (C) 2015 Dmitry Borisov

"""
from lxml import html 				# for xPath traversing
import requests 					# for downloading web pages
import argparse 					# for parsing program options
from configobj import ConfigObj		# for ini options
import textwrap
from urlparse import urlparse

# for program options parsing
def createParser ():
    parser = argparse.ArgumentParser()
    parser.add_argument ('-u', '--url')
 
    return parser

# Парсим html-документ
def getTree(str, m_xpath):
	r = requests.get(str)
	page = r.text
	
	doc = html.document_fromstring(page)
	result = doc.xpath(m_xpath)
	
	for item in result:
		print item.tag
		if item.tag == 'script type="text/javascript"':
			item.drop_tree()
		text = html.tostring(doc, encoding='cp1251')
		#print text
	
	return result

def printChild(root):
	for child in root:
		if child.tag != 'script':	
			print(child.text_content().encode("CP1251"))
			print child.tag
		printChild(child)

def getUrl():
	parser = createParser()
	namespace = parser.parse_args()
	
	return namespace.url

def prettyprint(text):
	return textwrap.fill(text, width=80)
	
def main():
	urlToParse = getUrl()
	if(not urlToParse):
		return
	
	# извлекаем базовый url сайта, который является ключом для извлечения информации из статей на этом сайте.
	# Смотрим в файл настроек и извлекаем 
	config = ConfigObj(u"rulez.ini")
	opts = config.dict()
	
	# пытаемся соотнести введенный url с настройками извлечения.
	m_url = urlparse(urlToParse)
	
	m_xPath = opts['filters'][m_url.netloc]
	
	if(m_xPath):
		res = getTree(urlToParse, m_xPath)
	else:
		print "Filters not found!!!"
		
	# Сейчас парсим оставшийся фрагмент, 
	
	
	# str2format = 'Для работы с различными типами данных было создано два объекта: MaterialList(object) — список статей (содержит метод парсинга отдельной страницы списка _ParseList и метод получения URL следующей страницы _GetNextPage, хранит список материалов и их идентификаторов) и Material(object) — собственно статья(содержит метод формирования идентификатора на основе даты _InitID, метод парсинга страницы _ParsePage, метод определения источника публикации _GetSection и атрибуты статьи, такие как дата публикации, тип материала и проч.)'
	# print prettyprint(str2format)
	

if __name__ == "__main__":
	main()

	
	

	
	
