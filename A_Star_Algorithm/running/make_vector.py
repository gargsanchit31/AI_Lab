import nltk
import sys
import re
import difflib

from nltk.corpus import wordnet
from nltk.tag import pos_tag
from nltk.stem.wordnet import WordNetLemmatizer

lmtzr = WordNetLemmatizer()


input_file_name=sys.argv[1]
input_file2_name=sys.argv[2]
output_file_name = sys.argv[3]


filein = open(input_file_name, "r")
filein2 = open(input_file2_name, "r")
fileout = open(output_file_name,"w")


remove_poslist = ('WP','NN','TO','PRP','WP','SYM','RP','POS','PDT','NNP','NNPS','NNS','LS','FW','CD',':',',','$','(',')','--','.')


tweet = filein.read()
dictionary = filein2.read().split()
tokens = []
old_list = tweet.split()
for tweet in old_list:
	if tweet == re.sub(r'[?*=|:();!@#$^]', r'', tweet):
		tweet = re.sub(r'[.,\"]',r'',tweet)
		tokens.append(tweet)
	else :
		print tweet
#tokens = nltk.word_tokenize(tweet)
print tokens
old_list = []
new_list = []
for words in tokens:
	old_list.append(lmtzr.lemmatize(words))

#print old_list

tagged_sent = pos_tag(old_list)
print tagged_sent
new_list = [word.lower() for word,pos in tagged_sent if pos not in remove_poslist ]

new_set = set(new_list)
new_list = list(new_list)
new_list.sort()

#print new_list


print dictionary
flag = 0
number = 0.0
for words in dictionary:
	#print word
	for token in new_list:
		#print token
		print words
		print token
		number = difflib.SequenceMatcher(None, words, token).ratio()
		#print number
		if number >= 0.7 :
			#print number
			fileout.write("1 ")
			flag = 1
			break;
		else :
			fileout.write("")
	if flag == 0 :
		fileout.write("0 ")
	else :
		fileout.write("")
		flag = 0



print new_list