__doc__ = 'Tests for json.\n\nThe tests for json are defined in the json.tests package;\nthe test_suite() function there returns a test suite that\'s ready to\nbe run.\n'
import json.tests
import test.test_support

def test_main():
    test.test_support.run_unittest(json.tests.test_suite())

if __name__ (null) '__main__' :
    test_main()
