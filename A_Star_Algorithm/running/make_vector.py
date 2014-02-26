import nltk
import sys
import re
import difflib
import random

from nltk.corpus import wordnet
from nltk.tag import pos_tag
from nltk.stem.wordnet import WordNetLemmatizer

lmtzr = WordNetLemmatizer()


#number of lines in a file
def file_len(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1



input_file_name=sys.argv[1]
input_file2_name=sys.argv[2]
output_file_name = sys.argv[3]
output_file_name2 = sys.argv[4]


filein = open(input_file_name, "r")
filein2 = open(input_file2_name, "r")
#fileout = open(output_file_name,"a")
#fileout2 = open(output_file_name2,"a")


remove_poslist = ('WP','NN','TO','PRP','WP','SYM','RP','POS','PDT','NNP','NNPS','NNS','LS','FW','CD',':',',','$','(',')','--','.')

dictionary = filein2.read().split()

tweet_corpi = filein.readlines()

hash_lines = file_len(input_file_name)

test_set = random.sample(xrange(1,hash_lines), hash_lines/5)

index = 0
out_string = ""
if "positive" in input_file_name:
	output = 1
	out_string = "1 0 0 "
elif "objective" in input_file_name:
	output = 0
	out_string = "0 1 0 "
else :
	output = -1
	out_string = "0 0 1 "



for tweet in tweet_corpi:
	index = index + 1
	if index in test_set:
		fileout = open(output_file_name2,"a")
	else :
		fileout = open (output_file_name,"a")
		fileout.write(out_string)
	#tweet = filein.read()
	tokens = []
	old_list = tweet.split()
	for tweet in old_list:
		if tweet == re.sub(r'[?*=|:();!@#$^]', r'', tweet):
			tweet = re.sub(r'[.,\"]',r'',tweet)
			tokens.append(tweet)
		else :
			print "tweet"
	#tokens = nltk.word_tokenize(tweet)
	#print tokens
	old_list = []
	new_list = []
	for words in tokens:
		old_list.append(lmtzr.lemmatize(words))

	#print old_list

	tagged_sent = pos_tag(old_list)
	#print tagged_sent
	new_list = [word.lower() for word,pos in tagged_sent if pos not in remove_poslist ]

	new_set = set(new_list)
	new_list = list(new_list)
	new_list.sort()

	#print new_list


	#print dictionary
	flag = 0
	number = 0.0
	for words in dictionary:
		#print word
		for token in new_list:
			#print token
			#print words
			#print token
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

	#fileout.write(out_string)
	fileout.write("\n")
	#print new_list