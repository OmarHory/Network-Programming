
#Requesting an HTTP to find a certain value
#Example for running: ./htmlReq.py 78.50 kilograms pounds

import sys
import re
import urllib
#!/usr/bin/python

number = str(sys.argv[1])

fromt = str(sys.argv[2])
to = str(sys.argv[3])

url = 'http://unitconverter.io/' + fromt + '/' + to + '/' + number

f= open('web.html', "w")
for line in urllib.urlopen(url):
	line.decode('utf-8')
	f.write(line)

f.close()
f= open('web.html', "r")


findObj = re.findall(r'the result is ([\d,.]+)',f.read())


print "%s %s = %s %s" % (number,fromt,str(findObj[0]),to)

f.close()