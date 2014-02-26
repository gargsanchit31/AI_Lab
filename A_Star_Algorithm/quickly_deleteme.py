from nltk.corpus import wordnet
from nltk.tag import pos_tag

#if not wordnet.synsets(word_to_test):
  #Not an English Word
#else:
  #English Word

import sys

#function to find unique elements in a list
def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist

deleters = ('#','@','&','0','1','2','3','4','5','6','7','8','9')
extras = ('"','.','')
remove_poslist2 = ('NN','TO','IN','PRP','WP','SYM','RP','POS','PDT','NNP','NNPS','NNS','LS','FW','DT','CD',':',',','$','(',')','--','.')
remove_poslist = ('NN','TO','IN','PRP','PRP$','WP','SYM','RP','POS','NNP','NNPS','NNS','LS','FW','CD',':',',','$','(',')','--','.')

input_file_name=sys.argv[1]
output_file_name = sys.argv[2]

filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")

#take input and split into sentences
list_of_sentences=[]
inputline2 = ""
templist1 = []
for inputline in filein:
	templist1 = inputline.split('\t',1)
	inputline2 = templist1[1]
	tagged_sent = pos_tag(inputline2.split())
	for word,pos in tagged_sent:

	templist2 = [word for word,pos in tagged_sent if pos not in remove_poslist ]