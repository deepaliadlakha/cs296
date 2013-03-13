#!/usr/bin/python3

import re
import subprocess

f = open('lab09_g09_data.csv', 'w')

for j in range(1,11): # j is rerun number
	for i in range(1,11): # i is iteration value
		process = subprocess.Popen(["../bin/cs296_base", str(i)], stdout=subprocess.PIPE)
		output = process.stdout.read()
		output = str(output)
		numbers = re.findall(r'[0-9][0-9]*[\.]*[0-9]*',output)
		for m in range(0,6):
			f.write(str(j)+',')
			if(m == 5): f.write(numbers[m])
			else: f.write(numbers[m]+',')
		f.write('\n')
