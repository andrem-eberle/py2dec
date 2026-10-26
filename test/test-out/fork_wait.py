__doc__ = 'This test case provides support for checking forking and wait behavior.\n\nTo test different wait behavior, override the wait_impl method.\n\nWe want fork1() semantics -- only the forking thread survives in the\nchild after a fork().\n\nOn some systems (e.g. Solaris without posix threads) we find that all\nactive threads survive in the child after a fork(); this is an error.\n\nWhile BeOS doesn\'t officially support fork and native threading in\nthe same application, the present example should work just fine.  DC\n'
import os
import sys
import time
import unittest
support = import test.support.support
threading = support.import_module('threading')
LONGSLEEP = 2
SHORTSLEEP = 0.50000000000000000
NUM_THREADS = 4

class ForkWait(unittest.TestCase,):
    
    def setUp(self):
        self._threading_key = support.threading_setup()
        self.alive = {}
        self.stop = 0
        self.threads = []
        pass
    
    def tearDown(self):
        self.stop = 1
        
        for thread in self.threads:
            thread.join()
            continue
        thread = None
        del self.threads[:]
        self._threading_key
        support.threading_cleanup(*self._threading_key)
    
    def f(self,id):
        
        while not self.stop :
            self.alive[id] = os.getpid()
            try:
                time.sleep(SHORTSLEEP)
                continue
            except IOError:
                continue
                continue
    
    def wait_impl(self,cpid):
        
        for i in range(10):
            spid, status = os.waitpid(cpid, os.WNOHANG)
            
            if spid == cpid :
                break
            time.sleep( 2 * SHORTSLEEP )
            continue
        else:
        self.assertEqual(spid, cpid)
        self.assertEqual(status, 0, 'cause = %d, exit = %d' % ( ( status & 255 ), ( status >> 8 )) )
    
    def test_wait(self):
        
        for i in range(NUM_THREADS):
            thread = threading.Thread(args=(i,),target=self.f)
            thread.start()
            self.threads.append(thread)
            continue
        time.sleep(LONGSLEEP)
        a = self.alive.keys()
        a.sort()
        self.assertEqual(a, range(NUM_THREADS))
        prefork_lives = self.alive.copy()
        
        if sys.platform in ('unixware7',) :
            cpid = os.fork1()
        else:
            cpid = os.fork()
        
        if cpid == 0 :
            time.sleep(LONGSLEEP)
            n = 0
            
            for key in self.alive:
                
                if not self.alive[key] != prefork_lives[key] :
                    continue
                n = (n + 1)
                continue
                continue
            os._exit(n)
        else:
            self.wait_impl(cpid)
