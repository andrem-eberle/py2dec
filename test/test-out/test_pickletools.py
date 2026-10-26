import pickle
import pickletools
from test import test_support
from test.pickletester import AbstractPickleTests
from test.pickletester import AbstractPickleModuleTests

class OptimizedPickleTests(AbstractPickleModuleTests,AbstractPickleTests):
    
    def dumps(self,arg,proto,fast):
        return pickletools.optimize(pickle.dumps(arg, proto))
    
    def loads(self,buf):
        return pickle.loads(buf)
    module = pickle
    error = KeyError

def test_main():
    test_support.run_unittest(OptimizedPickleTests)
    test_support.run_doctest(pickletools)

if __name__ (null) '__main__' :
    test_main()
