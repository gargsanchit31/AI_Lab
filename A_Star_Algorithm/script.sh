python test.py twitter_positive tempfile1
python test.py twitter_objective tempfile2
python test.py twitter_negative tempfile3
cat tempfile* > feature
python nlkt_TEST.py feature > deleteme
wc -w deletemetoo
