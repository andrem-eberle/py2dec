import os
import unittest
from test import test_support
test_support.import_module('_tkinter')
test_support.requires('gui')
this_dir = os.path.dirname(os.path.abspath(__file__))
lib_tk_test = os.path.abspath(os.path.join(this_dir, os.path.pardir, 'lib-tk', 'test'))
with test_support.DirsOnSysPath(lib_tk_test):
    import runtktests
import Tkinter
import ttk
from _tkinter import TclError
root = None
try:
    root = tkinter.Tk()
    button = ttk.Button(root)
    button.destroy()
    zero atom DELETE_NAME
except TclError:
        msg = 
        'ttk not available: %s'
        msg
        raise unittest.SkipTest(zero atom BINARY_MODULO)
finally:
    
    if root is not None :
        root.destroy()
zero atom DELETE_NAME

def test_main():
    with test_support.DirsOnSysPath(lib_tk_test):
        test_support.run_unittest
        zero atom CALL_FUNCTION_VAR
