read = "combinedCorpusFinal"
fr = open(read, 'r')
fpos = open('pos.txt', 'w')
fneg = open('neg.txt', 'w')
fneu = open('neu.txt', 'w')

line = fr.readline()
 
while line:
    print("in")
   # split_tweet = line.split('\t')
    bareline = line.rsplit(' ',1)[0]
    category = line.rsplit(' ',1)[1]
    if "pos" in category:
        writer = fpos
    elif "neg" in category:
        writer = fneg
    elif "neu" in category:
        writer = fneu
    #fw.write(split_tweet[0])
    #fw.write('\t')
    writer.write(bareline)
    writer.write('\n')
    line = fr.readline()


fr.close()
fneg.close()
fpos.close()
fneu.close()
