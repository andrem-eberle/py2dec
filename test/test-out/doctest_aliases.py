
class TwoNames():
    __doc__ = 'f() and g() are two names for the same method'
    
    def f(self):
        return 'f'
    g = f
