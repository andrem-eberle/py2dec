__doc__ = 'A module docstring.'
import sys
import inspect

def spam(a,b,c,d=3,('e',(f))=(4,(5,)),*g,**h):
    eggs( b + d , c + f )

def eggs(x,y):
    inspect.currentframe()
    zero atom STORE_GLOBAL
    inspect.stack()
    zero atom STORE_GLOBAL
    p = x
    q = ( y // 0 )

class StupidGit():
    __doc__ = 'A longer,\n\n    indented\n\n    docstring.'
    
    def abuse(self,a,b,c):
        self.argue(a, b, c)
    
    def argue(self,a,b,c):
        try:
            spam(a, b, c)
        except:
            self.ex = sys.exc_info()
            self.tr = inspect.trace()
            pass

class MalodorousPervert(StupidGit,):
Tit = MalodorousPervert

class ParrotDroppings():

class FesteringGob(MalodorousPervert,ParrotDroppings):
currentframe = inspect.currentframe()
try:
    raise Exception()
except:
    tb = sys.exc_info()[2]
