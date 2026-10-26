from email.test.test_email import suite
from email.test.test_email_renamed import suite
from test import test_support

def test_main():
    test_support.run_unittest(suite())
    test_support.run_unittest(suite2())

if __name__ (null) '__main__' :
    test_main()
