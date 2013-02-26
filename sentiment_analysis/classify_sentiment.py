
# Sentiment Analysis code

import sys
import nltk
import nltk.classify.util
from nltk.classify import NaiveBayesClassifier
from nltk import MaxentClassifier
from text_utilities import *
from CorpusHandler import *
from collections import Counter
import os
import ipdb

class SentimentClassifier(object):
    """
    Class Methods For Sentiment analysis
    """   
    
    def __init__(self,model_parameters):
        """
        Initialize the basic parameters for the Model !
        """        
        self.counter = Counter()
        self.corpus = CorpusReader()
        self.nlp = TextProcess()
        self.train_features = []
        self.classifier = None
        self.test_model = []
        self.model_parameters = {}

    def get_word_count_feature_vector(self,word_list):
        """
        Returns Word Frequency Counts
        """
        freq_dict = Counter(word_list)
        return dict(freq_dict)

    def TrainModel(self):
        """
        Train the model for the required Classifier
        """
        # Initialize the Needed Classifier
        self.classifier = NaiveBayesClassifier.train(self.train_features)
        #self.classifier = MaxentClassifier.train(self.train_features,algorithm="iis")

    def TestModel(self):
        """
        Classify and return the Labels
        """
        labels= []
        actual_labels = []
        correct =0
        for each_test in self.test_model:
            label = self.classifier.classify(each_test[0])
            labels.append(label)
            """
            actual_labels = each_test[1]           
            if each_test[1]==label:
                correct=correct + 1

        total = len(actual_labels)
        print correct,total        
        """

        self.TestModelAccuracy()
        return labels                       
            

    def TestModelAccuracy(self):
        """
        Test the Model for the required Parameters
        """
        print 'accuracy:', nltk.classify.util.accuracy(self.classifier, self.test_model)

    def process_corpus_training(self,corpus,polarity,test=False):
        """
        Pre-Process Document with all NLP tasks
        """        
        for cnt,each_doc in enumerate(corpus):
            f = open(each_doc,"rb")
            text = f.read()

            # Sentence Splitter 
            token_list = []
            sentences = self.nlp.split_sentence(text)

            for each_sent in sentences:
                # Stop Word Removal
                each_sent = self.nlp.contractions_remove(each_sent)
                tokens = self.nlp.tokenize(each_sent)
                tokens_filt = self.nlp.remove_stop_words(tokens)
                
                token_list.extend(tokens_filt)              
                
            freq_dist = self.get_word_count_feature_vector(token_list)

            if test is False:
                self.train_features.append((freq_dist,polarity))                     
            else:
                self.test_model.append((freq_dist,polarity))                 
        

    def main(self):
        """
        Perform all the Preprocessing Operations prior to Training
        """

        # Process Training Documents
        corpus_dict = self.corpus.get_file_Iterators()
        train_neg_files= corpus_dict['train_neg']
        train_pos_files = corpus_dict['train_pos']

        print "Processing Training Corpus"
        # Build the Model
        self.process_corpus_training(train_neg_files,"neg",False)
        self.process_corpus_training(train_pos_files,"pos",False)

        # Train The Model
        self.TrainModel()
        
        # Perform Testing
        test_neg_files= corpus_dict['test_neg']
        test_pos_files = corpus_dict['test_pos']

        print "Processing Testing Corpus"
        # Testing Feature Vector
        
        self.process_corpus_training(test_neg_files,"neg",True)
        self.process_corpus_training(test_pos_files,"pos",True)

        # Test the Classifier
        self.TestModel()
        
if __name__=="__main__":
    classifier = SentimentClassifier({})
    classifier.main()



            
            


        

        

        
        
        
        

        
        

        
        

        

        
        




        

        

        
        
        





        

    
    
