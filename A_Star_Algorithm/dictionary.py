#!/usr/bin/python

from nltk.corpus import wordnet
from nltk.tag import pos_tag
from nltk.stem.wordnet import WordNetLemmatizer
#if not wordnet.synsets(word_to_test):
  #Not an English Word
#else:
  #English Word

import sys
import re

#function to find unique elements in a list
def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist

def remove_extras(l):
	new_list = []
	new_tagged_list = pos_tag(l)

deleters = ('#','@','&','0','1','2','3','4','5','6','7','8','9')
extras = ('"','.','(',')','-','/','\\')
remove_poslist = ('NN','TO','IN','PRP','WP','SYM','RP','POS','PDT','NNP','NNPS','NNS','LS','FW','DT','CD',':',',','$','(',')','--','.')
shred = ('"','*','@','(')

input_file_name=sys.argv[1]
output_file_name = sys.argv[2]

filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")

#take input and split into sentences
list_of_sentences=[]
inputlist2 = ""
templist1 = []
for inputline in filein:
	templist1 = inputline.split('\t',1)
	inputlist2 = templist1[1].split()
	for word in inputlist2:
		for element in shred:
			if element in word and word in templist1 :
				word = re.sub('[?*=|:();,!@#$.\"^]', '', word)
				print word
				print "        asdf"
				print re.sub(r"[?*=|:();,!@#$.\"^]", r"", word)
	tagged_sent = pos_tag(inputlist2)
	templist2 = [word for word,pos in tagged_sent if pos not in remove_poslist ]
	#templist1 = unique_list(inputline2.split())
	#templist1.remove(templist1[0])
	list_of_sentences.extend(templist2)

#print list_of_sentences
new_list_of_sentences=[]
#for sentence in list_of_sentences:
#	sentence.extend

#remove null strings from the list of sentences
while '' in list_of_sentences:
	list_of_sentences.remove('')

list_of_sentences.sort()
#now remove unnecessary words
templist = ""
for templist in list_of_sentences:
	if templist.startswith(deleters):
		list_of_sentences.remove(templist)
	elif len(templist) <= 2:
		list_of_sentences.remove(templist)
	elif "http" in templist :
		list_of_sentences.remove(templist)
	elif templist[0].isupper():
		list_of_sentences.remove(templist)
	else:
		for element in extras:
			if element in templist and templist in list_of_sentences:
				list_of_sentences.remove(templist)
				#print templist
		for element in deleters:
			if element in templist and templist in list_of_sentences:
				list_of_sentences.remove(templist)
				#print templist
		fileout.write(templist.lower())
		fileout.write("\n")