#!/usr/bin/env python
# -*- coding: utf-8 -*- 
import requests
from subprocess import call
from lxml import html

class bank:
	def __init__(self, name, url, path, js):
		self._name = name
		self._url = url
		self._path = path
		self._js = js	

	_name = "Имя банка";
	_url = "url банка"; # дублируется в скриптах. Оставим для вывода
	_path = "Строка для поиса в html-документе"
	_js = "Путь к phanthomjs скрипту"
	_curs = 0.0

	
def file_get_contents(filename):
    with open(filename) as f:
        return f.read()

def get_page(js):
	page = None

	call(["phantomjs", js])
	# в файле out.html -> cкачанная версия сайта.
	# заполняем page содержимым из файла.
  
	page = file_get_contents("out.html")
	return page

def get_urls_from_page(banks):

	for b in banks:
		page = get_page(b._js)	
		if(page == None):
			print "Page is none!!!"
		doc = html.document_fromstring(page)
		value = doc.xpath(b._path)
 		for i in value:
			#print "Текущее значение валюты: " + i
			i = i.replace(',', '.');
			b._curs = float(i.strip())
	return banks

banks = []
banks.append(bank('ВТБ24','http://m.vtb24.ru/personal','.//span[@data-bind="text: cash.eurSellValue"]/text()', 'js/vtb24.js'))
#banks.append(bank('Сбербанк', 'http://www.sberbank.ru/saintpetersburg/ru/quotes/currencies/','((.//table[@class="table3_eggs4"]/tbody/tr)[3]/td)[5]/text()','sber.js'))
banks.append(bank('Промсвязьбанк','http://www.psbank.ru/','(.//li[@class="sale-column"])[2]/text()','js/prom.js'))

banks = get_urls_from_page(banks)

out_str = 'Продажа евро: '

for b in banks:
	out_str += b._name + " --> " + str(b._curs) + "\n"
	print b._name
	print b._path
	print b._url
	print b._curs
	print "================================"
	print
