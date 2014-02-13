import nltk
import sys
import re

from nltk.corpus import wordnet
from nltk.tag import pos_tag
from nltk.stem.wordnet import WordNetLemmatizer

remove_poslist = ('WP','TO','NN','PRP','WP','MD','SYM','RP','POS','PDT','NNP','NNPS','NNS','LS','FW','DT','CD',':',',','$','(',')','--','.')
lmtzr = WordNetLemmatizer()

input_file_name=sys.argv[1]

filein = open(input_file_name, "r")

#for synset in list(wn.all_synsets('n')):
#    print synset


string = filein.read()

new_list = string.split()
new_set = set(new_list)
old_list = list(new_set)

new_list = []
for words in old_list:
	new_list.append(lmtzr.lemmatize(words))

tagged_sent = pos_tag(new_list)

new_list = [word.lower() for word,pos in tagged_sent if pos not in remove_poslist or "itchy" in word]


new_list.sort()
for element in new_list:
	if "'" not in element and len(element) > 1:
		print element
		#new_set = set(new_list)
	else :
		new_set = set(new_list)

#for ele in tagged_sent:
#	print ele

#tagged_sent = pos_tag(corpus_list)
	#print tagged_sent
#	new_corpus_list = [word.lower() for word,pos in tagged_sent if pos not in remove_poslist ]
