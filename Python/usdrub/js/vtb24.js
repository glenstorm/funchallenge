var page = require('webpage').create();
var fs = require('fs');
page.open('http://m.vtb24.ru/personal', function() {
	fs.write('out.html', page.content, 'w');
	phantom.exit();
});

