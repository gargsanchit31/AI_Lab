from optparse import OptionParser
from processTweet import *
import os
def clean():
    filelist = [ f for f in os.listdir("Corpus") if f.startswith("processed_") ]
    for f in filelist:
        os.remove("Corpus/"+f)

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-a","--all", action="store_true", dest="all", default=None, help="Run the entire script")
    parser.add_option("-p", "--preprocess", action="store_true", dest="preprocess", default=None, help="Process most recent data")
    parser.add_option("-e", "--extract", action="store_true", dest="extractfeature", default=None, help="Extract Feature Vector")
    parser.add_option("-d", "--clean", action="store_true", dest="clean", default=None, help="Clean previous processed files")
    (options, args) = parser.parse_args()

    if options.all:
        options.preprocess = options.combine = options.extractfeature = True

    if options.preprocess:
        print "Preprocessing sample tweets" 
        clean()
        print "Processing negative tweets..."
        processFile("neg.txt")
        print "Processing positive tweets..."
        processFile("pos.txt")
        print "Processing objective tweets..."
        processFile("neu.txt")
    
    if options.extractfeature:
        print "Extracting Feature Vector"
        featureVector = []
        print "Extracting positive features"
        getAllFeatureWords("pos.txt",featureVector)
        print "Extracting negative features" 
        getAllFeatureWords("neg.txt",featureVector)
        print "Extracting neutral features"
        getAllFeatureWords("neu.txt",featureVector)
        print "Finding the word frequency"
        worddict = {}
        worddict = getFreq(featureVector)
        print "Processed word universe according to frequency, now writing to file"
        finallist = []
        finallist = finalVector(worddict)
        print (len(finallist))
        print "Wrote word universe, now extracting feature vector"
        printFeatureVector(finallist)
        print "Done extracting features and writing to file"

        while(True):
            newtweet = raw_input("Please enter tweet : ")
            features = extract_features(newtweet, finallist, '')
            fp = open("in.txt", 'w')
            for w in features:
                fp.write(str(w))
                fp.write(" ")
            fp.write("\n")
            fp.close()
        
    if options.clean:
        print "Cleaning crap..."
        clean()
        print "....Done cleaning"



