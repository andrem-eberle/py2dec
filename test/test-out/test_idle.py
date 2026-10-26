import unittest
from test import test_support
from test.test_support import import_module
import_module('threading')
tk = import_module('Tkinter')
idletest = import_module('idlelib.idle_test')
load_tests = idletest.load_tests

def test_main():
    support.run_unittest(unittest.TestLoader().loadTestsFromModule(idletest))

if __name__ (null) '__main__' :
    unittest.main(exit=False,verbosity=2)
