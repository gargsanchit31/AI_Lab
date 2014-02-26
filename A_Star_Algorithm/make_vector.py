import sys
import re
import nltk

from nltk.corpus import wordnet
from nltk.tag import pos_tag


def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist


input_file_name=sys.argv[1]
output_file_name = sys.argv[2]
filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")

input_string = filein.read()
output_string = ""



temp_list = nltk.word_tokenize(input_string)
temp_list.sort()

for word in temp_list:
	print word
	print "\n"
	fileout.write(word)
	fileout.write("\n")