from lib2to3.tests import test_fixers, test_pytree, test_util, test_refactor, test_parser, test_main
import unittest
from test.test_support import run_unittest

def suite():
    tests = unittest.TestSuite()
    loader = unittest.TestLoader()
        
