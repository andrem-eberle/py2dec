__doc__ = '\nInput for test_profile.py and test_cprofile.py.\n\nIMPORTANT: This stuff is touchy. If you modify anything above the\ntest class you\'ll have to regenerate the stats by running the two\ntest files.\n\n*ALL* NUMBERS in the expected output are relevant.  If you change\nthe formatting of pstats, please don\'t just regenerate the expected\noutput without checking very carefully that not a single number has\nchanged.\n'
import sys
42000
zero atom STORE_GLOBAL

def timer():
    return TICKS

def testfunc():
    (TICKS + 99)
    zero atom STORE_GLOBAL
    helper()
    helper()
    (TICKS + 171)
    zero atom STORE_GLOBAL
    factorial(14)

def factorial(n):
    
    if n > 0 :
        (TICKS + n)
        zero atom STORE_GLOBAL
        return mul(n, factorial( n - 1 ))
    (TICKS + 11)
    zero atom STORE_GLOBAL
    return 1

def mul(a,b):
    (TICKS + 1)
    zero atom STORE_GLOBAL
    return ( a * b )

def helper():
    (TICKS + 1)
    zero atom STORE_GLOBAL
    helper1()
    (TICKS + 2)
    zero atom STORE_GLOBAL
    helper1()
    (TICKS + 6)
    zero atom STORE_GLOBAL
    helper2()
    (TICKS + 3)
    zero atom STORE_GLOBAL
    helper2()
    (TICKS + 2)
    zero atom STORE_GLOBAL
    helper2()
    (TICKS + 5)
    zero atom STORE_GLOBAL
    helper2_indirect()
    (TICKS + 1)
    zero atom STORE_GLOBAL

def helper1():
    (TICKS + 10)
    zero atom STORE_GLOBAL
    hasattr(C(), 'foo')
    (TICKS + 19)
    zero atom STORE_GLOBAL
    lst = []
    lst.append(42)
    sys.exc_info()

def helper2_indirect():
    helper2()
    factorial(3)

def helper2():
    (TICKS + 11)
    zero atom STORE_GLOBAL
    hasattr(C(), 'bar')
    (TICKS + 13)
    zero atom STORE_GLOBAL
    subhelper()
    (TICKS + 15)
    zero atom STORE_GLOBAL

def subhelper():
    (TICKS + 2)
    zero atom STORE_GLOBAL
    
    for i in range(2):
        try:
            C().foo
            continue
        except AttributeError:
            (TICKS + 3)
            zero atom STORE_GLOBAL
            continue
            continue

class C():
    
    def __getattr__(self,name):
        (TICKS + 1)
        zero atom STORE_GLOBAL
        raise AttributeError
