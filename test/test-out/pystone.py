__doc__ = '\n"PYSTONE" Benchmark Program\n\nVersion:        Python/1.1 (corresponds to C/1.1 plus 2 Pystone fixes)\n\nAuthor:         Reinhold P. Weicker,  CACM Vol 27, No 10, 10/84 pg. 1013.\n\n                Translated from ADA to C by Rick Richardson.\n                Every method to preserve ADA-likeness has been used,\n                at the expense of C-ness.\n\n                Translated from C to Python by Guido van Rossum.\n\nVersion History:\n\n                Version 1.1 corrects two bugs in version 1.0:\n\n                First, it leaked memory: in Proc1(), NextRecord ends\n                up having a pointer to itself.  I have corrected this\n                by zapping NextRecord.PtrComp at the end of Proc1().\n\n                Second, Proc3() used the operator != to compare a\n                record to None.  This is rather inefficient and not\n                true to the intention of the original benchmark (where\n                a pointer comparison to None is intended; the !=\n                operator attempts to find a method __cmp__ to do value\n                comparison of the record).  Version 1.1 runs 5-10\n                percent faster than version 1.0, so benchmark figures\n                of different versions can\'t be compared directly.\n\n'
LOOPS = 50000
from time import 'clock',
__version__ = '1.1'
Ident1, Ident2, Ident3, Ident4, Ident5 = range(1, 6)

class Record():
    
    def __init__(self,PtrComp=None,Discr=0,EnumComp=0,IntComp=0,StringComp=0):
        self.PtrComp = PtrComp
        self.Discr = Discr
        self.EnumComp = EnumComp
        self.IntComp = IntComp
        self.StringComp = StringComp
        pass
    
    def copy(self):
        return Record(self.PtrComp, self.Discr, self.EnumComp, self.IntComp, self.StringComp)
TRUE = 1
FALSE = 0

def main(loops=LOOPS):
    benchtime, stones = pystones(loops)
    print( ( 'Pystone(%s) time for %d passes = %g' % (__version__,loops,benchtime) ))
    print( ( 'This machine benchmarks at %g pystones/second' % stones ))

def pystones(loops=LOOPS):
    return Proc0(loops)
0
zero atom STORE_GLOBAL
zero atom STORE_GLOBAL
zero atom STORE_GLOBAL
zero atom STORE_GLOBAL
 ( [0] * 51 )
zero atom STORE_GLOBAL
map(lambda x :x[:], [Array1Glob] * 51 )
zero atom STORE_GLOBAL
zero atom STORE_GLOBAL
zero atom STORE_GLOBAL

def Proc0(loops=LOOPS):
    starttime = clock()
    
    for i in range(loops):
        continue
    nulltime = ( clock() - starttime )
    Record()
    zero atom STORE_GLOBAL
    Record()
    zero atom STORE_GLOBAL
    PtrGlb.PtrComp = PtrGlbNext
    PtrGlb.Discr = Ident1
    PtrGlb.EnumComp = Ident3
    PtrGlb.IntComp = 40
    PtrGlb.StringComp = 'DHRYSTONE PROGRAM, SOME STRING'
    String1Loc = 'DHRYSTONE PROGRAM, 1\'ST STRING'
    Array2Glob[8][7] = 10
    starttime = clock()
    
    for i in range(loops):
        Proc5()
        Proc4()
        IntLoc1 = 2
        IntLoc2 = 3
        String2Loc = 'DHRYSTONE PROGRAM, 2\'ND STRING'
        EnumLoc = Ident2
        not Func2(String1Loc, String2Loc)
        zero atom STORE_GLOBAL
        
        while IntLoc1 < IntLoc2 :
            IntLoc3 = ( ( 5 * IntLoc1 ) - IntLoc2 )
            IntLoc3 = Proc7(IntLoc1, IntLoc2)
            IntLoc1 = ( IntLoc1 + 1 )
            continue
        Proc8(Array1Glob, Array2Glob, IntLoc1, IntLoc3)
        Proc1(PtrGlb)
        zero atom STORE_GLOBAL
        CharIndex = 'A'
        
        while CharIndex <= Char2Glob :
            
            if EnumLoc == Func1(CharIndex, 'C') :
                EnumLoc = Proc6(Ident1)
            CharIndex = chr( ord(CharIndex) + 1 )
            continue
        IntLoc3 = ( IntLoc2 * IntLoc1 )
        IntLoc2 = ( IntLoc3 / IntLoc1 )
        IntLoc2 = ( ( 7 * ( IntLoc3 - IntLoc2 ) ) - IntLoc1 )
        IntLoc1 = Proc2(IntLoc1)
        continue
    benchtime = ( ( clock() - starttime ) - nulltime )
    
    if benchtime == 0.00000000000000000 :
        loopsPerBenchtime = 0.00000000000000000
    else:
        loopsPerBenchtime = ( loops / benchtime )
    return (benchtime,loopsPerBenchtime)

def Proc1(PtrParIn):
    PtrParIn.PtrComp = PtrGlb.copy()
    NextRecord = PtrGlb.copy()
    PtrParIn.IntComp = 5
    NextRecord.IntComp = PtrParIn.IntComp
    NextRecord.PtrComp = PtrParIn.PtrComp
    NextRecord.PtrComp = Proc3(NextRecord.PtrComp)
    
    if NextRecord.Discr == Ident1 :
        NextRecord.IntComp = 6
        NextRecord.EnumComp = Proc6(PtrParIn.EnumComp)
        NextRecord.PtrComp = PtrGlb.PtrComp
        NextRecord.IntComp = Proc7(NextRecord.IntComp, 10)
    else:
        PtrParIn = NextRecord.copy()
    NextRecord.PtrComp = None
    return PtrParIn

def Proc2(IntParIO):
    IntLoc = ( IntParIO + 10 )
    
    while Char1Glob == 'A' :
        IntLoc = ( IntLoc - 1 )
        IntParIO = ( IntLoc - IntGlob )
        EnumLoc = Ident1
    
    if not EnumLoc == Ident1 :
        continue
    break
    continue
    continue
    return IntParIO

def Proc3(PtrParOut):
    
    if PtrGlb is not None :
        PtrParOut = PtrGlb.PtrComp
    else:
        100
        zero atom STORE_GLOBAL
    PtrGlb.IntComp = Proc7(10, IntGlob)
    return PtrParOut

def Proc4():
    BoolLoc = Char1Glob == 'A'
    zero atom JUMP_IF_TRUE_OR_POP
    BoolLoc = BoolGlob
    zero atom STORE_GLOBAL

def Proc5():
    zero atom STORE_GLOBAL
    zero atom STORE_GLOBAL

def Proc6(EnumParIn):
    EnumParOut = EnumParIn
    
    if not Func3(EnumParIn) :
        EnumParOut = Ident4
    
    if EnumParIn == Ident1 :
        EnumParOut = Ident1
    else:
        
        if EnumParIn == Ident2 :
            
            if IntGlob > 100 :
                EnumParOut = Ident1
            else:
                EnumParOut = Ident4
        else:
            
            if EnumParIn == Ident3 :
                EnumParOut = Ident2
            else:
                
                if EnumParIn == Ident4 :
                else:
                    
                    if EnumParIn == Ident5 :
                        EnumParOut = Ident3
    return EnumParOut

def Proc7(IntParI1,IntParI2):
    IntLoc = ( IntParI1 + 2 )
    IntParOut = ( IntParI2 + IntLoc )
    return IntParOut

def Proc8(Array1Par,Array2Par,IntParI1,IntParI2):
    IntLoc = ( IntParI1 + 5 )
    Array1Par[IntLoc] = IntParI2
    Array1Par[ ( IntLoc + 1 )] = Array1Par[IntLoc]
    Array1Par[ ( IntLoc + 30 )] = IntLoc
    
    for IntIndex in range(IntLoc, IntLoc + 2 ):
        Array2Par[IntLoc][IntIndex] = IntLoc
        continue
    Array2Par[IntLoc][ ( IntLoc - 1 )] = ( Array2Par[IntLoc][ ( IntLoc - 1 )] + 1 )
    Array2Par[ ( IntLoc + 20 )][IntLoc] = Array1Par[IntLoc]
    5
    zero atom STORE_GLOBAL

def Func1(CharPar1,CharPar2):
    CharLoc1 = CharPar1
    CharLoc2 = CharLoc1
    
    if CharLoc2 != CharPar2 :
        return Ident1
    return Ident2

def Func2(StrParI1,StrParI2):
    IntLoc = 1
    
    while IntLoc <= 1 :
        
        if not Func1(StrParI1[IntLoc], StrParI2[ ( IntLoc + 1 )]) == Ident1 :
            continue
        CharLoc = 'A'
        IntLoc = ( IntLoc + 1 )
        continue
        continue
    
    if CharLoc >= 'W' and CharLoc <= 'Z' :
        IntLoc = 7
    
    if CharLoc == 'X' :
        return TRUE
    
    if StrParI1 > StrParI2 :
        IntLoc = ( IntLoc + 7 )
        return TRUE
    return FALSE

def Func3(EnumParIn):
    EnumLoc = EnumParIn
    
    if EnumLoc == Ident3 :
        return TRUE
    return FALSE

if __name__ == '__main__' :
    import sys
    
    def error(msg):
        zero atom PRINT_ITEM_TO
        sys.stderr
        ( 'usage: %s [number_of_loops]' % sys.argv[0] )
        zero atom PRINT_ITEM_TO
        zero atom PRINT_NEWLINE_TO
        sys.exit(100)
    nargs = ( len(sys.argv) - 1 )
    
    if nargs > 1 :
        error( '%d arguments are too many;' % nargs )
    else:
        
        if nargs == 1 :
            try:
                loops = int(sys.argv[1])
            except ValueError:
                error( 'Invalid argument %r;' % sys.argv[1] )
    main(loops)
