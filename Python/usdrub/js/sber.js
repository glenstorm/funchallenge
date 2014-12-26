var page = require('webpage').create();
var fs = require('fs');
page.open('http://www.sberbank.ru/saintpetersburg/ru/quotes/currencies/', function() {
	fs.write('out.html', page.content, 'w');
	phantom.exit();
});

