function <module>():

 L.  1      0 LOAD_CONST str: A module docstring.
            1 STORE_NAME str: __doc__
 L.  3      2 LOAD_CONST long: -1
            3 LOAD_CONST obj: N
            4 IMPORT_NAME str: sys
            5 STORE_NAME str: sys
            6 LOAD_CONST long: -1
            7 LOAD_CONST obj: N
            8 IMPORT_NAME str: inspect
            9 STORE_NAME str: inspect
 L.  7     10 LOAD_CONST long: 3
           11 LOAD_CONST long: 4
           12 LOAD_CONST (long: 5,)
           13 BUILD_TUPLE 2
           14 LOAD_CONST obj: c
           15 MAKE_FUNCTION 2
           16 STORE_NAME str: spam
 L. 11     17 LOAD_CONST obj: c
           18 MAKE_FUNCTION 0
           19 STORE_NAME str: eggs
 L. 20     20 LOAD_CONST str: StupidGit
           21 LOAD_CONST ()
           22 LOAD_CONST obj: c
           23 MAKE_FUNCTION 0
           24 CALL_FUNCTION 0
           25 BUILD_CLASS
           26 STORE_NAME str: StupidGit
 L. 48     27 LOAD_CONST str: MalodorousPervert
           28 LOAD_NAME str: StupidGit
           29 BUILD_TUPLE 1
           30 LOAD_CONST obj: c
           31 MAKE_FUNCTION 0
           32 CALL_FUNCTION 0
           33 BUILD_CLASS
           34 STORE_NAME str: MalodorousPervert
 L. 51     35 LOAD_NAME str: MalodorousPervert
           36 STORE_NAME str: Tit
 L. 53     37 LOAD_CONST str: ParrotDroppings
           38 LOAD_CONST ()
           39 LOAD_CONST obj: c
           40 MAKE_FUNCTION 0
           41 CALL_FUNCTION 0
           42 BUILD_CLASS
           43 STORE_NAME str: ParrotDroppings
 L. 56     44 LOAD_CONST str: FesteringGob
           45 LOAD_NAME str: MalodorousPervert
           46 LOAD_NAME str: ParrotDroppings
           47 BUILD_TUPLE 2
           48 LOAD_CONST obj: c
           49 MAKE_FUNCTION 0
           50 CALL_FUNCTION 0
           51 BUILD_CLASS
           52 STORE_NAME str: FesteringGob
 L. 59     53 LOAD_NAME str: inspect
           54 LOAD_ATTR str: currentframe
           55 CALL_FUNCTION 0
           56 STORE_NAME str: currentframe
 L. 60     57 SETUP_EXCEPT 13 to 63
 L. 61     58 LOAD_NAME str: Exception
           59 CALL_FUNCTION 0
           60 RAISE_VARARGS 1
           61 POP_BLOCK
           62 JUMP_FORWARD 23 to 74
 L. 62     63 POP_TOP
           64 POP_TOP
           65 POP_TOP
 L. 63     66 LOAD_NAME str: sys
           67 LOAD_ATTR str: exc_info
           68 CALL_FUNCTION 0
           69 LOAD_CONST long: 2
           70 BINARY_SUBSCR
           71 STORE_NAME str: tb
           72 JUMP_FORWARD 1 to 74
           73 END_FINALLY to 74
           74 LOAD_CONST obj: N
           75 RETURN_VALUE

function spam(a,b,c,d,.4,*g,**h):

 L.  1      0 LOAD_FAST str: .4
            1 UNPACK_SEQUENCE 2
            2 STORE_FAST str: e
            3 UNPACK_SEQUENCE 1
            4 STORE_FAST str: f
 L.  2      5 LOAD_GLOBAL str: eggs
            6 LOAD_FAST str: b
            7 LOAD_FAST str: d
            8 BINARY_ADD
            9 LOAD_FAST str: c
           10 LOAD_FAST str: f
           11 BINARY_ADD
           12 CALL_FUNCTION 2
           13 POP_TOP
           14 LOAD_CONST obj: N
           15 RETURN_VALUE

function eggs(x,y):

 L.  4      0 LOAD_GLOBAL str: inspect
            1 LOAD_ATTR str: currentframe
            2 CALL_FUNCTION 0
            3 STORE_GLOBAL str: fr
 L.  5      4 LOAD_GLOBAL str: inspect
            5 LOAD_ATTR str: stack
            6 CALL_FUNCTION 0
            7 STORE_GLOBAL str: st
 L.  6      8 LOAD_FAST str: x
            9 STORE_FAST str: p
 L.  7     10 LOAD_FAST str: y
           11 LOAD_CONST long: 0
           12 BINARY_FLOOR_DIVIDE
           13 STORE_FAST str: q
           14 LOAD_CONST obj: N
           15 RETURN_VALUE

class StupidGit:

build class function StupidGit():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  6      2 LOAD_CONST str: A longer,

    indented

    docstring.
            3 STORE_NAME str: __doc__
 L.  9      4 LOAD_CONST obj: c
            5 MAKE_FUNCTION 0
            6 STORE_NAME str: abuse
 L. 21      7 LOAD_CONST obj: c
            8 MAKE_FUNCTION 0
            9 STORE_NAME str: argue
           10 LOAD_LOCALS
           11 RETURN_VALUE

function abuse(self,a,b,c):

 L. 11      0 LOAD_FAST str: self
            1 LOAD_ATTR str: argue
            2 LOAD_FAST str: a
            3 LOAD_FAST str: b
            4 LOAD_FAST str: c
            5 CALL_FUNCTION 3
            6 POP_TOP
            7 LOAD_CONST obj: N
            8 RETURN_VALUE

function argue(self,a,b,c):

 L.  2      0 SETUP_EXCEPT 20 to 9
 L.  3      1 LOAD_GLOBAL str: spam
            2 LOAD_FAST str: a
            3 LOAD_FAST str: b
            4 LOAD_FAST str: c
            5 CALL_FUNCTION 3
            6 POP_TOP
            7 POP_BLOCK
            8 JUMP_FORWARD 37 to 24
 L.  4      9 POP_TOP
           10 POP_TOP
           11 POP_TOP
 L.  5     12 LOAD_GLOBAL str: sys
           13 LOAD_ATTR str: exc_info
           14 CALL_FUNCTION 0
           15 LOAD_FAST str: self
           16 STORE_ATTR str: ex
 L.  6     17 LOAD_GLOBAL str: inspect
           18 LOAD_ATTR str: trace
           19 CALL_FUNCTION 0
           20 LOAD_FAST str: self
           21 STORE_ATTR str: tr
           22 JUMP_FORWARD 1 to 24
           23 END_FINALLY to 24
           24 LOAD_CONST obj: N
           25 RETURN_VALUE

method abuse(self,a,b,c):

 L. 11      0 LOAD_FAST str: self
            1 LOAD_ATTR str: argue
            2 LOAD_FAST str: a
            3 LOAD_FAST str: b
            4 LOAD_FAST str: c
            5 CALL_FUNCTION 3
            6 POP_TOP
            7 LOAD_CONST obj: N
            8 RETURN_VALUE

method argue(self,a,b,c):

 L.  2      0 SETUP_EXCEPT 20 to 9
 L.  3      1 LOAD_GLOBAL str: spam
            2 LOAD_FAST str: a
            3 LOAD_FAST str: b
            4 LOAD_FAST str: c
            5 CALL_FUNCTION 3
            6 POP_TOP
            7 POP_BLOCK
            8 JUMP_FORWARD 37 to 24
 L.  4      9 POP_TOP
           10 POP_TOP
           11 POP_TOP
 L.  5     12 LOAD_GLOBAL str: sys
           13 LOAD_ATTR str: exc_info
           14 CALL_FUNCTION 0
           15 LOAD_FAST str: self
           16 STORE_ATTR str: ex
 L.  6     17 LOAD_GLOBAL str: inspect
           18 LOAD_ATTR str: trace
           19 CALL_FUNCTION 0
           20 LOAD_FAST str: self
           21 STORE_ATTR str: tr
           22 JUMP_FORWARD 1 to 24
           23 END_FINALLY to 24
           24 LOAD_CONST obj: N
           25 RETURN_VALUE


class MalodorousPervert:

build class function MalodorousPervert():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  2      2 LOAD_LOCALS
            3 RETURN_VALUE


class ParrotDroppings:

build class function ParrotDroppings():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  2      2 LOAD_LOCALS
            3 RETURN_VALUE


class FesteringGob:

build class function FesteringGob():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  2      2 LOAD_LOCALS
            3 RETURN_VALUE


