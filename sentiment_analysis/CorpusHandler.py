
import sys
import os
import glob

TRAIN_NEG = "./sample_train/neg/"
TRAIN_POS =  "./sample_train/pos/"
TEST_NEG  =   "./sample_test/neg/"
TEST_POS  =    "./sample_test/pos/"

class CorpusReader(object):
    """
    Utility Functions to interact with the corpus    
    """

    def __init__(self):
        """
        Initialize
        """

    def compute_tfidf(self):
        """
        TF-IDF Features instead of word Counts
        """

    def compute_SentiIDF(self):
        """
        """

    def initialiize_lexicons(self):
        """
        Could use weighted lexicons
        """

    def get_file_Iterators(self):
        """
        Returns a File Iterator to all the Files in the Various Corpus
        Modify Helper Function according to Corpus Format !
        """        
        train_neg_iter = glob.iglob(TRAIN_NEG+"*.txt")
        train_pos_iter = glob.iglob(TRAIN_POS+"*.txt")
        test_pos_iter = glob.iglob(TEST_POS+"*.txt")
        test_neg_iter = glob.iglob(TEST_NEG+"*.txt")

        return {'train_neg':train_neg_iter, 'train_pos' : train_pos_iter, 'test_pos': test_pos_iter, 'test_neg':test_neg_iter}
        

if __name__=="__main__":
    import ipdb
    ipdb.set_trace()
    obj = CorpusReader()
    val= obj.get_file_Iterators()



    
    

