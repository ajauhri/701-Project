
import os
import sys
import nltk
from nltk.corpus import stopwords
import cPickle
import re


CONTRACTIONS={"ain't":"ai not", "aren't":"are not",
                                   "isn't":"is not", "wasn't":"was not",
                                   "weren't":"were not", "didn't":"did not",
                                   "doesn't":"does not", "don't":"do not",
                                   "hadn't":"had not", "hasn't":"has not",
                                   "haven't":"have not", "can't":"can not",
                                   "couldn't":"could not", "needn't":"need not",
                                   "shouldn't":"should not", "shan't":"shall not",
                                   "won't":"would not", "wouldn't":"would not",
                                   "i'm":"i am", "you're":"you are",
                                   "he's":"he is", "she's":"she is",
                                   "it's":"it is", "we're":"we are",
                                   "they're":"they are", "i've":"i have",
                                   "you've":"you have", "we've":"we have",
                                   "they've":"they have", "who've":"who have",
                                   "what've":"what have", "when've":"when have",
                                   "where've":"where have", "why've":"why have",
                                   "how've":"how have", "i'd":"i would",
                                   "you'd":"you would", "he'd":"he would",
                                   "she'd":"she would", "we'd":"we would",
                                   "they'd":"they would", "i'll":"i will",
                                   "you'll":"you will", "he'll":"he will",
                                   "she'll":"she will", "we'll":"we will",
                                   "they'll":"they will", "cant":"can not",
                                   "wont":"would not", "dont":"do not",
                                   }


class TextProcess(object):
    """
    Utility methods for Text PreProcessing
    """

    def __init__(self):
        """
        Initialize the Objects
        """
        self.tokenizer = nltk.tokenize.treebank.TreebankWordTokenizer()
        self.contractions_re = re.compile("(%s)" % "|".join(map(re.escape, CONTRACTIONS.keys())))

        tagger_file = open("brill.tagger")
        self.brill_tagger = cPickle.load(tagger_file)

        self.stop_words_dict = {}
        true_list = [True for each in range(len(stopwords.words("english")))]

        self.negation_dict = {'not':True, 'no':True, 'never':True}

        self.stop_words_dict = dict(zip(stopwords.words("english"),true_list))
        self.sentence_splitter = nltk.data.load('tokenizers/punkt/english.pickle')

    def _check_stop_word(self,word):

        if self.stop_words_dict.get(word.lower()):
            if not self.negation_dict.get(word.lower()):
                return True               
            else:
                return False        

    def remove_stop_words(self,tokens):        
        """
        Filter Stop Words
        """
        word_list =  [word for word in tokens if not self._check_stop_word(word)]
        return word_list

    def tokenize(self,sentence):
        """
        Tokenize the sentence
        """
        return self.tokenizer.tokenize(sentence)

    def split_sentence(self,sentence):
        """
        Takes text as input and return a list of sentences
        """
        sents = self.sentence_splitter.tokenize(sentence)      
        return sents        

    def pos_tag(self,sentence):
        """
        Returns Word and Pos Tag as a tuple (word,POS)
        POS_Tags are normalized - Eg [VB,VBZ] 
        """
        tagged = self.brill_tagger.tag(sentence.split())
        tagged_sentence = " ".join([nltk.tag.tuple2str(tok) for tok in tagged])
        print tagged_sentence

        tag_list = [(each.split("/")[0],each.split("/")[1]) for each in tagged_sentence.split()]
        return tag_list


    def negation_check(self,sentence):
        """
        Returns word and negation flag
        """

    def stemming(self,sentence):
        """
        Returns a stemmed Version of the Word List
        """

    def contractions_remove(self,sentence):
        """
        Replaces some Contractions using a contraction Dictionary
        Eg: is'nt = is not
        """
        sentence = self.contractions_re.sub(lambda mo: CONTRACTIONS[mo.string[mo.start():mo.end()]], sentence)
        return sentence

if __name__=="__main__":
    obj = TextProcess()
    









        
        
    
