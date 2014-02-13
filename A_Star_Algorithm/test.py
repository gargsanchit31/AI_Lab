#if not wordnet.synsets(word_to_test):
  #Not an English Word
#else:
  #English Word

import sys
import re
import nltk

from nltk.corpus import wordnet
from nltk.tag import pos_tag

input_file_name=sys.argv[1]
output_file_name = sys.argv[2]

filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")


deleters = ('#','@','&','0','1','2','3','4','5','6','7','8','9','\\','/')
extras = ('"','.','(',')','-','/','\\','!','*')
remove_poslist = ('NN','TO','IN','PRP','WP','SYM','RP','POS','PDT','NNP','NNPS','NNS','LS','FW','DT','CD',':',',','$','(',')','--','.')
shred = ('"','*','@','(')

#function to find unique elements in a list
def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist

def remove_extras(l):
	new_list = []
	tokens = []
	for line in l:
		tokens = nltk.word_tokenize(line)
		new_list.append(tokens)
	return new_list

corpus = ""
corpus = filein.read()

corpus_list = []
corpus_list = corpus.split('\n')

#this part removes the users who posted tweets, new_corpus_list contains list of lists
new_corpus_list = []
for line in corpus_list:
	tmp_str = line.split('\t',1)
	if len(tmp_str) == 2 :
		new_corpus_list.append(tmp_str[1])
	else :
		corpus = ""


corpus_list = []
out_list = []
remove_list = []
# this part removes the http words, and words with capitals etc
for line in new_corpus_list:
	corpus_list = line.split()
	#print corpus_list
	remove_list = []
	#print corpus_list
	for word in corpus_list:
		#print word
		wordlist = list(word)
		#print wordlist
		A_set = set(a for a in wordlist)
		B_set = set(b for b in deleters)
		if len(A_set & B_set) > 0 :
			remove_list.append(word)
		elif "http" in word:
			remove_list.append(word)
		else :
			A_set = B_set
	# now remove all elements in remove list, from the corpus list
	for word in remove_list:
		corpus_list.remove(word)
	str1 = ' '.join(str(e) for e in corpus_list)
	#remove the extra symbols
	str2 = re.sub(r"[-.:!*()\"\?]", r"", str1)
	out_list.append(str2)

corpus_list = []
new_corpus_list = []
final_list = []
for sentence in out_list:
	corpus_list = nltk.word_tokenize(sentence)
	tagged_sent = pos_tag(corpus_list)
	#print tagged_sent
	new_corpus_list = [word.lower() for word,pos in tagged_sent if pos not in remove_poslist ]
	str1 = ' '.join(str(e) for e in new_corpus_list)
	final_list.extend(new_corpus_list)

#print final_list
final_list = unique_list(final_list)
corpus_list = []
for words in final_list:
	#print words
	if len(words) > 0:
		#corpus_list = words.split()
		#for word in corpus_list:
		#print words
		fileout.write(words)
		fileout.write("\n")
	else :
		print "#######################"
#corpus_list = []
#for sentence in out_list:
#	for word in sentence:






#for sentence in out_list:
#	print sentence
#for wordlist in remove_list:
	
	#print out_list

#print out_list

#	corpus_list.extend(tmp_str)
#for words in new_corpus_list:
#	print words
#print corpus_list

#return_list = remove_extras(new_corpus_list)
#print return_list


#for words in return_list:
#
#	fileout.write(words)
#	fileout.write("\n")


#for sentence in return_list:
#	print sentence