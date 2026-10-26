function <module>():

 L.  1      0 LOAD_CONST obj: c
            1 MAKE_FUNCTION 0
            2 STORE_NAME str: get_files
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

function get_files(self):

 L.  2      0 LOAD_GLOBAL str: sorted
            1 LOAD_CONST obj: c
            2 MAKE_FUNCTION 0
 L.  3      3 LOAD_GLOBAL str: os
            4 LOAD_ATTR str: listdir
            5 LOAD_GLOBAL str: os
            6 LOAD_ATTR str: curdir
            7 CALL_FUNCTION 1
            8 GET_ITER
            9 CALL_FUNCTION 1
           10 CALL_FUNCTION 1
           11 RETURN_VALUE

function <genexpr>(.0):

 L.  1      0 LOAD_FAST str: .0
            1 FOR_ITER 39 to 17
 L.  2      2 STORE_FAST str: fn
            3 LOAD_FAST str: fn
            4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: path
            6 LOAD_ATTR str: isdir
            7 LOAD_FAST str: fn
            8 CALL_FUNCTION 1
            9 POP_JUMP_IF_FALSE 36 to 12
           10 LOAD_CONST str: /
           11 JUMP_FORWARD 3 to 13
           12 LOAD_CONST str: 
           13 BINARY_ADD
           14 YIELD_VALUE
           15 POP_TOP
           16 JUMP_ABSOLUTE 3 to 1
           17 LOAD_CONST obj: N
           18 RETURN_VALUE

