__doc__ = 'Tests for distutils.\n\nThe tests for distutils are defined in the distutils.tests package;\nthe test_suite() function there returns a test suite that\'s ready to\nbe run.\n'
from test import test_support
import distutils.tests

def test_main():
    test_support.run_unittest(distutils.tests.test_suite())
    test_support.reap_children()

if __name__ (null) '__main__' :
    test_main()
