import re
import enchant
#process tweets
def processTweet(tweet):
    #start processing
    #convert tweet to lower case
    tweet=tweet.lower()
    #Convert www.* or https?://* to URL
    tweet = re.sub('((www\.[\s]+)|(https?://[^\s]+))','URL',tweet)
    #Convert @username to AT_USER
    tweet = re.sub('@[^\s]+','AT_USER',tweet)
    #Remove additional white spaces
    tweet = re.sub('[\s]+', ' ', tweet)
    #Remove hastag '#' 
    tweet = re.sub(r'#([^\s]+)', r'\1', tweet)
    #trim
    tweet = tweet.strip('\'"')
    tweet = re.sub(r"(.)\1{1,}",r'\1\1',tweet)
    return tweet

#process the entire tweetfile
def processFile(filename):
    #Read the tweets one by one and process it
    read = 'Corpus/'+filename
    write= 'Corpus/processed_'+filename
    fr = open(read, 'r')
    fw = open(write,'a')
    line = fr.readline()
     
    while line:
       # split_tweet = line.split('\t')
        processedTweet = processTweet(line)
        #fw.write(split_tweet[0])
        #fw.write('\t')
        fw.write(processedTweet)
        fw.write('\n')
        line = fr.readline()
        
    #end loop
    fr.close()
    fw.close()



            
#start getStopWordList
def getStopWordList(stopWordListFileName):
    #read the stopwords file and build a list
    stopWords = []
    stopWords.append('AT_USER')
    stopWords.append('URL')

    fp = open(stopWordListFileName, 'r')
    line = fp.readline()
    while line:
        word = line.strip()
        stopWords.append(word)
        line = fp.readline()
    fp.close()
    return stopWords
#end


#start getfeatureVector from tweets
def getFeatureVector(tweet,featureVector,stopWords):
    #split tweet into words
    words = tweet.split()
    for w in words:
        #strip whitespace
        w = w.strip()
        #strip punctuation
        w = w.strip('\'"?,.!')
        #check if the word stats with an alphabet
        val = re.search(r"^[a-zA-Z][a-zA-Z0-9]*$", w)
        #ignore if it is a stop word
        if(w.lower() in stopWords or val is None):
            continue
        else:
            #if(w.lower() not in featureVector):
            featureVector.append(w.lower())
    return featureVector
#end

#start getAllFeatureWords from preprocessed tweets
def getAllFeatureWords(filename,featureVector):
    filename = 'Corpus/processed_'+filename
    stopWords = getStopWordList("Corpus/stopword.txt")
    fp = open(filename,'r')
    line = fp.readline()
    while line:
        getFeatureVector(line,featureVector,stopWords)
        line = fp.readline()
    fp.close()
    return
#end

#start printFeature vector
def getFreq(featureVector):
    worddict={}
    d=enchant.Dict()
    fp = open("Corpus/sentiwords.txt",'r')
    line  = fp.readline()
    featureVector.append(line.strip("\n"))
    while line:
        featureVector.append(line.strip("\n"))
        line = fp.readline()

    fp.close()
    for word in featureVector:
        if(len(word)>=3):
            if(word.endswith("es") and (len(word) > 4) and d.check(word[:-2])):
                if(word[:-2] in worddict):
                    temp = word[:-2]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-2]] = 1
            elif(word.endswith("s") and (len(word) > 4) and d.check(word[:-1])):
                if(word[:-1] in worddict):
                    temp = word[:-1]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-1]] = 1
            elif(word.endswith("ed") and (len(word) > 4) and d.check(word[:-2])):
                if(word[:-2] in worddict):
                    temp = word[:-2]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-2]] = 1
            elif(word.endswith("ing") and (len(word) > 5) and d.check(word[:-3])):
                if(word[:-3] in worddict):
                    temp = word[:-3]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-3]] = 1
            elif(word.endswith("ied") and (len(word) > 5) and d.check(word[:-3])):
                if(word[:-3] in worddict):
                    temp = word[:-3]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-3]] = 1
            elif(word.endswith("est") and (len(word) > 5) and d.check(word[:-3])):
                if(word[:-3] in worddict):
                    temp = word[:-3]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-3]] = 1    
	    elif(word.endswith("ful") and (len(word) > 5) and d.check(word[:-3])):
                if(word[:-3] in worddict):
                    temp = word[:-3]
                    worddict[temp] = worddict.get(temp)+1
                else:
                    worddict[word[:-3]] = 1    
	    else:
                if(word in worddict):
                    worddict[word] = worddict.get(word)+1
                elif((len(word) > 2) and d.check(word)):
                    worddict[word] = 1
    return worddict
#end

#remove words occuring once
def finalVector(worddict):
    finallist = []
    for k,v in worddict.iteritems():
        if(v>1):
            finallist.append(k)

    fp = open("Corpus/featurewords.dump",'w')
    
    for word in finallist:
        fp.write(word)
        fp.write("\n")

    fp.close()
    return finallist

#start extract_features
def extract_features(tweet,featureVector,senti):
    tweet = processTweet(tweet)
    tweet.strip()
    tweet.strip('\'"?,.!')
    words = tweet.split()
    words_up = []
    d=enchant.Dict()
    for word in words:
        word = word.strip()
        word = word.strip('\'"?,.!') 
        if(word.endswith("es") and (len(word) > 4) and d.check(word[:-2])):
            words_up.append(word[:-2])
        elif(word.endswith("s")):
            words_up.append(word[:-1])
        elif(word.endswith("ed") and (len(word) > 4) and d.check(word[:-2])):
            words_up.append(word[:-2])
        elif(word.endswith("ing") and (len(word) > 5) and  d.check(word[:-3])):
            words_up.append(word[:-3])
        elif(word.endswith("ied") and (len(word) > 5) and d.check(word[:-3])):
            words_up.append(word[:-3])
	elif(word.endswith("est") and (len(word) > 5) and d.check(word[:-3])):
            words_up.append(word[:-3])                
	elif(word.endswith("ful") and (len(word) > 5) and d.check(word[:-3])):
            words_up.append(word[:-3])                
	else:
	    if ((len(word) > 2) and d.check(word)):
                words_up.append(word)
    extractf = []
    extractf.append(senti) 
    for w in featureVector:
        if w in words_up:
            extractf.append(1)
        else:
            extractf.append(0)
    return extractf
#end



#start  printing feature vector
def printFeatureVector(allWords):
    featureVector = []
    fp=open("Corpus/processed_pos.txt" ,'r')
    d=enchant.Dict()
    line = fp.readline()
    while line:
        featureVector.append(extract_features(line,allWords, '1 0'))
        line = fp.readline()
    fp.close()
    
    fp=open("Corpus/processed_neg.txt" ,'r')
    line = fp.readline()
    while line:
        featureVector.append(extract_features(line,allWords,'0 1'))
        line = fp.readline()
    fp.close()

    fp=open("Corpus/processed_neu.txt" ,'r')
    line = fp.readline()
    while line:
        featureVector.append(extract_features(line,allWords,'0 0'))
        line = fp.readline()
    fp.close()

    fp=open("Corpus/extracted-features.dump",'w')
    for veclist in featureVector:
        for w in veclist:
            fp.write(str(w))
            fp.write(" ")
        fp.write("\n")
    return
#end

