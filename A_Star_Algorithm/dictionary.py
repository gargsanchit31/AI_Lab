#!/usr/bin/python

from nltk.corpus import wordnet

#if not wordnet.synsets(word_to_test):
  #Not an English Word
#else:
  #English Word



import sys
#import en

def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist

deleters = ('#','@','&')

input_file_name=sys.argv[1]
output_file_name = sys.argv[2]

filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")

b=[]
a = ""
for a in filein:
	b.extend(unique_list(a.split(" ")))

print b

l = ""
for l in b:
	if l.startswith(deleters):
		print ""
	elif len(l) <= 2 :
		print ""
	elif "http" in l :
		print ""
	elif "ing" in l :
		print ""
	elif "ed" in l :
		print ""
	else:
		print l