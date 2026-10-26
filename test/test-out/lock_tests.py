__doc__ = '\nVarious tests for synchronization primitives.\n'
import sys
import time
from thread import 'start_new_thread','get_ident'
import threading
import unittest
from test import 'test_support',

def _wait():
    time.sleep(0.01000000000000000)

class Bunch(object,):
    __doc__ = '\n    A bunch of threads.\n    '
    
    def __init__(self,f,n,wait_before_exit=False):
        self.f = f
        self.n = n
        self.started = []
        self.finished = []
        self._can_exit = not wait_before_exit
        
        def task():
            tid = get_ident()
            self.started.append(tid)
            try:
                f()
            finally:
                self.finished.append(tid)
                
                while not self._can_exit :
                _wait()
                continue
        try:
            
            for i in range(n):
                start_new_thread(task, ())
                continue
        except:
            self._can_exit = True
            raise 
    
    def wait_for_started(self):
        
        while len(self.started) < self.n :
            _wait()
            continue
    
    def wait_for_finished(self):
        
        while len(self.finished) < self.n :
            _wait()
            continue
    
    def do_finish(self):
        self._can_exit = True
        pass

class BaseTestCase(unittest.TestCase,):
    
    def setUp(self):
        self._threads = support.threading_setup()
        pass
    
    def tearDown(self):
        self._threads
        support.threading_cleanup(*self._threads)
        support.reap_children()

class BaseLockTests(BaseTestCase,):
    __doc__ = '\n    Tests for both recursive and non-recursive locks.\n    '
    
    def test_constructor(self):
        lock = self.locktype()
        zero atom DELETE_FAST
    
    def test_acquire_destroy(self):
        lock = self.locktype()
        lock.acquire()
        zero atom DELETE_FAST
    
    def test_acquire_release(self):
        lock = self.locktype()
        lock.acquire()
        lock.release()
        zero atom DELETE_FAST
    
    def test_try_acquire(self):
        lock = self.locktype()
        self.assertTrue(lock.acquire(False))
        lock.release()
    
    def test_try_acquire_contended(self):
        lock = self.locktype()
        lock.acquire()
        result = []
        
        def f():
            result.append(lock.acquire(False))
        Bunch(f, 1).wait_for_finished()
        self.assertFalse(result[0])
        lock.release()
    
    def test_acquire_contended(self):
        lock = self.locktype()
        lock.acquire()
        N = 5
        
        def f():
            lock.acquire()
            lock.release()
        b = Bunch(f, N)
        b.wait_for_started()
        _wait()
        self.assertEqual(len(b.finished), 0)
        lock.release()
        b.wait_for_finished()
        self.assertEqual(len(b.finished), N)
    
    def test_with(self):
        lock = self.locktype()
        
        def f():
            lock.acquire()
            lock.release()
        
