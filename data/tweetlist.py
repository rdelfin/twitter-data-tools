import csv
import nltk

def tweetIndexToSent(dictionary, tweets):
    return [[dictionary[word] for word in tweet] for tweet in tweets]

def loadTweetCsv(fileDir):
   tweetFile = open(fileDir, 'r')
   tweetReader = csv.reader(tweetFile, delimiter=',', quotechar='"')
   result = [[int(index) for index in tweet] for tweet in tweetReader]
   tweetFile.close()
   return result

def loadDictionary(fileDir):
    dictionaryFile = open(fileDir, 'r')
    lines = dictionaryFile.readlines();
    dictionaryFile.close()
    return [line.rstrip('\n') for line in lines]

def getTweets(dictionaryFile, tweetFile):
    tweetIdx = loadTweetCsv(tweetFile)
    dictionary = loadDictionary(dictionaryFile)
    return tweetIndexToSent(dictionary, tweetIdx)

def tweetBigramDist(tweets):
    sentenceBigrams = [list(nltk.bigrams(tweet)) for tweet in tweets]
    tweetBigrams = [bigram for sentence in sentenceBigrams for bigram in sentence]
    return nltk.ConditionalFreqDist(tweetBigrams)
