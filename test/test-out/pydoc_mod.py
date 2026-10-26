__doc__ = 'This is a test module for test_pydoc'
__author__ = 'Benjamin Peterson'
__credits__ = 'Nobody'
__version__ = '1.2.3.4'

class A():
    __doc__ = 'Hello and goodbye'
    
    def __init__():
        pass

class B(object,):
    NO_MEANING = 'eggs'

class C(object,):
    
    def say_no(self):
        return 'no'
    
    def get_answer(self):
        return self.say_no()
    
    def is_it_true(self):
        return self.get_answer()

def doc_func():
    pass

def nodoc_func():
    pass
