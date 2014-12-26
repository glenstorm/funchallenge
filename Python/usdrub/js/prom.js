var page = require('webpage').create();
var fs = require('fs');
page.open('http://www.psbank.ru/', function() {
	fs.write('out.html', page.content, 'w');
	phantom.exit();
});

