import unittest
import pickle
import cPickle
import StringIO
import cStringIO
import pickletools
import copy_reg
import sys
from test import 'test_support',
from test.test_support import 'TestFailed','verbose','have_unicode','TESTFN'
try:
    from test.test_support import '_2G','_1M','precisionbigmemtest'
except ImportError:
    _2G = 0
    _1M = 0
    
    def precisionbigmemtest(*args,**kwargs):
        return lambda self :None

if not pickle.HIGHEST_PROTOCOL == cPickle.HIGHEST_PROTOCOL or not pickle.HIGHEST_PROTOCOL == cPickle.HIGHEST_PROTOCOL or not cPickle.HIGHEST_PROTOCOL == 2 :
    raise AssertionError
protocols = range( pickle.HIGHEST_PROTOCOL + 1 )

def run_with_locale(catstr,*locales):
    
    def decorator(func):
        
        def inner(*args,**kwds):
            try:
                import locale
                category = getattr(locale, catstr)
                orig_locale = locale.setlocale(category)
            except AttributeError:
                raise 
            except:
                locale = None
                orig_locale = None
                
                for loc in locales:
                    try:
                        locale.setlocale(category, loc)
                        break
                        continue
                    except:
                        continue
                        continue
            try:
                return func(*args,**kwds)
            finally:
                
                if locale and orig_locale :
                    locale.setlocale(category, orig_locale)
        inner.func_name = func.func_name
        inner.__doc__ = func.__doc__
        return inner
    return decorator

def no_tracing(func):
    
    if not hasattr(sys, 'gettrace') :
        return func
    
    def wrapper(*args,**kwargs):
        original_trace = sys.gettrace()
        try:
            sys.settrace(None)
            return func(*args,**kwargs)
        finally:
            sys.settrace(original_trace)
    wrapper.__name__ = func.__name__
    return wrapper

def opcode_in_pickle(code,pickle):
    
    for op,dummy,dummy in pickletools.genops(pickle):
        
        if not op.code == code :
            continue
        return True
        continue
    return False

def count_opcode(code,pickle):
    n = 0
    
    for op,dummy,dummy in pickletools.genops(pickle):
        
        if not op.code == code :
            continue
        n = (n + 1)
        continue
        continue
    return n

class UnseekableIO(StringIO.StringIO,):
    
    def peek(self,*args):
        raise NotImplementedError
    
    def seek(self,*args):
        raise NotImplementedError
    
    def tell(self):
        raise NotImplementedError

class ExtensionSaver():
    
    def __init__(self,code):
        self.code = code
        
        if code in copy_reg._inverted_registry :
            self.pair = copy_reg._inverted_registry[code]
            copy_reg.remove_extension(self.pair[0], self.pair[1], code)
        else:
            self.pair = None
    
    def restore(self):
        code = self.code
        curpair = copy_reg._inverted_registry.get(code)
        
        if curpair is not None :
            copy_reg.remove_extension(curpair[0], curpair[1], code)
        pair = self.pair
        
        if pair is not None :
            copy_reg.add_extension(pair[0], pair[1], code)

class C():
    
    def __cmp__(self,other):
        return cmp(self.__dict__, other.__dict__)

class D(C,):
    
    def __init__(self,arg):
        pass

class E(C,):
    
    def __getinitargs__(self):
        return ()

class H(object,):

class MyErr(Exception,):
    
    def __init__(self):
        pass

class I():
    
    def __init__(self,*args,**kwargs):
        raise MyErr()
    
    def __getinitargs__(self):
        return ()

class K(object,):
    
    def __init__(self,value):
        self.value = value
        pass
    
    def __reduce__(self):
        return (K,(self.value,))
__main__ = sys.modules['__main__']
__main__.C = C
C.__module__ = '__main__'
__main__.D = D
D.__module__ = '__main__'
__main__.E = E
E.__module__ = '__main__'
__main__.H = H
H.__module__ = '__main__'
__main__.I = I
I.__module__ = '__main__'
__main__.K = K
K.__module__ = '__main__'

class myint(int,):
    
    def __init__(self,x):
        self.str = str(x)
        pass

class initarg(C,):
    
    def __init__(self,a,b):
        self.a = a
        self.b = b
        pass
    
    def __getinitargs__(self):
        return (self.a,self.b)

class metaclass(type,):

class use_metaclass(object,):
    __metaclass__ = metaclass

class pickling_metaclass(type,):
    
    def __eq__(self,other):
            type(self) == type(other) and type(self) == type(other) 
    
    def __reduce__(self):
        return (create_dynamic_class,self.reduce_args)
    __hash__ = None

def create_dynamic_class(name,bases):
    result = pickling_metaclass(name, bases, dict())
    result.reduce_args = (name,bases)
    return result
DATA0 = ( ( ( ( '(lp1\nI0\naL1L\naF2\nac__builtin__\ncomplex\np2\n' + '(F3\nF0\ntRp3\naI1\naI-1\naI255\naI-255\naI-256\naI65535\naI-65535\naI-65536\naI2147483647\naI-2147483647\naI-2147483648\na' ) + '(S\'abc\'\np4\ng4\n' ) + '(i__main__\nC\np5\n' ) + '(dp6\nS\'foo\'\np7\nI1\nsS\'bar\'\np8\nI2\nsbg5\ntp9\nag9\naI5\na.\n' )
DATA0_DIS = '    0: (    MARK\n    1: l        LIST       (MARK at 0)\n    2: p    PUT        1\n    5: I    INT        0\n    8: a    APPEND\n    9: L    LONG       1L\n   13: a    APPEND\n   14: F    FLOAT      2.0\n   17: a    APPEND\n   18: c    GLOBAL     \'__builtin__ complex\'\n   39: p    PUT        2\n   42: (    MARK\n   43: F        FLOAT      3.0\n   46: F        FLOAT      0.0\n   49: t        TUPLE      (MARK at 42)\n   50: R    REDUCE\n   51: p    PUT        3\n   54: a    APPEND\n   55: I    INT        1\n   58: a    APPEND\n   59: I    INT        -1\n   63: a    APPEND\n   64: I    INT        255\n   69: a    APPEND\n   70: I    INT        -255\n   76: a    APPEND\n   77: I    INT        -256\n   83: a    APPEND\n   84: I    INT        65535\n   91: a    APPEND\n   92: I    INT        -65535\n  100: a    APPEND\n  101: I    INT        -65536\n  109: a    APPEND\n  110: I    INT        2147483647\n  122: a    APPEND\n  123: I    INT        -2147483647\n  136: a    APPEND\n  137: I    INT        -2147483648\n  150: a    APPEND\n  151: (    MARK\n  152: S        STRING     \'abc\'\n  159: p        PUT        4\n  162: g        GET        4\n  165: (        MARK\n  166: i            INST       \'__main__ C\' (MARK at 165)\n  178: p        PUT        5\n  181: (        MARK\n  182: d            DICT       (MARK at 181)\n  183: p        PUT        6\n  186: S        STRING     \'foo\'\n  193: p        PUT        7\n  196: I        INT        1\n  199: s        SETITEM\n  200: S        STRING     \'bar\'\n  207: p        PUT        8\n  210: I        INT        2\n  213: s        SETITEM\n  214: b        BUILD\n  215: g        GET        5\n  218: t        TUPLE      (MARK at 151)\n  219: p    PUT        9\n  222: a    APPEND\n  223: g    GET        9\n  226: a    APPEND\n  227: I    INT        5\n  230: a    APPEND\n  231: .    STOP\nhighest protocol among opcodes = 0\n'
DATA1 = ']q\x01(K'
DATA1_DIS = '    0: ]    EMPTY_LIST\n    1: q    BINPUT     1\n    3: (    MARK\n    4: K        BININT1    0\n    6: L        LONG       1L\n   10: G        BINFLOAT   2.0\n   19: c        GLOBAL     \'__builtin__ complex\'\n   40: q        BINPUT     2\n   42: (        MARK\n   43: G            BINFLOAT   3.0\n   52: G            BINFLOAT   0.0\n   61: t            TUPLE      (MARK at 42)\n   62: R        REDUCE\n   63: q        BINPUT     3\n   65: K        BININT1    1\n   67: J        BININT     -1\n   72: K        BININT1    255\n   74: J        BININT     -255\n   79: J        BININT     -256\n   84: M        BININT2    65535\n   87: J        BININT     -65535\n   92: J        BININT     -65536\n   97: J        BININT     2147483647\n  102: J        BININT     -2147483647\n  107: J        BININT     -2147483648\n  112: (        MARK\n  113: U            SHORT_BINSTRING \'abc\'\n  118: q            BINPUT     4\n  120: h            BINGET     4\n  122: (            MARK\n  123: c                GLOBAL     \'__main__ C\'\n  135: q                BINPUT     5\n  137: o                OBJ        (MARK at 122)\n  138: q            BINPUT     6\n  140: }            EMPTY_DICT\n  141: q            BINPUT     7\n  143: (            MARK\n  144: U                SHORT_BINSTRING \'foo\'\n  149: q                BINPUT     8\n  151: K                BININT1    1\n  153: U                SHORT_BINSTRING \'bar\'\n  158: q                BINPUT     9\n  160: K                BININT1    2\n  162: u                SETITEMS   (MARK at 143)\n  163: b            BUILD\n  164: h            BINGET     6\n  166: t            TUPLE      (MARK at 112)\n  167: q        BINPUT     10\n  169: h        BINGET     10\n  171: K        BININT1    5\n  173: e        APPENDS    (MARK at 3)\n  174: .    STOP\nhighest protocol among opcodes = 1\n'
DATA2 = '\xffffff80\x02]q\x01(K'
DATA2_DIS = '    0: \xffffff80 PROTO      2\n    2: ]    EMPTY_LIST\n    3: q    BINPUT     1\n    5: (    MARK\n    6: K        BININT1    0\n    8: \xffffff8a     LONG1      1L\n   11: G        BINFLOAT   2.0\n   20: c        GLOBAL     \'__builtin__ complex\'\n   41: q        BINPUT     2\n   43: G        BINFLOAT   3.0\n   52: G        BINFLOAT   0.0\n   61: \xffffff86     TUPLE2\n   62: R        REDUCE\n   63: q        BINPUT     3\n   65: K        BININT1    1\n   67: J        BININT     -1\n   72: K        BININT1    255\n   74: J        BININT     -255\n   79: J        BININT     -256\n   84: M        BININT2    65535\n   87: J        BININT     -65535\n   92: J        BININT     -65536\n   97: J        BININT     2147483647\n  102: J        BININT     -2147483647\n  107: J        BININT     -2147483648\n  112: (        MARK\n  113: U            SHORT_BINSTRING \'abc\'\n  118: q            BINPUT     4\n  120: h            BINGET     4\n  122: (            MARK\n  123: c                GLOBAL     \'__main__ C\'\n  135: q                BINPUT     5\n  137: o                OBJ        (MARK at 122)\n  138: q            BINPUT     6\n  140: }            EMPTY_DICT\n  141: q            BINPUT     7\n  143: (            MARK\n  144: U                SHORT_BINSTRING \'foo\'\n  149: q                BINPUT     8\n  151: K                BININT1    1\n  153: U                SHORT_BINSTRING \'bar\'\n  158: q                BINPUT     9\n  160: K                BININT1    2\n  162: u                SETITEMS   (MARK at 143)\n  163: b            BUILD\n  164: h            BINGET     6\n  166: t            TUPLE      (MARK at 112)\n  167: q        BINPUT     10\n  169: h        BINGET     10\n  171: K        BININT1    5\n  173: e        APPENDS    (MARK at 5)\n  174: .    STOP\nhighest protocol among opcodes = 2\n'

def create_data():
    c = C()
    c.foo = 1
    c.bar = 2
    x = [0,1,2.00000000000000000,3.00000000000000000+0.00000000000000000j]
    uint1max = 255
    uint2max = 65535
    int4max = 2147483647
    x.extend([1,-1,uint1max,-uint1max, ( -uint1max - 1 ),uint2max,-uint2max, ( -uint2max - 1 ),int4max,-int4max, ( -int4max - 1 )])
    y = ('abc','abc',c,c)
    x.append(y)
    x.append(y)
    x.append(5)
    return x

class AbstractUnpickleTests(unittest.TestCase,):
    _testdata = create_data()
    
    def assert_is_copy(self,obj,objcopy,msg=None):
        
        if msg is None :
            msg = '{!r} is not a copy of {!r}'.format(obj, objcopy)
        self.assertEqual(obj, objcopy,msg=msg)
        self.assertIs(type(obj), type(objcopy),msg=msg)
        
        if hasattr(obj, '__dict__') :
            self.assertDictEqual(obj.__dict__, objcopy.__dict__,msg=msg)
            self.assertIsNot(obj.__dict__, objcopy.__dict__,msg=msg)
        
        if hasattr(obj, '__slots__') :
            self.assertListEqual(obj.__slots__, objcopy.__slots__,msg=msg)
            
            for slot in obj.__slots__:
                self.assertEqual(hasattr(obj, slot), hasattr(objcopy, slot),msg=msg)
                self.assertEqual(getattr(obj, slot, None), getattr(objcopy, slot, None),msg=msg)
                continue
    
    def check_unpickling_error(self,errors,data):
        try:
            self.loads(data)
        except:
            
            if support.verbose > 1 :
                exc_type, exc, tb = sys.exc_info()
                print( ( '%-32r - %s: %s' % (data,exc_type.__name__,exc) ))
            raise 
        except errors:
            pass
        try:
            exc_name = errors.__name__
        except AttributeError:
            exc_name = str(errors)
        raise self.failureException( '%s not raised' % exc_name )
    
    def test_load_from_canned_string(self):
        expected = self._testdata
        
        for canned in (DATA0,DATA1,DATA2):
            got = self.loads(canned)
            self.assert_is_copy(expected, got)
            continue
    
    def test_garyp(self):
        self.check_unpickling_error(self.error, 'garyp')
    
    def test_maxint64(self):
        maxint64 = 9223372036854775807
        data = ( ( 'I' + str(maxint64) ) + '\n.' )
        got = self.loads(data)
        self.assertEqual(got, maxint64)
        data = ( ( 'I' + str(maxint64) ) + 'JUNK\n.' )
        self.check_unpickling_error(ValueError, data)
    
    def test_insecure_strings(self):
        insecure = ['abc','2 + 2','\'abc','\'abc"','\'abc\'   ?','\'\\\'','\'','"','\' ','" ','\'"','"\'',' \'\'',' ""',' ']
        
        for s in insecure:
            buf = ( ( 'S' + s ) + '\n.' )
            self.check_unpickling_error(ValueError, buf)
            continue
    
    def test_correctly_quoted_string(self):
        goodpickles = [('S\'\'\n.',''),('S""\n.',''),('S"\\n"\n.','\n'),('S\'\\n\'\n.','\n')]
        
        for p,expected in goodpickles:
            self.assertEqual(self.loads(p), expected)
            continue
    
    def test_load_classic_instance(self):
        
        for X,args in [(C,()),(D,('x',)),(E,())]:
            xname = X.__name__.encode('ascii')
            pickle0 = '(i__main__\nX\np0\n(dp1\nb.'.replace('X', xname)
            self.assert_is_copy(X(*args), self.loads(pickle0))
            pickle1 = '(c__main__\nX\nq'.replace('X', xname)
            self.assert_is_copy(X(*args), self.loads(pickle1))
            pickle2 = '\xffffff80\x02(c__main__\nX\nq'.replace('X', xname)
            self.assert_is_copy(X(*args), self.loads(pickle2))
            continue
    
    def test_load_classic_instance_error(self):
        pickle0 = '(i__main__\nI\n(db.'
        self.assertRaises(MyErr, self.loads, pickle0)
        pickle1 = '(c__main__\nI\no}b.'
        self.assertRaises(MyErr, self.loads, pickle1)
    
    def test_load_str(self):
        self.assertEqual(self.loads('S\'a\\x00\\xa0\'\n.'), 'a')
        self.assertEqual(self.loads('U\x03a'), 'a')
        self.assertEqual(self.loads('\xffffff80\x02U\x03a'), 'a')
    
    def test_load_unicode(self):
        self.assertEqual(self.loads('V\\u03c0\n.'), u'\\u03C0')
        self.assertEqual(self.loads('X\x02'), u'\\u03C0')
        self.assertEqual(self.loads('\xffffff80\x02X\x02'), u'\\u03C0')
    
    def test_constants(self):
        self.assertIsNone(self.loads('N.'))
        self.assertIs(self.loads('\xffffff88.'), True)
        self.assertIs(self.loads('\xffffff89.'), False)
        self.assertIs(self.loads('I01\n.'), True)
        self.assertIs(self.loads('I00\n.'), False)
    
    def test_misc_get(self):
        self.check_unpickling_error(self.error, 'g0\np0\n')
        self.check_unpickling_error(self.error, 'h')
    
    def test_get(self):
        pickled = '((lp100000\ng100000\nt.'
        unpickled = self.loads(pickled)
        self.assertEqual(unpickled, ([],) * 2 )
        self.assertIs(unpickled[0], unpickled[1])
    
    def test_binget(self):
        pickled = '(]q\xffffffffh\xfffffffft.'
        unpickled = self.loads(pickled)
        self.assertEqual(unpickled, ([],) * 2 )
        self.assertIs(unpickled[0], unpickled[1])
    
    def test_long_binget(self):
        pickled = '(]r'
        unpickled = self.loads(pickled)
        self.assertEqual(unpickled, ([],) * 2 )
        self.assertIs(unpickled[0], unpickled[1])
    
    def test_dup(self):
        pickled = '((l2t.'
        unpickled = self.loads(pickled)
        self.assertEqual(unpickled, ([],) * 2 )
        self.assertIs(unpickled[0], unpickled[1])
    
    def test_bad_stack(self):
        badpickles = ['.','0','1','2','R',')R','a','Na','b','Nb','d','e','i__builtin__\nlist\n','l','o','(o','p1\n','q','r','s','Ns','NNs','t','u','}(Nu','\xffffff81',')\xffffff81','\xffffff85','\xffffff86','N\xffffff86','\xffffff87','N\xffffff87','NN\xffffff87']
        
        for p in badpickles:
            self.check_unpickling_error(self.bad_stack_errors, p)
            continue
    
    def test_bad_mark(self):
        badpickles = ['N(2','c__builtin__\nlist\n)(R','c__builtin__\nlist\n()R',']N(a','c__builtin__\nValueError\n)R}(b','c__builtin__\nValueError\n)R(}b','(Nd','N(p1\n','N(q','N(r','}NN(s','}N(Ns','}(NNs','}((u','c__builtin__\nlist\n)(\xffffff81','c__builtin__\nlist\n()\xffffff81','N(\xffffff85','NN(\xffffff86','N(N\xffffff86','NNN(\xffffff87','NN(N\xffffff87','N(NN\xffffff87']
        
        for p in badpickles:
            self.check_unpickling_error(self.bad_mark_errors, p)
            continue
    
    def test_truncated_data(self):
        self.check_unpickling_error(EOFError, '')
        self.check_unpickling_error(EOFError, 'N')
        badpickles = ['F','F0.0','F0.00','G','G','I','I0','J','J','K','L','L0','L10','L0L','L10L','M','M','S','S\'abc\'','T','T\x03','T\x03','T\x03','U','U\x03','U\x03ab','V','Vabc','X','X\x03','X\x03','X\x03','(c','(c__builtin__','(c__builtin__\n','(c__builtin__\nlist','Ng','Ng0','(i','(i__builtin__','(i__builtin__\n','(i__builtin__\nlist','Nh','Nj','Nj','Np','Np0','Nq','Nr','Nr','\xffffff80','\xffffff82','\xffffff83','\xffffff84\x01','\xffffff84','\xffffff84\x01','\xffffff8a','\xffffff8b','\xffffff8b']
        
        for p in badpickles:
            self.check_unpickling_error(self.truncated_errors, p)
            continue

class AbstractPickleTests(unittest.TestCase,):
    _testdata = AbstractUnpickleTests._testdata
    
    def setUp(self):
        pass
    
    def test_misc(self):
        
        for proto in protocols:
            x = myint(4)
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            x = (1,())
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            x = initarg(1, x)
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            continue
    
    def test_roundtrip_equality(self):
        expected = self._testdata
        
        for proto in protocols:
            s = self.dumps(expected, proto)
            got = self.loads(s)
            self.assertEqual(expected, got)
            continue
    
    def dont_test_disassembly(self):
        from pickletools import 'dis',
        
        for proto,expected in ((0,DATA0_DIS),(1,DATA1_DIS)):
            s = self.dumps(self._testdata, proto)
            filelike = cStringIO.StringIO()
            dis(s,out=filelike)
            got = filelike.getvalue()
            self.assertEqual(expected, got)
            continue
    
    def test_recursive_list(self):
        l = []
        l.append(l)
        
        for proto in protocols:
            s = self.dumps(l, proto)
            x = self.loads(s)
            self.assertIsInstance(x, list)
            self.assertEqual(len(x), 1)
            self.assertIs(x[0], x)
            continue
    
    def test_recursive_tuple_and_list(self):
        t = ([],)
        t[0].append(t)
        
        for proto in protocols:
            s = self.dumps(t, proto)
            x = self.loads(s)
            self.assertIsInstance(x, tuple)
            self.assertEqual(len(x), 1)
            self.assertIsInstance(x[0], list)
            self.assertEqual(len(x[0]), 1)
            self.assertIs(x[0][0], x)
            continue
    
    def test_recursive_dict(self):
        d = {}
        d[1] = d
        
        for proto in protocols:
            s = self.dumps(d, proto)
            x = self.loads(s)
            self.assertIsInstance(x, dict)
            self.assertEqual(x.keys(), [1])
            self.assertIs(x[1], x)
            continue
    
    def test_recursive_dict_key(self):
        d = {}
        k = K(d)
        d[k] = 1
        
        for proto in protocols:
            s = self.dumps(d, proto)
            x = self.loads(s)
            self.assertIsInstance(x, dict)
            self.assertEqual(len(x.keys()), 1)
            self.assertIsInstance(x.keys()[0], K)
            self.assertIs(x.keys()[0].value, x)
            continue
    
    def test_recursive_list_subclass(self):
        y = MyList()
        y.append(y)
        s = self.dumps(y, 2)
        x = self.loads(s)
        self.assertIsInstance(x, MyList)
        self.assertEqual(len(x), 1)
        self.assertIs(x[0], x)
    
    def test_recursive_dict_subclass(self):
        d = MyDict()
        d[1] = d
        s = self.dumps(d, 2)
        x = self.loads(s)
        self.assertIsInstance(x, MyDict)
        self.assertEqual(x.keys(), [1])
        self.assertIs(x[1], x)
    
    def test_recursive_dict_subclass_key(self):
        d = MyDict()
        k = K(d)
        d[k] = 1
        s = self.dumps(d, 2)
        x = self.loads(s)
        self.assertIsInstance(x, MyDict)
        self.assertEqual(len(x.keys()), 1)
        self.assertIsInstance(x.keys()[0], K)
        self.assertIs(x.keys()[0].value, x)
    
    def test_recursive_inst(self):
        i = C()
        i.attr = i
        
        for proto in protocols:
            s = self.dumps(i, proto)
            x = self.loads(s)
            self.assertIsInstance(x, C)
            self.assertEqual(dir(x), dir(i))
            self.assertIs(x.attr, x)
            continue
    
    def test_recursive_multi(self):
        l = []
        d = {1:l}
        i = C()
        i.attr = d
        l.append(i)
        
        for proto in protocols:
            s = self.dumps(l, proto)
            x = self.loads(s)
            self.assertIsInstance(x, list)
            self.assertEqual(len(x), 1)
            self.assertEqual(dir(x[0]), dir(i))
            self.assertEqual(x[0].attr.keys(), [1])
            self.assertTrue(x[0].attr[1] is x)
            continue
    
    def check_recursive_collection_and_inst(self,factory):
        h = H()
        y = factory([h])
        h.attr = y
        
        for proto in protocols:
            s = self.dumps(y, proto)
            x = self.loads(s)
            self.assertIsInstance(x, type(y))
            self.assertEqual(len(x), 1)
            self.assertIsInstance(list(x)[0], H)
            self.assertIs(list(x)[0].attr, x)
            continue
    
    def test_recursive_list_and_inst(self):
        self.check_recursive_collection_and_inst(list)
    
    def test_recursive_tuple_and_inst(self):
        self.check_recursive_collection_and_inst(tuple)
    
    def test_recursive_dict_and_inst(self):
        self.check_recursive_collection_and_inst(dict.fromkeys)
    
    def test_recursive_set_and_inst(self):
        self.check_recursive_collection_and_inst(set)
    
    def test_recursive_frozenset_and_inst(self):
        self.check_recursive_collection_and_inst(frozenset)
    
    def test_recursive_list_subclass_and_inst(self):
        self.check_recursive_collection_and_inst(MyList)
    
    def test_recursive_tuple_subclass_and_inst(self):
        self.check_recursive_collection_and_inst(MyTuple)
    
    def test_recursive_dict_subclass_and_inst(self):
        self.check_recursive_collection_and_inst(MyDict.fromkeys)
    
    if have_unicode :
        
        def test_unicode(self):
            endcases = [u'',u'<\\u>',u'<\\\\u1234>',u'<\n>',u'<\\>',u'<\\\\U00012345>',u'<\\uDC80>']
            
            for proto in protocols:
                
                for u in endcases:
                    p = self.dumps(u, proto)
                    u2 = self.loads(p)
                    self.assertEqual(u2, u)
                    continue
        
        def test_unicode_high_plane(self):
            t = u'\\U00012345'
            
            for proto in protocols:
                p = self.dumps(t, proto)
                t2 = self.loads(p)
                self.assertEqual(t2, t)
                continue
    
    def test_ints(self):
        import sys
        
        for proto in protocols:
            n = sys.maxint
            
            while n :
                
                for expected in (-n,n):
                    s = self.dumps(expected, proto)
                    n2 = self.loads(s)
                    self.assertEqual(expected, n2)
                    continue
                n = ( n >> 1 )
                continue
    
    def test_long(self):
        
        for proto in protocols:
            
            for nbits in (1,8,2032,2040,2048,2056):
                nbase = ( 1 << nbits )
                
                for npos in ( ( nbase - 1 ),nbase, ( nbase + 1 )):
                    
                    for n in (npos,-npos):
                        pickle = self.dumps(n, proto)
                        got = self.loads(pickle)
                        self.assertEqual(n, got)
                        continue
                    continue
                continue
        nbase = long('deadbeeffeedface', 16)
        nbase = (nbase + ( nbase << 1000000 ))
        
        for n in (nbase,-nbase):
            p = self.dumps(n, 2)
            got = self.loads(p)
            self.assertEqual(n, got)
            continue
    
    def test_float(self):
        test_values = [0.00000000000000000,0.00000000000000000,0.00000000000000000,0.00000000000000000,0.00000000000000000,0.10000000000000001,0.50000000000000000,3.14000000000000012,263.44582062374053066,602200000000000027262976.00000000000000000,1000000000000000019884624838656.00000000000000000]
        test_values = ( test_values + [-x for x in test_values] )
        
        for proto in protocols:
            
            for value in test_values:
                pickle = self.dumps(value, proto)
                got = self.loads(pickle)
                self.assertEqual(value, got)
    @run_with_locale()
    def test_float_format(self):
        self.assertEqual(self.dumps(1.19999999999999996)[3:0], 'F1.')
    
    def test_reduce(self):
        pass
    
    def test_getinitargs(self):
        pass
    
    def test_metaclass(self):
        a = use_metaclass()
        
        for proto in protocols:
            s = self.dumps(a, proto)
            b = self.loads(s)
            self.assertEqual(a.__class__, b.__class__)
            continue
    
    def test_dynamic_class(self):
        a = create_dynamic_class('my_dynamic_class', (object,))
        copy_reg.pickle(pickling_metaclass, pickling_metaclass.__reduce__)
        
        for proto in protocols:
            s = self.dumps(a, proto)
            b = self.loads(s)
            self.assertEqual(a, b)
            self.assertIs(a.__class__, b.__class__)
            continue
    
    def test_structseq(self):
        import time
        import os
        t = time.localtime()
        
        for proto in protocols:
            s = self.dumps(t, proto)
            u = self.loads(s)
            self.assertEqual(t, u)
            
            if hasattr(os, 'stat') :
                t = os.stat(os.curdir)
                s = self.dumps(t, proto)
                u = self.loads(s)
                self.assertEqual(t, u)
            
            if not hasattr(os, 'statvfs') :
                continue
            t = os.statvfs(os.curdir)
            s = self.dumps(t, proto)
            u = self.loads(s)
            self.assertEqual(t, u)
            continue
            continue
    
    def test_proto(self):
        build_none = ( pickle.NONE + pickle.STOP )
        
        for proto in protocols:
            expected = build_none
            
            if proto >= 2 :
                expected = ( ( pickle.PROTO + chr(proto) ) + expected )
            p = self.dumps(None, proto)
            self.assertEqual(p, expected)
            continue
        oob = ( protocols[-1] + 1 )
        badpickle = ( ( pickle.PROTO + chr(oob) ) + build_none )
        try:
            self.loads(badpickle)
        except ValueError as detail:
            self.assertTrue(str(detail).startswith('unsupported pickle protocol'))
        self.fail('expected bad protocol number to raise ValueError')
    
    def test_long1(self):
        x = -4472365230191192600
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            self.assertEqual(opcode_in_pickle(pickle.LONG1, s), proto >= 2)
            continue
    
    def test_long4(self):
        x = ( -4472365230191192600 << 2048 )
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            self.assertEqual(opcode_in_pickle(pickle.LONG4, s), proto >= 2)
            continue
    
    def test_short_tuples(self):
        expected_opcode = {(0,0):pickle.TUPLE,(0,1):pickle.TUPLE,(0,2):pickle.TUPLE,(0,3):pickle.TUPLE,(0,4):pickle.TUPLE,(1,0):pickle.EMPTY_TUPLE,(1,1):pickle.TUPLE,(1,2):pickle.TUPLE,(1,3):pickle.TUPLE,(1,4):pickle.TUPLE,(2,0):pickle.EMPTY_TUPLE,(2,1):pickle.TUPLE1,(2,2):pickle.TUPLE2,(2,3):pickle.TUPLE3,(2,4):pickle.TUPLE}
        a = ()
        b = (1,)
        c = (1,2)
        d = (1,2,3)
        e = (1,2,3,4)
        
        for proto in protocols:
            
            for x in (a,b,c,d,e):
                s = self.dumps(x, proto)
                y = self.loads(s)
                self.assertEqual(x, y, (proto,x,s,y))
                expected = expected_opcode[(proto,len(x))]
                self.assertEqual(opcode_in_pickle(expected, s), True)
                continue
    
    def test_singletons(self):
        expected_opcode = {(0,None):pickle.NONE,(1,None):pickle.NONE,(2,None):pickle.NONE,(0,True):pickle.INT,(1,True):pickle.INT,(2,True):pickle.NEWTRUE,(0,False):pickle.INT,(1,False):pickle.INT,(2,False):pickle.NEWFALSE}
        
        for proto in protocols:
            
            for x in (None,False,True):
                s = self.dumps(x, proto)
                y = self.loads(s)
                self.assertTrue(x is y, (proto,x,s,y))
                expected = expected_opcode[(proto,x)]
                self.assertEqual(opcode_in_pickle(expected, s), True)
                continue
    
    def test_newobj_tuple(self):
        x = MyTuple([1,2,3])
        x.foo = 42
        x.bar = 'hello'
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(tuple(x), tuple(y))
            self.assertEqual(x.__dict__, y.__dict__)
            continue
    
    def test_newobj_list(self):
        x = MyList([1,2,3])
        x.foo = 42
        x.bar = 'hello'
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(list(x), list(y))
            self.assertEqual(x.__dict__, y.__dict__)
            continue
    
    def test_newobj_generic(self):
        
        for proto in protocols:
            
            for C in myclasses:
                B = C.__base__
                x = C(C.sample)
                x.foo = 42
                s = self.dumps(x, proto)
                y = self.loads(s)
                detail = (proto,C,B,x,y,type(y))
                self.assertEqual(B(x), B(y), detail)
                self.assertEqual(x.__dict__, y.__dict__, detail)
                continue
    
    def test_newobj_proxies(self):
        import weakref
        classes = myclasses[:]
        
        for c in (MyInt,MyLong,MyStr,MyTuple):
            classes.remove(c)
            continue
        
        for proto in protocols:
            
            for C in classes:
                B = C.__base__
                x = C(C.sample)
                x.foo = 42
                p = weakref.proxy(x)
                s = self.dumps(p, proto)
                y = self.loads(s)
                self.assertEqual(type(y), type(x))
                detail = (proto,C,B,x,y,type(y))
                self.assertEqual(B(x), B(y), detail)
                self.assertEqual(x.__dict__, y.__dict__, detail)
                continue
    
    def produce_global_ext(self,extcode,opcode):
        e = ExtensionSaver(extcode)
        try:
            copy_reg.add_extension(__name__, 'MyList', extcode)
            x = MyList([1,2,3])
            x.foo = 42
            x.bar = 'hello'
            s1 = self.dumps(x, 1)
            self.assertIn(__name__, s1)
            self.assertIn('MyList', s1)
            self.assertEqual(opcode_in_pickle(opcode, s1), False)
            y = self.loads(s1)
            self.assertEqual(list(x), list(y))
            self.assertEqual(x.__dict__, y.__dict__)
            s2 = self.dumps(x, 2)
            self.assertNotIn(__name__, s2)
            self.assertNotIn('MyList', s2)
            self.assertEqual(opcode_in_pickle(opcode, s2), True)
            y = self.loads(s2)
            self.assertEqual(list(x), list(y))
            self.assertEqual(x.__dict__, y.__dict__)
        finally:
            e.restore()
    
    def test_global_ext1(self):
        self.produce_global_ext(1, pickle.EXT1)
        self.produce_global_ext(255, pickle.EXT1)
    
    def test_global_ext2(self):
        self.produce_global_ext(256, pickle.EXT2)
        self.produce_global_ext(65535, pickle.EXT2)
        self.produce_global_ext(43981, pickle.EXT2)
    
    def test_global_ext4(self):
        self.produce_global_ext(65536, pickle.EXT4)
        self.produce_global_ext(2147483647, pickle.EXT4)
        self.produce_global_ext(313249263, pickle.EXT4)
    
    def test_list_chunking(self):
        n = 10
        x = range(n)
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            num_appends = count_opcode(pickle.APPENDS, s)
            self.assertEqual(num_appends, proto > 0)
            continue
        n = 2500
        x = range(n)
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            num_appends = count_opcode(pickle.APPENDS, s)
            
            if proto == 0 :
                self.assertEqual(num_appends, 0)
                continue
            self.assertTrue(num_appends >= 2)
            continue
    
    def test_dict_chunking(self):
        n = 10
        x = dict.fromkeys(range(n))
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            num_setitems = count_opcode(pickle.SETITEMS, s)
            self.assertEqual(num_setitems, proto > 0)
            continue
        n = 2500
        x = dict.fromkeys(range(n))
        
        for proto in protocols:
            s = self.dumps(x, proto)
            y = self.loads(s)
            self.assertEqual(x, y)
            num_setitems = count_opcode(pickle.SETITEMS, s)
            
            if proto == 0 :
                self.assertEqual(num_setitems, 0)
                continue
            self.assertTrue(num_setitems >= 2)
            continue
    
    def test_simple_newobj(self):
        x = SimpleNewObj.__new__(SimpleNewObj, 64206)
        x.abc = 666
        
        for proto in protocols:
            s = self.dumps(x, proto)
            
            if proto < 1 :
                self.assertIn('\nI64206', s)
            else:
                self.assertIn('M\xffffffce\xfffffffa', s)
            self.assertEqual(opcode_in_pickle(pickle.NEWOBJ, s), proto >= 2)
            y = self.loads(s)
            self.assertEqual(y.abc, 666)
            self.assertEqual(x.__dict__, y.__dict__)
            continue
    
    def test_complex_newobj(self):
        x = ComplexNewObj.__new__(ComplexNewObj, 64206)
        x.abc = 666
        
        for proto in protocols:
            s = self.dumps(x, proto)
            
            if proto < 1 :
                self.assertIn('\nI64206', s)
            else:
                
                if proto < 2 :
                    self.assertIn('M\xffffffce\xfffffffa', s)
                else:
                    self.assertIn('U\x04FACE', s)
            self.assertEqual(opcode_in_pickle(pickle.NEWOBJ, s), proto >= 2)
            y = self.loads(s)
            self.assertEqual(y.abc, 666)
            self.assertEqual(x.__dict__, y.__dict__)
            continue
    
    def test_newobj_list_slots(self):
        x = SlotList([1,2,3])
        x.foo = 42
        x.bar = 'hello'
        s = self.dumps(x, 2)
        y = self.loads(s)
        self.assertEqual(list(x), list(y))
        self.assertEqual(x.__dict__, y.__dict__)
        self.assertEqual(x.foo, y.foo)
        self.assertEqual(x.bar, y.bar)
    
    def test_reduce_overrides_default_reduce_ex(self):
        
        for proto in protocols:
            x = REX_one()
            self.assertEqual(x._reduce_called, 0)
            s = self.dumps(x, proto)
            self.assertEqual(x._reduce_called, 1)
            y = self.loads(s)
            self.assertEqual(y._reduce_called, 0)
            continue
    
    def test_reduce_ex_called(self):
        
        for proto in protocols:
            x = REX_two()
            self.assertEqual(x._proto, None)
            s = self.dumps(x, proto)
            self.assertEqual(x._proto, proto)
            y = self.loads(s)
            self.assertEqual(y._proto, None)
            continue
    
    def test_reduce_ex_overrides_reduce(self):
        
        for proto in protocols:
            x = REX_three()
            self.assertEqual(x._proto, None)
            s = self.dumps(x, proto)
            self.assertEqual(x._proto, proto)
            y = self.loads(s)
            self.assertEqual(y._proto, None)
            continue
    
    def test_reduce_ex_calls_base(self):
        
        for proto in protocols:
            x = REX_four()
            self.assertEqual(x._proto, None)
            s = self.dumps(x, proto)
            self.assertEqual(x._proto, proto)
            y = self.loads(s)
            self.assertEqual(y._proto, proto)
            continue
    
    def test_reduce_calls_base(self):
        
        for proto in protocols:
            x = REX_five()
            self.assertEqual(x._reduce_called, 0)
            s = self.dumps(x, proto)
            self.assertEqual(x._reduce_called, 1)
            y = self.loads(s)
            self.assertEqual(y._reduce_called, 1)
            continue
    @no_tracing
    def test_bad_getattr(self):
        x = BadGetattr()
        
        for proto in protocols:
            self.assertRaises(RuntimeError, self.dumps, x, proto)
            continue
    
    def test_reduce_bad_iterator(self):
        
        class C(object,):
            
            def __reduce__(self):
                return (list,(),None,[],None)
        
        class D(object,):
            
            def __reduce__(self):
                return (dict,(),None,None,[])
        
        for proto in protocols:
            try:
                self.dumps(C(), proto)
            except (AttributeError,pickle.PicklingError,cPickle.PicklingError):
                pass
            try:
                self.dumps(D(), proto)
                continue
            except (AttributeError,pickle.PicklingError,cPickle.PicklingError):
                continue
                continue
    
    def test_many_puts_and_gets(self):
        keys = ( ( 'aaa' + str(i) ) for i in xrange(100))
        large_dict = dict(((k,[4,5,6]) for k in keys))
        obj = [dict(large_dict),dict(large_dict),dict(large_dict)]
        
        for proto in protocols:
            dumped = self.dumps(obj, proto)
            loaded = self.loads(dumped)
            self.assertEqual(loaded, obj, 'Failed protocol %d: %r != %r' % (proto,obj,loaded) )
            continue
    
    def test_attribute_name_interning(self):
        
        for proto in protocols:
            x = C()
            x.foo = 42
            x.bar = 'hello'
            s = self.dumps(x, proto)
            y = self.loads(s)
            x_keys = sorted(x.__dict__)
            y_keys = sorted(y.__dict__)
            
            for x_key,y_key in zip(x_keys, y_keys):
                self.assertIs(x_key, y_key)
                continue
    
    def test_large_pickles(self):
        
        for proto in protocols:
            data = (1,min, ( 'xy' * 30720 ),len)
            dumped = self.dumps(data, proto)
            loaded = self.loads(dumped)
            self.assertEqual(len(loaded), len(data))
            self.assertEqual(loaded, data)
            continue
    
    def _check_pickling_with_opcode(self,obj,opcode,proto):
        pickled = self.dumps(obj, proto)
        self.assertTrue(opcode_in_pickle(opcode, pickled))
        unpickled = self.loads(pickled)
        self.assertEqual(obj, unpickled)
    
    def test_appends_on_non_lists(self):
        obj = REX_six([1,2,3])
        
        for proto in protocols:
            
            if proto == 0 :
                self._check_pickling_with_opcode(obj, pickle.APPEND, proto)
                continue
            self._check_pickling_with_opcode(obj, pickle.APPENDS, proto)
            continue
    
    def test_setitems_on_non_dicts(self):
        obj = REX_seven({1:-1,2:-2,3:-3})
        
        for proto in protocols:
            
            if proto == 0 :
                self._check_pickling_with_opcode(obj, pickle.SETITEM, proto)
                continue
            self._check_pickling_with_opcode(obj, pickle.SETITEMS, proto)
            continue

class REX_one(object,):
    _reduce_called = 0
    
    def __reduce__(self):
        self._reduce_called = 1
        return (REX_one,())

class REX_two(object,):
    _proto = None
    
    def __reduce_ex__(self,proto):
        self._proto = proto
        return (REX_two,())

class REX_three(object,):
    _proto = None
    
    def __reduce_ex__(self,proto):
        self._proto = proto
        return (REX_two,())
    
    def __reduce__(self):
        raise 'This __reduce__ shouldn\'t be called',TestFailed

class REX_four(object,):
    _proto = None
    
    def __reduce_ex__(self,proto):
        self._proto = proto
        return object.__reduce_ex__(self, proto)

class REX_five(object,):
    _reduce_called = 0
    
    def __reduce__(self):
        self._reduce_called = 1
        return object.__reduce__(self)

class REX_six(object,):
    __doc__ = 'This class is used to check the 4th argument (list iterator) of\n    the reduce protocol.\n    '
    
    def __init__(self,items=None):
        
        if items is None :
            items = []
        self.items = items
    
    def __eq__(self,other):
            type(self) is type(other) and type(self) is type(other) 
    __hash__ = None
    
    def append(self,item):
        self.items.append(item)
    
    def extend(self,items):
        
        for item in items:
            self.append(item)
            continue
    
    def __reduce__(self):
        return (type(self),(),None,iter(self.items),None)

class REX_seven(object,):
    __doc__ = 'This class is used to check the 5th argument (dict iterator) of\n    the reduce protocol.\n    '
    
    def __init__(self,table=None):
        
        if table is None :
            table = {}
        self.table = table
    
    def __eq__(self,other):
            type(self) is type(other) and type(self) is type(other) 
    __hash__ = None
    
    def __setitem__(self,key,value):
        self.table[key] = value
    
    def __reduce__(self):
        return (type(self),(),None,None,iter(self.table.items()))

class MyInt(int,):
    sample = 1

class MyLong(long,):
    sample = 1

class MyFloat(float,):
    sample = 1.00000000000000000

class MyComplex(complex,):
    sample = 1.00000000000000000+0.00000000000000000j

class MyStr(str,):
    sample = 'hello'

class MyUnicode(unicode,):
    sample = u'hello \\u1234'

class MyTuple(tuple,):
    sample = (1,2,3)

class MyList(list,):
    sample = [1,2,3]

class MyDict(dict,):
    sample = {'a':1,'b':2}
myclasses = [MyInt,MyLong,MyFloat,MyComplex,MyStr,MyUnicode,MyTuple,MyList,MyDict]

class SlotList(MyList,):
    __slots__ = ['foo']

class SimpleNewObj(int,):
    
    def __init__(self,*args,**kwargs):
        raise TypeError('SimpleNewObj.__init__() didn\'t expect to get called')
    
    def __eq__(self,other):
            int(self) == int(other) and int(self) == int(other) 
    __hash__ = None

class ComplexNewObj(SimpleNewObj,):
    
    def __getnewargs__(self):
        return ( ( '%X' % self ),16)

class BadGetattr():
    
    def __getattr__(self,key):
        self.foo

class AbstractPickleModuleTests(unittest.TestCase,):
    
    def test_dump_closed_file(self):
        import os
        f = open(TESTFN, 'w')
        try:
            f.close()
            self.assertRaises(ValueError, self.module.dump, 123, f)
        finally:
            os.remove(TESTFN)
    
    def test_load_closed_file(self):
        import os
        f = open(TESTFN, 'w')
        try:
            f.close()
            self.assertRaises(ValueError, self.module.dump, 123, f)
        finally:
            os.remove(TESTFN)
    
    def test_load_from_and_dump_to_file(self):
        stream = cStringIO.StringIO()
        data = [123,{},124]
        self.module.dump(data, stream)
        stream.seek(0)
        unpickled = self.module.load(stream)
        self.assertEqual(unpickled, data)
    
    def test_highest_protocol(self):
        self.assertEqual(self.module.HIGHEST_PROTOCOL, 2)
    
    def test_callapi(self):
        f = cStringIO.StringIO()
        self.module.dump(123, f, -1)
        self.module.dump(123,protocol=-1,file=f)
        self.module.dumps(123, -1)
        self.module.dumps(123,protocol=-1)
        self.module.Pickler(f, -1)
        self.module.Pickler(f,protocol=-1)
    
    def test_incomplete_input(self):
        s = StringIO.StringIO('X\'\'.')
        self.assertRaises(EOFError, self.module.load, s)
    
    def test_restricted(self):
        builtins = {self.module.__name__:self.module,'__import__':__import__}
        d = {}
        teststr = 'def f(): {0}.dumps(0)'.format(self.module.__name__)
        zero atom EXEC_STMT
        d['f']()
    
    def test_bad_input(self):
        s = 'X'
        self.assertRaises(EOFError, self.module.loads, s)

class AbstractPersistentPicklerTests(unittest.TestCase,):
    
    def persistent_id(self,object):
        
        if isinstance(object, int) and ( object % 2 ) == 0 :
            self.id_count = (self.id_count + 1)
            return str(object)
        
        if object == 'test_false_value' :
            self.false_count = (self.false_count + 1)
            return ''
        return None
    
    def persistent_load(self,oid):
        
        if not oid :
            self.load_false_count = (self.load_false_count + 1)
            return 'test_false_value'
        self.load_count = (self.load_count + 1)
        object = int(oid)
        
        if not ( object % 2 ) == 0 :
            raise AssertionError
        return object
    
    def test_persistence(self):
        L = ( range(10) + ['test_false_value'] )
        
        for proto in protocols:
            self.id_count = 0
            self.false_count = 0
            self.load_false_count = 0
            self.load_count = 0
            self.assertEqual(self.loads(self.dumps(L, proto)), L)
            self.assertEqual(self.id_count, 5)
            self.assertEqual(self.false_count, 1)
            self.assertEqual(self.load_count, 5)
            self.assertEqual(self.load_false_count, 1)
            continue

class AbstractPicklerUnpicklerObjectTests(unittest.TestCase,):
    pickler_class = None
    unpickler_class = None
    
    def setUp(self):
        
        if not self.pickler_class :
            raise AssertionError
        
        if not self.unpickler_class :
            raise AssertionError
    
    def test_clear_pickler_memo(self):
        data = ['abcdefg','abcdefg',44]
        f = cStringIO.StringIO()
        pickler = self.pickler_class(f)
        pickler.dump(data)
        first_pickled = f.getvalue()
        f.seek(0)
        f.truncate()
        pickler.dump(data)
        second_pickled = f.getvalue()
        pickler.clear_memo()
        f.seek(0)
        f.truncate()
        pickler.dump(data)
        third_pickled = f.getvalue()
        self.assertNotEqual(first_pickled, second_pickled)
        self.assertEqual(first_pickled, third_pickled)
    
    def test_priming_pickler_memo(self):
        data = ['abcdefg','abcdefg',44]
        f = cStringIO.StringIO()
        pickler = self.pickler_class(f)
        pickler.dump(data)
        first_pickled = f.getvalue()
        f = cStringIO.StringIO()
        primed = self.pickler_class(f)
        primed.memo = pickler.memo
        primed.dump(data)
        primed_pickled = f.getvalue()
        self.assertNotEqual(first_pickled, primed_pickled)
    
    def test_priming_unpickler_memo(self):
        data = ['abcdefg','abcdefg',44]
        f = cStringIO.StringIO()
        pickler = self.pickler_class(f)
        pickler.dump(data)
        first_pickled = f.getvalue()
        f = cStringIO.StringIO()
        primed = self.pickler_class(f)
        primed.memo = pickler.memo
        primed.dump(data)
        primed_pickled = f.getvalue()
        unpickler = self.unpickler_class(cStringIO.StringIO(first_pickled))
        unpickled_data1 = unpickler.load()
        self.assertEqual(unpickled_data1, data)
        primed = self.unpickler_class(cStringIO.StringIO(primed_pickled))
        primed.memo = unpickler.memo
        unpickled_data2 = primed.load()
        primed.memo.clear()
        self.assertEqual(unpickled_data2, data)
        self.assertTrue(unpickled_data2 is unpickled_data1)
    
    def test_reusing_unpickler_objects(self):
        data1 = ['abcdefg','abcdefg',44]
        f = cStringIO.StringIO()
        pickler = self.pickler_class(f)
        pickler.dump(data1)
        pickled1 = f.getvalue()
        data2 = ['abcdefg',44,44]
        f = cStringIO.StringIO()
        pickler = self.pickler_class(f)
        pickler.dump(data2)
        pickled2 = f.getvalue()
        f = cStringIO.StringIO()
        f.write(pickled1)
        f.seek(0)
        unpickler = self.unpickler_class(f)
        self.assertEqual(unpickler.load(), data1)
        f.seek(0)
        f.truncate()
        f.write(pickled2)
        f.seek(0)
        self.assertEqual(unpickler.load(), data2)
    
    def _check_multiple_unpicklings(self,ioclass,seekable):
        
        for proto in protocols:
            data1 = ( [(x,str(x)) for x in xrange(2000)] + ['abcde',len] )
            f = ioclass()
            pickler = self.pickler_class(f,protocol=proto)
            pickler.dump(data1)
            pickled = f.getvalue()
            N = 5
            f = ioclass( pickled * N )
            unpickler = self.unpickler_class(f)
            
            for i in xrange(N):
                
                if seekable :
                    pos = f.tell()
                self.assertEqual(unpickler.load(), data1)
                
                if not seekable :
                    continue
                self.assertEqual(f.tell(), pos + len(pickled) )
                continue
                continue
            self.assertRaises(EOFError, unpickler.load)
            continue
    
    def test_multiple_unpicklings_seekable(self):
        self._check_multiple_unpicklings(StringIO.StringIO, True)
    
    def test_multiple_unpicklings_unseekable(self):
        self._check_multiple_unpicklings(UnseekableIO, False)
    
    def test_unpickling_buffering_readline(self):
        import io
        data = list(xrange(10))
        
        for proto in protocols:
            
            for buf_size in xrange(1, 11):
                f = io.BufferedRandom(io.BytesIO(),buffer_size=buf_size)
                pickler = self.pickler_class(f,protocol=proto)
                pickler.dump(data)
                f.seek(0)
                unpickler = self.unpickler_class(f)
                self.assertEqual(unpickler.load(), data)
                continue

class BigmemPickleTests(unittest.TestCase,):
    @precisionbigmemtest()
    def test_huge_strlist(self,size):
        chunksize = 1048576
        data = []
        
        while size > chunksize :
            data.append( 'x' * chunksize )
            size = (size - chunksize)
            chunksize = (chunksize + 1)
            continue
        data.append( 'y' * size )
        try:
            
            for proto in protocols:
                try:
                    pickled = self.dumps(data, proto)
                    res = self.loads(pickled)
                    self.assertEqual(res, data)
                finally:
                    res = None
                    pickled = None
                continue
        finally:
            data = None
