import subprocess

toprint = []
with open('examples.mdsource', 'r') as file:
	for line in file.readlines():
		words = line.split()
		if (len(words) > 0 and words[0] == '@@include'):
			with open(words[1], 'r') as subfile:
				for subline in subfile.readlines():
					toprint.append(subline)
		elif (len(words) > 0 and words[0] == '@@output'):
			cmd = subprocess.run(line[8:], shell=True)
			cmd = subprocess.run('a.exe', shell=True, capture_output=True)
			output = cmd.stderr
			toprint.append(output.decode())
		else:
			toprint.append(line)

with open('examples.md', 'w') as file:
	file.writelines(toprint)
