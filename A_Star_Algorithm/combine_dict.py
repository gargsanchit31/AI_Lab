import sys
import re
import nltk

def unique_list(l):
	ulist = []
	[ulist.append(x) for x in l if x not in ulist]
	return ulist

output_file_name = sys.argv[2]

input_file_name=sys.argv[1]
#input_file_name2 = sys.argv[2]
#input_file_name3 = sys.argv[3]

filein = open(input_file_name, "r")
fileout = open(output_file_name,"w")
#filein2 = open(input_file_name2,"r")
#filein3 = open(input_file_name3,"r")

#take input and split into sentences
inputline = ""
inputline = filein.read()

#print inputline
list_of_sentences=[]
list_of_sentences.extend(unique_list(inputline.split("\n")))
list_of_sentences.sort()

temp_list_of_sentences = []	
for line in list_of_sentences:
	line = re.sub('[?*=|:();,!@#$.\"^]', '', line)
	temp_list_of_sentences.append(line)
	
from nltk.stem.snowball import SnowballStemmer
from nltk.stem.wordnet import WordNetLemmatizer


lmtzr = WordNetLemmatizer()

stemmer = SnowballStemmer("english")

output_list_of_sentences=[]
for words in temp_list_of_sentences:
	output_list_of_sentences.append(stemmer.stem(words))

lines_list = []
for words in output_list_of_sentences:
	lines_list.append(lmtzr.lemmatize(words).lower())

final_list=[]
final_list.extend(unique_list(lines_list))

filtered_words = []
filtered_words = [w for w in final_list if not w in nltk.corpus.stopwords.words('english')]
for words in filtered_words:
	fileout.write(words)
	fileout.write("\n")

#print final_list

	#fileout.write(line)
	#fileout.write("\n")

#for inputline in filein2:
#	list_of_sentences.extend(unique_list(inputline.split("\n")))

#for inputline in filein3:
#	list_of_sentences.extend(unique_list(inputline.split("\n")))

#while '' in list_of_sentences:
#	list_of_sentences.remove('')

#print temp_list_of_sentences