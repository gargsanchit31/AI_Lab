#!/usr/bin/python

#from nltk.corpus import wordnet

#if not wordnet.synsets(word_to_test):
  #Not an English Word
#else:
  #English Word



import sys
import en

def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist

deleters = ('#','@','&')

input_file_name=sys.argv[1]
output_file_name = sys.argv[2]

filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")

a = ""
a = filein
a=' '.join(unique_list(a.split()))
l = ""
for l in a:
	for word in l.split():
		if word.startswith(deleters):
			print ""
		elif len(word) <= 2 :
			print ""
		elif "http" in word :
			print ""
		elif "ing" in word :
			print ""
		elif "ed" in word :
			print ""
		else:
			print word