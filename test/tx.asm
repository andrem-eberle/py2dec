function <module>():

 L.  1      0 LOAD_CONST str: 
Usage:

python -m test.regrtest [options] [test_name1 [test_name2 ...]]
python path/to/Lib/test/regrtest.py [options] [test_name1 [test_name2 ...]]


If no arguments or options are provided, finds all files matching
the pattern "test_*" in the Lib/test subdirectory and runs
them in alphabetical order (but see -M and -u, below, for exceptions).

For more rigorous testing, it is useful to use the following
command line:

python -E -tt -Wd -3 -m test.regrtest [options] [test_name1 ...]


Options:

-h/--
            1 STORE_NAME str: __doc__
 L.  3      2 LOAD_CONST long: -1
            3 LOAD_CONST obj: N
            4 IMPORT_NAME str: StringIO
            5 STORE_NAME str: StringIO
 L.  4      6 LOAD_CONST long: -1
            7 LOAD_CONST obj: N
            8 IMPORT_NAME str: datetime
            9 STORE_NAME str: datetime
 L.  5     10 LOAD_CONST long: -1
           11 LOAD_CONST obj: N
           12 IMPORT_NAME str: getopt
           13 STORE_NAME str: getopt
 L.  6     14 LOAD_CONST long: -1
           15 LOAD_CONST obj: N
           16 IMPORT_NAME str: imp
           17 STORE_NAME str: imp
 L.  7     18 LOAD_CONST long: -1
           19 LOAD_CONST obj: N
           20 IMPORT_NAME str: json
           21 STORE_NAME str: json
 L.  8     22 LOAD_CONST long: -1
           23 LOAD_CONST obj: N
           24 IMPORT_NAME str: math
           25 STORE_NAME str: math
 L.  9     26 LOAD_CONST long: -1
           27 LOAD_CONST obj: N
           28 IMPORT_NAME str: os
           29 STORE_NAME str: os
 L. 10     30 LOAD_CONST long: -1
           31 LOAD_CONST obj: N
           32 IMPORT_NAME str: platform
           33 STORE_NAME str: platform
 L. 11     34 LOAD_CONST long: -1
           35 LOAD_CONST obj: N
           36 IMPORT_NAME str: random
           37 STORE_NAME str: random
 L. 12     38 LOAD_CONST long: -1
           39 LOAD_CONST obj: N
           40 IMPORT_NAME str: re
           41 STORE_NAME str: re
 L. 13     42 LOAD_CONST long: -1
           43 LOAD_CONST obj: N
           44 IMPORT_NAME str: shutil
           45 STORE_NAME str: shutil
 L. 14     46 LOAD_CONST long: -1
           47 LOAD_CONST obj: N
           48 IMPORT_NAME str: sys
           49 STORE_NAME str: sys
 L. 15     50 LOAD_CONST long: -1
           51 LOAD_CONST obj: N
           52 IMPORT_NAME str: sysconfig
           53 STORE_NAME str: sysconfig
 L. 16     54 LOAD_CONST long: -1
           55 LOAD_CONST obj: N
           56 IMPORT_NAME str: tempfile
           57 STORE_NAME str: tempfile
 L. 17     58 LOAD_CONST long: -1
           59 LOAD_CONST obj: N
           60 IMPORT_NAME str: time
           61 STORE_NAME str: time
 L. 18     62 LOAD_CONST long: -1
           63 LOAD_CONST obj: N
           64 IMPORT_NAME str: traceback
           65 STORE_NAME str: traceback
 L. 19     66 LOAD_CONST long: -1
           67 LOAD_CONST obj: N
           68 IMPORT_NAME str: unittest
           69 STORE_NAME str: unittest
 L. 20     70 LOAD_CONST long: -1
           71 LOAD_CONST obj: N
           72 IMPORT_NAME str: warnings
           73 STORE_NAME str: warnings
 L. 33     74 SETUP_LOOP 119
           75 LOAD_NAME str: sys
           76 LOAD_ATTR str: modules
           77 LOAD_ATTR str: itervalues
           78 CALL_FUNCTION 0
           79 GET_ITER
           80 FOR_ITER 109 to 118
           81 STORE_NAME str: module
 L. 34     82 LOAD_NAME str: hasattr
           83 LOAD_NAME str: module
           84 LOAD_CONST str: __path__
           85 CALL_FUNCTION 2
           86 POP_JUMP_IF_FALSE 305 to 103
 L. 35     87 BUILD_LIST 0
           88 LOAD_NAME str: module
           89 LOAD_ATTR str: __path__
           90 GET_ITER
           91 FOR_ITER 24 to 100
           92 STORE_NAME str: path
           93 LOAD_NAME str: os
           94 LOAD_ATTR str: path
           95 LOAD_ATTR str: abspath
           96 LOAD_NAME str: path
           97 CALL_FUNCTION 1
           98 LIST_APPEND 2
           99 CONTINUE_LOOP 269 to 91
          100 LOAD_NAME str: module
          101 STORE_ATTR str: __path__
          102 JUMP_FORWARD 0 to 103
 L. 36    103 LOAD_NAME str: hasattr
          104 LOAD_NAME str: module
          105 LOAD_CONST str: __file__
          106 CALL_FUNCTION 2
          107 POP_JUMP_IF_FALSE 347 to 117
 L. 37    108 LOAD_NAME str: os
          109 LOAD_ATTR str: path
          110 LOAD_ATTR str: abspath
          111 LOAD_NAME str: module
          112 LOAD_ATTR str: __file__
          113 CALL_FUNCTION 1
          114 LOAD_NAME str: module
          115 STORE_ATTR str: __file__
          116 JUMP_FORWARD 0 to 117
          117 CONTINUE_LOOP 238 to 80
          118 POP_BLOCK
 L. 46    119 LOAD_NAME str: sys
          120 LOAD_ATTR str: platform
          121 LOAD_CONST str: darwin
          122 COMPARE_OP 2
          123 POP_JUMP_IF_FALSE 482 to 168
 L. 47    124 SETUP_EXCEPT 16 to 131
 L. 48    125 LOAD_CONST long: -1
          126 LOAD_CONST obj: N
          127 IMPORT_NAME str: resource
          128 STORE_NAME str: resource
          129 POP_BLOCK
          130 JUMP_FORWARD 17 to 140
 L. 49    131 DUP_TOP
          132 LOAD_NAME str: ImportError
          133 COMPARE_OP 10
          134 POP_JUMP_IF_FALSE 401 to 139
          135 POP_TOP
          136 POP_TOP
          137 POP_TOP
 L. 50    138 JUMP_FORWARD 78 to 167
          139 END_FINALLY to 140
 L. 52    140 LOAD_NAME str: resource
          141 LOAD_ATTR str: getrlimit
          142 LOAD_NAME str: resource
          143 LOAD_ATTR str: RLIMIT_STACK
          144 CALL_FUNCTION 1
          145 UNPACK_SEQUENCE 2
          146 STORE_NAME str: soft
          147 STORE_NAME str: hard
 L. 53    148 LOAD_NAME str: min
          149 LOAD_NAME str: hard
          150 LOAD_NAME str: max
          151 LOAD_NAME str: soft
          152 LOAD_CONST long: 1024
          153 LOAD_CONST long: 2048
          154 BINARY_MULTIPLY
          155 CALL_FUNCTION 2
          156 CALL_FUNCTION 2
          157 STORE_NAME str: newsoft
 L. 54    158 LOAD_NAME str: resource
          159 LOAD_ATTR str: setrlimit
          160 LOAD_NAME str: resource
          161 LOAD_ATTR str: RLIMIT_STACK
          162 LOAD_NAME str: newsoft
          163 LOAD_NAME str: hard
          164 BUILD_TUPLE 2
          165 CALL_FUNCTION 2
          166 POP_TOP
          167 JUMP_FORWARD 0 to 168
 L. 59    168 LOAD_NAME str: sys
          169 LOAD_ATTR str: platform
          170 LOAD_CONST str: win32
          171 COMPARE_OP 2
          172 POP_JUMP_IF_FALSE 536 to 190
 L. 60    173 SETUP_EXCEPT 16 to 180
 L. 61    174 LOAD_CONST long: -1
          175 LOAD_CONST obj: N
          176 IMPORT_NAME str: FixTk
          177 STORE_NAME str: FixTk
          178 POP_BLOCK
          179 JUMP_FORWARD 17 to 189
 L. 62    180 DUP_TOP
          181 LOAD_NAME str: Exception
          182 COMPARE_OP 10
          183 POP_JUMP_IF_FALSE 532 to 188
          184 POP_TOP
          185 POP_TOP
          186 POP_TOP
 L. 63    187 JUMP_FORWARD 1 to 189
          188 END_FINALLY to 189
          189 JUMP_FORWARD 0 to 190
 L. 66    190 LOAD_CONST long: 1
          191 STORE_NAME str: PASSED
 L. 67    192 LOAD_CONST long: 0
          193 STORE_NAME str: FAILED
 L. 68    194 LOAD_CONST long: -1
          195 STORE_NAME str: ENV_CHANGED
 L. 69    196 LOAD_CONST long: -2
          197 STORE_NAME str: SKIPPED
 L. 70    198 LOAD_CONST long: -3
          199 STORE_NAME str: RESOURCE_DENIED
 L. 71    200 LOAD_CONST long: -4
          201 STORE_NAME str: INTERRUPTED
 L. 72    202 LOAD_CONST long: -5
          203 STORE_NAME str: CHILD_ERROR
 L. 73    204 LOAD_CONST long: -6
          205 STORE_NAME str: TEST_DID_NOT_RUN
 L. 77    206 LOAD_CONST float: 30.000000
          207 STORE_NAME str: PROGRESS_MIN_TIME
 L. 80    208 LOAD_CONST float: 30.000000
          209 STORE_NAME str: PROGRESS_UPDATE
 L. 82    210 LOAD_CONST long: -1
          211 LOAD_CONST (str: support,)
          212 IMPORT_NAME str: test
          213 IMPORT_FROM str: support
          214 STORE_NAME str: support
          215 POP_TOP
 L. 84    216 LOAD_CONST str: audio
          217 LOAD_CONST str: curses
          218 LOAD_CONST str: largefile
          219 LOAD_CONST str: network
          220 LOAD_CONST str: bsddb
 L. 85    221 LOAD_CONST str: decimal
          222 LOAD_CONST str: cpu
          223 LOAD_CONST str: subprocess
          224 LOAD_CONST str: urlfetch
          225 LOAD_CONST str: gui
 L. 86    226 LOAD_CONST str: xpickle
          227 BUILD_TUPLE 11
          228 STORE_NAME str: ALL_RESOURCES
 L. 92    229 LOAD_NAME str: ALL_RESOURCES
          230 LOAD_CONST str: extralargefile
          231 BUILD_TUPLE 1
          232 BINARY_ADD
          233 STORE_NAME str: RESOURCE_NAMES
 L. 94    234 LOAD_NAME str: os
          235 LOAD_ATTR str: path
          236 LOAD_ATTR str: abspath
          237 LOAD_NAME str: tempfile
          238 LOAD_ATTR str: gettempdir
          239 CALL_FUNCTION 0
          240 CALL_FUNCTION 1
          241 STORE_GLOBAL str: TEMPDIR
 L. 97    242 LOAD_CONST str: 
          243 LOAD_CONST obj: c
          244 MAKE_FUNCTION 1
          245 STORE_NAME str: usage
 L.103    246 LOAD_CONST obj: c
          247 MAKE_FUNCTION 0
          248 STORE_NAME str: format_duration
 L.125    249 BUILD_MAP 8
 L.126    250 LOAD_CONST str: %s passed
          251 LOAD_NAME str: PASSED
          252 STORE_MAP
 L.127    253 LOAD_CONST str: %s failed
          254 LOAD_NAME str: FAILED
          255 STORE_MAP
 L.128    256 LOAD_CONST str: %s failed (env changed)
          257 LOAD_NAME str: ENV_CHANGED
          258 STORE_MAP
 L.129    259 LOAD_CONST str: %s skipped
          260 LOAD_NAME str: SKIPPED
          261 STORE_MAP
 L.130    262 LOAD_CONST str: %s skipped (resource denied)
          263 LOAD_NAME str: RESOURCE_DENIED
          264 STORE_MAP
 L.131    265 LOAD_CONST str: %s interrupted
          266 LOAD_NAME str: INTERRUPTED
          267 STORE_MAP
 L.132    268 LOAD_CONST str: %s crashed
          269 LOAD_NAME str: CHILD_ERROR
          270 STORE_MAP
 L.133    271 LOAD_CONST str: %s run no tests
          272 LOAD_NAME str: TEST_DID_NOT_RUN
          273 STORE_MAP
          274 STORE_NAME str: _FORMAT_TEST_RESULT
 L.137    275 LOAD_CONST obj: c
          276 MAKE_FUNCTION 0
          277 STORE_NAME str: format_test_result
 L.142    278 LOAD_CONST obj: c
          279 MAKE_FUNCTION 0
          280 STORE_NAME str: cpu_count
 L.160    281 LOAD_CONST obj: c
          282 MAKE_FUNCTION 0
          283 STORE_NAME str: unload_test_modules
 L.167    284 LOAD_NAME str: None
          285 LOAD_NAME str: None
          286 LOAD_CONST long: 0
          287 LOAD_NAME str: False
 L.168    288 LOAD_NAME str: False
          289 LOAD_NAME str: False
          290 LOAD_NAME str: False
          291 LOAD_NAME str: None
 L.169    292 LOAD_NAME str: False
          293 LOAD_NAME str: None
          294 LOAD_NAME str: False
          295 LOAD_CONST str: coverage
 L.170    296 LOAD_NAME str: False
          297 LOAD_NAME str: False
          298 LOAD_NAME str: False
          299 LOAD_NAME str: False
 L.171    300 LOAD_NAME str: None
          301 LOAD_NAME str: None
          302 LOAD_NAME str: False
          303 LOAD_NAME str: False
 L.172    304 LOAD_NAME str: False
          305 LOAD_NAME str: False
          306 LOAD_NAME str: False
          307 LOAD_NAME str: None
          308 LOAD_CONST obj: c
          309 MAKE_FUNCTION 24
          310 STORE_NAME str: main
 L.148    311 LOAD_CONST str: test_grammar
 L.149    312 LOAD_CONST str: test_opcodes
 L.150    313 LOAD_CONST str: test_dict
 L.151    314 LOAD_CONST str: test_builtin
 L.152    315 LOAD_CONST str: test_exceptions
 L.153    316 LOAD_CONST str: test_types
 L.154    317 LOAD_CONST str: test_unittest
 L.155    318 LOAD_CONST str: test_doctest
 L.156    319 LOAD_CONST str: test_doctest2
          320 BUILD_LIST 9
          321 STORE_NAME str: STDTESTS
 L.160    322 LOAD_CONST str: test_support
 L.161    323 LOAD_CONST str: test_future1
 L.162    324 LOAD_CONST str: test_future2
          325 BUILD_SET 3
          326 STORE_NAME str: NOTTESTS
 L.165    327 LOAD_NAME str: None
          328 LOAD_NAME str: STDTESTS
          329 LOAD_NAME str: NOTTESTS
          330 LOAD_CONST obj: c
          331 MAKE_FUNCTION 3
          332 STORE_NAME str: findtests
 L.178    333 LOAD_NAME str: False
          334 LOAD_NAME str: None
          335 LOAD_NAME str: False
 L.179    336 LOAD_NAME str: False
          337 LOAD_NAME str: None
          338 LOAD_NAME str: None
          339 LOAD_CONST obj: c
          340 MAKE_FUNCTION 6
          341 STORE_NAME str: runtest
 L.226    342 LOAD_CONST str: saved_test_environment
          343 BUILD_TUPLE 0
          344 LOAD_CONST obj: c
          345 MAKE_FUNCTION 0
          346 CALL_FUNCTION 0
          347 BUILD_CLASS
          348 STORE_NAME str: saved_test_environment
 L.122    349 LOAD_CONST obj: c
          350 MAKE_FUNCTION 0
          351 STORE_NAME str: post_test_cleanup
 L.125    352 LOAD_NAME str: False
          353 LOAD_NAME str: False
          354 LOAD_NAME str: None
          355 LOAD_CONST obj: c
          356 MAKE_FUNCTION 3
          357 STORE_NAME str: runtest_inner
 L.208    358 LOAD_CONST obj: c
          359 MAKE_FUNCTION 0
          360 STORE_NAME str: cleanup_test_droppings
 L.247    361 LOAD_CONST obj: c
          362 MAKE_FUNCTION 0
          363 STORE_NAME str: dash_R
 L.369    364 LOAD_CONST obj: c
          365 MAKE_FUNCTION 0
          366 STORE_NAME str: dash_R_cleanup
 L.397    367 LOAD_CONST obj: c
          368 MAKE_FUNCTION 0
          369 STORE_NAME str: clear_caches
 L.496    370 LOAD_CONST obj: c
          371 MAKE_FUNCTION 0
          372 STORE_NAME str: warm_caches
 L.508    373 LOAD_NAME str: None
          374 LOAD_CONST obj: c
          375 MAKE_FUNCTION 1
          376 STORE_NAME str: findtestdir
 L.511    377 LOAD_CONST obj: c
          378 MAKE_FUNCTION 0
          379 STORE_NAME str: removepy
 L.519    380 LOAD_CONST obj: c
          381 MAKE_FUNCTION 0
          382 STORE_NAME str: count
 L.525    383 LOAD_CONST long: 70
          384 LOAD_CONST long: 4
          385 LOAD_NAME str: None
          386 LOAD_CONST obj: c
          387 MAKE_FUNCTION 3
          388 STORE_NAME str: printlist
 L.539    389 LOAD_CONST obj: c
          390 MAKE_FUNCTION 0
          391 STORE_NAME str: get_abs_module
 L.546    392 LOAD_CONST obj: c
          393 MAKE_FUNCTION 0
          394 STORE_NAME str: _list_cases
 L.554    395 LOAD_CONST obj: c
          396 MAKE_FUNCTION 0
          397 STORE_NAME str: list_cases
 L.589    398 BUILD_MAP 16
 L.623    399 LOAD_CONST str: 
        test__locale
        test_bsddb185
        test_bsddb3
        test_commands
        test_crypt
        test_curses
        test_dbm
        test_dl
        test_fcntl
        test_fork1
        test_epoll
        test_gdbm
        test_grp
        test_ioctl
        test_largefile
        test_kqueue
        test_mhlib
        test_openpty
        test_ossaudiodev
        test_pipes
        test_poll
        test_posix
        test_pty
        test_pwd
        test_resource
        test_sign
          400 LOAD_CONST str: win32
          401 STORE_MAP
 L.632    402 LOAD_CONST str: 
        test_bsddb185
        test_curses
        test_dl
        test_largefile
        test_kqueue
        test_ossaudiodev
        
          403 LOAD_CONST str: linux2
          404 STORE_MAP
 L.646    405 LOAD_CONST str: 
        test_bsddb
        test_bsddb185
        test_dl
        test_epoll
        test_largefile
        test_kqueue
        test_minidom
        test_openpty
        test_pyexpat
        test_sax
        test_sundry
        
          406 LOAD_CONST str: unixware7
          407 STORE_MAP
 L.660    408 LOAD_CONST str: 
        test_bsddb
        test_bsddb185
        test_dl
        test_epoll
        test_largefile
        test_kqueue
        test_minidom
        test_openpty
        test_pyexpat
        test_sax
        test_sundry
        
          409 LOAD_CONST str: openunix8
          410 STORE_MAP
 L.683    411 LOAD_CONST str: 
        test_asynchat
        test_bsddb
        test_bsddb185
        test_dl
        test_fork1
        test_epoll
        test_gettext
        test_largefile
        test_locale
        test_kqueue
        test_minidom
        test_openpty
        test_pyexpat
        test_queue
        test_sax
        test_sundry
        test_thread
        test_threaded_import
        test_threadedtempfile
        test_threading
        
          412 LOAD_CONST str: sco_sv3
          413 STORE_MAP
 L.716    414 LOAD_CONST str: 
        test_asynchat
        test_atexit
        test_bsddb
        test_bsddb185
        test_bsddb3
        test_commands
        test_crypt
        test_dbm
        test_dl
        test_fcntl
        test_fork1
        test_epoll
        test_gdbm
        test_grp
        test_largefile
        test_locale
        test_kqueue
        test_mmap
        test_openpty
        test_poll
        test_popen2
        test_pty
        test_pwd
        test_strop
        test_sundry
        test_thread
   
          415 LOAD_CONST str: riscos
          416 STORE_MAP
 L.732    417 LOAD_CONST str: 
        test__locale
        test_bsddb
        test_bsddb3
        test_curses
        test_epoll
        test_gdb
        test_gdbm
        test_largefile
        test_locale
        test_kqueue
        test_minidom
        test_ossaudiodev
        test_poll
        
          418 LOAD_CONST str: darwin
          419 STORE_MAP
 L.746    420 LOAD_CONST str: 
        test_bsddb
        test_bsddb185
        test_curses
        test_dbm
        test_epoll
        test_kqueue
        test_gdbm
        test_gzip
        test_openpty
        test_zipfile
        test_zlib
        
          421 LOAD_CONST str: sunos5
          422 STORE_MAP
 L.765    423 LOAD_CONST str: 
        test_bsddb
        test_bsddb185
        test_curses
        test_dl
        test_epoll
        test_gdbm
        test_gzip
        test_largefile
        test_locale
        test_kqueue
        test_minidom
        test_openpty
        test_pyexpat
        test_sax
        test_zipfile
        test_zlib
        
          424 LOAD_CONST str: hp-ux11
          425 STORE_MAP
 L.781    426 LOAD_CONST str: 
        test_bsddb185
        test_curses
        test_dl
        test_gdbm
        test_epoll
        test_largefile
        test_locale
        test_kqueue
        test_mhlib
        test_mmap
        test_poll
        test_popen2
        test_resource
        
          427 LOAD_CONST str: atheos
          428 STORE_MAP
 L.795    429 LOAD_CONST str: 
        test_bsddb185
        test_bsddb3
        test_curses
        test_dbm
        test_epoll
        test_ioctl
        test_kqueue
        test_largefile
        test_locale
        test_ossaudiodev
        test_socketserver
        
          430 LOAD_CONST str: cygwin
          431 STORE_MAP
 L.814    432 LOAD_CONST str: 
        test_audioop
        test_bsddb185
        test_bsddb3
        test_commands
        test_curses
        test_dl
        test_epoll
        test_kqueue
        test_largefile
        test_mhlib
        test_mmap
        test_openpty
        test_ossaudiodev
        test_pty
        test_resource
        test_signal
        
          433 LOAD_CONST str: os2emx
          434 STORE_MAP
 L.833    435 LOAD_CONST str: 
        test_bsddb
        test_bsddb3
        test_epoll
        test_gdbm
        test_locale
        test_ossaudiodev
        test_pep277
        test_pty
        test_socketserver
        test_tcl
        test_tk
        test_ttk_guionly
        test_ttk_textonly
        test_timeout
        test_urllibnet
        test_multiprocessing
        
          436 LOAD_CONST str: freebsd4
          437 STORE_MAP
 L.852    438 LOAD_CONST str: 
        test_bsddb
        test_bsddb185
        test_bsddb3
        test_bz2
        test_dl
        test_epoll
        test_gdbm
        test_gzip
        test_kqueue
        test_ossaudiodev
        test_tcl
        test_tk
        test_ttk_guionly
        test_ttk_textonly
        test_zipimport
        test_zlib
        
          439 LOAD_CONST str: aix5
          440 STORE_MAP
 L.871    441 LOAD_CONST str: 
        test_ascii_formatd
        test_bsddb
        test_bsddb3
        test_ctypes
        test_dl
        test_epoll
        test_gdbm
        test_locale
        test_normalization
        test_ossaudiodev
        test_pep277
        test_tcl
        test_tk
        test_ttk_guionly
        test_ttk_textonly
        test_multiprocessing
        
          442 LOAD_CONST str: openbsd3
          443 STORE_MAP
 L.891    444 LOAD_CONST str: 
        test_ascii_formatd
        test_bsddb
        test_bsddb185
        test_bsddb3
        test_ctypes
        test_curses
        test_dl
        test_epoll
        test_gdbm
        test_locale
        test_ossaudiodev
        test_pep277
        test_tcl
        test_tk
        test_ttk_guionly
        test_ttk_textonly
        test_multiprocessing
        
          445 LOAD_CONST str: netbsd3
          446 STORE_MAP
          447 STORE_NAME str: _expectations
 L.893    448 LOAD_NAME str: _expectations
          449 LOAD_CONST str: freebsd4
          450 BINARY_SUBSCR
          451 LOAD_NAME str: _expectations
          452 LOAD_CONST str: freebsd5
          453 STORE_SUBSCR
 L.894    454 LOAD_NAME str: _expectations
          455 LOAD_CONST str: freebsd4
          456 BINARY_SUBSCR
          457 LOAD_NAME str: _expectations
          458 LOAD_CONST str: freebsd6
          459 STORE_SUBSCR
 L.895    460 LOAD_NAME str: _expectations
          461 LOAD_CONST str: freebsd4
          462 BINARY_SUBSCR
          463 LOAD_NAME str: _expectations
          464 LOAD_CONST str: freebsd7
          465 STORE_SUBSCR
 L.896    466 LOAD_NAME str: _expectations
          467 LOAD_CONST str: freebsd4
          468 BINARY_SUBSCR
          469 LOAD_NAME str: _expectations
          470 LOAD_CONST str: freebsd8
          471 STORE_SUBSCR
 L.898    472 LOAD_CONST str: _ExpectedSkips
          473 BUILD_TUPLE 0
          474 LOAD_CONST obj: c
          475 MAKE_FUNCTION 0
          476 CALL_FUNCTION 0
          477 BUILD_CLASS
          478 STORE_NAME str: _ExpectedSkips
 L.967    479 LOAD_CONST obj: c
          480 MAKE_FUNCTION 0
          481 STORE_NAME str: main_in_temp_cwd
 L.994    482 LOAD_NAME str: __name__
          483 LOAD_CONST str: __main__
          484 COMPARE_OP 2
          485 POP_JUMP_IF_FALSE 1417 to 509
 L.1000    486 LOAD_NAME str: os
          487 LOAD_ATTR str: path
          488 LOAD_ATTR str: abspath
          489 LOAD_GLOBAL str: __file__
          490 CALL_FUNCTION 1
          491 STORE_GLOBAL str: __file__
 L.1003    492 LOAD_GLOBAL str: __file__
          493 LOAD_NAME str: os
          494 LOAD_ATTR str: path
          495 LOAD_ATTR str: abspath
          496 LOAD_NAME str: sys
          497 LOAD_ATTR str: argv
          498 LOAD_CONST long: 0
          499 BINARY_SUBSCR
          500 CALL_FUNCTION 1
          501 COMPARE_OP 2
          502 POP_JUMP_IF_TRUE 1407 to 505
          503 LOAD_GLOBAL str: AssertionError
          504 RAISE_VARARGS 1
 L.1005    505 LOAD_NAME str: main_in_temp_cwd
          506 CALL_FUNCTION 0
          507 POP_TOP
          508 JUMP_FORWARD 0 to 509
          509 LOAD_CONST obj: N
          510 RETURN_VALUE

function usage(code,msg):

 L.  2      0 LOAD_GLOBAL str: __doc__
            1 PRINT_ITEM
            2 PRINT_NEWLINE
 L.  3      3 LOAD_FAST str: msg
            4 POP_JUMP_IF_FALSE 19 to 9
            5 LOAD_FAST str: msg
            6 PRINT_ITEM
            7 PRINT_NEWLINE
            8 JUMP_FORWARD 0 to 9
 L.  4      9 LOAD_GLOBAL str: sys
           10 LOAD_ATTR str: exit
           11 LOAD_FAST str: code
           12 CALL_FUNCTION 1
           13 POP_TOP
           14 LOAD_CONST obj: N
           15 RETURN_VALUE

function format_duration(seconds):

 L.  2      0 LOAD_GLOBAL str: int
            1 LOAD_GLOBAL str: math
            2 LOAD_ATTR str: ceil
            3 LOAD_FAST str: seconds
            4 LOAD_CONST float: 1000.000000
            5 BINARY_MULTIPLY
            6 CALL_FUNCTION 1
            7 CALL_FUNCTION 1
            8 STORE_FAST str: ms
 L.  3      9 LOAD_GLOBAL str: divmod
           10 LOAD_FAST str: ms
           11 LOAD_CONST long: 1000
           12 CALL_FUNCTION 2
           13 UNPACK_SEQUENCE 2
           14 STORE_FAST str: seconds
           15 STORE_FAST str: ms
 L.  4     16 LOAD_GLOBAL str: divmod
           17 LOAD_FAST str: seconds
           18 LOAD_CONST long: 60
           19 CALL_FUNCTION 2
           20 UNPACK_SEQUENCE 2
           21 STORE_FAST str: minutes
           22 STORE_FAST str: seconds
 L.  5     23 LOAD_GLOBAL str: divmod
           24 LOAD_FAST str: minutes
           25 LOAD_CONST long: 60
           26 CALL_FUNCTION 2
           27 UNPACK_SEQUENCE 2
           28 STORE_FAST str: hours
           29 STORE_FAST str: minutes
 L.  7     30 BUILD_LIST 0
           31 STORE_FAST str: parts
 L.  8     32 LOAD_FAST str: hours
           33 POP_JUMP_IF_FALSE 120 to 42
 L.  9     34 LOAD_FAST str: parts
           35 LOAD_ATTR str: append
           36 LOAD_CONST str: %s hour
           37 LOAD_FAST str: hours
           38 BINARY_MODULO
           39 CALL_FUNCTION 1
           40 POP_TOP
           41 JUMP_FORWARD 0 to 42
 L. 10     42 LOAD_FAST str: minutes
           43 POP_JUMP_IF_FALSE 146 to 52
 L. 11     44 LOAD_FAST str: parts
           45 LOAD_ATTR str: append
           46 LOAD_CONST str: %s min
           47 LOAD_FAST str: minutes
           48 BINARY_MODULO
           49 CALL_FUNCTION 1
           50 POP_TOP
           51 JUMP_FORWARD 0 to 52
 L. 12     52 LOAD_FAST str: seconds
           53 POP_JUMP_IF_FALSE 172 to 62
 L. 13     54 LOAD_FAST str: parts
           55 LOAD_ATTR str: append
           56 LOAD_CONST str: %s sec
           57 LOAD_FAST str: seconds
           58 BINARY_MODULO
           59 CALL_FUNCTION 1
           60 POP_TOP
           61 JUMP_FORWARD 0 to 62
 L. 14     62 LOAD_FAST str: ms
           63 POP_JUMP_IF_FALSE 198 to 72
 L. 15     64 LOAD_FAST str: parts
           65 LOAD_ATTR str: append
           66 LOAD_CONST str: %s ms
           67 LOAD_FAST str: ms
           68 BINARY_MODULO
           69 CALL_FUNCTION 1
           70 POP_TOP
           71 JUMP_FORWARD 0 to 72
 L. 16     72 LOAD_FAST str: parts
           73 POP_JUMP_IF_TRUE 208 to 76
 L. 17     74 LOAD_CONST str: 0 ms
           75 RETURN_VALUE to 76
 L. 19     76 LOAD_FAST str: parts
           77 LOAD_CONST long: 2
           78 SLICE_2
           79 STORE_FAST str: parts
 L. 20     80 LOAD_CONST str:  
           81 LOAD_ATTR str: join
           82 LOAD_FAST str: parts
           83 CALL_FUNCTION 1
           84 RETURN_VALUE

function format_test_result(test_name,result):

 L.  2      0 LOAD_GLOBAL str: _FORMAT_TEST_RESULT
            1 LOAD_ATTR str: get
            2 LOAD_FAST str: result
            3 LOAD_CONST str: %s
            4 CALL_FUNCTION 2
            5 STORE_FAST str: fmt
 L.  3      6 LOAD_FAST str: fmt
            7 LOAD_FAST str: test_name
            8 BINARY_MODULO
            9 RETURN_VALUE

function cpu_count():

 L.  3      0 SETUP_EXCEPT 17 to 8
 L.  4      1 LOAD_GLOBAL str: os
            2 LOAD_ATTR str: sysconf
            3 LOAD_CONST str: SC_NPROCESSORS_ONLN
            4 CALL_FUNCTION 1
            5 RETURN_VALUE to 6
            6 POP_BLOCK
            7 JUMP_FORWARD 23 to 19
 L.  5      8 DUP_TOP
            9 LOAD_GLOBAL str: AttributeError
           10 LOAD_GLOBAL str: ValueError
           11 BUILD_TUPLE 2
           12 COMPARE_OP 10
           13 POP_JUMP_IF_FALSE 42 to 18
           14 POP_TOP
           15 POP_TOP
           16 POP_TOP
 L.  6     17 JUMP_FORWARD 1 to 19
           18 END_FINALLY to 19
 L.  9     19 SETUP_EXCEPT 16 to 26
 L. 10     20 LOAD_CONST long: -1
           21 LOAD_CONST obj: N
           22 IMPORT_NAME str: multiprocessing
           23 STORE_FAST str: multiprocessing
           24 POP_BLOCK
           25 JUMP_FORWARD 17 to 35
 L. 11     26 DUP_TOP
           27 LOAD_GLOBAL str: ImportError
           28 COMPARE_OP 10
           29 POP_JUMP_IF_FALSE 78 to 34
           30 POP_TOP
           31 POP_TOP
           32 POP_TOP
 L. 12     33 JUMP_FORWARD 11 to 39
           34 END_FINALLY to 35
 L. 14     35 LOAD_FAST str: multiprocessing
           36 LOAD_ATTR str: cpu_count
           37 CALL_FUNCTION 0
           38 RETURN_VALUE to 39
 L. 16     39 LOAD_CONST obj: N
           40 RETURN_VALUE

function unload_test_modules(save_modules):

 L.  3      0 SETUP_LOOP 25
            1 LOAD_GLOBAL str: sys
            2 LOAD_ATTR str: modules
            3 LOAD_ATTR str: keys
            4 CALL_FUNCTION 0
            5 GET_ITER
            6 FOR_ITER 49 to 26
            7 STORE_FAST str: module
 L.  4      8 LOAD_FAST str: module
            9 LOAD_FAST str: save_modules
           10 COMPARE_OP 7
           11 POP_JUMP_IF_TRUE 16 to 13
           12 CONTINUE_LOOP 1 to 6
           13 LOAD_FAST str: module
           14 LOAD_ATTR str: startswith
           15 LOAD_CONST str: test.
           16 CALL_FUNCTION 1
           17 POP_JUMP_IF_TRUE 16 to 19
           18 CONTINUE_LOOP 1 to 6
 L.  5     19 LOAD_GLOBAL str: support
           20 LOAD_ATTR str: unload
           21 LOAD_FAST str: module
           22 CALL_FUNCTION 1
           23 POP_TOP
           24 CONTINUE_LOOP 16 to 6
           25 DUMMY 16 to 6
           26 POP_BLOCK
           27 LOAD_CONST obj: N
           28 RETURN_VALUE

function main(tests,testdir,verbose,quiet,exclude,single,randomize,fromfile,findleaks,use_resources,trace,coverdir,runleaks,huntrleaks,verbose2,print_slow,random_seed,use_mp,verbose3,forever,header,pgo,failfast,match_tests):

 L. 29      0 LOAD_GLOBAL str: time
            1 LOAD_ATTR str: time
            2 CALL_FUNCTION 0
            3 STORE_DEREF str: regrtest_start_time
 L. 31      4 LOAD_GLOBAL str: support
            5 LOAD_ATTR str: record_original_stdout
            6 LOAD_GLOBAL str: sys
            7 LOAD_ATTR str: stdout
            8 CALL_FUNCTION 1
            9 POP_TOP
 L. 32     10 SETUP_EXCEPT 143 to 60
 L. 33     11 LOAD_GLOBAL str: getopt
           12 LOAD_ATTR str: getopt
           13 LOAD_GLOBAL str: sys
           14 LOAD_ATTR str: argv
           15 LOAD_CONST long: 1
           16 SLICE_1
           17 LOAD_CONST str: hvqxsSrf:lu:t:TD:NLR:FwWM:j:PGm:
 L. 34     18 LOAD_CONST str: help
           19 LOAD_CONST str: verbose
           20 LOAD_CONST str: verbose2
           21 LOAD_CONST str: verbose3
           22 LOAD_CONST str: quiet
 L. 35     23 LOAD_CONST str: exclude
           24 LOAD_CONST str: single
           25 LOAD_CONST str: slow
           26 LOAD_CONST str: slowest
           27 LOAD_CONST str: randomize
           28 LOAD_CONST str: fromfile=
 L. 36     29 LOAD_CONST str: findleaks
 L. 37     30 LOAD_CONST str: use=
           31 LOAD_CONST str: threshold=
           32 LOAD_CONST str: trace
           33 LOAD_CONST str: coverdir=
           34 LOAD_CONST str: nocoverdir
 L. 38     35 LOAD_CONST str: runleaks
           36 LOAD_CONST str: huntrleaks=
           37 LOAD_CONST str: memlimit=
           38 LOAD_CONST str: randseed=
 L. 39     39 LOAD_CONST str: multiprocess=
           40 LOAD_CONST str: slaveargs=
           41 LOAD_CONST str: forever
           42 LOAD_CONST str: header
           43 LOAD_CONST str: pgo
 L. 40     44 LOAD_CONST str: failfast
           45 LOAD_CONST str: match=
           46 LOAD_CONST str: testdir=
           47 LOAD_CONST str: list-tests
           48 LOAD_CONST str: list-cases
 L. 41     49 LOAD_CONST str: coverage
           50 LOAD_CONST str: matchfile=
           51 LOAD_CONST str: fail-env-changed
           52 LOAD_CONST str: cleanup
           53 BUILD_LIST 35
           54 CALL_FUNCTION 3
           55 UNPACK_SEQUENCE 2
           56 STORE_FAST str: opts
           57 STORE_FAST str: args
           58 POP_BLOCK
           59 JUMP_FORWARD 35 to 75
 L. 42     60 DUP_TOP
           61 LOAD_GLOBAL str: getopt
           62 LOAD_ATTR str: error
           63 COMPARE_OP 10
           64 POP_JUMP_IF_FALSE 208 to 74
           65 POP_TOP
           66 STORE_FAST str: msg
           67 POP_TOP
 L. 43     68 LOAD_GLOBAL str: usage
           69 LOAD_CONST long: 2
           70 LOAD_FAST str: msg
           71 CALL_FUNCTION 2
           72 POP_TOP
           73 JUMP_FORWARD 1 to 75
           74 END_FINALLY to 75
 L. 46     75 LOAD_FAST str: random_seed
           76 LOAD_CONST obj: N
           77 COMPARE_OP 8
           78 POP_JUMP_IF_FALSE 239 to 85
 L. 47     79 LOAD_GLOBAL str: random
           80 LOAD_ATTR str: randrange
           81 LOAD_CONST long: 10000000
           82 CALL_FUNCTION 1
           83 STORE_FAST str: random_seed
           84 JUMP_FORWARD 0 to 85
 L. 48     85 LOAD_DEREF str: use_resources
           86 LOAD_CONST obj: N
           87 COMPARE_OP 8
           88 POP_JUMP_IF_FALSE 260 to 92
 L. 49     89 BUILD_LIST 0
           90 STORE_DEREF str: use_resources
           91 JUMP_FORWARD 0 to 92
 L. 50     92 LOAD_CONST obj: N
           93 STORE_FAST str: slaveargs
 L. 51     94 LOAD_GLOBAL str: False
           95 STORE_FAST str: list_tests
 L. 52     96 LOAD_GLOBAL str: False
           97 STORE_FAST str: list_cases_opt
 L. 53     98 LOAD_GLOBAL str: False
           99 STORE_DEREF str: fail_env_changed
 L. 54    100 LOAD_GLOBAL str: False
          101 STORE_FAST str: cleanup_tests
 L. 55    102 SETUP_LOOP 581
          103 LOAD_FAST str: opts
          104 GET_ITER
          105 FOR_ITER 1340 to 581
          106 UNPACK_SEQUENCE 2
          107 STORE_FAST str: o
          108 STORE_FAST str: a
 L. 56    109 LOAD_FAST str: o
          110 LOAD_CONST (str: -h,str: --help,)
          111 COMPARE_OP 6
          112 POP_JUMP_IF_FALSE 334 to 118
 L. 57    113 LOAD_GLOBAL str: usage
          114 LOAD_CONST long: 0
          115 CALL_FUNCTION 1
          116 POP_TOP
          117 CONTINUE_LOOP 297 to 105
 L. 58    118 LOAD_FAST str: o
          119 LOAD_CONST (str: -v,str: --verbose,)
          120 COMPARE_OP 6
          121 POP_JUMP_IF_FALSE 359 to 127
 L. 59    122 LOAD_DEREF str: verbose
          123 LOAD_CONST long: 1
          124 INPLACE_ADD
          125 STORE_DEREF str: verbose
          126 CONTINUE_LOOP 297 to 105
 L. 60    127 LOAD_FAST str: o
          128 LOAD_CONST (str: -w,str: --verbose2,)
          129 COMPARE_OP 6
          130 POP_JUMP_IF_FALSE 380 to 134
 L. 61    131 LOAD_GLOBAL str: True
          132 STORE_FAST str: verbose2
          133 CONTINUE_LOOP 297 to 105
 L. 62    134 LOAD_FAST str: o
          135 LOAD_CONST (str: -W,str: --verbose3,)
          136 COMPARE_OP 6
          137 POP_JUMP_IF_FALSE 401 to 141
 L. 63    138 LOAD_GLOBAL str: True
          139 STORE_FAST str: verbose3
          140 CONTINUE_LOOP 297 to 105
 L. 64    141 LOAD_FAST str: o
          142 LOAD_CONST (str: -G,str: --failfast,)
          143 COMPARE_OP 6
          144 POP_JUMP_IF_FALSE 422 to 148
 L. 65    145 LOAD_GLOBAL str: True
          146 STORE_DEREF str: failfast
          147 CONTINUE_LOOP 297 to 105
 L. 66    148 LOAD_FAST str: o
          149 LOAD_CONST (str: -q,str: --quiet,)
          150 COMPARE_OP 6
          151 POP_JUMP_IF_FALSE 449 to 157
 L. 67    152 LOAD_GLOBAL str: True
          153 STORE_DEREF str: quiet
 L. 68    154 LOAD_CONST long: 0
          155 STORE_DEREF str: verbose
          156 CONTINUE_LOOP 297 to 105
 L. 69    157 LOAD_FAST str: o
          158 LOAD_CONST (str: -x,str: --exclude,)
          159 COMPARE_OP 6
          160 POP_JUMP_IF_FALSE 470 to 164
 L. 70    161 LOAD_GLOBAL str: True
          162 STORE_FAST str: exclude
          163 CONTINUE_LOOP 297 to 105
 L. 71    164 LOAD_FAST str: o
          165 LOAD_CONST (str: -s,str: --single,)
          166 COMPARE_OP 6
          167 POP_JUMP_IF_FALSE 491 to 171
 L. 72    168 LOAD_GLOBAL str: True
          169 STORE_FAST str: single
          170 CONTINUE_LOOP 297 to 105
 L. 73    171 LOAD_FAST str: o
          172 LOAD_CONST (str: -S,str: --slow,str: --slowest,)
          173 COMPARE_OP 6
          174 POP_JUMP_IF_FALSE 512 to 178
 L. 74    175 LOAD_GLOBAL str: True
          176 STORE_DEREF str: print_slow
          177 CONTINUE_LOOP 297 to 105
 L. 75    178 LOAD_FAST str: o
          179 LOAD_CONST (str: -r,str: --randomize,)
          180 COMPARE_OP 6
          181 POP_JUMP_IF_FALSE 533 to 185
 L. 76    182 LOAD_GLOBAL str: True
          183 STORE_FAST str: randomize
          184 CONTINUE_LOOP 297 to 105
 L. 77    185 LOAD_FAST str: o
          186 LOAD_CONST str: --randseed
          187 COMPARE_OP 2
          188 POP_JUMP_IF_FALSE 560 to 194
 L. 78    189 LOAD_GLOBAL str: int
          190 LOAD_FAST str: a
          191 CALL_FUNCTION 1
          192 STORE_FAST str: random_seed
          193 CONTINUE_LOOP 297 to 105
 L. 79    194 LOAD_FAST str: o
          195 LOAD_CONST (str: -f,str: --fromfile,)
          196 COMPARE_OP 6
          197 POP_JUMP_IF_FALSE 581 to 201
 L. 80    198 LOAD_FAST str: a
          199 STORE_FAST str: fromfile
          200 CONTINUE_LOOP 297 to 105
 L. 81    201 LOAD_FAST str: o
          202 LOAD_CONST (str: -m,str: --match,)
          203 COMPARE_OP 6
          204 POP_JUMP_IF_FALSE 630 to 218
 L. 82    205 LOAD_DEREF str: match_tests
          206 LOAD_CONST obj: N
          207 COMPARE_OP 8
          208 POP_JUMP_IF_FALSE 614 to 212
 L. 83    209 BUILD_LIST 0
          210 STORE_DEREF str: match_tests
          211 JUMP_FORWARD 0 to 212
 L. 84    212 LOAD_DEREF str: match_tests
          213 LOAD_ATTR str: append
          214 LOAD_FAST str: a
          215 CALL_FUNCTION 1
          216 POP_TOP
          217 CONTINUE_LOOP 297 to 105
 L. 85    218 LOAD_FAST str: o
          219 LOAD_CONST str: --matchfile
          220 COMPARE_OP 2
          221 POP_JUMP_IF_FALSE 747 to 261
 L. 86    222 LOAD_DEREF str: match_tests
          223 LOAD_CONST obj: N
          224 COMPARE_OP 8
          225 POP_JUMP_IF_FALSE 663 to 229
 L. 87    226 BUILD_LIST 0
          227 STORE_DEREF str: match_tests
          228 JUMP_FORWARD 0 to 229
 L. 88    229 LOAD_GLOBAL str: os
          230 LOAD_ATTR str: path
          231 LOAD_ATTR str: join
          232 LOAD_GLOBAL str: support
          233 LOAD_ATTR str: SAVEDCWD
          234 LOAD_FAST str: a
          235 CALL_FUNCTION 2
          236 STORE_FAST str: filename
 L. 89    237 LOAD_GLOBAL str: open
          238 LOAD_FAST str: filename
          239 CALL_FUNCTION 1
          240 SETUP_WITH 17
          241 STORE_FAST str: fp
 L. 90    242 SETUP_LOOP 256
          243 LOAD_FAST str: fp
          244 GET_ITER
          245 FOR_ITER 25 to 255
          246 STORE_FAST str: line
 L. 91    247 LOAD_DEREF str: match_tests
          248 LOAD_ATTR str: append
          249 LOAD_FAST str: line
          250 LOAD_ATTR str: strip
          251 CALL_FUNCTION 0
          252 CALL_FUNCTION 1
          253 POP_TOP
          254 CONTINUE_LOOP 709 to 245
          255 POP_BLOCK
          256 POP_BLOCK
          257 LOAD_CONST obj: N
          258 WITH_CLEANUP
          259 END_FINALLY to 260
          260 CONTINUE_LOOP 297 to 105
 L. 92    261 LOAD_FAST str: o
          262 LOAD_CONST (str: -l,str: --findleaks,)
          263 COMPARE_OP 6
          264 POP_JUMP_IF_FALSE 768 to 268
 L. 93    265 LOAD_GLOBAL str: True
          266 STORE_FAST str: findleaks
          267 CONTINUE_LOOP 297 to 105
 L. 94    268 LOAD_FAST str: o
          269 LOAD_CONST (str: -L,str: --runleaks,)
          270 COMPARE_OP 6
          271 POP_JUMP_IF_FALSE 789 to 275
 L. 95    272 LOAD_GLOBAL str: True
          273 STORE_FAST str: runleaks
          274 CONTINUE_LOOP 297 to 105
 L. 96    275 LOAD_FAST str: o
          276 LOAD_CONST (str: -t,str: --threshold,)
          277 COMPARE_OP 6
          278 POP_JUMP_IF_FALSE 835 to 291
 L. 97    279 LOAD_CONST long: -1
          280 LOAD_CONST obj: N
          281 IMPORT_NAME str: gc
          282 STORE_FAST str: gc
 L. 98    283 LOAD_FAST str: gc
          284 LOAD_ATTR str: set_threshold
          285 LOAD_GLOBAL str: int
          286 LOAD_FAST str: a
          287 CALL_FUNCTION 1
          288 CALL_FUNCTION 1
          289 POP_TOP
          290 CONTINUE_LOOP 297 to 105
 L. 99    291 LOAD_FAST str: o
          292 LOAD_CONST (str: -T,str: --coverage,)
          293 COMPARE_OP 6
          294 POP_JUMP_IF_FALSE 856 to 298
 L.100    295 LOAD_GLOBAL str: True
          296 STORE_FAST str: trace
          297 CONTINUE_LOOP 297 to 105
 L.101    298 LOAD_FAST str: o
          299 LOAD_CONST (str: -D,str: --coverdir,)
          300 COMPARE_OP 6
          301 POP_JUMP_IF_FALSE 898 to 312
 L.102    302 LOAD_GLOBAL str: os
          303 LOAD_ATTR str: path
          304 LOAD_ATTR str: join
          305 LOAD_GLOBAL str: os
          306 LOAD_ATTR str: getcwd
          307 CALL_FUNCTION 0
          308 LOAD_FAST str: a
          309 CALL_FUNCTION 2
          310 STORE_FAST str: coverdir
          311 CONTINUE_LOOP 297 to 105
 L.103    312 LOAD_FAST str: o
          313 LOAD_CONST (str: -N,str: --nocoverdir,)
          314 COMPARE_OP 6
          315 POP_JUMP_IF_FALSE 919 to 319
 L.104    316 LOAD_CONST obj: N
          317 STORE_FAST str: coverdir
          318 CONTINUE_LOOP 297 to 105
 L.105    319 LOAD_FAST str: o
          320 LOAD_CONST (str: -R,str: --huntrleaks,)
          321 COMPARE_OP 6
          322 POP_JUMP_IF_FALSE 1123 to 397
 L.106    323 LOAD_FAST str: a
          324 LOAD_ATTR str: split
          325 LOAD_CONST str: :
          326 CALL_FUNCTION 1
          327 STORE_DEREF str: huntrleaks
 L.107    328 LOAD_GLOBAL str: len
          329 LOAD_DEREF str: huntrleaks
          330 CALL_FUNCTION 1
          331 LOAD_CONST (long: 2,long: 3,)
          332 COMPARE_OP 7
          333 POP_JUMP_IF_FALSE 989 to 345
 L.108    334 LOAD_FAST str: a
          335 PRINT_ITEM
          336 LOAD_DEREF str: huntrleaks
          337 PRINT_ITEM
          338 PRINT_NEWLINE
 L.109    339 LOAD_GLOBAL str: usage
          340 LOAD_CONST long: 2
          341 LOAD_CONST str: -R takes 2 or 3 colon-separated arguments
          342 CALL_FUNCTION 2
          343 POP_TOP
          344 JUMP_FORWARD 0 to 345
 L.110    345 LOAD_DEREF str: huntrleaks
          346 LOAD_CONST long: 0
          347 BINARY_SUBSCR
          348 POP_JUMP_IF_TRUE 1012 to 354
 L.111    349 LOAD_CONST long: 5
          350 LOAD_DEREF str: huntrleaks
          351 LOAD_CONST long: 0
          352 STORE_SUBSCR
          353 JUMP_FORWARD 20 to 362
 L.113    354 LOAD_GLOBAL str: int
          355 LOAD_DEREF str: huntrleaks
          356 LOAD_CONST long: 0
          357 BINARY_SUBSCR
          358 CALL_FUNCTION 1
          359 LOAD_DEREF str: huntrleaks
          360 LOAD_CONST long: 0
          361 STORE_SUBSCR
 L.114    362 LOAD_DEREF str: huntrleaks
          363 LOAD_CONST long: 1
          364 BINARY_SUBSCR
          365 POP_JUMP_IF_TRUE 1055 to 371
 L.115    366 LOAD_CONST long: 4
          367 LOAD_DEREF str: huntrleaks
          368 LOAD_CONST long: 1
          369 STORE_SUBSCR
          370 JUMP_FORWARD 20 to 379
 L.117    371 LOAD_GLOBAL str: int
          372 LOAD_DEREF str: huntrleaks
          373 LOAD_CONST long: 1
          374 BINARY_SUBSCR
          375 CALL_FUNCTION 1
          376 LOAD_DEREF str: huntrleaks
          377 LOAD_CONST long: 1
          378 STORE_SUBSCR
 L.118    379 LOAD_GLOBAL str: len
          380 LOAD_DEREF str: huntrleaks
          381 CALL_FUNCTION 1
          382 LOAD_CONST long: 2
          383 COMPARE_OP 2
          384 POP_JUMP_IF_TRUE 1104 to 390
          385 LOAD_DEREF str: huntrleaks
          386 LOAD_CONST long: 2
          387 BINARY_SUBSCR
          388 UNARY_NOT
          389 POP_JUMP_IF_FALSE 1637 to 580
 L.119    390 LOAD_CONST str: reflog.txt
          391 BUILD_LIST 1
          392 LOAD_DEREF str: huntrleaks
          393 LOAD_CONST long: 2
          394 STORE_SLICE_1
          395 JUMP_ABSOLUTE 1637 to 580
          396 DUMMY 297 to 105
 L.120    397 LOAD_FAST str: o
          398 LOAD_CONST (str: -M,str: --memlimit,)
          399 COMPARE_OP 6
          400 POP_JUMP_IF_FALSE 1151 to 407
 L.121    401 LOAD_GLOBAL str: support
          402 LOAD_ATTR str: set_memlimit
          403 LOAD_FAST str: a
          404 CALL_FUNCTION 1
          405 POP_TOP
          406 CONTINUE_LOOP 297 to 105
 L.122    407 LOAD_FAST str: o
          408 LOAD_CONST (str: -u,str: --use,)
          409 COMPARE_OP 6
          410 POP_JUMP_IF_FALSE 1386 to 493
 L.123    411 BUILD_LIST 0
          412 LOAD_FAST str: a
          413 LOAD_ATTR str: split
          414 LOAD_CONST str: ,
          415 CALL_FUNCTION 1
          416 GET_ITER
          417 FOR_ITER 18 to 424
          418 STORE_FAST str: x
          419 LOAD_FAST str: x
          420 LOAD_ATTR str: lower
          421 CALL_FUNCTION 0
          422 LIST_APPEND 2
          423 CONTINUE_LOOP 1179 to 417
          424 STORE_FAST str: u
 L.124    425 SETUP_LOOP 579
          426 LOAD_FAST str: u
          427 GET_ITER
          428 FOR_ITER 169 to 491
          429 STORE_FAST str: r
 L.125    430 LOAD_FAST str: r
          431 LOAD_CONST str: all
          432 COMPARE_OP 2
          433 POP_JUMP_IF_FALSE 1241 to 439
 L.126    434 LOAD_GLOBAL str: ALL_RESOURCES
          435 LOAD_DEREF str: use_resources
          436 STORE_SLICE
 L.127    437 CONTINUE_LOOP 1210 to 428
          438 JUMP_FORWARD 0 to 439
 L.128    439 LOAD_GLOBAL str: False
          440 STORE_FAST str: remove
 L.129    441 LOAD_FAST str: r
          442 LOAD_CONST long: 0
          443 BINARY_SUBSCR
          444 LOAD_CONST str: -
          445 COMPARE_OP 2
          446 POP_JUMP_IF_FALSE 1282 to 454
 L.130    447 LOAD_GLOBAL str: True
          448 STORE_FAST str: remove
 L.131    449 LOAD_FAST str: r
          450 LOAD_CONST long: 1
          451 SLICE_1
          452 STORE_FAST str: r
          453 JUMP_FORWARD 0 to 454
 L.132    454 LOAD_FAST str: r
          455 LOAD_GLOBAL str: RESOURCE_NAMES
          456 COMPARE_OP 7
          457 POP_JUMP_IF_FALSE 1314 to 466
 L.133    458 LOAD_GLOBAL str: usage
          459 LOAD_CONST long: 1
          460 LOAD_CONST str: Invalid -u/--use option: 
          461 LOAD_FAST str: a
          462 BINARY_ADD
          463 CALL_FUNCTION 2
          464 POP_TOP
          465 JUMP_FORWARD 0 to 466
 L.134    466 LOAD_FAST str: remove
          467 POP_JUMP_IF_FALSE 1351 to 479
 L.135    468 LOAD_FAST str: r
          469 LOAD_DEREF str: use_resources
          470 COMPARE_OP 6
          471 POP_JUMP_IF_FALSE 1379 to 490
 L.136    472 LOAD_DEREF str: use_resources
          473 LOAD_ATTR str: remove
          474 LOAD_FAST str: r
          475 CALL_FUNCTION 1
          476 POP_TOP
          477 JUMP_ABSOLUTE 1379 to 490
          478 DUMMY 1210 to 428
 L.137    479 LOAD_FAST str: r
          480 LOAD_DEREF str: use_resources
          481 COMPARE_OP 7
          482 POP_JUMP_IF_TRUE 1210 to 484
          483 CONTINUE_LOOP 1 to 428
 L.138    484 LOAD_DEREF str: use_resources
          485 LOAD_ATTR str: append
          486 LOAD_FAST str: r
          487 CALL_FUNCTION 1
          488 POP_TOP
          489 CONTINUE_LOOP 1210 to 428
          490 CONTINUE_LOOP 1210 to 428
          491 POP_BLOCK
          492 CONTINUE_LOOP 297 to 105
 L.139    493 LOAD_FAST str: o
          494 LOAD_CONST (str: -F,str: --forever,)
          495 COMPARE_OP 6
          496 POP_JUMP_IF_FALSE 1407 to 500
 L.140    497 LOAD_GLOBAL str: True
          498 STORE_FAST str: forever
          499 CONTINUE_LOOP 297 to 105
 L.141    500 LOAD_FAST str: o
          501 LOAD_CONST (str: -j,str: --multiprocess,)
          502 COMPARE_OP 6
          503 POP_JUMP_IF_FALSE 1434 to 509
 L.142    504 LOAD_GLOBAL str: int
          505 LOAD_FAST str: a
          506 CALL_FUNCTION 1
          507 STORE_FAST str: use_mp
          508 CONTINUE_LOOP 297 to 105
 L.143    509 LOAD_FAST str: o
          510 LOAD_CONST str: --header
          511 COMPARE_OP 2
          512 POP_JUMP_IF_FALSE 1455 to 516
 L.144    513 LOAD_GLOBAL str: True
          514 STORE_FAST str: header
          515 CONTINUE_LOOP 297 to 105
 L.145    516 LOAD_FAST str: o
          517 LOAD_CONST str: --slaveargs
          518 COMPARE_OP 2
          519 POP_JUMP_IF_FALSE 1476 to 523
 L.146    520 LOAD_FAST str: a
          521 STORE_FAST str: slaveargs
          522 CONTINUE_LOOP 297 to 105
 L.147    523 LOAD_FAST str: o
          524 LOAD_CONST (str: -P,str: --pgo,)
          525 COMPARE_OP 6
          526 POP_JUMP_IF_FALSE 1497 to 530
 L.148    527 LOAD_GLOBAL str: True
          528 STORE_DEREF str: pgo
          529 CONTINUE_LOOP 297 to 105
 L.149    530 LOAD_FAST str: o
          531 LOAD_CONST str: --testdir
          532 COMPARE_OP 2
          533 POP_JUMP_IF_FALSE 1518 to 537
 L.150    534 LOAD_FAST str: a
          535 STORE_DEREF str: testdir
          536 CONTINUE_LOOP 297 to 105
 L.151    537 LOAD_FAST str: o
          538 LOAD_CONST str: --list-tests
          539 COMPARE_OP 2
          540 POP_JUMP_IF_FALSE 1539 to 544
 L.152    541 LOAD_GLOBAL str: True
          542 STORE_FAST str: list_tests
          543 CONTINUE_LOOP 297 to 105
 L.153    544 LOAD_FAST str: o
          545 LOAD_CONST str: --list-cases
          546 COMPARE_OP 2
          547 POP_JUMP_IF_FALSE 1560 to 551
 L.154    548 LOAD_GLOBAL str: True
          549 STORE_FAST str: list_cases_opt
          550 CONTINUE_LOOP 297 to 105
 L.155    551 LOAD_FAST str: o
          552 LOAD_CONST str: --fail-env-changed
          553 COMPARE_OP 2
          554 POP_JUMP_IF_FALSE 1581 to 558
 L.156    555 LOAD_GLOBAL str: True
          556 STORE_DEREF str: fail_env_changed
          557 CONTINUE_LOOP 297 to 105
 L.157    558 LOAD_FAST str: o
          559 LOAD_CONST str: --cleanup
          560 COMPARE_OP 2
          561 POP_JUMP_IF_FALSE 1602 to 565
 L.158    562 LOAD_GLOBAL str: True
          563 STORE_FAST str: cleanup_tests
          564 CONTINUE_LOOP 297 to 105
 L.160    565 LOAD_GLOBAL str: sys
          566 LOAD_ATTR str: stderr
          567 DUP_TOP
          568 LOAD_CONST str: No handler for option {}.  Please report this as a bug at http://bugs.python.org.
          569 LOAD_ATTR str: format
 L.161    570 LOAD_FAST str: o
          571 CALL_FUNCTION 1
          572 ROT_TWO
          573 PRINT_ITEM_TO
          574 PRINT_NEWLINE_TO
 L.162    575 LOAD_GLOBAL str: sys
          576 LOAD_ATTR str: exit
          577 LOAD_CONST long: 1
          578 CALL_FUNCTION 1
          579 POP_TOP
          580 CONTINUE_LOOP 297 to 105
          581 POP_BLOCK
 L.163    582 LOAD_FAST str: single
          583 POP_JUMP_IF_FALSE 1669 to 592
          584 LOAD_FAST str: fromfile
          585 POP_JUMP_IF_FALSE 1669 to 592
 L.164    586 LOAD_GLOBAL str: usage
          587 LOAD_CONST long: 2
          588 LOAD_CONST str: -s and -f don't go together!
          589 CALL_FUNCTION 2
          590 POP_TOP
          591 JUMP_FORWARD 0 to 592
 L.165    592 LOAD_FAST str: use_mp
          593 POP_JUMP_IF_FALSE 1697 to 602
          594 LOAD_FAST str: trace
          595 POP_JUMP_IF_FALSE 1697 to 602
 L.166    596 LOAD_GLOBAL str: usage
          597 LOAD_CONST long: 2
          598 LOAD_CONST str: -T and -j don't go together!
          599 CALL_FUNCTION 2
          600 POP_TOP
          601 JUMP_FORWARD 0 to 602
 L.167    602 LOAD_FAST str: use_mp
          603 POP_JUMP_IF_FALSE 1725 to 612
          604 LOAD_FAST str: findleaks
          605 POP_JUMP_IF_FALSE 1725 to 612
 L.168    606 LOAD_GLOBAL str: usage
          607 LOAD_CONST long: 2
          608 LOAD_CONST str: -l and -j don't go together!
          609 CALL_FUNCTION 2
          610 POP_TOP
          611 JUMP_FORWARD 0 to 612
 L.169    612 LOAD_DEREF str: failfast
          613 POP_JUMP_IF_FALSE 1757 to 624
          614 LOAD_DEREF str: verbose
          615 JUMP_IF_TRUE_OR_POP 1740
          616 LOAD_FAST str: verbose3
          617 UNARY_NOT
          618 POP_JUMP_IF_FALSE 1757 to 624
 L.170    619 LOAD_GLOBAL str: usage
          620 LOAD_CONST str: -G/--failfast needs either -v or -W
          621 CALL_FUNCTION 1
          622 POP_TOP
          623 JUMP_FORWARD 0 to 624
 L.172    624 LOAD_DEREF str: testdir
          625 POP_JUMP_IF_FALSE 1803 to 640
 L.173    626 LOAD_GLOBAL str: os
          627 LOAD_ATTR str: path
          628 LOAD_ATTR str: abspath
          629 LOAD_DEREF str: testdir
          630 CALL_FUNCTION 1
          631 STORE_DEREF str: testdir
 L.177    632 LOAD_GLOBAL str: sys
          633 LOAD_ATTR str: path
          634 LOAD_ATTR str: insert
          635 LOAD_CONST long: 0
          636 LOAD_DEREF str: testdir
          637 CALL_FUNCTION 2
          638 POP_TOP
          639 JUMP_FORWARD 0 to 640
 L.180    640 LOAD_GLOBAL str: os
          641 LOAD_ATTR str: path
          642 LOAD_ATTR str: abspath
          643 LOAD_GLOBAL str: os
          644 LOAD_ATTR str: path
          645 LOAD_ATTR str: dirname
          646 LOAD_GLOBAL str: __file__
          647 CALL_FUNCTION 1
          648 CALL_FUNCTION 1
          649 STORE_FAST str: regrtest_dir
 L.181    650 SETUP_LOOP 676
          651 LOAD_CONST str: 
          652 LOAD_FAST str: regrtest_dir
          653 BUILD_TUPLE 2
          654 GET_ITER
          655 FOR_ITER 46 to 676
          656 STORE_FAST str: path
 L.182    657 SETUP_EXCEPT 20 to 666
 L.183    658 LOAD_GLOBAL str: sys
          659 LOAD_ATTR str: path
          660 LOAD_ATTR str: remove
          661 LOAD_FAST str: path
          662 CALL_FUNCTION 1
          663 POP_TOP
          664 POP_BLOCK
          665 CONTINUE_LOOP 1846 to 655
 L.184    666 DUP_TOP
          667 LOAD_GLOBAL str: ValueError
          668 COMPARE_OP 10
          669 POP_JUMP_IF_FALSE 1891 to 674
          670 POP_TOP
          671 POP_TOP
          672 POP_TOP
 L.185    673 CONTINUE_LOOP 1846 to 655
          674 END_FINALLY to 675
          675 CONTINUE_LOOP 1846 to 655
          676 POP_BLOCK
 L.187    677 LOAD_DEREF str: huntrleaks
          678 POP_JUMP_IF_FALSE 1979 to 708
 L.188    679 LOAD_DEREF str: huntrleaks
          680 UNPACK_SEQUENCE 3
          681 STORE_FAST str: warmup
          682 STORE_FAST str: repetitions
          683 STORE_FAST str: _
 L.189    684 LOAD_FAST str: warmup
          685 LOAD_CONST long: 1
          686 COMPARE_OP 0
          687 POP_JUMP_IF_TRUE 1941 to 692
          688 LOAD_FAST str: repetitions
          689 LOAD_CONST long: 1
          690 COMPARE_OP 0
          691 POP_JUMP_IF_FALSE 1979 to 708
 L.190    692 LOAD_CONST str: Invalid values for the --huntrleaks/-R parameters. The number of warmups and repetitions must be at least 1 each (1:1).
          693 STORE_FAST str: msg
 L.193    694 LOAD_GLOBAL str: sys
          695 LOAD_ATTR str: stderr
          696 DUP_TOP
          697 LOAD_FAST str: msg
          698 ROT_TWO
          699 PRINT_ITEM_TO
          700 PRINT_NEWLINE_TO
 L.194    701 LOAD_GLOBAL str: sys
          702 LOAD_ATTR str: exit
          703 LOAD_CONST long: 2
          704 CALL_FUNCTION 1
          705 POP_TOP
          706 JUMP_ABSOLUTE 1979 to 708
          707 JUMP_FORWARD 0 to 708
 L.196    708 LOAD_FAST str: cleanup_tests
          709 POP_JUMP_IF_FALSE 2150 to 775
 L.197    710 LOAD_CONST long: -1
          711 LOAD_CONST obj: N
          712 IMPORT_NAME str: glob
          713 STORE_FAST str: glob
 L.199    714 LOAD_GLOBAL str: os
          715 LOAD_ATTR str: chdir
          716 LOAD_GLOBAL str: support
          717 LOAD_ATTR str: SAVEDCWD
          718 CALL_FUNCTION 1
          719 POP_TOP
 L.200    720 LOAD_GLOBAL str: os
          721 LOAD_ATTR str: path
          722 LOAD_ATTR str: join
          723 LOAD_GLOBAL str: TEMPDIR
          724 LOAD_CONST str: test_python_*
          725 CALL_FUNCTION 2
          726 STORE_FAST str: path
 L.201    727 LOAD_CONST str: Cleanup %s directory
          728 LOAD_GLOBAL str: TEMPDIR
          729 BINARY_MODULO
          730 PRINT_ITEM
          731 PRINT_NEWLINE
 L.202    732 SETUP_LOOP 768
          733 LOAD_FAST str: glob
          734 LOAD_ATTR str: glob
          735 LOAD_FAST str: path
          736 CALL_FUNCTION 1
          737 GET_ITER
          738 FOR_ITER 71 to 768
          739 STORE_FAST str: name
 L.203    740 LOAD_GLOBAL str: os
          741 LOAD_ATTR str: path
          742 LOAD_ATTR str: isdir
          743 LOAD_FAST str: name
          744 CALL_FUNCTION 1
          745 POP_JUMP_IF_FALSE 2108 to 757
 L.204    746 LOAD_CONST str: Remove directory: %s
          747 LOAD_FAST str: name
          748 BINARY_MODULO
          749 PRINT_ITEM
          750 PRINT_NEWLINE
 L.205    751 LOAD_GLOBAL str: support
          752 LOAD_ATTR str: rmtree
          753 LOAD_FAST str: name
          754 CALL_FUNCTION 1
          755 POP_TOP
          756 CONTINUE_LOOP 2059 to 738
 L.207    757 LOAD_CONST str: Remove file: %s
          758 LOAD_FAST str: name
          759 BINARY_MODULO
          760 PRINT_ITEM
          761 PRINT_NEWLINE
 L.208    762 LOAD_GLOBAL str: support
          763 LOAD_ATTR str: unlink
          764 LOAD_FAST str: name
          765 CALL_FUNCTION 1
          766 POP_TOP
          767 CONTINUE_LOOP 2059 to 738
          768 POP_BLOCK
 L.209    769 LOAD_GLOBAL str: sys
          770 LOAD_ATTR str: exit
          771 LOAD_CONST long: 0
          772 CALL_FUNCTION 1
          773 POP_TOP
          774 JUMP_FORWARD 0 to 775
 L.212    775 LOAD_FAST str: slaveargs
          776 LOAD_CONST obj: N
          777 COMPARE_OP 9
          778 POP_JUMP_IF_FALSE 2292 to 829
 L.213    779 LOAD_GLOBAL str: json
          780 LOAD_ATTR str: loads
          781 LOAD_FAST str: slaveargs
          782 CALL_FUNCTION 1
          783 UNPACK_SEQUENCE 2
          784 STORE_FAST str: args
          785 STORE_FAST str: kwargs
 L.214    786 LOAD_DEREF str: testdir
          787 POP_JUMP_IF_FALSE 2202 to 793
 L.215    788 LOAD_DEREF str: testdir
          789 LOAD_FAST str: kwargs
          790 LOAD_CONST str: testdir
          791 STORE_SUBSCR
          792 JUMP_FORWARD 0 to 793
 L.216    793 SETUP_EXCEPT 19 to 801
 L.217    794 LOAD_GLOBAL str: runtest
          795 LOAD_FAST str: args
          796 LOAD_FAST str: kwargs
          797 CALL_FUNCTION_VAR_KW 0
          798 STORE_FAST str: result
          799 POP_BLOCK
          800 JUMP_FORWARD 37 to 816
 L.218    801 DUP_TOP
          802 LOAD_GLOBAL str: BaseException
          803 COMPARE_OP 10
          804 POP_JUMP_IF_FALSE 2260 to 815
          805 POP_TOP
          806 STORE_FAST str: e
          807 POP_TOP
 L.219    808 LOAD_GLOBAL str: INTERRUPTED
          809 LOAD_FAST str: e
          810 LOAD_ATTR str: __class__
          811 LOAD_ATTR str: __name__
          812 BUILD_TUPLE 2
          813 STORE_FAST str: result
          814 JUMP_FORWARD 1 to 816
          815 END_FINALLY to 816
 L.220    816 PRINT_NEWLINE
 L.221    817 LOAD_GLOBAL str: json
          818 LOAD_ATTR str: dumps
          819 LOAD_FAST str: result
          820 CALL_FUNCTION 1
          821 PRINT_ITEM
          822 PRINT_NEWLINE
 L.222    823 LOAD_GLOBAL str: sys
          824 LOAD_ATTR str: exit
          825 LOAD_CONST long: 0
          826 CALL_FUNCTION 1
          827 POP_TOP
          828 JUMP_FORWARD 0 to 829
 L.224    829 BUILD_LIST 0
          830 STORE_DEREF str: good
 L.225    831 BUILD_LIST 0
          832 STORE_DEREF str: bad
 L.226    833 BUILD_LIST 0
          834 STORE_DEREF str: skipped
 L.227    835 BUILD_LIST 0
          836 STORE_DEREF str: resource_denieds
 L.228    837 BUILD_LIST 0
          838 STORE_DEREF str: environment_changed
 L.229    839 BUILD_LIST 0
          840 STORE_DEREF str: rerun
 L.230    841 BUILD_LIST 0
          842 STORE_DEREF str: run_no_tests
 L.231    843 LOAD_CONST obj: N
          844 STORE_DEREF str: first_result
 L.232    845 LOAD_GLOBAL str: False
          846 STORE_DEREF str: interrupted
 L.234    847 LOAD_FAST str: findleaks
          848 POP_JUMP_IF_FALSE 2408 to 873
 L.235    849 SETUP_EXCEPT 16 to 856
 L.236    850 LOAD_CONST long: -1
          851 LOAD_CONST obj: N
          852 IMPORT_NAME str: gc
          853 STORE_FAST str: gc
          854 POP_BLOCK
          855 JUMP_FORWARD 28 to 870
 L.237    856 DUP_TOP
          857 LOAD_GLOBAL str: ImportError
          858 COMPARE_OP 10
          859 POP_JUMP_IF_FALSE 2398 to 869
          860 POP_TOP
          861 POP_TOP
          862 POP_TOP
 L.238    863 LOAD_CONST str: No GC available, disabling findleaks.
          864 PRINT_ITEM
          865 PRINT_NEWLINE
 L.239    866 LOAD_GLOBAL str: False
          867 STORE_FAST str: findleaks
          868 JUMP_ABSOLUTE 2408 to 873
          869 END_FINALLY to 870
 L.245    870 BUILD_LIST 0
          871 STORE_FAST str: found_garbage
          872 JUMP_FORWARD 0 to 873
 L.247    873 LOAD_FAST str: single
          874 POP_JUMP_IF_FALSE 2514 to 913
 L.248    875 LOAD_GLOBAL str: os
          876 LOAD_ATTR str: path
          877 LOAD_ATTR str: join
          878 LOAD_GLOBAL str: TEMPDIR
          879 LOAD_CONST str: pynexttest
          880 CALL_FUNCTION 2
          881 STORE_FAST str: filename
 L.249    882 SETUP_EXCEPT 56 to 903
 L.250    883 LOAD_GLOBAL str: open
          884 LOAD_FAST str: filename
          885 LOAD_CONST str: r
          886 CALL_FUNCTION 2
          887 STORE_FAST str: fp
 L.251    888 LOAD_FAST str: fp
          889 LOAD_ATTR str: read
          890 CALL_FUNCTION 0
          891 LOAD_ATTR str: strip
          892 CALL_FUNCTION 0
          893 STORE_FAST str: next_test
 L.252    894 LOAD_FAST str: next_test
          895 BUILD_LIST 1
          896 STORE_DEREF str: tests
 L.253    897 LOAD_FAST str: fp
          898 LOAD_ATTR str: close
          899 CALL_FUNCTION 0
          900 POP_TOP
          901 POP_BLOCK
          902 JUMP_ABSOLUTE 2514 to 913
 L.254    903 DUP_TOP
          904 LOAD_GLOBAL str: IOError
          905 COMPARE_OP 10
          906 POP_JUMP_IF_FALSE 2510 to 911
          907 POP_TOP
          908 POP_TOP
          909 POP_TOP
 L.255    910 JUMP_ABSOLUTE 2514 to 913
          911 END_FINALLY to 912
          912 JUMP_FORWARD 0 to 913
 L.257    913 LOAD_FAST str: fromfile
          914 POP_JUMP_IF_FALSE 2640 to 961
 L.258    915 BUILD_LIST 0
          916 STORE_DEREF str: tests
 L.259    917 LOAD_GLOBAL str: open
          918 LOAD_GLOBAL str: os
          919 LOAD_ATTR str: path
          920 LOAD_ATTR str: join
          921 LOAD_GLOBAL str: support
          922 LOAD_ATTR str: SAVEDCWD
          923 LOAD_FAST str: fromfile
          924 CALL_FUNCTION 2
          925 CALL_FUNCTION 1
          926 STORE_FAST str: fp
 L.260    927 SETUP_LOOP 953
          928 LOAD_FAST str: fp
          929 GET_ITER
          930 FOR_ITER 60 to 955
          931 STORE_FAST str: line
 L.261    932 LOAD_FAST str: line
          933 LOAD_ATTR str: split
          934 CALL_FUNCTION 0
          935 STORE_FAST str: guts
 L.262    936 LOAD_FAST str: guts
          937 POP_JUMP_IF_TRUE 2563 to 939
          938 CONTINUE_LOOP 1 to 930
          939 LOAD_FAST str: guts
          940 LOAD_CONST long: 0
          941 BINARY_SUBSCR
          942 LOAD_ATTR str: startswith
          943 LOAD_CONST str: #
          944 CALL_FUNCTION 1
          945 UNARY_NOT
          946 POP_JUMP_IF_TRUE 2563 to 948
          947 CONTINUE_LOOP 1 to 930
 L.263    948 LOAD_DEREF str: tests
          949 LOAD_ATTR str: extend
          950 LOAD_FAST str: guts
          951 CALL_FUNCTION 1
          952 POP_TOP
          953 DUMMY 2563 to 930
          954 JUMP_ABSOLUTE 2563 to 930
          955 POP_BLOCK
 L.264    956 LOAD_FAST str: fp
          957 LOAD_ATTR str: close
          958 CALL_FUNCTION 0
          959 POP_TOP
          960 JUMP_FORWARD 0 to 961
 L.267    961 LOAD_GLOBAL str: removepy
          962 LOAD_FAST str: args
          963 CALL_FUNCTION 1
          964 POP_TOP
 L.268    965 LOAD_GLOBAL str: removepy
          966 LOAD_DEREF str: tests
          967 CALL_FUNCTION 1
          968 POP_TOP
 L.270    969 LOAD_GLOBAL str: STDTESTS
          970 SLICE
          971 STORE_FAST str: stdtests
 L.271    972 LOAD_GLOBAL str: NOTTESTS
          973 LOAD_ATTR str: copy
          974 CALL_FUNCTION 0
          975 STORE_FAST str: nottests
 L.272    976 LOAD_FAST str: exclude
          977 POP_JUMP_IF_FALSE 2752 to 1003
 L.273    978 SETUP_LOOP 997
          979 LOAD_FAST str: args
          980 GET_ITER
          981 FOR_ITER 47 to 999
          982 STORE_FAST str: arg
 L.274    983 LOAD_FAST str: arg
          984 LOAD_FAST str: stdtests
          985 COMPARE_OP 6
          986 POP_JUMP_IF_FALSE 2726 to 993
 L.275    987 LOAD_FAST str: stdtests
          988 LOAD_ATTR str: remove
          989 LOAD_FAST str: arg
          990 CALL_FUNCTION 1
          991 POP_TOP
          992 JUMP_FORWARD 0 to 993
 L.276    993 LOAD_FAST str: nottests
          994 LOAD_ATTR str: add
          995 LOAD_FAST str: arg
          996 CALL_FUNCTION 1
          997 POP_TOP
          998 JUMP_ABSOLUTE 2692 to 981
          999 POP_BLOCK
 L.277   1000 BUILD_LIST 0
         1001 STORE_FAST str: args
         1002 JUMP_FORWARD 0 to 1003
 L.279   1003 LOAD_DEREF str: huntrleaks
         1004 POP_JUMP_IF_FALSE 2779 to 1014
 L.281   1005 LOAD_CONST str: Warning: bpo-31731: test_io hangs with --huntrleaks: exclude the test
         1006 PRINT_ITEM
         1007 PRINT_NEWLINE
 L.283   1008 LOAD_FAST str: nottests
         1009 LOAD_ATTR str: add
         1010 LOAD_CONST str: test_io
         1011 CALL_FUNCTION 1
         1012 POP_TOP
         1013 JUMP_FORWARD 0 to 1014
 L.285   1014 LOAD_DEREF str: verbose
         1015 POP_JUMP_IF_TRUE 2816 to 1027
         1016 LOAD_FAST str: header
         1017 POP_JUMP_IF_TRUE 2816 to 1027
         1018 LOAD_DEREF str: quiet
         1019 JUMP_IF_TRUE_OR_POP 2812
         1020 LOAD_FAST str: single
         1021 JUMP_IF_TRUE_OR_POP 2812
         1022 LOAD_DEREF str: tests
         1023 JUMP_IF_TRUE_OR_POP 2812
         1024 LOAD_FAST str: args
         1025 UNARY_NOT
         1026 JUMP_IF_FALSE_OR_POP 2820 to 1029
         1027 LOAD_DEREF str: pgo
         1028 UNARY_NOT
         1029 STORE_FAST str: display_header
 L.286   1030 LOAD_GLOBAL str: findtests
         1031 LOAD_DEREF str: testdir
         1032 LOAD_FAST str: stdtests
         1033 LOAD_FAST str: nottests
         1034 CALL_FUNCTION 3
         1035 STORE_FAST str: alltests
 L.287   1036 LOAD_DEREF str: tests
         1037 JUMP_IF_TRUE_OR_POP 2856
         1038 LOAD_FAST str: args
         1039 JUMP_IF_TRUE_OR_POP 2856
         1040 LOAD_FAST str: alltests
         1041 STORE_DEREF str: selected
 L.288   1042 LOAD_FAST str: single
         1043 POP_JUMP_IF_FALSE 2935 to 1074
 L.289   1044 LOAD_DEREF str: selected
         1045 LOAD_CONST long: 1
         1046 SLICE_2
         1047 STORE_DEREF str: selected
 L.290   1048 SETUP_EXCEPT 31 to 1062
 L.291   1049 LOAD_FAST str: alltests
         1050 LOAD_FAST str: alltests
         1051 LOAD_ATTR str: index
         1052 LOAD_DEREF str: selected
         1053 LOAD_CONST long: 0
         1054 BINARY_SUBSCR
         1055 CALL_FUNCTION 1
         1056 LOAD_CONST long: 1
         1057 BINARY_ADD
         1058 BINARY_SUBSCR
         1059 STORE_FAST str: next_single_test
         1060 POP_BLOCK
         1061 JUMP_ABSOLUTE 2935 to 1074
 L.292   1062 DUP_TOP
         1063 LOAD_GLOBAL str: IndexError
         1064 COMPARE_OP 10
         1065 POP_JUMP_IF_FALSE 2931 to 1072
         1066 POP_TOP
         1067 POP_TOP
         1068 POP_TOP
 L.293   1069 LOAD_CONST obj: N
         1070 STORE_FAST str: next_single_test
         1071 JUMP_ABSOLUTE 2935 to 1074
         1072 END_FINALLY to 1073
         1073 JUMP_FORWARD 0 to 1074
 L.295   1074 LOAD_FAST str: list_tests
         1075 POP_JUMP_IF_FALSE 2979 to 1092
 L.296   1076 SETUP_LOOP 1083
         1077 LOAD_DEREF str: selected
         1078 GET_ITER
         1079 FOR_ITER 11 to 1085
         1080 STORE_FAST str: name
 L.297   1081 LOAD_FAST str: name
         1082 PRINT_ITEM
         1083 PRINT_NEWLINE
         1084 JUMP_ABSOLUTE 2948 to 1079
         1085 POP_BLOCK
 L.298   1086 LOAD_GLOBAL str: sys
         1087 LOAD_ATTR str: exit
         1088 LOAD_CONST long: 0
         1089 CALL_FUNCTION 1
         1090 POP_TOP
         1091 JUMP_FORWARD 0 to 1092
 L.300   1092 LOAD_FAST str: list_cases_opt
         1093 POP_JUMP_IF_FALSE 3017 to 1106
 L.301   1094 LOAD_GLOBAL str: list_cases
         1095 LOAD_DEREF str: testdir
         1096 LOAD_DEREF str: selected
         1097 LOAD_DEREF str: match_tests
         1098 CALL_FUNCTION 3
         1099 POP_TOP
 L.302   1100 LOAD_GLOBAL str: sys
         1101 LOAD_ATTR str: exit
         1102 LOAD_CONST long: 0
         1103 CALL_FUNCTION 1
         1104 POP_TOP
         1105 JUMP_FORWARD 0 to 1106
 L.304   1106 LOAD_FAST str: trace
         1107 POP_JUMP_IF_FALSE 3062 to 1121
 L.305   1108 LOAD_CONST long: -1
         1109 LOAD_CONST obj: N
         1110 IMPORT_NAME str: trace
         1111 STORE_FAST str: trace
 L.306   1112 LOAD_FAST str: trace
         1113 LOAD_ATTR str: Trace
         1114 LOAD_CONST str: trace
         1115 LOAD_GLOBAL str: False
         1116 LOAD_CONST str: count
         1117 LOAD_GLOBAL str: True
         1118 CALL_FUNCTION 512
         1119 STORE_FAST str: tracer
         1120 JUMP_FORWARD 0 to 1121
 L.308   1121 BUILD_LIST 0
         1122 STORE_DEREF str: test_times
 L.309   1123 LOAD_DEREF str: use_resources
         1124 LOAD_GLOBAL str: support
         1125 STORE_ATTR str: use_resources
 L.310   1126 LOAD_GLOBAL str: set
         1127 LOAD_GLOBAL str: sys
         1128 LOAD_ATTR str: modules
         1129 CALL_FUNCTION 1
         1130 STORE_FAST str: save_modules
 L.312   1131 LOAD_CLOSURE str: bad
         1132 LOAD_CLOSURE str: environment_changed
         1133 LOAD_CLOSURE str: good
         1134 LOAD_CLOSURE str: resource_denieds
         1135 LOAD_CLOSURE str: run_no_tests
         1136 LOAD_CLOSURE str: skipped
         1137 LOAD_CLOSURE str: test_times
         1138 BUILD_TUPLE 7
         1139 LOAD_CONST obj: c
         1140 MAKE_CLOSURE 0
         1141 STORE_DEREF str: accumulate_result
 L.332   1142 LOAD_FAST str: forever
         1143 POP_JUMP_IF_FALSE 3185 to 1162
 L.333   1144 LOAD_GLOBAL str: list
         1145 LOAD_DEREF str: selected
         1146 CALL_FUNCTION 1
         1147 LOAD_CLOSURE str: bad
         1148 LOAD_CLOSURE str: environment_changed
         1149 LOAD_CLOSURE str: fail_env_changed
         1150 BUILD_TUPLE 3
         1151 LOAD_CONST obj: c
         1152 MAKE_CLOSURE 1
         1153 STORE_FAST str: test_forever
 L.341   1154 LOAD_FAST str: test_forever
         1155 CALL_FUNCTION 0
         1156 STORE_DEREF str: tests
 L.342   1157 LOAD_CONST str: 
         1158 STORE_DEREF str: test_count
 L.343   1159 LOAD_CONST long: 3
         1160 STORE_DEREF str: test_count_width
         1161 JUMP_FORWARD 49 to 1179
 L.345   1162 LOAD_GLOBAL str: iter
         1163 LOAD_DEREF str: selected
         1164 CALL_FUNCTION 1
         1165 STORE_DEREF str: tests
 L.346   1166 LOAD_CONST str: /{}
         1167 LOAD_ATTR str: format
         1168 LOAD_GLOBAL str: len
         1169 LOAD_DEREF str: selected
         1170 CALL_FUNCTION 1
         1171 CALL_FUNCTION 1
         1172 STORE_DEREF str: test_count
 L.347   1173 LOAD_GLOBAL str: len
         1174 LOAD_DEREF str: test_count
         1175 CALL_FUNCTION 1
         1176 LOAD_CONST long: 1
         1177 BINARY_SUBTRACT
         1178 STORE_DEREF str: test_count_width
 L.349   1179 LOAD_CLOSURE str: bad
         1180 LOAD_CLOSURE str: environment_changed
         1181 LOAD_CLOSURE str: pgo
         1182 LOAD_CLOSURE str: regrtest_start_time
         1183 LOAD_CLOSURE str: test_count
         1184 LOAD_CLOSURE str: test_count_width
         1185 BUILD_TUPLE 6
         1186 LOAD_CONST obj: c
         1187 MAKE_CLOSURE 0
         1188 STORE_FAST str: display_progress
 L.374   1189 LOAD_FAST str: display_header
         1190 POP_JUMP_IF_FALSE 3384 to 1239
 L.376   1191 LOAD_CONST str: ==
         1192 PRINT_ITEM
         1193 LOAD_GLOBAL str: platform
         1194 LOAD_ATTR str: python_implementation
         1195 CALL_FUNCTION 0
         1196 PRINT_ITEM
 L.377   1197 LOAD_CONST str:  
         1198 LOAD_ATTR str: join
         1199 LOAD_GLOBAL str: sys
         1200 LOAD_ATTR str: version
         1201 LOAD_ATTR str: split
         1202 CALL_FUNCTION 0
         1203 CALL_FUNCTION 1
         1204 PRINT_ITEM
         1205 PRINT_NEWLINE
 L.378   1206 LOAD_CONST str: ==  
         1207 PRINT_ITEM
         1208 LOAD_GLOBAL str: platform
         1209 LOAD_ATTR str: platform
         1210 LOAD_CONST str: aliased
         1211 LOAD_GLOBAL str: True
         1212 CALL_FUNCTION 256
         1213 PRINT_ITEM
 L.379   1214 LOAD_CONST str: %s-endian
         1215 LOAD_GLOBAL str: sys
         1216 LOAD_ATTR str: byteorder
         1217 BINARY_MODULO
         1218 PRINT_ITEM
         1219 PRINT_NEWLINE
 L.380   1220 LOAD_CONST str: ==  
         1221 PRINT_ITEM
         1222 LOAD_GLOBAL str: os
         1223 LOAD_ATTR str: getcwd
         1224 CALL_FUNCTION 0
         1225 PRINT_ITEM
         1226 PRINT_NEWLINE
 L.381   1227 LOAD_GLOBAL str: cpu_count
         1228 CALL_FUNCTION 0
         1229 STORE_FAST str: ncpu
 L.382   1230 LOAD_FAST str: ncpu
         1231 POP_JUMP_IF_FALSE 3384 to 1239
 L.383   1232 LOAD_CONST str: == CPU count:
         1233 PRINT_ITEM
         1234 LOAD_FAST str: ncpu
         1235 PRINT_ITEM
         1236 PRINT_NEWLINE
         1237 JUMP_ABSOLUTE 3384 to 1239
         1238 JUMP_FORWARD 0 to 1239
 L.385   1239 LOAD_DEREF str: huntrleaks
         1240 POP_JUMP_IF_FALSE 3428 to 1255
 L.386   1241 LOAD_DEREF str: huntrleaks
         1242 UNPACK_SEQUENCE 3
         1243 STORE_FAST str: warmup
         1244 STORE_FAST str: repetitions
         1245 STORE_FAST str: _
 L.387   1246 LOAD_FAST str: warmup
         1247 LOAD_CONST long: 3
         1248 COMPARE_OP 0
         1249 POP_JUMP_IF_FALSE 3428 to 1255
 L.388   1250 LOAD_CONST str: WARNING: Running tests with --huntrleaks/-R and less than 3 warmup repetitions can give false positives!
         1251 PRINT_ITEM
         1252 PRINT_NEWLINE
         1253 JUMP_ABSOLUTE 3428 to 1255
         1254 JUMP_FORWARD 0 to 1255
 L.391   1255 LOAD_FAST str: randomize
         1256 POP_JUMP_IF_FALSE 3472 to 1273
 L.392   1257 LOAD_GLOBAL str: random
         1258 LOAD_ATTR str: seed
         1259 LOAD_FAST str: random_seed
         1260 CALL_FUNCTION 1
         1261 POP_TOP
 L.393   1262 LOAD_CONST str: Using random seed
         1263 PRINT_ITEM
         1264 LOAD_FAST str: random_seed
         1265 PRINT_ITEM
         1266 PRINT_NEWLINE
 L.394   1267 LOAD_GLOBAL str: random
         1268 LOAD_ATTR str: shuffle
         1269 LOAD_DEREF str: selected
         1270 CALL_FUNCTION 1
         1271 POP_TOP
         1272 JUMP_FORWARD 0 to 1273
 L.396   1273 LOAD_FAST str: use_mp
         1274 POP_JUMP_IF_FALSE 4405 to 1630
 L.397   1275 SETUP_EXCEPT 20 to 1284
 L.398   1276 LOAD_CONST long: -1
         1277 LOAD_CONST (str: Thread,)
         1278 IMPORT_NAME str: threading
         1279 IMPORT_FROM str: Thread
         1280 STORE_FAST str: Thread
         1281 POP_TOP
         1282 POP_BLOCK
         1283 JUMP_FORWARD 35 to 1301
 L.399   1284 DUP_TOP
         1285 LOAD_GLOBAL str: ImportError
         1286 COMPARE_OP 10
         1287 POP_JUMP_IF_FALSE 3535 to 1300
         1288 POP_TOP
         1289 POP_TOP
         1290 POP_TOP
 L.400   1291 LOAD_CONST str: Multiprocess option requires thread support
         1292 PRINT_ITEM
         1293 PRINT_NEWLINE
 L.401   1294 LOAD_GLOBAL str: sys
         1295 LOAD_ATTR str: exit
         1296 LOAD_CONST long: 2
         1297 CALL_FUNCTION 1
         1298 POP_TOP
         1299 JUMP_FORWARD 1 to 1301
         1300 END_FINALLY to 1301
 L.402   1301 LOAD_CONST long: -1
         1302 LOAD_CONST (str: Queue,str: Empty,)
         1303 IMPORT_NAME str: Queue
         1304 IMPORT_FROM str: Queue
         1305 STORE_FAST str: Queue
         1306 IMPORT_FROM str: Empty
         1307 STORE_FAST str: Empty
         1308 POP_TOP
 L.403   1309 LOAD_CONST long: -1
         1310 LOAD_CONST (str: Popen,str: PIPE,)
         1311 IMPORT_NAME str: subprocess
         1312 IMPORT_FROM str: Popen
         1313 STORE_DEREF str: Popen
         1314 IMPORT_FROM str: PIPE
         1315 STORE_DEREF str: PIPE
         1316 POP_TOP
 L.404   1317 LOAD_GLOBAL str: re
         1318 LOAD_ATTR str: compile
         1319 LOAD_CONST str: \[\d+ refs\]$
         1320 CALL_FUNCTION 1
         1321 STORE_DEREF str: debug_output_pat
 L.405   1322 LOAD_FAST str: Queue
         1323 CALL_FUNCTION 0
         1324 STORE_DEREF str: output
 L.406   1325 LOAD_CLOSURE str: failfast
         1326 LOAD_CLOSURE str: huntrleaks
         1327 LOAD_CLOSURE str: match_tests
         1328 LOAD_CLOSURE str: pgo
         1329 LOAD_CLOSURE str: quiet
         1330 LOAD_CLOSURE str: tests
         1331 LOAD_CLOSURE str: use_resources
         1332 LOAD_CLOSURE str: verbose
         1333 BUILD_TUPLE 8
         1334 LOAD_CONST obj: c
         1335 MAKE_CLOSURE 0
         1336 STORE_FAST str: tests_and_args
 L.416   1337 LOAD_FAST str: tests_and_args
         1338 CALL_FUNCTION 0
         1339 STORE_DEREF str: pending
 L.417   1340 LOAD_GLOBAL str: support
         1341 LOAD_ATTR str: args_from_interpreter_flags
         1342 CALL_FUNCTION 0
         1343 STORE_FAST str: opt_args
 L.418   1344 LOAD_GLOBAL str: sys
         1345 LOAD_ATTR str: executable
         1346 BUILD_LIST 1
         1347 LOAD_FAST str: opt_args
         1348 BINARY_ADD
         1349 LOAD_CONST str: -m
         1350 LOAD_CONST str: test.regrtest
         1351 BUILD_LIST 2
         1352 BINARY_ADD
         1353 STORE_DEREF str: base_cmd
 L.420   1354 LOAD_DEREF str: pgo
         1355 POP_JUMP_IF_FALSE 3709 to 1362
 L.421   1356 LOAD_DEREF str: base_cmd
         1357 LOAD_CONST str: --pgo
         1358 BUILD_LIST 1
         1359 BINARY_ADD
         1360 STORE_DEREF str: base_cmd
         1361 JUMP_FORWARD 0 to 1362
 L.423   1362 LOAD_CONST str: MultiprocessThread
         1363 LOAD_FAST str: Thread
         1364 BUILD_TUPLE 1
         1365 LOAD_CLOSURE str: PIPE
         1366 LOAD_CLOSURE str: Popen
         1367 LOAD_CLOSURE str: base_cmd
         1368 LOAD_CLOSURE str: debug_output_pat
         1369 LOAD_CLOSURE str: output
         1370 LOAD_CLOSURE str: pending
         1371 LOAD_CLOSURE str: testdir
         1372 BUILD_TUPLE 7
         1373 LOAD_CONST obj: c
         1374 MAKE_CLOSURE 0
         1375 CALL_FUNCTION 0
         1376 BUILD_CLASS
         1377 STORE_FAST str: MultiprocessThread
 L.476   1378 BUILD_LIST 0
         1379 LOAD_GLOBAL str: range
         1380 LOAD_FAST str: use_mp
         1381 CALL_FUNCTION 1
         1382 GET_ITER
         1383 FOR_ITER 15 to 1389
         1384 STORE_FAST str: i
         1385 LOAD_FAST str: MultiprocessThread
         1386 CALL_FUNCTION 0
         1387 LIST_APPEND 2
         1388 JUMP_ABSOLUTE 3768 to 1383
         1389 STORE_FAST str: workers
 L.477   1390 LOAD_CONST str: Run tests in parallel using %s child processes
 L.478   1391 LOAD_GLOBAL str: len
         1392 LOAD_FAST str: workers
         1393 CALL_FUNCTION 1
         1394 BINARY_MODULO
         1395 PRINT_ITEM
         1396 PRINT_NEWLINE
 L.479   1397 SETUP_LOOP 1405
         1398 LOAD_FAST str: workers
         1399 GET_ITER
         1400 FOR_ITER 16 to 1407
         1401 STORE_FAST str: worker
 L.480   1402 LOAD_FAST str: worker
         1403 LOAD_ATTR str: start
         1404 CALL_FUNCTION 0
         1405 POP_TOP
         1406 JUMP_ABSOLUTE 3811 to 1400
         1407 POP_BLOCK
 L.482   1408 LOAD_CONST obj: c
         1409 MAKE_FUNCTION 0
         1410 STORE_FAST str: get_running
 L.493   1411 LOAD_CONST long: 0
         1412 STORE_FAST str: finished
 L.494   1413 LOAD_CONST long: 1
         1414 STORE_FAST str: test_index
 L.495   1415 LOAD_GLOBAL str: max
         1416 LOAD_GLOBAL str: PROGRESS_UPDATE
         1417 LOAD_GLOBAL str: PROGRESS_MIN_TIME
         1418 CALL_FUNCTION 2
         1419 STORE_FAST str: get_timeout
 L.496   1420 SETUP_EXCEPT 472 to 1603
 L.497   1421 SETUP_LOOP 1596
         1422 LOAD_FAST str: finished
         1423 LOAD_FAST str: use_mp
         1424 COMPARE_OP 0
         1425 POP_JUMP_IF_FALSE 4337 to 1600
 L.498   1426 SETUP_EXCEPT 22 to 1435
 L.499   1427 LOAD_DEREF str: output
         1428 LOAD_ATTR str: get
         1429 LOAD_CONST str: timeout
         1430 LOAD_FAST str: get_timeout
         1431 CALL_FUNCTION 256
         1432 STORE_FAST str: item
         1433 POP_BLOCK
         1434 JUMP_FORWARD 79 to 1470
 L.500   1435 DUP_TOP
         1436 LOAD_FAST str: Empty
         1437 COMPARE_OP 10
         1438 POP_JUMP_IF_FALSE 3988 to 1469
         1439 POP_TOP
         1440 POP_TOP
         1441 POP_TOP
 L.501   1442 LOAD_FAST str: get_running
         1443 LOAD_FAST str: workers
         1444 CALL_FUNCTION 1
         1445 STORE_FAST str: running
 L.502   1446 LOAD_FAST str: running
         1447 POP_JUMP_IF_TRUE 3873 to 1449
         1448 CONTINUE_LOOP 1 to 1422
         1449 LOAD_DEREF str: pgo
         1450 UNARY_NOT
         1451 POP_JUMP_IF_TRUE 3873 to 1453
         1452 CONTINUE_LOOP 1 to 1422
 L.503   1453 LOAD_CONST str: running: %s
         1454 LOAD_CONST str: , 
         1455 LOAD_ATTR str: join
         1456 LOAD_FAST str: running
         1457 CALL_FUNCTION 1
         1458 BINARY_MODULO
         1459 PRINT_ITEM
         1460 PRINT_NEWLINE
 L.504   1461 LOAD_GLOBAL str: sys
         1462 LOAD_ATTR str: stdout
         1463 LOAD_ATTR str: flush
         1464 CALL_FUNCTION 0
         1465 POP_TOP
         1466 CONTINUE_LOOP 3873 to 1422
 L.505   1467 CONTINUE_LOOP 3873 to 1422
         1468 JUMP_FORWARD 1 to 1470
         1469 END_FINALLY to 1470
 L.507   1470 LOAD_FAST str: item
         1471 UNPACK_SEQUENCE 4
         1472 STORE_DEREF str: test
         1473 STORE_FAST str: stdout
         1474 STORE_FAST str: stderr
         1475 STORE_FAST str: result
 L.508   1476 LOAD_DEREF str: test
         1477 LOAD_CONST obj: N
         1478 COMPARE_OP 8
         1479 POP_JUMP_IF_FALSE 4035 to 1486
 L.509   1480 LOAD_FAST str: finished
         1481 LOAD_CONST long: 1
         1482 INPLACE_ADD
         1483 STORE_FAST str: finished
 L.510   1484 CONTINUE_LOOP 3873 to 1422
         1485 JUMP_FORWARD 0 to 1486
 L.511   1486 LOAD_DEREF str: accumulate_result
         1487 LOAD_DEREF str: test
         1488 LOAD_FAST str: result
         1489 CALL_FUNCTION 2
         1490 POP_TOP
 L.512   1491 LOAD_DEREF str: quiet
         1492 POP_JUMP_IF_TRUE 4208 to 1549
 L.513   1493 LOAD_FAST str: result
         1494 UNPACK_SEQUENCE 2
         1495 STORE_FAST str: ok
         1496 STORE_FAST str: test_time
 L.514   1497 LOAD_GLOBAL str: format_test_result
         1498 LOAD_DEREF str: test
         1499 LOAD_FAST str: ok
         1500 CALL_FUNCTION 2
         1501 STORE_FAST str: text
 L.515   1502 LOAD_FAST str: ok
         1503 LOAD_GLOBAL str: CHILD_ERROR
         1504 LOAD_GLOBAL str: INTERRUPTED
         1505 BUILD_TUPLE 2
         1506 COMPARE_OP 7
         1507 POP_JUMP_IF_FALSE 4141 to 1524
 L.516   1508 LOAD_FAST str: test_time
         1509 LOAD_GLOBAL str: PROGRESS_MIN_TIME
         1510 COMPARE_OP 5
         1511 POP_JUMP_IF_FALSE 4141 to 1524
 L.517   1512 LOAD_DEREF str: pgo
         1513 UNARY_NOT
         1514 POP_JUMP_IF_FALSE 4141 to 1524
 L.518   1515 LOAD_FAST str: text
         1516 LOAD_CONST str:  (%s)
         1517 LOAD_GLOBAL str: format_duration
         1518 LOAD_FAST str: test_time
         1519 CALL_FUNCTION 1
         1520 BINARY_MODULO
         1521 INPLACE_ADD
         1522 STORE_FAST str: text
         1523 JUMP_FORWARD 0 to 1524
 L.519   1524 LOAD_FAST str: get_running
         1525 LOAD_FAST str: workers
         1526 CALL_FUNCTION 1
         1527 STORE_FAST str: running
 L.520   1528 LOAD_FAST str: running
         1529 POP_JUMP_IF_FALSE 4192 to 1543
         1530 LOAD_DEREF str: pgo
         1531 UNARY_NOT
         1532 POP_JUMP_IF_FALSE 4192 to 1543
 L.521   1533 LOAD_FAST str: text
         1534 LOAD_CONST str:  -- running: %s
         1535 LOAD_CONST str: , 
         1536 LOAD_ATTR str: join
         1537 LOAD_FAST str: running
         1538 CALL_FUNCTION 1
         1539 BINARY_MODULO
         1540 INPLACE_ADD
         1541 STORE_FAST str: text
         1542 JUMP_FORWARD 0 to 1543
 L.522   1543 LOAD_FAST str: display_progress
         1544 LOAD_FAST str: test_index
         1545 LOAD_FAST str: text
         1546 CALL_FUNCTION 2
         1547 POP_TOP
         1548 JUMP_FORWARD 0 to 1549
 L.524   1549 LOAD_FAST str: stdout
         1550 POP_JUMP_IF_FALSE 4222 to 1555
 L.525   1551 LOAD_FAST str: stdout
         1552 PRINT_ITEM
         1553 PRINT_NEWLINE
         1554 JUMP_FORWARD 0 to 1555
 L.526   1555 LOAD_GLOBAL str: sys
         1556 LOAD_ATTR str: stdout
         1557 LOAD_ATTR str: flush
         1558 CALL_FUNCTION 0
         1559 POP_TOP
 L.527   1560 LOAD_FAST str: stderr
         1561 POP_JUMP_IF_FALSE 4264 to 1573
         1562 LOAD_DEREF str: pgo
         1563 UNARY_NOT
         1564 POP_JUMP_IF_FALSE 4264 to 1573
 L.528   1565 LOAD_GLOBAL str: sys
         1566 LOAD_ATTR str: stderr
         1567 DUP_TOP
         1568 LOAD_FAST str: stderr
         1569 ROT_TWO
         1570 PRINT_ITEM_TO
         1571 PRINT_NEWLINE_TO
         1572 JUMP_FORWARD 0 to 1573
 L.529   1573 LOAD_GLOBAL str: sys
         1574 LOAD_ATTR str: stderr
         1575 LOAD_ATTR str: flush
         1576 CALL_FUNCTION 0
         1577 POP_TOP
 L.531   1578 LOAD_FAST str: result
         1579 LOAD_CONST long: 0
         1580 BINARY_SUBSCR
         1581 LOAD_GLOBAL str: INTERRUPTED
         1582 COMPARE_OP 2
         1583 POP_JUMP_IF_FALSE 4324 to 1595
 L.532   1584 LOAD_FAST str: result
         1585 LOAD_CONST long: 1
         1586 BINARY_SUBSCR
         1587 LOAD_CONST str: KeyboardInterrupt
         1588 COMPARE_OP 2
         1589 POP_JUMP_IF_TRUE 4315 to 1592
         1590 LOAD_GLOBAL str: AssertionError
         1591 RAISE_VARARGS 1
 L.533   1592 LOAD_GLOBAL str: KeyboardInterrupt
         1593 RAISE_VARARGS 1
         1594 JUMP_FORWARD 0 to 1595
 L.535   1595 LOAD_FAST str: test_index
         1596 LOAD_CONST long: 1
         1597 INPLACE_ADD
         1598 STORE_FAST str: test_index
         1599 JUMP_ABSOLUTE 3873 to 1422
         1600 POP_BLOCK
         1601 POP_BLOCK
         1602 JUMP_FORWARD 33 to 1618
 L.536   1603 DUP_TOP
         1604 LOAD_GLOBAL str: KeyboardInterrupt
         1605 COMPARE_OP 10
         1606 POP_JUMP_IF_FALSE 4374 to 1617
         1607 POP_TOP
         1608 POP_TOP
         1609 POP_TOP
 L.537   1610 LOAD_GLOBAL str: True
         1611 STORE_DEREF str: interrupted
 L.538   1612 LOAD_DEREF str: pending
         1613 LOAD_ATTR str: close
         1614 CALL_FUNCTION 0
         1615 POP_TOP
         1616 JUMP_FORWARD 1 to 1618
         1617 END_FINALLY to 1618
 L.539   1618 SETUP_LOOP 1820
         1619 LOAD_FAST str: workers
         1620 GET_ITER
         1621 FOR_ITER 16 to 1628
         1622 STORE_FAST str: worker
 L.540   1623 LOAD_FAST str: worker
         1624 LOAD_ATTR str: join
         1625 CALL_FUNCTION 0
         1626 POP_TOP
         1627 CONTINUE_LOOP 4382 to 1621
         1628 POP_BLOCK
         1629 JUMP_FORWARD 515 to 1825
 L.542   1630 LOAD_CONST str: Run tests sequentially
         1631 PRINT_ITEM
         1632 PRINT_NEWLINE
 L.544   1633 LOAD_CONST obj: N
         1634 STORE_FAST str: previous_test
 L.545   1635 SETUP_LOOP 1820
         1636 LOAD_GLOBAL str: enumerate
         1637 LOAD_DEREF str: tests
         1638 LOAD_CONST long: 1
         1639 CALL_FUNCTION 2
         1640 GET_ITER
         1641 FOR_ITER 484 to 1824
         1642 UNPACK_SEQUENCE 2
         1643 STORE_FAST str: test_index
         1644 STORE_DEREF str: test
 L.546   1645 LOAD_DEREF str: quiet
         1646 POP_JUMP_IF_TRUE 4497 to 1664
 L.547   1647 LOAD_DEREF str: test
         1648 STORE_FAST str: text
 L.548   1649 LOAD_FAST str: previous_test
         1650 POP_JUMP_IF_FALSE 4481 to 1658
 L.549   1651 LOAD_CONST str: %s -- %s
         1652 LOAD_FAST str: text
         1653 LOAD_FAST str: previous_test
         1654 BUILD_TUPLE 2
         1655 BINARY_MODULO
         1656 STORE_FAST str: text
         1657 JUMP_FORWARD 0 to 1658
 L.550   1658 LOAD_FAST str: display_progress
         1659 LOAD_FAST str: test_index
         1660 LOAD_FAST str: text
         1661 CALL_FUNCTION 2
         1662 POP_TOP
         1663 JUMP_FORWARD 0 to 1664
 L.552   1664 LOAD_CLOSURE str: accumulate_result
         1665 LOAD_CLOSURE str: failfast
         1666 LOAD_CLOSURE str: huntrleaks
         1667 LOAD_CLOSURE str: match_tests
         1668 LOAD_CLOSURE str: pgo
         1669 LOAD_CLOSURE str: quiet
         1670 LOAD_CLOSURE str: test
         1671 LOAD_CLOSURE str: testdir
         1672 LOAD_CLOSURE str: verbose
         1673 BUILD_TUPLE 9
         1674 LOAD_CONST obj: c
         1675 MAKE_CLOSURE 0
         1676 STORE_FAST str: local_runtest
 L.560   1677 LOAD_GLOBAL str: time
         1678 LOAD_ATTR str: time
         1679 CALL_FUNCTION 0
         1680 STORE_FAST str: start_time
 L.561   1681 LOAD_FAST str: trace
         1682 POP_JUMP_IF_FALSE 4610 to 1703
 L.564   1683 LOAD_GLOBAL str: dict
         1684 LOAD_GLOBAL str: locals
         1685 CALL_FUNCTION 0
         1686 CALL_FUNCTION 1
         1687 STORE_FAST str: ns
 L.565   1688 LOAD_FAST str: tracer
         1689 LOAD_ATTR str: runctx
         1690 LOAD_CONST str: result = local_runtest()
         1691 LOAD_CONST str: globals
 L.566   1692 LOAD_GLOBAL str: globals
         1693 CALL_FUNCTION 0
         1694 LOAD_CONST str: locals
         1695 LOAD_FAST str: ns
         1696 CALL_FUNCTION 513
         1697 POP_TOP
 L.567   1698 LOAD_FAST str: ns
         1699 LOAD_CONST str: result
         1700 BINARY_SUBSCR
         1701 STORE_FAST str: result
         1702 JUMP_FORWARD 123 to 1754
 L.569   1703 SETUP_EXCEPT 87 to 1737
 L.570   1704 LOAD_FAST str: local_runtest
         1705 CALL_FUNCTION 0
         1706 STORE_FAST str: result
 L.571   1707 LOAD_FAST str: verbose3
         1708 POP_JUMP_IF_FALSE 4696 to 1735
         1709 LOAD_FAST str: result
         1710 LOAD_CONST long: 0
         1711 BINARY_SUBSCR
         1712 LOAD_GLOBAL str: FAILED
         1713 COMPARE_OP 2
         1714 POP_JUMP_IF_FALSE 4696 to 1735
 L.572   1715 LOAD_DEREF str: pgo
         1716 POP_JUMP_IF_TRUE 4662 to 1723
 L.573   1717 LOAD_CONST str: Re-running test %r in verbose mode
         1718 LOAD_DEREF str: test
         1719 BINARY_MODULO
         1720 PRINT_ITEM
         1721 PRINT_NEWLINE
         1722 JUMP_FORWARD 0 to 1723
 L.574   1723 LOAD_GLOBAL str: runtest
         1724 LOAD_DEREF str: test
         1725 LOAD_GLOBAL str: True
         1726 LOAD_DEREF str: quiet
         1727 LOAD_DEREF str: huntrleaks
         1728 LOAD_CONST obj: N
         1729 LOAD_DEREF str: pgo
         1730 LOAD_CONST str: testdir
 L.575   1731 LOAD_DEREF str: testdir
         1732 CALL_FUNCTION 262
         1733 POP_TOP
         1734 JUMP_FORWARD 0 to 1735
         1735 POP_BLOCK
         1736 JUMP_FORWARD 33 to 1754
 L.576   1737 DUP_TOP
         1738 LOAD_GLOBAL str: KeyboardInterrupt
         1739 COMPARE_OP 10
         1740 POP_JUMP_IF_FALSE 4723 to 1748
         1741 POP_TOP
         1742 POP_TOP
         1743 POP_TOP
 L.577   1744 LOAD_GLOBAL str: True
         1745 STORE_DEREF str: interrupted
 L.578   1746 BREAK_LOOP
         1747 JUMP_FORWARD 10 to 1754
 L.579   1748 POP_TOP
         1749 POP_TOP
         1750 POP_TOP
 L.580   1751 RAISE_VARARGS 0
         1752 JUMP_FORWARD 1 to 1754
         1753 END_FINALLY to 1754
 L.582   1754 LOAD_GLOBAL str: time
         1755 LOAD_ATTR str: time
         1756 CALL_FUNCTION 0
         1757 LOAD_FAST str: start_time
         1758 BINARY_SUBTRACT
         1759 STORE_FAST str: test_time
 L.583   1760 LOAD_GLOBAL str: format_test_result
         1761 LOAD_DEREF str: test
         1762 LOAD_FAST str: result
         1763 LOAD_CONST long: 0
         1764 BINARY_SUBSCR
         1765 CALL_FUNCTION 2
         1766 STORE_FAST str: previous_test
 L.584   1767 LOAD_FAST str: test_time
         1768 LOAD_GLOBAL str: PROGRESS_MIN_TIME
         1769 COMPARE_OP 5
         1770 POP_JUMP_IF_FALSE 4805 to 1780
 L.585   1771 LOAD_CONST str: %s in %s
         1772 LOAD_FAST str: previous_test
 L.586   1773 LOAD_GLOBAL str: format_duration
         1774 LOAD_FAST str: test_time
         1775 CALL_FUNCTION 1
         1776 BUILD_TUPLE 2
         1777 BINARY_MODULO
         1778 STORE_FAST str: previous_test
         1779 JUMP_FORWARD 25 to 1789
 L.587   1780 LOAD_FAST str: result
         1781 LOAD_CONST long: 0
         1782 BINARY_SUBSCR
         1783 LOAD_GLOBAL str: PASSED
         1784 COMPARE_OP 2
         1785 POP_JUMP_IF_FALSE 4830 to 1789
 L.589   1786 LOAD_CONST obj: N
         1787 STORE_FAST str: previous_test
         1788 JUMP_FORWARD 0 to 1789
 L.591   1789 LOAD_FAST str: findleaks
         1790 POP_JUMP_IF_FALSE 4906 to 1819
 L.592   1791 LOAD_FAST str: gc
         1792 LOAD_ATTR str: collect
         1793 CALL_FUNCTION 0
         1794 POP_TOP
 L.593   1795 LOAD_FAST str: gc
         1796 LOAD_ATTR str: garbage
         1797 POP_JUMP_IF_FALSE 4906 to 1819
 L.594   1798 LOAD_CONST str: Warning: test created
         1799 PRINT_ITEM
         1800 LOAD_GLOBAL str: len
         1801 LOAD_FAST str: gc
         1802 LOAD_ATTR str: garbage
         1803 CALL_FUNCTION 1
         1804 PRINT_ITEM
 L.595   1805 LOAD_CONST str: uncollectable object(s).
         1806 PRINT_ITEM
         1807 PRINT_NEWLINE
 L.598   1808 LOAD_FAST str: found_garbage
         1809 LOAD_ATTR str: extend
         1810 LOAD_FAST str: gc
         1811 LOAD_ATTR str: garbage
         1812 CALL_FUNCTION 1
         1813 POP_TOP
 L.599   1814 LOAD_FAST str: gc
         1815 LOAD_ATTR str: garbage
         1816 DELETE_SLICE
         1817 JUMP_ABSOLUTE 4906 to 1819
         1818 JUMP_FORWARD 0 to 1819
 L.601   1819 LOAD_GLOBAL str: unload_test_modules
         1820 LOAD_FAST str: save_modules
         1821 CALL_FUNCTION 1
         1822 POP_TOP
         1823 JUMP_ABSOLUTE 4432 to 1641
         1824 POP_BLOCK
 L.604   1825 LOAD_CLOSURE str: bad
         1826 LOAD_CLOSURE str: environment_changed
         1827 LOAD_CLOSURE str: fail_env_changed
         1828 LOAD_CLOSURE str: first_result
         1829 LOAD_CLOSURE str: good
         1830 LOAD_CLOSURE str: interrupted
         1831 LOAD_CLOSURE str: skipped
         1832 BUILD_TUPLE 7
         1833 LOAD_CONST obj: c
         1834 MAKE_CLOSURE 0
         1835 STORE_DEREF str: get_tests_result
 L.625   1836 LOAD_CLOSURE str: bad
         1837 LOAD_CLOSURE str: environment_changed
         1838 LOAD_CLOSURE str: get_tests_result
         1839 LOAD_CLOSURE str: good
         1840 LOAD_CLOSURE str: interrupted
         1841 LOAD_CLOSURE str: pgo
         1842 LOAD_CLOSURE str: print_slow
         1843 LOAD_CLOSURE str: quiet
         1844 LOAD_CLOSURE str: rerun
         1845 LOAD_CLOSURE str: resource_denieds
         1846 LOAD_CLOSURE str: run_no_tests
         1847 LOAD_CLOSURE str: selected
         1848 LOAD_CLOSURE str: skipped
         1849 LOAD_CLOSURE str: test_times
         1850 BUILD_TUPLE 14
         1851 LOAD_CONST obj: c
         1852 MAKE_CLOSURE 0
         1853 STORE_FAST str: display_result
 L.691   1854 LOAD_FAST str: display_result
         1855 CALL_FUNCTION 0
         1856 POP_TOP
 L.693   1857 LOAD_FAST str: verbose2
         1858 POP_JUMP_IF_FALSE 5258 to 1956
         1859 LOAD_DEREF str: bad
         1860 POP_JUMP_IF_FALSE 5258 to 1956
 L.694   1861 LOAD_DEREF str: get_tests_result
         1862 CALL_FUNCTION 0
         1863 STORE_DEREF str: first_result
 L.696   1864 PRINT_NEWLINE
 L.697   1865 LOAD_CONST str: Re-running failed tests in verbose mode
         1866 PRINT_ITEM
         1867 PRINT_NEWLINE
 L.698   1868 LOAD_DEREF str: bad
         1869 SLICE
         1870 STORE_DEREF str: rerun
 L.699   1871 SETUP_LOOP 1946
         1872 LOAD_DEREF str: rerun
         1873 GET_ITER
         1874 FOR_ITER 146 to 1934
         1875 STORE_DEREF str: test
 L.700   1876 LOAD_CONST str: Re-running test %r in verbose mode
         1877 LOAD_DEREF str: test
         1878 BINARY_MODULO
         1879 PRINT_ITEM
         1880 PRINT_NEWLINE
 L.701   1881 LOAD_GLOBAL str: sys
         1882 LOAD_ATTR str: stdout
         1883 LOAD_ATTR str: flush
         1884 CALL_FUNCTION 0
         1885 POP_TOP
 L.702   1886 SETUP_EXCEPT 52 to 1905
 L.703   1887 LOAD_GLOBAL str: True
         1888 LOAD_GLOBAL str: support
         1889 STORE_ATTR str: verbose
 L.704   1890 LOAD_GLOBAL str: runtest
         1891 LOAD_DEREF str: test
         1892 LOAD_GLOBAL str: True
         1893 LOAD_DEREF str: quiet
         1894 LOAD_DEREF str: huntrleaks
         1895 LOAD_CONST obj: N
         1896 LOAD_DEREF str: pgo
         1897 LOAD_CONST str: match_tests
 L.705   1898 LOAD_DEREF str: match_tests
         1899 LOAD_CONST str: testdir
         1900 LOAD_DEREF str: testdir
         1901 CALL_FUNCTION 518
         1902 STORE_FAST str: ok
         1903 POP_BLOCK
         1904 JUMP_FORWARD 19 to 1916
 L.706   1905 DUP_TOP
         1906 LOAD_GLOBAL str: KeyboardInterrupt
         1907 COMPARE_OP 10
         1908 POP_JUMP_IF_FALSE 5156 to 1915
         1909 POP_TOP
         1910 POP_TOP
         1911 POP_TOP
 L.708   1912 PRINT_NEWLINE
 L.709   1913 BREAK_LOOP
         1914 CONTINUE_LOOP 5055 to 1874
         1915 END_FINALLY to 1916
 L.711   1916 LOAD_FAST str: ok
         1917 LOAD_CONST long: 0
         1918 BINARY_SUBSCR
         1919 LOAD_GLOBAL str: PASSED
         1920 LOAD_GLOBAL str: ENV_CHANGED
         1921 LOAD_GLOBAL str: SKIPPED
         1922 LOAD_GLOBAL str: RESOURCE_DENIED
         1923 BUILD_SET 4
         1924 COMPARE_OP 6
         1925 POP_JUMP_IF_TRUE 5055 to 1927
         1926 CONTINUE_LOOP 1 to 1874
 L.712   1927 LOAD_DEREF str: bad
         1928 LOAD_ATTR str: remove
         1929 LOAD_DEREF str: test
         1930 CALL_FUNCTION 1
         1931 POP_TOP
         1932 CONTINUE_LOOP 5055 to 1874
         1933 CONTINUE_LOOP 5055 to 1874
         1934 POP_BLOCK
 L.714   1935 LOAD_DEREF str: bad
         1936 POP_JUMP_IF_FALSE 5248 to 1952
 L.715   1937 LOAD_GLOBAL str: count
         1938 LOAD_GLOBAL str: len
         1939 LOAD_DEREF str: bad
         1940 CALL_FUNCTION 1
         1941 LOAD_CONST str: test
         1942 CALL_FUNCTION 2
         1943 PRINT_ITEM
         1944 LOAD_CONST str: failed again:
         1945 PRINT_ITEM
         1946 PRINT_NEWLINE
 L.716   1947 LOAD_GLOBAL str: printlist
         1948 LOAD_DEREF str: bad
         1949 CALL_FUNCTION 1
         1950 POP_TOP
         1951 JUMP_FORWARD 0 to 1952
 L.718   1952 LOAD_FAST str: display_result
         1953 CALL_FUNCTION 0
         1954 POP_TOP
         1955 JUMP_FORWARD 0 to 1956
 L.720   1956 LOAD_FAST str: single
         1957 POP_JUMP_IF_FALSE 5330 to 1984
 L.721   1958 LOAD_FAST str: next_single_test
         1959 POP_JUMP_IF_FALSE 5314 to 1978
 L.722   1960 LOAD_GLOBAL str: open
         1961 LOAD_FAST str: filename
         1962 LOAD_CONST str: w
         1963 CALL_FUNCTION 2
         1964 SETUP_WITH 10
         1965 STORE_FAST str: fp
 L.723   1966 LOAD_FAST str: fp
         1967 LOAD_ATTR str: write
         1968 LOAD_FAST str: next_single_test
         1969 LOAD_CONST str: 

         1970 BINARY_ADD
         1971 CALL_FUNCTION 1
         1972 POP_TOP
         1973 POP_BLOCK
         1974 LOAD_CONST obj: N
         1975 WITH_CLEANUP
         1976 END_FINALLY to 1977
         1977 JUMP_ABSOLUTE 5330 to 1984
 L.725   1978 LOAD_GLOBAL str: os
         1979 LOAD_ATTR str: unlink
         1980 LOAD_FAST str: filename
         1981 CALL_FUNCTION 1
         1982 POP_TOP
         1983 JUMP_FORWARD 0 to 1984
 L.727   1984 LOAD_FAST str: trace
         1985 POP_JUMP_IF_FALSE 5379 to 2001
 L.728   1986 LOAD_FAST str: tracer
         1987 LOAD_ATTR str: results
         1988 CALL_FUNCTION 0
         1989 STORE_FAST str: r
 L.729   1990 LOAD_FAST str: r
         1991 LOAD_ATTR str: write_results
         1992 LOAD_CONST str: show_missing
         1993 LOAD_GLOBAL str: True
         1994 LOAD_CONST str: summary
         1995 LOAD_GLOBAL str: True
         1996 LOAD_CONST str: coverdir
         1997 LOAD_FAST str: coverdir
         1998 CALL_FUNCTION 768
         1999 POP_TOP
         2000 JUMP_FORWARD 0 to 2001
 L.731   2001 LOAD_FAST str: runleaks
         2002 POP_JUMP_IF_FALSE 5411 to 2013
 L.732   2003 LOAD_GLOBAL str: os
         2004 LOAD_ATTR str: system
         2005 LOAD_CONST str: leaks %d
         2006 LOAD_GLOBAL str: os
         2007 LOAD_ATTR str: getpid
         2008 CALL_FUNCTION 0
         2009 BINARY_MODULO
         2010 CALL_FUNCTION 1
         2011 POP_TOP
         2012 JUMP_FORWARD 0 to 2013
 L.734   2013 PRINT_NEWLINE
 L.735   2014 LOAD_GLOBAL str: time
         2015 LOAD_ATTR str: time
         2016 CALL_FUNCTION 0
         2017 LOAD_DEREF str: regrtest_start_time
         2018 BINARY_SUBTRACT
         2019 STORE_FAST str: duration
 L.736   2020 LOAD_CONST str: Total duration: %s
         2021 LOAD_GLOBAL str: format_duration
         2022 LOAD_FAST str: duration
         2023 CALL_FUNCTION 1
         2024 BINARY_MODULO
         2025 PRINT_ITEM
         2026 PRINT_NEWLINE
 L.738   2027 LOAD_CONST str: Tests result: %s
         2028 LOAD_DEREF str: get_tests_result
         2029 CALL_FUNCTION 0
         2030 BINARY_MODULO
         2031 PRINT_ITEM
         2032 PRINT_NEWLINE
 L.740   2033 LOAD_DEREF str: bad
         2034 POP_JUMP_IF_FALSE 5477 to 2041
 L.741   2035 LOAD_GLOBAL str: sys
         2036 LOAD_ATTR str: exit
         2037 LOAD_CONST long: 2
         2038 CALL_FUNCTION 1
         2039 POP_TOP
         2040 JUMP_FORWARD 0 to 2041
 L.742   2041 LOAD_DEREF str: interrupted
         2042 POP_JUMP_IF_FALSE 5499 to 2049
 L.743   2043 LOAD_GLOBAL str: sys
         2044 LOAD_ATTR str: exit
         2045 LOAD_CONST long: 130
         2046 CALL_FUNCTION 1
         2047 POP_TOP
         2048 JUMP_FORWARD 0 to 2049
 L.744   2049 LOAD_DEREF str: fail_env_changed
         2050 POP_JUMP_IF_FALSE 5527 to 2059
         2051 LOAD_DEREF str: environment_changed
         2052 POP_JUMP_IF_FALSE 5527 to 2059
 L.745   2053 LOAD_GLOBAL str: sys
         2054 LOAD_ATTR str: exit
         2055 LOAD_CONST long: 3
         2056 CALL_FUNCTION 1
         2057 POP_TOP
         2058 JUMP_FORWARD 0 to 2059
 L.746   2059 LOAD_GLOBAL str: sys
         2060 LOAD_ATTR str: exit
         2061 LOAD_CONST long: 0
         2062 CALL_FUNCTION 1
         2063 POP_TOP
         2064 LOAD_CONST obj: N
         2065 RETURN_VALUE

function get_running(workers):

 L.  2      0 BUILD_LIST 0
            1 STORE_FAST str: running
 L.  3      2 SETUP_LOOP 39
            3 LOAD_FAST str: workers
            4 GET_ITER
            5 FOR_ITER 90 to 39
            6 STORE_FAST str: worker
 L.  4      7 LOAD_FAST str: worker
            8 LOAD_ATTR str: current_test
            9 STORE_FAST str: current_test
 L.  5     10 LOAD_FAST str: current_test
           11 POP_JUMP_IF_TRUE 40 to 14
 L.  6     12 CONTINUE_LOOP 13 to 5
           13 JUMP_FORWARD 0 to 14
 L.  7     14 LOAD_GLOBAL str: time
           15 LOAD_ATTR str: time
           16 CALL_FUNCTION 0
           17 LOAD_FAST str: worker
           18 LOAD_ATTR str: start_time
           19 BINARY_SUBTRACT
           20 STORE_FAST str: dt
 L.  8     21 LOAD_FAST str: dt
           22 LOAD_GLOBAL str: PROGRESS_MIN_TIME
           23 COMPARE_OP 5
           24 POP_JUMP_IF_TRUE 13 to 26
           25 CONTINUE_LOOP 1 to 5
 L.  9     26 LOAD_FAST str: running
           27 LOAD_ATTR str: append
           28 LOAD_CONST str: %s (%s)
           29 LOAD_FAST str: current_test
           30 LOAD_GLOBAL str: format_duration
           31 LOAD_FAST str: dt
           32 CALL_FUNCTION 1
           33 BUILD_TUPLE 2
           34 BINARY_MODULO
           35 CALL_FUNCTION 1
           36 POP_TOP
           37 CONTINUE_LOOP 13 to 5
           38 CONTINUE_LOOP 13 to 5
           39 POP_BLOCK
 L. 10     40 LOAD_FAST str: running
           41 RETURN_VALUE

closure accumulate_result(test,result):

 L.  2      0 LOAD_FAST str: result
            1 UNPACK_SEQUENCE 2
            2 STORE_FAST str: ok
            3 STORE_FAST str: test_time
 L.  3      4 LOAD_FAST str: ok
            5 LOAD_GLOBAL str: CHILD_ERROR
            6 LOAD_GLOBAL str: INTERRUPTED
            7 BUILD_TUPLE 2
            8 COMPARE_OP 7
            9 POP_JUMP_IF_FALSE 52 to 18
 L.  4     10 LOAD_DEREF str: test_times
           11 LOAD_ATTR str: append
           12 LOAD_FAST str: test_time
           13 LOAD_FAST str: test
           14 BUILD_TUPLE 2
           15 CALL_FUNCTION 1
           16 POP_TOP
           17 JUMP_FORWARD 0 to 18
 L.  5     18 LOAD_FAST str: ok
           19 LOAD_GLOBAL str: PASSED
           20 COMPARE_OP 2
           21 POP_JUMP_IF_FALSE 80 to 28
 L.  6     22 LOAD_DEREF str: good
           23 LOAD_ATTR str: append
           24 LOAD_FAST str: test
           25 CALL_FUNCTION 1
           26 POP_TOP
           27 JUMP_FORWARD 190 to 96
 L.  7     28 LOAD_FAST str: ok
           29 LOAD_GLOBAL str: FAILED
           30 LOAD_GLOBAL str: CHILD_ERROR
           31 BUILD_TUPLE 2
           32 COMPARE_OP 6
           33 POP_JUMP_IF_FALSE 114 to 40
 L.  8     34 LOAD_DEREF str: bad
           35 LOAD_ATTR str: append
           36 LOAD_FAST str: test
           37 CALL_FUNCTION 1
           38 POP_TOP
           39 JUMP_FORWARD 156 to 96
 L.  9     40 LOAD_FAST str: ok
           41 LOAD_GLOBAL str: ENV_CHANGED
           42 COMPARE_OP 2
           43 POP_JUMP_IF_FALSE 142 to 50
 L. 10     44 LOAD_DEREF str: environment_changed
           45 LOAD_ATTR str: append
           46 LOAD_FAST str: test
           47 CALL_FUNCTION 1
           48 POP_TOP
           49 JUMP_FORWARD 128 to 96
 L. 11     50 LOAD_FAST str: ok
           51 LOAD_GLOBAL str: SKIPPED
           52 COMPARE_OP 2
           53 POP_JUMP_IF_FALSE 170 to 60
 L. 12     54 LOAD_DEREF str: skipped
           55 LOAD_ATTR str: append
           56 LOAD_FAST str: test
           57 CALL_FUNCTION 1
           58 POP_TOP
           59 JUMP_FORWARD 100 to 96
 L. 13     60 LOAD_FAST str: ok
           61 LOAD_GLOBAL str: RESOURCE_DENIED
           62 COMPARE_OP 2
           63 POP_JUMP_IF_FALSE 211 to 75
 L. 14     64 LOAD_DEREF str: skipped
           65 LOAD_ATTR str: append
           66 LOAD_FAST str: test
           67 CALL_FUNCTION 1
           68 POP_TOP
 L. 15     69 LOAD_DEREF str: resource_denieds
           70 LOAD_ATTR str: append
           71 LOAD_FAST str: test
           72 CALL_FUNCTION 1
           73 POP_TOP
           74 JUMP_FORWARD 59 to 96
 L. 16     75 LOAD_FAST str: ok
           76 LOAD_GLOBAL str: TEST_DID_NOT_RUN
           77 COMPARE_OP 2
           78 POP_JUMP_IF_FALSE 239 to 85
 L. 17     79 LOAD_DEREF str: run_no_tests
           80 LOAD_ATTR str: append
           81 LOAD_FAST str: test
           82 CALL_FUNCTION 1
           83 POP_TOP
           84 JUMP_FORWARD 31 to 96
 L. 18     85 LOAD_FAST str: ok
           86 LOAD_GLOBAL str: INTERRUPTED
           87 COMPARE_OP 3
           88 POP_JUMP_IF_FALSE 270 to 96
 L. 19     89 LOAD_GLOBAL str: ValueError
           90 LOAD_CONST str: invalid test result: %r
           91 LOAD_FAST str: ok
           92 BINARY_MODULO
           93 CALL_FUNCTION 1
           94 RAISE_VARARGS 1
           95 JUMP_FORWARD 0 to 96
           96 LOAD_CONST obj: N
           97 RETURN_VALUE

closure test_forever(tests):

 L.  2      0 SETUP_LOOP 25
            1 LOAD_GLOBAL str: True
            2 POP_JUMP_IF_FALSE 60 to 26
 L.  3      3 SETUP_LOOP 23
            4 LOAD_FAST str: tests
            5 GET_ITER
            6 FOR_ITER 37 to 24
            7 STORE_FAST str: test
 L.  4      8 LOAD_FAST str: test
            9 YIELD_VALUE
           10 POP_TOP
 L.  5     11 LOAD_DEREF str: bad
           12 POP_JUMP_IF_FALSE 37 to 15
 L.  6     13 LOAD_CONST obj: N
           14 RETURN_VALUE to 15
 L.  7     15 LOAD_DEREF str: fail_env_changed
           16 POP_JUMP_IF_TRUE 16 to 18
           17 CONTINUE_LOOP 1 to 6
           18 LOAD_DEREF str: environment_changed
           19 POP_JUMP_IF_TRUE 16 to 21
           20 CONTINUE_LOOP 1 to 6
 L.  8     21 LOAD_CONST obj: N
           22 RETURN_VALUE to 23
           23 DUMMY 16 to 6
           24 POP_BLOCK
           25 DUMMY 3 to 1
           26 POP_BLOCK
           27 LOAD_CONST obj: N
           28 RETURN_VALUE

closure display_progress(test_index,test):

 L.  3      0 LOAD_CONST str: {1:{0}}{2}
            1 LOAD_ATTR str: format
            2 LOAD_DEREF str: test_count_width
            3 LOAD_FAST str: test_index
            4 LOAD_DEREF str: test_count
            5 CALL_FUNCTION 3
            6 STORE_FAST str: line
 L.  4      7 LOAD_GLOBAL str: len
            8 LOAD_DEREF str: bad
            9 CALL_FUNCTION 1
           10 LOAD_GLOBAL str: len
           11 LOAD_DEREF str: environment_changed
           12 CALL_FUNCTION 1
           13 BINARY_ADD
           14 STORE_FAST str: fails
 L.  5     15 LOAD_FAST str: fails
           16 POP_JUMP_IF_FALSE 77 to 27
           17 LOAD_DEREF str: pgo
           18 UNARY_NOT
           19 POP_JUMP_IF_FALSE 77 to 27
 L.  6     20 LOAD_CONST str: {}/{}
           21 LOAD_ATTR str: format
           22 LOAD_FAST str: line
           23 LOAD_FAST str: fails
           24 CALL_FUNCTION 2
           25 STORE_FAST str: line
           26 JUMP_FORWARD 0 to 27
 L.  7     27 LOAD_CONST str: [{}]
           28 LOAD_ATTR str: format
           29 LOAD_FAST str: line
           30 CALL_FUNCTION 1
           31 STORE_FAST str: line
 L. 10     32 LOAD_GLOBAL str: hasattr
           33 LOAD_GLOBAL str: os
           34 LOAD_CONST str: getloadavg
           35 CALL_FUNCTION 2
           36 POP_JUMP_IF_FALSE 144 to 50
 L. 11     37 LOAD_GLOBAL str: os
           38 LOAD_ATTR str: getloadavg
           39 CALL_FUNCTION 0
           40 LOAD_CONST long: 0
           41 BINARY_SUBSCR
           42 STORE_FAST str: load_avg_1min
 L. 12     43 LOAD_CONST str: load avg: {:.2f} {}
           44 LOAD_ATTR str: format
           45 LOAD_FAST str: load_avg_1min
           46 LOAD_FAST str: line
           47 CALL_FUNCTION 2
           48 STORE_FAST str: line
           49 JUMP_FORWARD 0 to 50
 L. 15     50 LOAD_GLOBAL str: time
           51 LOAD_ATTR str: time
           52 CALL_FUNCTION 0
           53 LOAD_DEREF str: regrtest_start_time
           54 BINARY_SUBTRACT
           55 STORE_FAST str: test_time
 L. 16     56 LOAD_GLOBAL str: datetime
           57 LOAD_ATTR str: timedelta
           58 LOAD_CONST str: seconds
           59 LOAD_GLOBAL str: int
           60 LOAD_FAST str: test_time
           61 CALL_FUNCTION 1
           62 CALL_FUNCTION 256
           63 STORE_FAST str: test_time
 L. 17     64 LOAD_CONST str: %s %s
           65 LOAD_FAST str: test_time
           66 LOAD_FAST str: line
           67 BUILD_TUPLE 2
           68 BINARY_MODULO
           69 STORE_FAST str: line
 L. 20     70 LOAD_CONST str: {} {}
           71 LOAD_ATTR str: format
           72 LOAD_FAST str: line
           73 LOAD_FAST str: test
           74 CALL_FUNCTION 2
           75 STORE_FAST str: line
 L. 22     76 LOAD_FAST str: line
           77 PRINT_ITEM
           78 PRINT_NEWLINE
 L. 23     79 LOAD_GLOBAL str: sys
           80 LOAD_ATTR str: stdout
           81 LOAD_ATTR str: flush
           82 CALL_FUNCTION 0
           83 POP_TOP
           84 LOAD_CONST obj: N
           85 RETURN_VALUE

closure tests_and_args():

 L.  2      0 SETUP_LOOP 30
            1 LOAD_DEREF str: tests
            2 GET_ITER
            3 FOR_ITER 71 to 29
            4 STORE_FAST str: test
 L.  4      5 LOAD_FAST str: test
            6 LOAD_DEREF str: verbose
            7 LOAD_DEREF str: quiet
            8 BUILD_TUPLE 3
 L.  5      9 LOAD_GLOBAL str: dict
           10 LOAD_CONST str: huntrleaks
           11 LOAD_DEREF str: huntrleaks
           12 LOAD_CONST str: use_resources
           13 LOAD_DEREF str: use_resources
           14 LOAD_CONST str: failfast
 L.  6     15 LOAD_DEREF str: failfast
           16 LOAD_CONST str: match_tests
 L.  7     17 LOAD_DEREF str: match_tests
           18 LOAD_CONST str: pgo
 L.  8     19 LOAD_DEREF str: pgo
           20 CALL_FUNCTION 1280
           21 BUILD_TUPLE 2
           22 STORE_FAST str: args_tuple
 L. 10     23 LOAD_FAST str: test
           24 LOAD_FAST str: args_tuple
           25 BUILD_TUPLE 2
           26 YIELD_VALUE
           27 POP_TOP
           28 CONTINUE_LOOP 7 to 3
           29 POP_BLOCK
           30 LOAD_CONST obj: N
           31 RETURN_VALUE

closure MultiprocessThread():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  2      2 LOAD_CONST obj: N
            3 STORE_NAME str: current_test
 L.  3      4 LOAD_CONST obj: N
            5 STORE_NAME str: start_time
 L.  5      6 LOAD_CLOSURE str: PIPE
            7 LOAD_CLOSURE str: Popen
            8 LOAD_CLOSURE str: base_cmd
            9 LOAD_CLOSURE str: debug_output_pat
           10 LOAD_CLOSURE str: output
           11 LOAD_CLOSURE str: pending
           12 LOAD_CLOSURE str: testdir
           13 BUILD_TUPLE 7
           14 LOAD_CONST obj: c
           15 MAKE_CLOSURE 0
           16 STORE_NAME str: runtest
 L. 45     17 LOAD_CLOSURE str: output
           18 BUILD_TUPLE 1
           19 LOAD_CONST obj: c
           20 MAKE_CLOSURE 0
           21 STORE_NAME str: run
           22 LOAD_LOCALS
           23 RETURN_VALUE

closure runtest(self):

 L.  2      0 SETUP_EXCEPT 22 to 9
 L.  3      1 LOAD_GLOBAL str: next
            2 LOAD_DEREF str: pending
            3 CALL_FUNCTION 1
            4 UNPACK_SEQUENCE 2
            5 STORE_FAST str: test
            6 STORE_FAST str: args_tuple
            7 POP_BLOCK
            8 JUMP_FORWARD 31 to 24
 L.  4      9 DUP_TOP
           10 LOAD_GLOBAL str: StopIteration
           11 COMPARE_OP 10
           12 POP_JUMP_IF_FALSE 55 to 23
           13 POP_TOP
           14 POP_TOP
           15 POP_TOP
 L.  5     16 LOAD_DEREF str: output
           17 LOAD_ATTR str: put
           18 LOAD_CONST (obj: N,obj: N,obj: N,obj: N,)
           19 CALL_FUNCTION 1
           20 POP_TOP
 L.  6     21 LOAD_GLOBAL str: True
           22 RETURN_VALUE to 23
           23 END_FINALLY to 24
 L.  9     24 LOAD_DEREF str: base_cmd
           25 LOAD_CONST str: --slaveargs
           26 LOAD_GLOBAL str: json
           27 LOAD_ATTR str: dumps
           28 LOAD_FAST str: args_tuple
           29 CALL_FUNCTION 1
           30 BUILD_LIST 2
           31 BINARY_ADD
           32 STORE_FAST str: args
 L. 10     33 LOAD_DEREF str: testdir
           34 POP_JUMP_IF_FALSE 109 to 43
 L. 11     35 LOAD_FAST str: args
           36 LOAD_ATTR str: extend
           37 LOAD_CONST str: --testdir
           38 LOAD_DEREF str: testdir
           39 BUILD_TUPLE 2
           40 CALL_FUNCTION 1
           41 POP_TOP
           42 JUMP_FORWARD 0 to 43
 L. 12     43 SETUP_FINALLY 103 to 79
 L. 13     44 LOAD_GLOBAL str: time
           45 LOAD_ATTR str: time
           46 CALL_FUNCTION 0
           47 LOAD_FAST str: self
           48 STORE_ATTR str: start_time
 L. 14     49 LOAD_FAST str: test
           50 LOAD_FAST str: self
           51 STORE_ATTR str: current_test
 L. 15     52 LOAD_DEREF str: Popen
           53 LOAD_FAST str: args
           54 LOAD_CONST str: stdout
 L. 16     55 LOAD_DEREF str: PIPE
           56 LOAD_CONST str: stderr
           57 LOAD_DEREF str: PIPE
           58 LOAD_CONST str: universal_newlines
 L. 17     59 LOAD_GLOBAL str: True
           60 LOAD_CONST str: close_fds
 L. 18     61 LOAD_GLOBAL str: os
           62 LOAD_ATTR str: name
           63 LOAD_CONST str: nt
           64 COMPARE_OP 3
           65 CALL_FUNCTION 1025
           66 STORE_FAST str: popen
 L. 19     67 LOAD_FAST str: popen
           68 LOAD_ATTR str: communicate
           69 CALL_FUNCTION 0
           70 UNPACK_SEQUENCE 2
           71 STORE_FAST str: stdout
           72 STORE_FAST str: stderr
 L. 20     73 LOAD_FAST str: popen
           74 LOAD_ATTR str: wait
           75 CALL_FUNCTION 0
           76 STORE_FAST str: retcode
           77 POP_BLOCK
           78 LOAD_CONST obj: N
 L. 22     79 LOAD_CONST obj: N
           80 LOAD_FAST str: self
           81 STORE_ATTR str: current_test
           82 END_FINALLY to 83
 L. 26     83 LOAD_DEREF str: debug_output_pat
           84 LOAD_ATTR str: sub
           85 LOAD_CONST str: 
           86 LOAD_FAST str: stderr
           87 CALL_FUNCTION 2
           88 STORE_FAST str: stderr
 L. 28     89 LOAD_FAST str: retcode
           90 LOAD_CONST long: 0
           91 COMPARE_OP 2
           92 POP_JUMP_IF_FALSE 326 to 118
 L. 29     93 LOAD_FAST str: stdout
           94 LOAD_ATTR str: strip
           95 CALL_FUNCTION 0
           96 LOAD_ATTR str: rpartition
           97 LOAD_CONST str: 

           98 CALL_FUNCTION 1
           99 UNPACK_SEQUENCE 3
          100 STORE_FAST str: stdout
          101 STORE_FAST str: _
          102 STORE_FAST str: result
 L. 30    103 LOAD_FAST str: result
          104 POP_JUMP_IF_TRUE 308 to 112
 L. 31    105 LOAD_DEREF str: output
          106 LOAD_ATTR str: put
          107 LOAD_CONST (obj: N,obj: N,obj: N,obj: N,)
          108 CALL_FUNCTION 1
          109 POP_TOP
 L. 32    110 LOAD_GLOBAL str: True
          111 RETURN_VALUE to 112
 L. 34    112 LOAD_GLOBAL str: json
          113 LOAD_ATTR str: loads
          114 LOAD_FAST str: result
          115 CALL_FUNCTION 1
          116 STORE_FAST str: result
          117 JUMP_FORWARD 16 to 124
 L. 36    118 LOAD_GLOBAL str: CHILD_ERROR
          119 LOAD_CONST str: Exit code %s
          120 LOAD_FAST str: retcode
          121 BINARY_MODULO
          122 BUILD_TUPLE 2
          123 STORE_FAST str: result
 L. 38    124 LOAD_DEREF str: output
          125 LOAD_ATTR str: put
          126 LOAD_FAST str: test
          127 LOAD_FAST str: stdout
          128 LOAD_ATTR str: rstrip
          129 CALL_FUNCTION 0
          130 LOAD_FAST str: stderr
          131 LOAD_ATTR str: rstrip
          132 CALL_FUNCTION 0
          133 LOAD_FAST str: result
          134 BUILD_TUPLE 4
          135 CALL_FUNCTION 1
          136 POP_TOP
 L. 39    137 LOAD_GLOBAL str: False
          138 RETURN_VALUE

closure run(self):

 L.  2      0 SETUP_EXCEPT 35 to 14
 L.  3      1 LOAD_GLOBAL str: False
            2 STORE_FAST str: stop
 L.  4      3 SETUP_LOOP 12
            4 LOAD_FAST str: stop
            5 POP_JUMP_IF_TRUE 33 to 11
 L.  5      6 LOAD_FAST str: self
            7 LOAD_ATTR str: runtest
            8 CALL_FUNCTION 0
            9 STORE_FAST str: stop
           10 CONTINUE_LOOP 12 to 4
           11 POP_BLOCK
           12 POP_BLOCK
           13 JUMP_FORWARD 33 to 29
 L.  6     14 DUP_TOP
           15 LOAD_GLOBAL str: BaseException
           16 COMPARE_OP 10
           17 POP_JUMP_IF_FALSE 70 to 28
           18 POP_TOP
           19 POP_TOP
           20 POP_TOP
 L.  7     21 LOAD_DEREF str: output
           22 LOAD_ATTR str: put
           23 LOAD_CONST (obj: N,obj: N,obj: N,obj: N,)
           24 CALL_FUNCTION 1
           25 POP_TOP
 L.  8     26 RAISE_VARARGS 0
           27 JUMP_FORWARD 1 to 29
           28 END_FINALLY to 29
           29 LOAD_CONST obj: N
           30 RETURN_VALUE

closure local_runtest():

 L.  2      0 LOAD_GLOBAL str: runtest
            1 LOAD_DEREF str: test
            2 LOAD_DEREF str: verbose
            3 LOAD_DEREF str: quiet
            4 LOAD_DEREF str: huntrleaks
            5 LOAD_CONST obj: N
            6 LOAD_DEREF str: pgo
            7 LOAD_CONST str: failfast
 L.  3      8 LOAD_DEREF str: failfast
            9 LOAD_CONST str: match_tests
 L.  4     10 LOAD_DEREF str: match_tests
           11 LOAD_CONST str: testdir
 L.  5     12 LOAD_DEREF str: testdir
           13 CALL_FUNCTION 774
           14 STORE_FAST str: result
 L.  6     15 LOAD_DEREF str: accumulate_result
           16 LOAD_DEREF str: test
           17 LOAD_FAST str: result
           18 CALL_FUNCTION 2
           19 POP_TOP
 L.  7     20 LOAD_FAST str: result
           21 RETURN_VALUE

closure get_tests_result():

 L.  2      0 BUILD_LIST 0
            1 STORE_FAST str: result
 L.  3      2 LOAD_DEREF str: bad
            3 POP_JUMP_IF_FALSE 28 to 10
 L.  4      4 LOAD_FAST str: result
            5 LOAD_ATTR str: append
            6 LOAD_CONST str: FAILURE
            7 CALL_FUNCTION 1
            8 POP_TOP
            9 JUMP_FORWARD 71 to 35
 L.  5     10 LOAD_DEREF str: fail_env_changed
           11 POP_JUMP_IF_FALSE 56 to 20
           12 LOAD_DEREF str: environment_changed
           13 POP_JUMP_IF_FALSE 56 to 20
 L.  6     14 LOAD_FAST str: result
           15 LOAD_ATTR str: append
           16 LOAD_CONST str: ENV CHANGED
           17 CALL_FUNCTION 1
           18 POP_TOP
           19 JUMP_FORWARD 43 to 35
 L.  7     20 LOAD_GLOBAL str: any
           21 LOAD_DEREF str: good
           22 LOAD_DEREF str: bad
           23 LOAD_DEREF str: skipped
           24 LOAD_DEREF str: interrupted
           25 LOAD_DEREF str: environment_changed
           26 BUILD_TUPLE 5
           27 CALL_FUNCTION 1
           28 POP_JUMP_IF_TRUE 99 to 35
 L.  8     29 LOAD_FAST str: result
           30 LOAD_ATTR str: append
           31 LOAD_CONST str: NO TEST RUN
           32 CALL_FUNCTION 1
           33 POP_TOP
           34 JUMP_FORWARD 0 to 35
 L. 10     35 LOAD_DEREF str: interrupted
           36 POP_JUMP_IF_FALSE 121 to 43
 L. 11     37 LOAD_FAST str: result
           38 LOAD_ATTR str: append
           39 LOAD_CONST str: INTERRUPTED
           40 CALL_FUNCTION 1
           41 POP_TOP
           42 JUMP_FORWARD 0 to 43
 L. 13     43 LOAD_FAST str: result
           44 POP_JUMP_IF_TRUE 143 to 51
 L. 14     45 LOAD_FAST str: result
           46 LOAD_ATTR str: append
           47 LOAD_CONST str: SUCCESS
           48 CALL_FUNCTION 1
           49 POP_TOP
           50 JUMP_FORWARD 0 to 51
 L. 16     51 LOAD_CONST str: , 
           52 LOAD_ATTR str: join
           53 LOAD_FAST str: result
           54 CALL_FUNCTION 1
           55 STORE_FAST str: result
 L. 17     56 LOAD_DEREF str: first_result
           57 POP_JUMP_IF_FALSE 183 to 65
 L. 18     58 LOAD_CONST str: %s then %s
           59 LOAD_DEREF str: first_result
           60 LOAD_FAST str: result
           61 BUILD_TUPLE 2
           62 BINARY_MODULO
           63 STORE_FAST str: result
           64 JUMP_FORWARD 0 to 65
 L. 19     65 LOAD_FAST str: result
           66 RETURN_VALUE

closure display_result():

 L.  3      0 PRINT_NEWLINE
 L.  4      1 LOAD_CONST str: == Tests result: %s ==
            2 LOAD_DEREF str: get_tests_result
            3 CALL_FUNCTION 0
            4 BINARY_MODULO
            5 PRINT_ITEM
            6 PRINT_NEWLINE
 L.  6      7 LOAD_DEREF str: interrupted
            8 POP_JUMP_IF_FALSE 111 to 47
            9 LOAD_DEREF str: pgo
           10 UNARY_NOT
           11 POP_JUMP_IF_FALSE 111 to 47
 L.  7     12 PRINT_NEWLINE
 L.  8     13 LOAD_CONST str: Test suite interrupted by signal SIGINT.
           14 PRINT_ITEM
           15 PRINT_NEWLINE
 L.  9     16 LOAD_GLOBAL str: set
           17 LOAD_DEREF str: selected
           18 CALL_FUNCTION 1
           19 LOAD_GLOBAL str: set
           20 LOAD_DEREF str: good
           21 CALL_FUNCTION 1
           22 BINARY_SUBTRACT
           23 LOAD_GLOBAL str: set
           24 LOAD_DEREF str: bad
           25 CALL_FUNCTION 1
           26 BINARY_SUBTRACT
           27 LOAD_GLOBAL str: set
           28 LOAD_DEREF str: skipped
           29 CALL_FUNCTION 1
           30 BINARY_SUBTRACT
           31 STORE_FAST str: omitted
 L. 10     32 LOAD_GLOBAL str: count
           33 LOAD_GLOBAL str: len
           34 LOAD_FAST str: omitted
           35 CALL_FUNCTION 1
           36 LOAD_CONST str: test
           37 CALL_FUNCTION 2
           38 PRINT_ITEM
           39 LOAD_CONST str: omitted:
           40 PRINT_ITEM
           41 PRINT_NEWLINE
 L. 11     42 LOAD_GLOBAL str: printlist
           43 LOAD_FAST str: omitted
           44 CALL_FUNCTION 1
           45 POP_TOP
           46 JUMP_FORWARD 0 to 47
 L. 13     47 LOAD_DEREF str: good
           48 POP_JUMP_IF_FALSE 205 to 85
           49 LOAD_DEREF str: quiet
           50 UNARY_NOT
           51 POP_JUMP_IF_FALSE 205 to 85
           52 LOAD_DEREF str: pgo
           53 UNARY_NOT
           54 POP_JUMP_IF_FALSE 205 to 85
 L. 14     55 PRINT_NEWLINE
 L. 15     56 LOAD_DEREF str: bad
           57 UNARY_NOT
           58 POP_JUMP_IF_FALSE 178 to 74
           59 LOAD_DEREF str: skipped
           60 UNARY_NOT
           61 POP_JUMP_IF_FALSE 178 to 74
           62 LOAD_DEREF str: interrupted
           63 UNARY_NOT
           64 POP_JUMP_IF_FALSE 178 to 74
           65 LOAD_GLOBAL str: len
           66 LOAD_DEREF str: good
           67 CALL_FUNCTION 1
           68 LOAD_CONST long: 1
           69 COMPARE_OP 4
           70 POP_JUMP_IF_FALSE 178 to 74
 L. 16     71 LOAD_CONST str: All
           72 PRINT_ITEM
           73 JUMP_FORWARD 0 to 74
 L. 17     74 LOAD_GLOBAL str: count
           75 LOAD_GLOBAL str: len
           76 LOAD_DEREF str: good
           77 CALL_FUNCTION 1
           78 LOAD_CONST str: test
           79 CALL_FUNCTION 2
           80 PRINT_ITEM
           81 LOAD_CONST str: OK.
           82 PRINT_ITEM
           83 PRINT_NEWLINE
           84 JUMP_FORWARD 0 to 85
 L. 19     85 LOAD_DEREF str: print_slow
           86 POP_JUMP_IF_FALSE 278 to 116
 L. 20     87 LOAD_DEREF str: test_times
           88 LOAD_ATTR str: sort
           89 LOAD_CONST str: reverse
           90 LOAD_GLOBAL str: True
           91 CALL_FUNCTION 256
           92 POP_TOP
 L. 21     93 PRINT_NEWLINE
 L. 22     94 LOAD_CONST str: 10 slowest tests:
           95 PRINT_ITEM
           96 PRINT_NEWLINE
 L. 23     97 SETUP_LOOP 116
           98 LOAD_DEREF str: test_times
           99 LOAD_CONST long: 10
          100 SLICE_2
          101 GET_ITER
          102 FOR_ITER 27 to 114
          103 UNPACK_SEQUENCE 2
          104 STORE_FAST str: test_time
          105 STORE_FAST str: test
 L. 24    106 LOAD_CONST str: - %s: %.1fs
          107 LOAD_FAST str: test
          108 LOAD_FAST str: test_time
          109 BUILD_TUPLE 2
          110 BINARY_MODULO
          111 PRINT_ITEM
          112 PRINT_NEWLINE
          113 CONTINUE_LOOP 244 to 102
          114 POP_BLOCK
          115 JUMP_FORWARD 0 to 116
 L. 26    116 LOAD_DEREF str: bad
          117 POP_JUMP_IF_FALSE 329 to 137
          118 LOAD_DEREF str: pgo
          119 UNARY_NOT
          120 POP_JUMP_IF_FALSE 329 to 137
 L. 27    121 PRINT_NEWLINE
 L. 28    122 LOAD_GLOBAL str: count
          123 LOAD_GLOBAL str: len
          124 LOAD_DEREF str: bad
          125 CALL_FUNCTION 1
          126 LOAD_CONST str: test
          127 CALL_FUNCTION 2
          128 PRINT_ITEM
          129 LOAD_CONST str: failed:
          130 PRINT_ITEM
          131 PRINT_NEWLINE
 L. 29    132 LOAD_GLOBAL str: printlist
          133 LOAD_DEREF str: bad
          134 CALL_FUNCTION 1
          135 POP_TOP
          136 JUMP_FORWARD 0 to 137
 L. 31    137 LOAD_DEREF str: environment_changed
          138 POP_JUMP_IF_FALSE 385 to 159
          139 LOAD_DEREF str: pgo
          140 UNARY_NOT
          141 POP_JUMP_IF_FALSE 385 to 159
 L. 32    142 PRINT_NEWLINE
 L. 33    143 LOAD_CONST str: {} altered the execution environment:
          144 LOAD_ATTR str: format
 L. 34    145 LOAD_GLOBAL str: count
          146 LOAD_GLOBAL str: len
          147 LOAD_DEREF str: environment_changed
          148 CALL_FUNCTION 1
          149 LOAD_CONST str: test
          150 CALL_FUNCTION 2
          151 CALL_FUNCTION 1
          152 PRINT_ITEM
          153 PRINT_NEWLINE
 L. 35    154 LOAD_GLOBAL str: printlist
          155 LOAD_DEREF str: environment_changed
          156 CALL_FUNCTION 1
          157 POP_TOP
          158 JUMP_FORWARD 0 to 159
 L. 37    159 LOAD_DEREF str: skipped
          160 POP_JUMP_IF_FALSE 590 to 244
          161 LOAD_DEREF str: quiet
          162 UNARY_NOT
          163 POP_JUMP_IF_FALSE 590 to 244
          164 LOAD_DEREF str: pgo
          165 UNARY_NOT
          166 POP_JUMP_IF_FALSE 590 to 244
 L. 38    167 PRINT_NEWLINE
 L. 39    168 LOAD_GLOBAL str: count
          169 LOAD_GLOBAL str: len
          170 LOAD_DEREF str: skipped
          171 CALL_FUNCTION 1
          172 LOAD_CONST str: test
          173 CALL_FUNCTION 2
          174 PRINT_ITEM
          175 LOAD_CONST str: skipped:
          176 PRINT_ITEM
          177 PRINT_NEWLINE
 L. 40    178 LOAD_GLOBAL str: printlist
          179 LOAD_DEREF str: skipped
          180 CALL_FUNCTION 1
          181 POP_TOP
 L. 42    182 LOAD_GLOBAL str: _ExpectedSkips
          183 CALL_FUNCTION 0
          184 STORE_FAST str: e
 L. 43    185 LOAD_GLOBAL str: sys
          186 LOAD_ATTR str: platform
          187 STORE_FAST str: plat
 L. 44    188 LOAD_FAST str: e
          189 LOAD_ATTR str: isvalid
          190 CALL_FUNCTION 0
          191 POP_JUMP_IF_FALSE 569 to 233
 L. 45    192 LOAD_GLOBAL str: set
          193 LOAD_DEREF str: skipped
          194 CALL_FUNCTION 1
          195 LOAD_FAST str: e
          196 LOAD_ATTR str: getexpected
          197 CALL_FUNCTION 0
          198 BINARY_SUBTRACT
          199 LOAD_GLOBAL str: set
          200 LOAD_DEREF str: resource_denieds
          201 CALL_FUNCTION 1
          202 BINARY_SUBTRACT
          203 STORE_FAST str: surprise
 L. 46    204 LOAD_FAST str: surprise
          205 POP_JUMP_IF_FALSE 553 to 225
 L. 47    206 LOAD_GLOBAL str: count
          207 LOAD_GLOBAL str: len
          208 LOAD_FAST str: surprise
          209 CALL_FUNCTION 1
          210 LOAD_CONST str: skip
          211 CALL_FUNCTION 2
          212 PRINT_ITEM
 L. 48    213 LOAD_CONST str: unexpected on
          214 PRINT_ITEM
          215 LOAD_FAST str: plat
          216 LOAD_CONST str: :
          217 BINARY_ADD
          218 PRINT_ITEM
          219 PRINT_NEWLINE
 L. 49    220 LOAD_GLOBAL str: printlist
          221 LOAD_FAST str: surprise
          222 CALL_FUNCTION 1
          223 POP_TOP
          224 JUMP_ABSOLUTE 587 to 243
 L. 51    225 LOAD_CONST str: Those skips are all expected on
          226 PRINT_ITEM
          227 LOAD_FAST str: plat
          228 LOAD_CONST str: .
          229 BINARY_ADD
          230 PRINT_ITEM
          231 PRINT_NEWLINE
          232 JUMP_ABSOLUTE 590 to 244
 L. 53    233 LOAD_CONST str: Ask someone to teach regrtest.py about which tests are
          234 PRINT_ITEM
          235 PRINT_NEWLINE
 L. 54    236 LOAD_CONST str: expected to get skipped on
          237 PRINT_ITEM
          238 LOAD_FAST str: plat
          239 LOAD_CONST str: .
          240 BINARY_ADD
          241 PRINT_ITEM
          242 PRINT_NEWLINE
          243 JUMP_FORWARD 0 to 244
 L. 56    244 LOAD_DEREF str: rerun
          245 POP_JUMP_IF_FALSE 638 to 264
 L. 57    246 LOAD_CONST str: 
          247 PRINT_ITEM
          248 PRINT_NEWLINE
 L. 58    249 LOAD_CONST str: %s:
          250 LOAD_GLOBAL str: count
          251 LOAD_GLOBAL str: len
          252 LOAD_DEREF str: rerun
          253 CALL_FUNCTION 1
          254 LOAD_CONST str: re-run test
          255 CALL_FUNCTION 2
          256 BINARY_MODULO
          257 PRINT_ITEM
          258 PRINT_NEWLINE
 L. 59    259 LOAD_GLOBAL str: printlist
          260 LOAD_DEREF str: rerun
          261 CALL_FUNCTION 1
          262 POP_TOP
          263 JUMP_FORWARD 0 to 264
 L. 61    264 LOAD_DEREF str: run_no_tests
          265 POP_JUMP_IF_FALSE 686 to 284
 L. 62    266 LOAD_CONST str: 
          267 PRINT_ITEM
          268 PRINT_NEWLINE
 L. 63    269 LOAD_CONST str: %s run no tests:
          270 LOAD_GLOBAL str: count
          271 LOAD_GLOBAL str: len
          272 LOAD_DEREF str: run_no_tests
          273 CALL_FUNCTION 1
          274 LOAD_CONST str: test
          275 CALL_FUNCTION 2
          276 BINARY_MODULO
          277 PRINT_ITEM
          278 PRINT_NEWLINE
 L. 64    279 LOAD_GLOBAL str: printlist
          280 LOAD_DEREF str: run_no_tests
          281 CALL_FUNCTION 1
          282 POP_TOP
          283 JUMP_FORWARD 0 to 284
          284 LOAD_CONST obj: N
          285 RETURN_VALUE

class MultiprocessThread:

build class function MultiprocessThread():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  2      2 LOAD_CONST obj: N
            3 STORE_NAME str: current_test
 L.  3      4 LOAD_CONST obj: N
            5 STORE_NAME str: start_time
 L.  5      6 LOAD_CLOSURE str: PIPE
            7 LOAD_CLOSURE str: Popen
            8 LOAD_CLOSURE str: base_cmd
            9 LOAD_CLOSURE str: debug_output_pat
           10 LOAD_CLOSURE str: output
           11 LOAD_CLOSURE str: pending
           12 LOAD_CLOSURE str: testdir
           13 BUILD_TUPLE 7
           14 LOAD_CONST obj: c
           15 MAKE_CLOSURE 0
           16 STORE_NAME str: runtest
 L. 45     17 LOAD_CLOSURE str: output
           18 BUILD_TUPLE 1
           19 LOAD_CONST obj: c
           20 MAKE_CLOSURE 0
           21 STORE_NAME str: run
           22 LOAD_LOCALS
           23 RETURN_VALUE

closure runtest(self):

 L.  2      0 SETUP_EXCEPT 22 to 9
 L.  3      1 LOAD_GLOBAL str: next
            2 LOAD_DEREF str: pending
            3 CALL_FUNCTION 1
            4 UNPACK_SEQUENCE 2
            5 STORE_FAST str: test
            6 STORE_FAST str: args_tuple
            7 POP_BLOCK
            8 JUMP_FORWARD 31 to 24
 L.  4      9 DUP_TOP
           10 LOAD_GLOBAL str: StopIteration
           11 COMPARE_OP 10
           12 POP_JUMP_IF_FALSE 55 to 23
           13 POP_TOP
           14 POP_TOP
           15 POP_TOP
 L.  5     16 LOAD_DEREF str: output
           17 LOAD_ATTR str: put
           18 LOAD_CONST (obj: N,obj: N,obj: N,obj: N,)
           19 CALL_FUNCTION 1
           20 POP_TOP
 L.  6     21 LOAD_GLOBAL str: True
           22 RETURN_VALUE to 23
           23 END_FINALLY to 24
 L.  9     24 LOAD_DEREF str: base_cmd
           25 LOAD_CONST str: --slaveargs
           26 LOAD_GLOBAL str: json
           27 LOAD_ATTR str: dumps
           28 LOAD_FAST str: args_tuple
           29 CALL_FUNCTION 1
           30 BUILD_LIST 2
           31 BINARY_ADD
           32 STORE_FAST str: args
 L. 10     33 LOAD_DEREF str: testdir
           34 POP_JUMP_IF_FALSE 109 to 43
 L. 11     35 LOAD_FAST str: args
           36 LOAD_ATTR str: extend
           37 LOAD_CONST str: --testdir
           38 LOAD_DEREF str: testdir
           39 BUILD_TUPLE 2
           40 CALL_FUNCTION 1
           41 POP_TOP
           42 JUMP_FORWARD 0 to 43
 L. 12     43 SETUP_FINALLY 103 to 79
 L. 13     44 LOAD_GLOBAL str: time
           45 LOAD_ATTR str: time
           46 CALL_FUNCTION 0
           47 LOAD_FAST str: self
           48 STORE_ATTR str: start_time
 L. 14     49 LOAD_FAST str: test
           50 LOAD_FAST str: self
           51 STORE_ATTR str: current_test
 L. 15     52 LOAD_DEREF str: Popen
           53 LOAD_FAST str: args
           54 LOAD_CONST str: stdout
 L. 16     55 LOAD_DEREF str: PIPE
           56 LOAD_CONST str: stderr
           57 LOAD_DEREF str: PIPE
           58 LOAD_CONST str: universal_newlines
 L. 17     59 LOAD_GLOBAL str: True
           60 LOAD_CONST str: close_fds
 L. 18     61 LOAD_GLOBAL str: os
           62 LOAD_ATTR str: name
           63 LOAD_CONST str: nt
           64 COMPARE_OP 3
           65 CALL_FUNCTION 1025
           66 STORE_FAST str: popen
 L. 19     67 LOAD_FAST str: popen
           68 LOAD_ATTR str: communicate
           69 CALL_FUNCTION 0
           70 UNPACK_SEQUENCE 2
           71 STORE_FAST str: stdout
           72 STORE_FAST str: stderr
 L. 20     73 LOAD_FAST str: popen
           74 LOAD_ATTR str: wait
           75 CALL_FUNCTION 0
           76 STORE_FAST str: retcode
           77 POP_BLOCK
           78 LOAD_CONST obj: N
 L. 22     79 LOAD_CONST obj: N
           80 LOAD_FAST str: self
           81 STORE_ATTR str: current_test
           82 END_FINALLY to 83
 L. 26     83 LOAD_DEREF str: debug_output_pat
           84 LOAD_ATTR str: sub
           85 LOAD_CONST str: 
           86 LOAD_FAST str: stderr
           87 CALL_FUNCTION 2
           88 STORE_FAST str: stderr
 L. 28     89 LOAD_FAST str: retcode
           90 LOAD_CONST long: 0
           91 COMPARE_OP 2
           92 POP_JUMP_IF_FALSE 326 to 118
 L. 29     93 LOAD_FAST str: stdout
           94 LOAD_ATTR str: strip
           95 CALL_FUNCTION 0
           96 LOAD_ATTR str: rpartition
           97 LOAD_CONST str: 

           98 CALL_FUNCTION 1
           99 UNPACK_SEQUENCE 3
          100 STORE_FAST str: stdout
          101 STORE_FAST str: _
          102 STORE_FAST str: result
 L. 30    103 LOAD_FAST str: result
          104 POP_JUMP_IF_TRUE 308 to 112
 L. 31    105 LOAD_DEREF str: output
          106 LOAD_ATTR str: put
          107 LOAD_CONST (obj: N,obj: N,obj: N,obj: N,)
          108 CALL_FUNCTION 1
          109 POP_TOP
 L. 32    110 LOAD_GLOBAL str: True
          111 RETURN_VALUE to 112
 L. 34    112 LOAD_GLOBAL str: json
          113 LOAD_ATTR str: loads
          114 LOAD_FAST str: result
          115 CALL_FUNCTION 1
          116 STORE_FAST str: result
          117 JUMP_FORWARD 16 to 124
 L. 36    118 LOAD_GLOBAL str: CHILD_ERROR
          119 LOAD_CONST str: Exit code %s
          120 LOAD_FAST str: retcode
          121 BINARY_MODULO
          122 BUILD_TUPLE 2
          123 STORE_FAST str: result
 L. 38    124 LOAD_DEREF str: output
          125 LOAD_ATTR str: put
          126 LOAD_FAST str: test
          127 LOAD_FAST str: stdout
          128 LOAD_ATTR str: rstrip
          129 CALL_FUNCTION 0
          130 LOAD_FAST str: stderr
          131 LOAD_ATTR str: rstrip
          132 CALL_FUNCTION 0
          133 LOAD_FAST str: result
          134 BUILD_TUPLE 4
          135 CALL_FUNCTION 1
          136 POP_TOP
 L. 39    137 LOAD_GLOBAL str: False
          138 RETURN_VALUE

closure run(self):

 L.  2      0 SETUP_EXCEPT 35 to 14
 L.  3      1 LOAD_GLOBAL str: False
            2 STORE_FAST str: stop
 L.  4      3 SETUP_LOOP 12
            4 LOAD_FAST str: stop
            5 POP_JUMP_IF_TRUE 33 to 11
 L.  5      6 LOAD_FAST str: self
            7 LOAD_ATTR str: runtest
            8 CALL_FUNCTION 0
            9 STORE_FAST str: stop
           10 CONTINUE_LOOP 12 to 4
           11 POP_BLOCK
           12 POP_BLOCK
           13 JUMP_FORWARD 33 to 29
 L.  6     14 DUP_TOP
           15 LOAD_GLOBAL str: BaseException
           16 COMPARE_OP 10
           17 POP_JUMP_IF_FALSE 70 to 28
           18 POP_TOP
           19 POP_TOP
           20 POP_TOP
 L.  7     21 LOAD_DEREF str: output
           22 LOAD_ATTR str: put
           23 LOAD_CONST (obj: N,obj: N,obj: N,obj: N,)
           24 CALL_FUNCTION 1
           25 POP_TOP
 L.  8     26 RAISE_VARARGS 0
           27 JUMP_FORWARD 1 to 29
           28 END_FINALLY to 29
           29 LOAD_CONST obj: N
           30 RETURN_VALUE


function findtests(testdir,stdtests,nottests):

 L.  3      0 LOAD_GLOBAL str: findtestdir
            1 LOAD_FAST str: testdir
            2 CALL_FUNCTION 1
            3 STORE_FAST str: testdir
 L.  4      4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: listdir
            6 LOAD_FAST str: testdir
            7 CALL_FUNCTION 1
            8 STORE_FAST str: names
 L.  5      9 BUILD_LIST 0
           10 STORE_FAST str: tests
 L.  6     11 LOAD_GLOBAL str: set
           12 LOAD_FAST str: stdtests
           13 CALL_FUNCTION 1
           14 LOAD_FAST str: nottests
           15 BINARY_OR
           16 STORE_FAST str: others
 L.  7     17 SETUP_LOOP 52
           18 LOAD_FAST str: names
           19 GET_ITER
           20 FOR_ITER 86 to 54
           21 STORE_FAST str: name
 L.  8     22 LOAD_GLOBAL str: os
           23 LOAD_ATTR str: path
           24 LOAD_ATTR str: splitext
           25 LOAD_FAST str: name
           26 CALL_FUNCTION 1
           27 UNPACK_SEQUENCE 2
           28 STORE_FAST str: modname
           29 STORE_FAST str: ext
 L.  9     30 LOAD_FAST str: modname
           31 LOAD_CONST long: 5
           32 SLICE_2
           33 LOAD_CONST str: test_
           34 COMPARE_OP 2
           35 POP_JUMP_IF_TRUE 56 to 37
           36 CONTINUE_LOOP 1 to 20
           37 LOAD_FAST str: ext
           38 LOAD_CONST str: .py
           39 COMPARE_OP 2
           40 POP_JUMP_IF_TRUE 56 to 42
           41 CONTINUE_LOOP 1 to 20
           42 LOAD_FAST str: modname
           43 LOAD_FAST str: others
           44 COMPARE_OP 7
           45 POP_JUMP_IF_TRUE 56 to 47
           46 CONTINUE_LOOP 1 to 20
 L. 10     47 LOAD_FAST str: tests
           48 LOAD_ATTR str: append
           49 LOAD_FAST str: modname
           50 CALL_FUNCTION 1
           51 POP_TOP
           52 DUMMY 56 to 20
           53 JUMP_ABSOLUTE 56 to 20
           54 POP_BLOCK
 L. 11     55 LOAD_FAST str: stdtests
           56 LOAD_GLOBAL str: sorted
           57 LOAD_FAST str: tests
           58 CALL_FUNCTION 1
           59 BINARY_ADD
           60 RETURN_VALUE

function runtest(test,verbose,quiet,huntrleaks,use_resources,pgo,failfast,match_tests,testdir):

 L. 26      0 LOAD_FAST str: verbose
            1 LOAD_GLOBAL str: support
            2 STORE_ATTR str: verbose
 L. 27      3 LOAD_FAST str: use_resources
            4 LOAD_CONST obj: N
            5 COMPARE_OP 9
            6 POP_JUMP_IF_FALSE 33 to 11
 L. 28      7 LOAD_FAST str: use_resources
            8 LOAD_GLOBAL str: support
            9 STORE_ATTR str: use_resources
           10 JUMP_FORWARD 0 to 11
 L. 29     11 SETUP_FINALLY 69 to 37
 L. 30     12 LOAD_GLOBAL str: support
           13 LOAD_ATTR str: set_match_tests
           14 LOAD_FAST str: match_tests
           15 CALL_FUNCTION 1
           16 POP_TOP
 L. 33     17 LOAD_GLOBAL str: False
           18 LOAD_GLOBAL str: support
           19 STORE_ATTR str: environment_altered
 L. 34     20 LOAD_FAST str: failfast
           21 POP_JUMP_IF_FALSE 76 to 26
 L. 35     22 LOAD_GLOBAL str: True
           23 LOAD_GLOBAL str: support
           24 STORE_ATTR str: failfast
           25 JUMP_FORWARD 0 to 26
 L. 37     26 LOAD_GLOBAL str: runtest_inner
           27 LOAD_FAST str: test
           28 LOAD_FAST str: verbose
           29 LOAD_FAST str: quiet
           30 LOAD_FAST str: huntrleaks
           31 LOAD_FAST str: pgo
           32 LOAD_FAST str: testdir
           33 CALL_FUNCTION 6
           34 RETURN_VALUE to 35
           35 POP_BLOCK
           36 LOAD_CONST obj: N
 L. 39     37 LOAD_GLOBAL str: cleanup_test_droppings
           38 LOAD_FAST str: test
           39 LOAD_FAST str: verbose
           40 CALL_FUNCTION 2
           41 POP_TOP
           42 END_FINALLY to 43
           43 LOAD_CONST obj: N
           44 RETURN_VALUE

function post_test_cleanup():

 L.  2      0 LOAD_GLOBAL str: support
            1 LOAD_ATTR str: reap_children
            2 CALL_FUNCTION 0
            3 POP_TOP
            4 LOAD_CONST obj: N
            5 RETURN_VALUE

function runtest_inner(test,verbose,quiet,huntrleaks,pgo,testdir):

 L.  2      0 LOAD_GLOBAL str: support
            1 LOAD_ATTR str: unload
            2 LOAD_FAST str: test
            3 CALL_FUNCTION 1
            4 POP_TOP
 L.  3      5 LOAD_FAST str: verbose
            6 POP_JUMP_IF_FALSE 28 to 10
 L.  4      7 LOAD_CONST obj: N
            8 STORE_FAST str: capture_stdout
            9 JUMP_FORWARD 12 to 14
 L.  6     10 LOAD_GLOBAL str: StringIO
           11 LOAD_ATTR str: StringIO
           12 CALL_FUNCTION 0
           13 STORE_FAST str: capture_stdout
 L.  8     14 LOAD_CONST float: 0.000000
           15 STORE_FAST str: test_time
 L.  9     16 LOAD_GLOBAL str: False
           17 STORE_FAST str: refleak
 L. 10     18 SETUP_EXCEPT 274 to 117
 L. 11     19 LOAD_GLOBAL str: sys
           20 LOAD_ATTR str: stdout
           21 STORE_FAST str: save_stdout
 L. 12     22 SETUP_FINALLY 248 to 111
 L. 13     23 LOAD_FAST str: capture_stdout
           24 POP_JUMP_IF_FALSE 85 to 29
 L. 14     25 LOAD_FAST str: capture_stdout
           26 LOAD_GLOBAL str: sys
           27 STORE_ATTR str: stdout
           28 JUMP_FORWARD 0 to 29
 L. 15     29 LOAD_GLOBAL str: get_abs_module
           30 LOAD_FAST str: testdir
           31 LOAD_FAST str: test
           32 CALL_FUNCTION 2
           33 STORE_FAST str: abstest
 L. 16     34 LOAD_GLOBAL str: clear_caches
           35 CALL_FUNCTION 0
           36 POP_TOP
 L. 17     37 LOAD_GLOBAL str: saved_test_environment
           38 LOAD_FAST str: test
           39 LOAD_FAST str: verbose
           40 LOAD_FAST str: quiet
           41 LOAD_FAST str: pgo
           42 CALL_FUNCTION 4
           43 SETUP_WITH 60
           44 STORE_FAST str: environment
 L. 18     45 LOAD_GLOBAL str: time
           46 LOAD_ATTR str: time
           47 CALL_FUNCTION 0
           48 STORE_FAST str: start_time
 L. 19     49 LOAD_GLOBAL str: __import__
           50 LOAD_FAST str: abstest
           51 LOAD_GLOBAL str: globals
           52 CALL_FUNCTION 0
           53 LOAD_GLOBAL str: locals
           54 CALL_FUNCTION 0
           55 BUILD_LIST 0
           56 CALL_FUNCTION 4
           57 STORE_FAST str: the_package
 L. 20     58 LOAD_FAST str: abstest
           59 LOAD_ATTR str: startswith
           60 LOAD_CONST str: test.
           61 CALL_FUNCTION 1
           62 POP_JUMP_IF_FALSE 203 to 69
 L. 21     63 LOAD_GLOBAL str: getattr
           64 LOAD_FAST str: the_package
           65 LOAD_FAST str: test
           66 CALL_FUNCTION 2
           67 STORE_FAST str: the_module
           68 JUMP_FORWARD 6 to 71
 L. 23     69 LOAD_FAST str: the_package
           70 STORE_FAST str: the_module
 L. 27     71 LOAD_GLOBAL str: getattr
           72 LOAD_FAST str: the_module
           73 LOAD_CONST str: test_main
           74 LOAD_CONST obj: N
           75 CALL_FUNCTION 3
           76 STORE_FAST str: indirect_test
 L. 28     77 LOAD_FAST str: huntrleaks
           78 POP_JUMP_IF_FALSE 260 to 88
 L. 29     79 LOAD_GLOBAL str: dash_R
           80 LOAD_FAST str: the_module
           81 LOAD_FAST str: test
           82 LOAD_FAST str: indirect_test
 L. 30     83 LOAD_FAST str: huntrleaks
           84 LOAD_FAST str: quiet
           85 CALL_FUNCTION 5
           86 STORE_FAST str: refleak
           87 JUMP_FORWARD 22 to 96
 L. 32     88 LOAD_FAST str: indirect_test
           89 LOAD_CONST obj: N
           90 COMPARE_OP 9
           91 POP_JUMP_IF_FALSE 282 to 96
 L. 33     92 LOAD_FAST str: indirect_test
           93 CALL_FUNCTION 0
           94 POP_TOP
           95 JUMP_FORWARD 0 to 96
 L. 34     96 LOAD_GLOBAL str: time
           97 LOAD_ATTR str: time
           98 CALL_FUNCTION 0
           99 LOAD_FAST str: start_time
          100 BINARY_SUBTRACT
          101 STORE_FAST str: test_time
          102 POP_BLOCK
          103 LOAD_CONST obj: N
          104 WITH_CLEANUP
          105 END_FINALLY to 106
 L. 35    106 LOAD_GLOBAL str: post_test_cleanup
          107 CALL_FUNCTION 0
          108 POP_TOP
          109 POP_BLOCK
          110 LOAD_CONST obj: N
 L. 37    111 LOAD_FAST str: save_stdout
          112 LOAD_GLOBAL str: sys
          113 STORE_ATTR str: stdout
          114 END_FINALLY to 115
          115 POP_BLOCK
          116 JUMP_FORWARD 421 to 308
 L. 38    117 DUP_TOP
          118 LOAD_GLOBAL str: support
          119 LOAD_ATTR str: ResourceDenied
          120 COMPARE_OP 10
          121 POP_JUMP_IF_FALSE 400 to 148
          122 POP_TOP
          123 STORE_FAST str: msg
          124 POP_TOP
 L. 39    125 LOAD_FAST str: quiet
          126 UNARY_NOT
          127 POP_JUMP_IF_FALSE 390 to 144
          128 LOAD_FAST str: pgo
          129 UNARY_NOT
          130 POP_JUMP_IF_FALSE 390 to 144
 L. 40    131 LOAD_FAST str: test
          132 PRINT_ITEM
          133 LOAD_CONST str: skipped --
          134 PRINT_ITEM
          135 LOAD_FAST str: msg
          136 PRINT_ITEM
          137 PRINT_NEWLINE
 L. 41    138 LOAD_GLOBAL str: sys
          139 LOAD_ATTR str: stdout
          140 LOAD_ATTR str: flush
          141 CALL_FUNCTION 0
          142 POP_TOP
          143 JUMP_FORWARD 0 to 144
 L. 42    144 LOAD_GLOBAL str: RESOURCE_DENIED
          145 LOAD_FAST str: test_time
          146 BUILD_TUPLE 2
          147 RETURN_VALUE to 148
 L. 43    148 DUP_TOP
          149 LOAD_GLOBAL str: unittest
          150 LOAD_ATTR str: SkipTest
          151 COMPARE_OP 10
          152 POP_JUMP_IF_FALSE 471 to 179
          153 POP_TOP
          154 STORE_FAST str: msg
          155 POP_TOP
 L. 44    156 LOAD_FAST str: quiet
          157 UNARY_NOT
          158 POP_JUMP_IF_FALSE 461 to 175
          159 LOAD_FAST str: pgo
          160 UNARY_NOT
          161 POP_JUMP_IF_FALSE 461 to 175
 L. 45    162 LOAD_FAST str: test
          163 PRINT_ITEM
          164 LOAD_CONST str: skipped --
          165 PRINT_ITEM
          166 LOAD_FAST str: msg
          167 PRINT_ITEM
          168 PRINT_NEWLINE
 L. 46    169 LOAD_GLOBAL str: sys
          170 LOAD_ATTR str: stdout
          171 LOAD_ATTR str: flush
          172 CALL_FUNCTION 0
          173 POP_TOP
          174 JUMP_FORWARD 0 to 175
 L. 47    175 LOAD_GLOBAL str: SKIPPED
          176 LOAD_FAST str: test_time
          177 BUILD_TUPLE 2
          178 RETURN_VALUE to 179
 L. 48    179 DUP_TOP
          180 LOAD_GLOBAL str: KeyboardInterrupt
          181 COMPARE_OP 10
          182 POP_JUMP_IF_FALSE 490 to 188
          183 POP_TOP
          184 POP_TOP
          185 POP_TOP
 L. 49    186 RAISE_VARARGS 0
          187 JUMP_FORWARD 404 to 368
 L. 50    188 DUP_TOP
          189 LOAD_GLOBAL str: support
          190 LOAD_ATTR str: TestFailed
          191 COMPARE_OP 10
          192 POP_JUMP_IF_FALSE 571 to 227
          193 POP_TOP
          194 STORE_FAST str: msg
          195 POP_TOP
 L. 51    196 LOAD_FAST str: pgo
          197 POP_JUMP_IF_TRUE 548 to 218
 L. 52    198 LOAD_GLOBAL str: sys
          199 LOAD_ATTR str: stderr
          200 DUP_TOP
          201 LOAD_CONST str: test
          202 ROT_TWO
          203 PRINT_ITEM_TO
          204 DUP_TOP
          205 LOAD_FAST str: test
          206 ROT_TWO
          207 PRINT_ITEM_TO
          208 DUP_TOP
          209 LOAD_CONST str: failed --
          210 ROT_TWO
          211 PRINT_ITEM_TO
          212 DUP_TOP
          213 LOAD_FAST str: msg
          214 ROT_TWO
          215 PRINT_ITEM_TO
          216 PRINT_NEWLINE_TO
          217 JUMP_FORWARD 0 to 218
 L. 53    218 LOAD_GLOBAL str: sys
          219 LOAD_ATTR str: stderr
          220 LOAD_ATTR str: flush
          221 CALL_FUNCTION 0
          222 POP_TOP
 L. 54    223 LOAD_GLOBAL str: FAILED
          224 LOAD_FAST str: test_time
          225 BUILD_TUPLE 2
          226 RETURN_VALUE to 227
 L. 55    227 DUP_TOP
          228 LOAD_GLOBAL str: support
          229 LOAD_ATTR str: TestDidNotRun
          230 COMPARE_OP 10
          231 POP_JUMP_IF_FALSE 597 to 239
          232 POP_TOP
          233 POP_TOP
          234 POP_TOP
 L. 56    235 LOAD_GLOBAL str: TEST_DID_NOT_RUN
          236 LOAD_FAST str: test_time
          237 BUILD_TUPLE 2
          238 RETURN_VALUE to 239
 L. 57    239 POP_TOP
          240 POP_TOP
          241 POP_TOP
 L. 58    242 LOAD_GLOBAL str: sys
          243 LOAD_ATTR str: exc_info
          244 CALL_FUNCTION 0
          245 LOAD_CONST long: 2
          246 SLICE_2
          247 UNPACK_SEQUENCE 2
          248 STORE_FAST str: type
          249 STORE_FAST str: value
 L. 59    250 LOAD_FAST str: pgo
          251 POP_JUMP_IF_TRUE 678 to 280
 L. 60    252 LOAD_GLOBAL str: sys
          253 LOAD_ATTR str: stderr
          254 DUP_TOP
          255 LOAD_CONST str: test
          256 ROT_TWO
          257 PRINT_ITEM_TO
          258 DUP_TOP
          259 LOAD_FAST str: test
          260 ROT_TWO
          261 PRINT_ITEM_TO
          262 DUP_TOP
          263 LOAD_CONST str: crashed --
          264 ROT_TWO
          265 PRINT_ITEM_TO
          266 DUP_TOP
          267 LOAD_GLOBAL str: str
          268 LOAD_FAST str: type
          269 CALL_FUNCTION 1
          270 LOAD_CONST str: :
          271 BINARY_ADD
          272 ROT_TWO
          273 PRINT_ITEM_TO
          274 DUP_TOP
          275 LOAD_FAST str: value
          276 ROT_TWO
          277 PRINT_ITEM_TO
          278 PRINT_NEWLINE_TO
          279 JUMP_FORWARD 0 to 280
 L. 61    280 LOAD_GLOBAL str: sys
          281 LOAD_ATTR str: stderr
          282 LOAD_ATTR str: flush
          283 CALL_FUNCTION 0
          284 POP_TOP
 L. 62    285 LOAD_FAST str: verbose
          286 POP_JUMP_IF_FALSE 739 to 303
          287 LOAD_FAST str: pgo
          288 UNARY_NOT
          289 POP_JUMP_IF_FALSE 739 to 303
 L. 63    290 LOAD_GLOBAL str: traceback
          291 LOAD_ATTR str: print_exc
          292 LOAD_CONST str: file
          293 LOAD_GLOBAL str: sys
          294 LOAD_ATTR str: stderr
          295 CALL_FUNCTION 256
          296 POP_TOP
 L. 64    297 LOAD_GLOBAL str: sys
          298 LOAD_ATTR str: stderr
          299 LOAD_ATTR str: flush
          300 CALL_FUNCTION 0
          301 POP_TOP
          302 JUMP_FORWARD 0 to 303
 L. 65    303 LOAD_GLOBAL str: FAILED
          304 LOAD_FAST str: test_time
          305 BUILD_TUPLE 2
          306 RETURN_VALUE to 307
          307 END_FINALLY to 308
 L. 67    308 LOAD_FAST str: refleak
          309 POP_JUMP_IF_FALSE 766 to 314
 L. 68    310 LOAD_GLOBAL str: FAILED
          311 LOAD_FAST str: test_time
          312 BUILD_TUPLE 2
          313 RETURN_VALUE to 314
 L. 69    314 LOAD_FAST str: environment
          315 LOAD_ATTR str: changed
          316 POP_JUMP_IF_FALSE 785 to 321
 L. 70    317 LOAD_GLOBAL str: ENV_CHANGED
          318 LOAD_FAST str: test_time
          319 BUILD_TUPLE 2
          320 RETURN_VALUE to 321
 L. 72    321 LOAD_FAST str: verbose
          322 POP_JUMP_IF_TRUE 797 to 325
          323 LOAD_FAST str: huntrleaks
          324 POP_JUMP_IF_FALSE 807 to 329
 L. 73    325 LOAD_GLOBAL str: PASSED
          326 LOAD_FAST str: test_time
          327 BUILD_TUPLE 2
          328 RETURN_VALUE to 329
 L. 74    329 LOAD_FAST str: capture_stdout
          330 LOAD_ATTR str: getvalue
          331 CALL_FUNCTION 0
          332 STORE_FAST str: output
 L. 75    333 LOAD_FAST str: output
          334 POP_JUMP_IF_TRUE 835 to 339
 L. 76    335 LOAD_GLOBAL str: PASSED
          336 LOAD_FAST str: test_time
          337 BUILD_TUPLE 2
          338 RETURN_VALUE to 339
 L. 77    339 LOAD_CONST str: test
          340 PRINT_ITEM
          341 LOAD_FAST str: test
          342 PRINT_ITEM
          343 LOAD_CONST str: produced unexpected output:
          344 PRINT_ITEM
          345 PRINT_NEWLINE
 L. 78    346 LOAD_CONST str: *
          347 LOAD_CONST long: 70
          348 BINARY_MULTIPLY
          349 PRINT_ITEM
          350 PRINT_NEWLINE
 L. 79    351 LOAD_FAST str: output
          352 PRINT_ITEM
          353 PRINT_NEWLINE
 L. 80    354 LOAD_CONST str: *
          355 LOAD_CONST long: 70
          356 BINARY_MULTIPLY
          357 PRINT_ITEM
          358 PRINT_NEWLINE
 L. 81    359 LOAD_GLOBAL str: sys
          360 LOAD_ATTR str: stdout
          361 LOAD_ATTR str: flush
          362 CALL_FUNCTION 0
          363 POP_TOP
 L. 82    364 LOAD_GLOBAL str: FAILED
          365 LOAD_FAST str: test_time
          366 BUILD_TUPLE 2
          367 RETURN_VALUE to 368
          368 LOAD_CONST obj: N
          369 RETURN_VALUE

function cleanup_test_droppings(testname,verbose):

 L.  2      0 LOAD_CONST long: -1
            1 LOAD_CONST obj: N
            2 IMPORT_NAME str: stat
            3 STORE_FAST str: stat
 L.  3      4 LOAD_CONST long: -1
            5 LOAD_CONST obj: N
            6 IMPORT_NAME str: gc
            7 STORE_FAST str: gc
 L.  6      8 LOAD_FAST str: gc
            9 LOAD_ATTR str: collect
           10 CALL_FUNCTION 0
           11 POP_TOP
 L. 14     12 SETUP_LOOP 121
           13 LOAD_GLOBAL str: support
           14 LOAD_ATTR str: TESTFN
 L. 15     15 LOAD_CONST str: db_home
           16 BUILD_TUPLE 2
           17 GET_ITER
           18 FOR_ITER 263 to 120
           19 STORE_FAST str: name
 L. 17     20 LOAD_GLOBAL str: os
           21 LOAD_ATTR str: path
           22 LOAD_ATTR str: exists
           23 LOAD_FAST str: name
           24 CALL_FUNCTION 1
           25 POP_JUMP_IF_TRUE 80 to 28
 L. 18     26 CONTINUE_LOOP 50 to 18
           27 JUMP_FORWARD 0 to 28
 L. 20     28 LOAD_GLOBAL str: os
           29 LOAD_ATTR str: path
           30 LOAD_ATTR str: isdir
           31 LOAD_FAST str: name
           32 CALL_FUNCTION 1
           33 POP_JUMP_IF_FALSE 117 to 41
 L. 21     34 LOAD_CONST str: directory
           35 LOAD_GLOBAL str: shutil
           36 LOAD_ATTR str: rmtree
           37 ROT_TWO
           38 STORE_FAST str: kind
           39 STORE_FAST str: nuker
           40 JUMP_FORWARD 53 to 60
 L. 22     41 LOAD_GLOBAL str: os
           42 LOAD_ATTR str: path
           43 LOAD_ATTR str: isfile
           44 LOAD_FAST str: name
           45 CALL_FUNCTION 1
           46 POP_JUMP_IF_FALSE 154 to 54
 L. 23     47 LOAD_CONST str: file
           48 LOAD_GLOBAL str: os
           49 LOAD_ATTR str: unlink
           50 ROT_TWO
           51 STORE_FAST str: kind
           52 STORE_FAST str: nuker
           53 JUMP_FORWARD 16 to 60
 L. 25     54 LOAD_GLOBAL str: SystemError
           55 LOAD_CONST str: os.path says %r exists but is neither directory nor file
 L. 26     56 LOAD_FAST str: name
           57 BINARY_MODULO
           58 CALL_FUNCTION 1
           59 RAISE_VARARGS 1
 L. 28     60 LOAD_FAST str: verbose
           61 POP_JUMP_IF_FALSE 197 to 71
 L. 29     62 LOAD_CONST str: %r left behind %s %r
           63 LOAD_FAST str: testname
           64 LOAD_FAST str: kind
           65 LOAD_FAST str: name
           66 BUILD_TUPLE 3
           67 BINARY_MODULO
           68 PRINT_ITEM
           69 PRINT_NEWLINE
           70 JUMP_FORWARD 0 to 71
 L. 30     71 SETUP_EXCEPT 65 to 97
 L. 33     72 LOAD_GLOBAL str: hasattr
           73 LOAD_GLOBAL str: os
           74 LOAD_CONST str: chmod
           75 CALL_FUNCTION 2
           76 POP_JUMP_IF_FALSE 251 to 91
 L. 34     77 LOAD_GLOBAL str: os
           78 LOAD_ATTR str: chmod
           79 LOAD_FAST str: name
           80 LOAD_FAST str: stat
           81 LOAD_ATTR str: S_IRWXU
           82 LOAD_FAST str: stat
           83 LOAD_ATTR str: S_IRWXG
           84 BINARY_OR
           85 LOAD_FAST str: stat
           86 LOAD_ATTR str: S_IRWXO
           87 BINARY_OR
           88 CALL_FUNCTION 2
           89 POP_TOP
           90 JUMP_FORWARD 0 to 91
 L. 35     91 LOAD_FAST str: nuker
           92 LOAD_FAST str: name
           93 CALL_FUNCTION 1
           94 POP_TOP
           95 POP_BLOCK
           96 CONTINUE_LOOP 50 to 18
 L. 36     97 DUP_TOP
           98 LOAD_GLOBAL str: Exception
           99 COMPARE_OP 10
          100 POP_JUMP_IF_FALSE 312 to 118
          101 POP_TOP
          102 STORE_FAST str: msg
          103 POP_TOP
 L. 37    104 LOAD_GLOBAL str: sys
          105 LOAD_ATTR str: stderr
          106 DUP_TOP
          107 LOAD_CONST str: %r left behind %s %r and it couldn't be removed: %s
 L. 38    108 LOAD_FAST str: testname
          109 LOAD_FAST str: kind
          110 LOAD_FAST str: name
          111 LOAD_FAST str: msg
          112 BUILD_TUPLE 4
          113 BINARY_MODULO
          114 ROT_TWO
          115 PRINT_ITEM_TO
          116 PRINT_NEWLINE_TO
          117 CONTINUE_LOOP 50 to 18
          118 END_FINALLY to 119
          119 CONTINUE_LOOP 50 to 18
          120 POP_BLOCK
          121 LOAD_CONST obj: N
          122 RETURN_VALUE

function dash_R(the_module,test,indirect_test,huntrleaks,quiet):

 L.  8      0 LOAD_CONST long: -1
            1 LOAD_CONST obj: N
            2 IMPORT_NAME str: copy_reg
            3 STORE_FAST str: copy_reg
            4 LOAD_CONST long: -1
            5 LOAD_CONST obj: N
            6 IMPORT_NAME str: _abcoll
            7 STORE_FAST str: _abcoll
            8 LOAD_CONST long: -1
            9 LOAD_CONST obj: N
           10 IMPORT_NAME str: _pyio
           11 STORE_FAST str: _pyio
 L. 10     12 LOAD_GLOBAL str: hasattr
           13 LOAD_GLOBAL str: sys
           14 LOAD_CONST str: gettotalrefcount
           15 CALL_FUNCTION 2
           16 POP_JUMP_IF_TRUE 66 to 22
 L. 11     17 LOAD_GLOBAL str: Exception
           18 LOAD_CONST str: Tracking reference leaks requires a debug build of Python
           19 CALL_FUNCTION 1
           20 RAISE_VARARGS 1
           21 JUMP_FORWARD 0 to 22
 L. 16     22 LOAD_GLOBAL str: warm_caches
           23 CALL_FUNCTION 0
           24 POP_TOP
 L. 19     25 LOAD_GLOBAL str: warnings
           26 LOAD_ATTR str: filters
           27 SLICE
           28 STORE_FAST str: fs
 L. 20     29 LOAD_FAST str: copy_reg
           30 LOAD_ATTR str: dispatch_table
           31 LOAD_ATTR str: copy
           32 CALL_FUNCTION 0
           33 STORE_FAST str: ps
 L. 21     34 LOAD_GLOBAL str: sys
           35 LOAD_ATTR str: path_importer_cache
           36 LOAD_ATTR str: copy
           37 CALL_FUNCTION 0
           38 STORE_FAST str: pic
 L. 22     39 SETUP_EXCEPT 16 to 46
 L. 23     40 LOAD_CONST long: -1
           41 LOAD_CONST obj: N
           42 IMPORT_NAME str: zipimport
           43 STORE_FAST str: zipimport
           44 POP_BLOCK
           45 JUMP_FORWARD 23 to 57
 L. 24     46 DUP_TOP
           47 LOAD_GLOBAL str: ImportError
           48 COMPARE_OP 10
           49 POP_JUMP_IF_FALSE 154 to 56
           50 POP_TOP
           51 POP_TOP
           52 POP_TOP
 L. 25     53 LOAD_CONST obj: N
           54 STORE_FAST str: zdc
           55 JUMP_FORWARD 16 to 62
           56 END_FINALLY to 57
 L. 27     57 LOAD_FAST str: zipimport
           58 LOAD_ATTR str: _zip_directory_cache
           59 LOAD_ATTR str: copy
           60 CALL_FUNCTION 0
           61 STORE_FAST str: zdc
 L. 28     62 BUILD_MAP 0
           63 STORE_FAST str: abcs
 L. 29     64 LOAD_FAST str: _abcoll
           65 LOAD_FAST str: _pyio
           66 BUILD_TUPLE 2
           67 STORE_FAST str: modules
 L. 30     68 SETUP_LOOP 117
           69 BUILD_LIST 0
           70 LOAD_FAST str: modules
           71 GET_ITER
           72 FOR_ITER 37 to 86
           73 STORE_FAST str: mod
           74 LOAD_FAST str: mod
           75 LOAD_ATTR str: __all__
           76 GET_ITER
           77 FOR_ITER 21 to 85
           78 STORE_FAST str: a
           79 LOAD_GLOBAL str: getattr
           80 LOAD_FAST str: mod
           81 LOAD_FAST str: a
           82 CALL_FUNCTION 2
           83 LIST_APPEND 3
           84 CONTINUE_LOOP 211 to 77
           85 CONTINUE_LOOP 198 to 72
           86 GET_ITER
           87 FOR_ITER 76 to 116
           88 STORE_FAST str: abc
 L. 32     89 LOAD_GLOBAL str: hasattr
           90 LOAD_FAST str: abc
           91 LOAD_CONST str: _abc_registry
           92 CALL_FUNCTION 2
           93 POP_JUMP_IF_TRUE 266 to 96
 L. 33     94 CONTINUE_LOOP 239 to 87
           95 JUMP_FORWARD 0 to 96
 L. 34     96 SETUP_LOOP 115
           97 LOAD_FAST str: abc
           98 LOAD_ATTR str: __subclasses__
           99 CALL_FUNCTION 0
          100 LOAD_FAST str: abc
          101 BUILD_LIST 1
          102 BINARY_ADD
          103 GET_ITER
          104 FOR_ITER 25 to 114
          105 STORE_FAST str: obj
 L. 35    106 LOAD_FAST str: obj
          107 LOAD_ATTR str: _abc_registry
          108 LOAD_ATTR str: copy
          109 CALL_FUNCTION 0
          110 LOAD_FAST str: abcs
          111 LOAD_FAST str: obj
          112 STORE_SUBSCR
          113 CONTINUE_LOOP 286 to 104
          114 POP_BLOCK
          115 JUMP_ABSOLUTE 239 to 87
          116 POP_BLOCK
 L. 41    117 LOAD_CONST obj: c
          118 MAKE_FUNCTION 0
          119 LOAD_GLOBAL str: range
          120 LOAD_CONST long: -1000
          121 LOAD_CONST long: 1000
          122 CALL_FUNCTION 2
          123 GET_ITER
          124 CALL_FUNCTION 1
          125 STORE_DEREF str: int_pool
 L. 42    126 LOAD_CLOSURE str: int_pool
          127 BUILD_TUPLE 1
          128 LOAD_CONST obj: c
          129 MAKE_CLOSURE 0
          130 STORE_FAST str: get_pooled_int
 L. 45    131 LOAD_DEREF str: indirect_test
          132 POP_JUMP_IF_FALSE 383 to 139
 L. 46    133 LOAD_CLOSURE str: indirect_test
          134 BUILD_TUPLE 1
          135 LOAD_CONST obj: c
          136 MAKE_CLOSURE 0
          137 STORE_FAST str: run_the_test
          138 JUMP_FORWARD 15 to 144
 L. 49    139 LOAD_CLOSURE str: the_module
          140 BUILD_TUPLE 1
          141 LOAD_CONST obj: c
          142 MAKE_CLOSURE 0
          143 STORE_FAST str: run_the_test
 L. 52    144 BUILD_LIST 0
          145 STORE_FAST str: deltas
 L. 53    146 LOAD_FAST str: huntrleaks
          147 UNPACK_SEQUENCE 3
          148 STORE_FAST str: nwarmup
          149 STORE_FAST str: ntracked
          150 STORE_FAST str: fname
 L. 54    151 LOAD_GLOBAL str: os
          152 LOAD_ATTR str: path
          153 LOAD_ATTR str: join
          154 LOAD_GLOBAL str: support
          155 LOAD_ATTR str: SAVEDCWD
          156 LOAD_FAST str: fname
          157 CALL_FUNCTION 2
          158 STORE_FAST str: fname
 L. 57    159 LOAD_FAST str: nwarmup
          160 LOAD_FAST str: ntracked
          161 BINARY_ADD
          162 STORE_FAST str: repcount
 L. 58    163 LOAD_CONST long: 0
          164 BUILD_LIST 1
          165 LOAD_FAST str: repcount
          166 BINARY_MULTIPLY
          167 STORE_FAST str: rc_deltas
 L. 59    168 LOAD_CONST long: 0
          169 BUILD_LIST 1
          170 LOAD_FAST str: repcount
          171 BINARY_MULTIPLY
          172 STORE_FAST str: fd_deltas
 L. 60    173 LOAD_GLOBAL str: list
          174 LOAD_GLOBAL str: range
          175 LOAD_FAST str: repcount
          176 CALL_FUNCTION 1
          177 CALL_FUNCTION 1
          178 STORE_FAST str: rep_range
 L. 62    179 LOAD_FAST str: quiet
          180 POP_JUMP_IF_TRUE 560 to 212
 L. 63    181 LOAD_GLOBAL str: sys
          182 LOAD_ATTR str: stderr
          183 DUP_TOP
          184 LOAD_CONST str: beginning
          185 ROT_TWO
          186 PRINT_ITEM_TO
          187 DUP_TOP
          188 LOAD_FAST str: repcount
          189 ROT_TWO
          190 PRINT_ITEM_TO
          191 DUP_TOP
          192 LOAD_CONST str: repetitions
          193 ROT_TWO
          194 PRINT_ITEM_TO
          195 PRINT_NEWLINE_TO
 L. 64    196 LOAD_GLOBAL str: sys
          197 LOAD_ATTR str: stderr
          198 DUP_TOP
          199 LOAD_CONST str: 1234567890
          200 LOAD_FAST str: repcount
          201 LOAD_CONST long: 10
          202 BINARY_FLOOR_DIVIDE
          203 LOAD_CONST long: 1
          204 BINARY_ADD
          205 BINARY_MULTIPLY
          206 LOAD_FAST str: repcount
          207 SLICE_2
          208 ROT_TWO
          209 PRINT_ITEM_TO
          210 PRINT_NEWLINE_TO
          211 JUMP_FORWARD 0 to 212
 L. 66    212 LOAD_GLOBAL str: dash_R_cleanup
          213 LOAD_FAST str: fs
          214 LOAD_FAST str: ps
          215 LOAD_FAST str: pic
          216 LOAD_FAST str: zdc
          217 LOAD_FAST str: abcs
          218 CALL_FUNCTION 5
          219 POP_TOP
 L. 69    220 LOAD_CONST long: 0
          221 DUP_TOP
          222 STORE_FAST str: rc_before
          223 STORE_FAST str: fd_before
 L. 71    224 SETUP_LOOP 279
          225 LOAD_FAST str: rep_range
          226 GET_ITER
          227 FOR_ITER 136 to 278
          228 STORE_FAST str: i
 L. 72    229 LOAD_FAST str: run_the_test
          230 CALL_FUNCTION 0
          231 POP_TOP
 L. 74    232 LOAD_FAST str: quiet
          233 POP_JUMP_IF_TRUE 637 to 241
 L. 75    234 LOAD_GLOBAL str: sys
          235 LOAD_ATTR str: stderr
          236 LOAD_ATTR str: write
          237 LOAD_CONST str: .
          238 CALL_FUNCTION 1
          239 POP_TOP
          240 JUMP_FORWARD 0 to 241
 L. 77    241 LOAD_GLOBAL str: dash_R_cleanup
          242 LOAD_FAST str: fs
          243 LOAD_FAST str: ps
          244 LOAD_FAST str: pic
          245 LOAD_FAST str: zdc
          246 LOAD_FAST str: abcs
          247 CALL_FUNCTION 5
          248 POP_TOP
 L. 79    249 LOAD_GLOBAL str: sys
          250 LOAD_ATTR str: gettotalrefcount
          251 CALL_FUNCTION 0
          252 STORE_FAST str: rc_after
 L. 80    253 LOAD_GLOBAL str: support
          254 LOAD_ATTR str: fd_count
          255 CALL_FUNCTION 0
          256 STORE_FAST str: fd_after
 L. 81    257 LOAD_FAST str: get_pooled_int
          258 LOAD_FAST str: rc_after
          259 LOAD_FAST str: rc_before
          260 BINARY_SUBTRACT
          261 CALL_FUNCTION 1
          262 LOAD_FAST str: rc_deltas
          263 LOAD_FAST str: i
          264 STORE_SUBSCR
 L. 82    265 LOAD_FAST str: get_pooled_int
          266 LOAD_FAST str: fd_after
          267 LOAD_FAST str: fd_before
          268 BINARY_SUBTRACT
          269 CALL_FUNCTION 1
          270 LOAD_FAST str: fd_deltas
          271 LOAD_FAST str: i
          272 STORE_SUBSCR
 L. 83    273 LOAD_FAST str: rc_after
          274 STORE_FAST str: rc_before
 L. 84    275 LOAD_FAST str: fd_after
          276 STORE_FAST str: fd_before
          277 CONTINUE_LOOP 599 to 227
          278 POP_BLOCK
 L. 86    279 LOAD_FAST str: quiet
          280 POP_JUMP_IF_TRUE 755 to 285
 L. 87    281 LOAD_GLOBAL str: sys
          282 LOAD_ATTR str: stderr
          283 PRINT_NEWLINE_TO
          284 JUMP_FORWARD 0 to 285
 L. 90    285 LOAD_CONST obj: c
          286 MAKE_FUNCTION 0
          287 STORE_FAST str: check_rc_deltas
 L.105    288 LOAD_CONST obj: c
          289 MAKE_FUNCTION 0
          290 STORE_FAST str: check_fd_deltas
 L.108    291 LOAD_GLOBAL str: False
          292 STORE_FAST str: failed
 L.109    293 SETUP_LOOP 359
 L.110    294 LOAD_FAST str: rc_deltas
          295 LOAD_CONST str: references
          296 LOAD_FAST str: check_rc_deltas
          297 BUILD_TUPLE 3
 L.111    298 LOAD_FAST str: fd_deltas
          299 LOAD_CONST str: file descriptors
          300 LOAD_FAST str: check_fd_deltas
          301 BUILD_TUPLE 3
          302 BUILD_LIST 2
          303 GET_ITER
          304 FOR_ITER 131 to 359
          305 UNPACK_SEQUENCE 3
          306 STORE_FAST str: deltas
          307 STORE_FAST str: item_name
          308 STORE_FAST str: checker
 L.113    309 LOAD_FAST str: deltas
          310 LOAD_FAST str: nwarmup
          311 SLICE_1
          312 STORE_FAST str: deltas
 L.114    313 LOAD_FAST str: checker
          314 LOAD_FAST str: deltas
          315 CALL_FUNCTION 1
          316 POP_JUMP_IF_TRUE 810 to 318
          317 CONTINUE_LOOP 1 to 304
 L.115    318 LOAD_CONST str: %s leaked %s %s, sum=%s
          319 LOAD_FAST str: test
          320 LOAD_FAST str: deltas
          321 LOAD_FAST str: item_name
          322 LOAD_GLOBAL str: sum
          323 LOAD_FAST str: deltas
          324 CALL_FUNCTION 1
          325 BUILD_TUPLE 4
          326 BINARY_MODULO
          327 STORE_FAST str: msg
 L.116    328 LOAD_GLOBAL str: sys
          329 LOAD_ATTR str: stderr
          330 DUP_TOP
          331 LOAD_FAST str: msg
          332 ROT_TWO
          333 PRINT_ITEM_TO
          334 PRINT_NEWLINE_TO
 L.117    335 LOAD_GLOBAL str: open
          336 LOAD_FAST str: fname
          337 LOAD_CONST str: a
          338 CALL_FUNCTION 2
          339 SETUP_WITH 13
          340 STORE_FAST str: refrep
 L.118    341 LOAD_FAST str: refrep
          342 DUP_TOP
          343 LOAD_FAST str: msg
          344 ROT_TWO
          345 PRINT_ITEM_TO
          346 PRINT_NEWLINE_TO
 L.119    347 LOAD_FAST str: refrep
          348 LOAD_ATTR str: flush
          349 CALL_FUNCTION 0
          350 POP_TOP
          351 POP_BLOCK
          352 LOAD_CONST obj: N
          353 WITH_CLEANUP
          354 END_FINALLY to 355
 L.120    355 LOAD_GLOBAL str: True
          356 STORE_FAST str: failed
          357 CONTINUE_LOOP 810 to 304
          358 CONTINUE_LOOP 810 to 304
          359 POP_BLOCK
 L.121    360 LOAD_FAST str: failed
          361 RETURN_VALUE

function <dictcomp>(.0):

 L.  1      0 BUILD_MAP 0
            1 LOAD_FAST str: .0
            2 FOR_ITER 15 to 8
            3 STORE_FAST str: value
            4 LOAD_FAST str: value
            5 LOAD_FAST str: value
            6 MAP_ADD 2
            7 JUMP_ABSOLUTE 6 to 2
            8 RETURN_VALUE

function check_rc_deltas(deltas):

 L. 14      0 LOAD_GLOBAL str: all
            1 LOAD_CONST obj: c
            2 MAKE_FUNCTION 0
            3 LOAD_FAST str: deltas
            4 GET_ITER
            5 CALL_FUNCTION 1
            6 CALL_FUNCTION 1
            7 RETURN_VALUE

function <genexpr>(.0):

 L.  1      0 LOAD_FAST str: .0
            1 FOR_ITER 17 to 9
            2 STORE_FAST str: delta
            3 LOAD_FAST str: delta
            4 LOAD_CONST long: 1
            5 COMPARE_OP 5
            6 YIELD_VALUE
            7 POP_TOP
            8 JUMP_ABSOLUTE 3 to 1
            9 LOAD_CONST obj: N
           10 RETURN_VALUE

function check_fd_deltas(deltas):

 L.  2      0 LOAD_GLOBAL str: any
            1 LOAD_FAST str: deltas
            2 CALL_FUNCTION 1
            3 RETURN_VALUE

closure get_pooled_int(value):

 L.  2      0 LOAD_DEREF str: int_pool
            1 LOAD_ATTR str: setdefault
            2 LOAD_FAST str: value
            3 LOAD_FAST str: value
            4 CALL_FUNCTION 2
            5 RETURN_VALUE

closure run_the_test():

 L.  2      0 LOAD_DEREF str: indirect_test
            1 CALL_FUNCTION 0
            2 POP_TOP
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

closure run_the_test():

 L.  2      0 LOAD_GLOBAL str: imp
            1 LOAD_ATTR str: reload
            2 LOAD_DEREF str: the_module
            3 CALL_FUNCTION 1
            4 POP_TOP
            5 LOAD_CONST obj: N
            6 RETURN_VALUE

function dash_R_cleanup(fs,ps,pic,zdc,abcs):

 L.  2      0 LOAD_CONST long: -1
            1 LOAD_CONST obj: N
            2 IMPORT_NAME str: gc
            3 STORE_FAST str: gc
            4 LOAD_CONST long: -1
            5 LOAD_CONST obj: N
            6 IMPORT_NAME str: copy_reg
            7 STORE_FAST str: copy_reg
 L.  5      8 LOAD_FAST str: fs
            9 LOAD_GLOBAL str: warnings
           10 LOAD_ATTR str: filters
           11 STORE_SLICE
 L.  6     12 LOAD_FAST str: copy_reg
           13 LOAD_ATTR str: dispatch_table
           14 LOAD_ATTR str: clear
           15 CALL_FUNCTION 0
           16 POP_TOP
 L.  7     17 LOAD_FAST str: copy_reg
           18 LOAD_ATTR str: dispatch_table
           19 LOAD_ATTR str: update
           20 LOAD_FAST str: ps
           21 CALL_FUNCTION 1
           22 POP_TOP
 L.  8     23 LOAD_GLOBAL str: sys
           24 LOAD_ATTR str: path_importer_cache
           25 LOAD_ATTR str: clear
           26 CALL_FUNCTION 0
           27 POP_TOP
 L.  9     28 LOAD_GLOBAL str: sys
           29 LOAD_ATTR str: path_importer_cache
           30 LOAD_ATTR str: update
           31 LOAD_FAST str: pic
           32 CALL_FUNCTION 1
           33 POP_TOP
 L. 10     34 SETUP_EXCEPT 16 to 41
 L. 11     35 LOAD_CONST long: -1
           36 LOAD_CONST obj: N
           37 IMPORT_NAME str: zipimport
           38 STORE_FAST str: zipimport
           39 POP_BLOCK
           40 JUMP_FORWARD 17 to 50
 L. 12     41 DUP_TOP
           42 LOAD_GLOBAL str: ImportError
           43 COMPARE_OP 10
           44 POP_JUMP_IF_FALSE 127 to 49
           45 POP_TOP
           46 POP_TOP
           47 POP_TOP
 L. 13     48 JUMP_FORWARD 30 to 61
           49 END_FINALLY to 50
 L. 15     50 LOAD_FAST str: zipimport
           51 LOAD_ATTR str: _zip_directory_cache
           52 LOAD_ATTR str: clear
           53 CALL_FUNCTION 0
           54 POP_TOP
 L. 16     55 LOAD_FAST str: zipimport
           56 LOAD_ATTR str: _zip_directory_cache
           57 LOAD_ATTR str: update
           58 LOAD_FAST str: zdc
           59 CALL_FUNCTION 1
           60 POP_TOP
 L. 19     61 LOAD_GLOBAL str: sys
           62 LOAD_ATTR str: _clear_type_cache
           63 CALL_FUNCTION 0
           64 POP_TOP
 L. 22     65 SETUP_LOOP 91
           66 LOAD_FAST str: abcs
           67 LOAD_ATTR str: items
           68 CALL_FUNCTION 0
           69 GET_ITER
           70 FOR_ITER 53 to 90
           71 UNPACK_SEQUENCE 2
           72 STORE_FAST str: abc
           73 STORE_FAST str: registry
 L. 23     74 LOAD_FAST str: registry
           75 LOAD_ATTR str: copy
           76 CALL_FUNCTION 0
           77 LOAD_FAST str: abc
           78 STORE_ATTR str: _abc_registry
 L. 24     79 LOAD_FAST str: abc
           80 LOAD_ATTR str: _abc_cache
           81 LOAD_ATTR str: clear
           82 CALL_FUNCTION 0
           83 POP_TOP
 L. 25     84 LOAD_FAST str: abc
           85 LOAD_ATTR str: _abc_negative_cache
           86 LOAD_ATTR str: clear
           87 CALL_FUNCTION 0
           88 POP_TOP
           89 CONTINUE_LOOP 180 to 70
           90 POP_BLOCK
 L. 27     91 LOAD_GLOBAL str: clear_caches
           92 CALL_FUNCTION 0
           93 POP_TOP
           94 LOAD_CONST obj: N
           95 RETURN_VALUE

function clear_caches():

 L.  2      0 LOAD_CONST long: -1
            1 LOAD_CONST obj: N
            2 IMPORT_NAME str: gc
            3 STORE_FAST str: gc
 L.  5      4 SETUP_LOOP 22
            5 LOAD_GLOBAL str: sys
            6 LOAD_ATTR str: modules
            7 LOAD_ATTR str: values
            8 CALL_FUNCTION 0
            9 GET_ITER
           10 FOR_ITER 30 to 22
           11 STORE_FAST str: mod
 L.  6     12 LOAD_GLOBAL str: hasattr
           13 LOAD_FAST str: mod
           14 LOAD_CONST str: __warningregistry__
           15 CALL_FUNCTION 2
           16 POP_JUMP_IF_TRUE 28 to 18
           17 CONTINUE_LOOP 1 to 10
 L.  7     18 LOAD_FAST str: mod
           19 DELETE_ATTR 5
           20 CONTINUE_LOOP 28 to 10
           21 CONTINUE_LOOP 28 to 10
           22 POP_BLOCK
 L. 11     23 SETUP_EXCEPT 17 to 31
 L. 12     24 LOAD_GLOBAL str: sys
           25 LOAD_ATTR str: modules
           26 LOAD_CONST str: distutils.dir_util
           27 BINARY_SUBSCR
           28 STORE_FAST str: distutils_dir_util
           29 POP_BLOCK
           30 JUMP_FORWARD 17 to 40
 L. 13     31 DUP_TOP
           32 LOAD_GLOBAL str: KeyError
           33 COMPARE_OP 10
           34 POP_JUMP_IF_FALSE 98 to 39
           35 POP_TOP
           36 POP_TOP
           37 POP_TOP
 L. 14     38 JUMP_FORWARD 14 to 45
           39 END_FINALLY to 40
 L. 16     40 LOAD_FAST str: distutils_dir_util
           41 LOAD_ATTR str: _path_created
           42 LOAD_ATTR str: clear
           43 CALL_FUNCTION 0
           44 POP_TOP
 L. 18     45 LOAD_GLOBAL str: re
           46 LOAD_ATTR str: purge
           47 CALL_FUNCTION 0
           48 POP_TOP
 L. 20     49 SETUP_EXCEPT 17 to 57
 L. 21     50 LOAD_GLOBAL str: sys
           51 LOAD_ATTR str: modules
           52 LOAD_CONST str: _strptime
           53 BINARY_SUBSCR
           54 STORE_FAST str: _strptime
           55 POP_BLOCK
           56 JUMP_FORWARD 17 to 66
 L. 22     57 DUP_TOP
           58 LOAD_GLOBAL str: KeyError
           59 COMPARE_OP 10
           60 POP_JUMP_IF_FALSE 158 to 65
           61 POP_TOP
           62 POP_TOP
           63 POP_TOP
 L. 23     64 JUMP_FORWARD 14 to 71
           65 END_FINALLY to 66
 L. 25     66 LOAD_FAST str: _strptime
           67 LOAD_ATTR str: _regex_cache
           68 LOAD_ATTR str: clear
           69 CALL_FUNCTION 0
           70 POP_TOP
 L. 27     71 SETUP_EXCEPT 17 to 79
 L. 28     72 LOAD_GLOBAL str: sys
           73 LOAD_ATTR str: modules
           74 LOAD_CONST str: urlparse
           75 BINARY_SUBSCR
           76 STORE_FAST str: urlparse
           77 POP_BLOCK
           78 JUMP_FORWARD 17 to 88
 L. 29     79 DUP_TOP
           80 LOAD_GLOBAL str: KeyError
           81 COMPARE_OP 10
           82 POP_JUMP_IF_FALSE 208 to 87
           83 POP_TOP
           84 POP_TOP
           85 POP_TOP
 L. 30     86 JUMP_FORWARD 11 to 92
           87 END_FINALLY to 88
 L. 32     88 LOAD_FAST str: urlparse
           89 LOAD_ATTR str: clear_cache
           90 CALL_FUNCTION 0
           91 POP_TOP
 L. 34     92 SETUP_EXCEPT 17 to 100
 L. 35     93 LOAD_GLOBAL str: sys
           94 LOAD_ATTR str: modules
           95 LOAD_CONST str: urllib
           96 BINARY_SUBSCR
           97 STORE_FAST str: urllib
           98 POP_BLOCK
           99 JUMP_FORWARD 17 to 109
 L. 36    100 DUP_TOP
          101 LOAD_GLOBAL str: KeyError
          102 COMPARE_OP 10
          103 POP_JUMP_IF_FALSE 255 to 108
          104 POP_TOP
          105 POP_TOP
          106 POP_TOP
 L. 37    107 JUMP_FORWARD 11 to 113
          108 END_FINALLY to 109
 L. 39    109 LOAD_FAST str: urllib
          110 LOAD_ATTR str: urlcleanup
          111 CALL_FUNCTION 0
          112 POP_TOP
 L. 41    113 SETUP_EXCEPT 17 to 121
 L. 42    114 LOAD_GLOBAL str: sys
          115 LOAD_ATTR str: modules
          116 LOAD_CONST str: urllib2
          117 BINARY_SUBSCR
          118 STORE_FAST str: urllib2
          119 POP_BLOCK
          120 JUMP_FORWARD 17 to 130
 L. 43    121 DUP_TOP
          122 LOAD_GLOBAL str: KeyError
          123 COMPARE_OP 10
          124 POP_JUMP_IF_FALSE 302 to 129
          125 POP_TOP
          126 POP_TOP
          127 POP_TOP
 L. 44    128 JUMP_FORWARD 14 to 135
          129 END_FINALLY to 130
 L. 46    130 LOAD_FAST str: urllib2
          131 LOAD_ATTR str: install_opener
          132 LOAD_CONST obj: N
          133 CALL_FUNCTION 1
          134 POP_TOP
 L. 48    135 SETUP_EXCEPT 17 to 143
 L. 49    136 LOAD_GLOBAL str: sys
          137 LOAD_ATTR str: modules
          138 LOAD_CONST str: dircache
          139 BINARY_SUBSCR
          140 STORE_FAST str: dircache
          141 POP_BLOCK
          142 JUMP_FORWARD 17 to 152
 L. 50    143 DUP_TOP
          144 LOAD_GLOBAL str: KeyError
          145 COMPARE_OP 10
          146 POP_JUMP_IF_FALSE 352 to 151
          147 POP_TOP
          148 POP_TOP
          149 POP_TOP
 L. 51    150 JUMP_FORWARD 11 to 156
          151 END_FINALLY to 152
 L. 53    152 LOAD_FAST str: dircache
          153 LOAD_ATTR str: reset
          154 CALL_FUNCTION 0
          155 POP_TOP
 L. 55    156 SETUP_EXCEPT 17 to 164
 L. 56    157 LOAD_GLOBAL str: sys
          158 LOAD_ATTR str: modules
          159 LOAD_CONST str: linecache
          160 BINARY_SUBSCR
          161 STORE_FAST str: linecache
          162 POP_BLOCK
          163 JUMP_FORWARD 17 to 173
 L. 57    164 DUP_TOP
          165 LOAD_GLOBAL str: KeyError
          166 COMPARE_OP 10
          167 POP_JUMP_IF_FALSE 399 to 172
          168 POP_TOP
          169 POP_TOP
          170 POP_TOP
 L. 58    171 JUMP_FORWARD 11 to 177
          172 END_FINALLY to 173
 L. 60    173 LOAD_FAST str: linecache
          174 LOAD_ATTR str: clearcache
          175 CALL_FUNCTION 0
          176 POP_TOP
 L. 62    177 SETUP_EXCEPT 17 to 185
 L. 63    178 LOAD_GLOBAL str: sys
          179 LOAD_ATTR str: modules
          180 LOAD_CONST str: mimetypes
          181 BINARY_SUBSCR
          182 STORE_FAST str: mimetypes
          183 POP_BLOCK
          184 JUMP_FORWARD 17 to 194
 L. 64    185 DUP_TOP
          186 LOAD_GLOBAL str: KeyError
          187 COMPARE_OP 10
          188 POP_JUMP_IF_FALSE 446 to 193
          189 POP_TOP
          190 POP_TOP
          191 POP_TOP
 L. 65    192 JUMP_FORWARD 11 to 198
          193 END_FINALLY to 194
 L. 67    194 LOAD_FAST str: mimetypes
          195 LOAD_ATTR str: _default_mime_types
          196 CALL_FUNCTION 0
          197 POP_TOP
 L. 69    198 SETUP_EXCEPT 17 to 206
 L. 70    199 LOAD_GLOBAL str: sys
          200 LOAD_ATTR str: modules
          201 LOAD_CONST str: filecmp
          202 BINARY_SUBSCR
          203 STORE_FAST str: filecmp
          204 POP_BLOCK
          205 JUMP_FORWARD 17 to 215
 L. 71    206 DUP_TOP
          207 LOAD_GLOBAL str: KeyError
          208 COMPARE_OP 10
          209 POP_JUMP_IF_FALSE 493 to 214
          210 POP_TOP
          211 POP_TOP
          212 POP_TOP
 L. 72    213 JUMP_FORWARD 14 to 220
          214 END_FINALLY to 215
 L. 74    215 LOAD_FAST str: filecmp
          216 LOAD_ATTR str: _cache
          217 LOAD_ATTR str: clear
          218 CALL_FUNCTION 0
          219 POP_TOP
 L. 76    220 SETUP_EXCEPT 17 to 228
 L. 77    221 LOAD_GLOBAL str: sys
          222 LOAD_ATTR str: modules
          223 LOAD_CONST str: struct
          224 BINARY_SUBSCR
          225 STORE_FAST str: struct
          226 POP_BLOCK
          227 JUMP_FORWARD 17 to 237
 L. 78    228 DUP_TOP
          229 LOAD_GLOBAL str: KeyError
          230 COMPARE_OP 10
          231 POP_JUMP_IF_FALSE 543 to 236
          232 POP_TOP
          233 POP_TOP
          234 POP_TOP
 L. 79    235 JUMP_FORWARD 11 to 241
          236 END_FINALLY to 237
 L. 81    237 LOAD_FAST str: struct
          238 LOAD_ATTR str: _clearcache
          239 CALL_FUNCTION 0
          240 POP_TOP
 L. 83    241 SETUP_EXCEPT 17 to 249
 L. 84    242 LOAD_GLOBAL str: sys
          243 LOAD_ATTR str: modules
          244 LOAD_CONST str: doctest
          245 BINARY_SUBSCR
          246 STORE_FAST str: doctest
          247 POP_BLOCK
          248 JUMP_FORWARD 17 to 258
 L. 85    249 DUP_TOP
          250 LOAD_GLOBAL str: KeyError
          251 COMPARE_OP 10
          252 POP_JUMP_IF_FALSE 590 to 257
          253 POP_TOP
          254 POP_TOP
          255 POP_TOP
 L. 86    256 JUMP_FORWARD 10 to 261
          257 END_FINALLY to 258
 L. 88    258 LOAD_CONST obj: N
          259 LOAD_FAST str: doctest
          260 STORE_ATTR str: master
 L. 90    261 SETUP_EXCEPT 17 to 269
 L. 91    262 LOAD_GLOBAL str: sys
          263 LOAD_ATTR str: modules
          264 LOAD_CONST str: ctypes
          265 BINARY_SUBSCR
          266 STORE_FAST str: ctypes
          267 POP_BLOCK
          268 JUMP_FORWARD 17 to 278
 L. 92    269 DUP_TOP
          270 LOAD_GLOBAL str: KeyError
          271 COMPARE_OP 10
          272 POP_JUMP_IF_FALSE 636 to 277
          273 POP_TOP
          274 POP_TOP
          275 POP_TOP
 L. 93    276 JUMP_FORWARD 11 to 282
          277 END_FINALLY to 278
 L. 95    278 LOAD_FAST str: ctypes
          279 LOAD_ATTR str: _reset_cache
          280 CALL_FUNCTION 0
          281 POP_TOP
 L. 98    282 LOAD_GLOBAL str: support
          283 LOAD_ATTR str: gc_collect
          284 CALL_FUNCTION 0
          285 POP_TOP
          286 LOAD_CONST obj: N
          287 RETURN_VALUE

function warm_caches():

 L.  5      0 SETUP_LOOP 13
            1 LOAD_GLOBAL str: range
            2 LOAD_CONST long: 256
            3 CALL_FUNCTION 1
            4 GET_ITER
            5 FOR_ITER 16 to 12
            6 STORE_FAST str: i
 L.  6      7 LOAD_GLOBAL str: chr
            8 LOAD_FAST str: i
            9 CALL_FUNCTION 1
           10 POP_TOP
           11 CONTINUE_LOOP 13 to 5
           12 POP_BLOCK
 L.  8     13 SETUP_LOOP 26
           14 LOAD_GLOBAL str: range
           15 LOAD_CONST long: 256
           16 CALL_FUNCTION 1
           17 GET_ITER
           18 FOR_ITER 16 to 25
           19 STORE_FAST str: i
 L.  9     20 LOAD_GLOBAL str: unichr
           21 LOAD_FAST str: i
           22 CALL_FUNCTION 1
           23 POP_TOP
           24 CONTINUE_LOOP 46 to 18
           25 POP_BLOCK
 L. 11     26 LOAD_GLOBAL str: list
           27 LOAD_GLOBAL str: range
           28 LOAD_CONST long: -5
           29 LOAD_CONST long: 257
           30 CALL_FUNCTION 2
           31 CALL_FUNCTION 1
           32 POP_TOP
           33 LOAD_CONST obj: N
           34 RETURN_VALUE

function findtestdir(path):

 L.  2      0 LOAD_FAST str: path
            1 JUMP_IF_TRUE_OR_POP 30
            2 LOAD_GLOBAL str: os
            3 LOAD_ATTR str: path
            4 LOAD_ATTR str: dirname
            5 LOAD_GLOBAL str: __file__
            6 CALL_FUNCTION 1
            7 JUMP_IF_TRUE_OR_POP 30
            8 LOAD_GLOBAL str: os
            9 LOAD_ATTR str: curdir
           10 RETURN_VALUE

function removepy(names):

 L.  2      0 LOAD_FAST str: names
            1 POP_JUMP_IF_TRUE 10 to 4
 L.  3      2 LOAD_CONST obj: N
            3 RETURN_VALUE to 4
 L.  4      4 SETUP_LOOP 32
            5 LOAD_GLOBAL str: enumerate
            6 LOAD_FAST str: names
            7 CALL_FUNCTION 1
            8 GET_ITER
            9 FOR_ITER 61 to 32
           10 UNPACK_SEQUENCE 2
           11 STORE_FAST str: idx
           12 STORE_FAST str: name
 L.  5     13 LOAD_GLOBAL str: os
           14 LOAD_ATTR str: path
           15 LOAD_ATTR str: splitext
           16 LOAD_FAST str: name
           17 CALL_FUNCTION 1
           18 UNPACK_SEQUENCE 2
           19 STORE_FAST str: basename
           20 STORE_FAST str: ext
 L.  6     21 LOAD_FAST str: ext
           22 LOAD_CONST str: .py
           23 COMPARE_OP 2
           24 POP_JUMP_IF_TRUE 23 to 26
           25 CONTINUE_LOOP 1 to 9
 L.  7     26 LOAD_FAST str: basename
           27 LOAD_FAST str: names
           28 LOAD_FAST str: idx
           29 STORE_SUBSCR
           30 CONTINUE_LOOP 23 to 9
           31 CONTINUE_LOOP 23 to 9
           32 POP_BLOCK
           33 LOAD_CONST obj: N
           34 RETURN_VALUE

function count(n,word):

 L.  2      0 LOAD_FAST str: n
            1 LOAD_CONST long: 1
            2 COMPARE_OP 2
            3 POP_JUMP_IF_FALSE 26 to 10
 L.  3      4 LOAD_CONST str: %d %s
            5 LOAD_FAST str: n
            6 LOAD_FAST str: word
            7 BUILD_TUPLE 2
            8 BINARY_MODULO
            9 RETURN_VALUE to 10
 L.  5     10 LOAD_CONST str: %d %ss
           11 LOAD_FAST str: n
           12 LOAD_FAST str: word
           13 BUILD_TUPLE 2
           14 BINARY_MODULO
           15 RETURN_VALUE to 16
           16 LOAD_CONST obj: N
           17 RETURN_VALUE

function printlist(x,width,indent,file):

 L.  9      0 LOAD_CONST long: -1
            1 LOAD_CONST (str: fill,)
            2 IMPORT_NAME str: textwrap
            3 IMPORT_FROM str: fill
            4 STORE_FAST str: fill
            5 POP_TOP
 L. 10      6 LOAD_CONST str:  
            7 LOAD_FAST str: indent
            8 BINARY_MULTIPLY
            9 STORE_FAST str: blanks
 L. 12     10 LOAD_FAST str: file
           11 DUP_TOP
           12 LOAD_FAST str: fill
           13 LOAD_CONST str:  
           14 LOAD_ATTR str: join
           15 LOAD_CONST obj: c
           16 MAKE_FUNCTION 0
           17 LOAD_GLOBAL str: sorted
           18 LOAD_FAST str: x
           19 CALL_FUNCTION 1
           20 GET_ITER
           21 CALL_FUNCTION 1
           22 CALL_FUNCTION 1
           23 LOAD_FAST str: width
           24 LOAD_CONST str: initial_indent
 L. 13     25 LOAD_FAST str: blanks
           26 LOAD_CONST str: subsequent_indent
           27 LOAD_FAST str: blanks
           28 CALL_FUNCTION 514
           29 ROT_TWO
           30 PRINT_ITEM_TO
           31 PRINT_NEWLINE_TO
           32 LOAD_CONST obj: N
           33 RETURN_VALUE

function <genexpr>(.0):

 L.  1      0 LOAD_FAST str: .0
            1 FOR_ITER 17 to 9
            2 STORE_FAST str: elt
            3 LOAD_GLOBAL str: str
            4 LOAD_FAST str: elt
            5 CALL_FUNCTION 1
            6 YIELD_VALUE
            7 POP_TOP
            8 JUMP_ABSOLUTE 3 to 1
            9 LOAD_CONST obj: N
           10 RETURN_VALUE

function get_abs_module(testdir,test):

 L.  2      0 LOAD_FAST str: test
            1 LOAD_ATTR str: startswith
            2 LOAD_CONST str: test.
            3 CALL_FUNCTION 1
            4 POP_JUMP_IF_TRUE 21 to 7
            5 LOAD_FAST str: testdir
            6 POP_JUMP_IF_FALSE 25 to 9
 L.  3      7 LOAD_FAST str: test
            8 RETURN_VALUE to 9
 L.  6      9 LOAD_CONST str: test.
           10 LOAD_FAST str: test
           11 BINARY_ADD
           12 RETURN_VALUE to 13
           13 LOAD_CONST obj: N
           14 RETURN_VALUE

function _list_cases(suite):

 L.  2      0 SETUP_LOOP 36
            1 LOAD_FAST str: suite
            2 GET_ITER
            3 FOR_ITER 87 to 36
            4 STORE_FAST str: test
 L.  3      5 LOAD_GLOBAL str: isinstance
            6 LOAD_FAST str: test
            7 LOAD_GLOBAL str: unittest
            8 LOAD_ATTR str: TestSuite
            9 CALL_FUNCTION 2
           10 POP_JUMP_IF_FALSE 44 to 16
 L.  4     11 LOAD_GLOBAL str: _list_cases
           12 LOAD_FAST str: test
           13 CALL_FUNCTION 1
           14 POP_TOP
           15 CONTINUE_LOOP 7 to 3
 L.  5     16 LOAD_GLOBAL str: isinstance
           17 LOAD_FAST str: test
           18 LOAD_GLOBAL str: unittest
           19 LOAD_ATTR str: TestCase
           20 CALL_FUNCTION 2
           21 POP_JUMP_IF_TRUE 7 to 23
           22 CONTINUE_LOOP 1 to 3
 L.  6     23 LOAD_GLOBAL str: support
           24 LOAD_ATTR str: match_test
           25 LOAD_FAST str: test
           26 CALL_FUNCTION 1
           27 POP_JUMP_IF_FALSE 94 to 35
 L.  7     28 LOAD_FAST str: test
           29 LOAD_ATTR str: id
           30 CALL_FUNCTION 0
           31 PRINT_ITEM
           32 PRINT_NEWLINE
           33 JUMP_ABSOLUTE 94 to 35
           34 DUMMY 7 to 3
           35 CONTINUE_LOOP 7 to 3
           36 POP_BLOCK
           37 LOAD_CONST obj: N
           38 RETURN_VALUE

function list_cases(testdir,selected,match_tests):

 L.  2      0 LOAD_GLOBAL str: False
            1 LOAD_GLOBAL str: support
            2 STORE_ATTR str: verbose
 L.  3      3 LOAD_GLOBAL str: support
            4 LOAD_ATTR str: set_match_tests
            5 LOAD_FAST str: match_tests
            6 CALL_FUNCTION 1
            7 POP_TOP
 L.  5      8 LOAD_GLOBAL str: set
            9 LOAD_GLOBAL str: sys
           10 LOAD_ATTR str: modules
           11 CALL_FUNCTION 1
           12 STORE_FAST str: save_modules
 L.  6     13 BUILD_LIST 0
           14 STORE_FAST str: skipped
 L.  7     15 SETUP_LOOP 59
           16 LOAD_FAST str: selected
           17 GET_ITER
           18 FOR_ITER 99 to 58
           19 STORE_FAST str: test
 L.  8     20 LOAD_GLOBAL str: get_abs_module
           21 LOAD_FAST str: testdir
           22 LOAD_FAST str: test
           23 CALL_FUNCTION 2
           24 STORE_FAST str: abstest
 L.  9     25 SETUP_EXCEPT 32 to 38
 L. 10     26 LOAD_GLOBAL str: unittest
           27 LOAD_ATTR str: defaultTestLoader
           28 LOAD_ATTR str: loadTestsFromName
           29 LOAD_FAST str: abstest
           30 CALL_FUNCTION 1
           31 STORE_FAST str: suite
 L. 11     32 LOAD_GLOBAL str: _list_cases
           33 LOAD_FAST str: suite
           34 CALL_FUNCTION 1
           35 POP_TOP
           36 POP_BLOCK
           37 JUMP_FORWARD 33 to 53
 L. 12     38 DUP_TOP
           39 LOAD_GLOBAL str: unittest
           40 LOAD_ATTR str: SkipTest
           41 COMPARE_OP 10
           42 POP_JUMP_IF_FALSE 138 to 52
           43 POP_TOP
           44 POP_TOP
           45 POP_TOP
 L. 13     46 LOAD_FAST str: skipped
           47 LOAD_ATTR str: append
           48 LOAD_FAST str: test
           49 CALL_FUNCTION 1
           50 POP_TOP
           51 JUMP_FORWARD 1 to 53
           52 END_FINALLY to 53
 L. 15     53 LOAD_GLOBAL str: unload_test_modules
           54 LOAD_FAST str: save_modules
           55 CALL_FUNCTION 1
           56 POP_TOP
           57 CONTINUE_LOOP 50 to 18
           58 POP_BLOCK
 L. 17     59 LOAD_FAST str: skipped
           60 POP_JUMP_IF_FALSE 222 to 88
 L. 18     61 LOAD_GLOBAL str: sys
           62 LOAD_ATTR str: stderr
           63 PRINT_NEWLINE_TO
 L. 19     64 LOAD_GLOBAL str: sys
           65 LOAD_ATTR str: stderr
           66 DUP_TOP
           67 LOAD_GLOBAL str: count
           68 LOAD_GLOBAL str: len
           69 LOAD_FAST str: skipped
           70 CALL_FUNCTION 1
           71 LOAD_CONST str: test
           72 CALL_FUNCTION 2
           73 ROT_TWO
           74 PRINT_ITEM_TO
           75 DUP_TOP
           76 LOAD_CONST str: skipped:
           77 ROT_TWO
           78 PRINT_ITEM_TO
           79 PRINT_NEWLINE_TO
 L. 20     80 LOAD_GLOBAL str: printlist
           81 LOAD_FAST str: skipped
           82 LOAD_CONST str: file
           83 LOAD_GLOBAL str: sys
           84 LOAD_ATTR str: stderr
           85 CALL_FUNCTION 257
           86 POP_TOP
           87 JUMP_FORWARD 0 to 88
           88 LOAD_CONST obj: N
           89 RETURN_VALUE

function main_in_temp_cwd():

 L.  8      0 LOAD_GLOBAL str: sysconfig
            1 LOAD_ATTR str: is_python_build
            2 CALL_FUNCTION 0
            3 POP_JUMP_IF_FALSE 97 to 33
 L.  9      4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: path
            6 LOAD_ATTR str: join
            7 LOAD_GLOBAL str: sysconfig
            8 LOAD_ATTR str: get_config_var
            9 LOAD_CONST str: srcdir
           10 CALL_FUNCTION 1
           11 LOAD_CONST str: build
           12 CALL_FUNCTION 2
           13 STORE_GLOBAL str: TEMPDIR
 L. 10     14 LOAD_GLOBAL str: os
           15 LOAD_ATTR str: path
           16 LOAD_ATTR str: abspath
           17 LOAD_GLOBAL str: TEMPDIR
           18 CALL_FUNCTION 1
           19 STORE_GLOBAL str: TEMPDIR
 L. 11     20 LOAD_GLOBAL str: os
           21 LOAD_ATTR str: path
           22 LOAD_ATTR str: exists
           23 LOAD_GLOBAL str: TEMPDIR
           24 CALL_FUNCTION 1
           25 POP_JUMP_IF_TRUE 97 to 33
 L. 12     26 LOAD_GLOBAL str: os
           27 LOAD_ATTR str: mkdir
           28 LOAD_GLOBAL str: TEMPDIR
           29 CALL_FUNCTION 1
           30 POP_TOP
           31 JUMP_ABSOLUTE 97 to 33
           32 JUMP_FORWARD 0 to 33
 L. 17     33 LOAD_CONST str: test_python_{}
           34 LOAD_ATTR str: format
           35 LOAD_GLOBAL str: os
           36 LOAD_ATTR str: getpid
           37 CALL_FUNCTION 0
           38 CALL_FUNCTION 1
           39 STORE_FAST str: TESTCWD
 L. 19     40 LOAD_GLOBAL str: os
           41 LOAD_ATTR str: path
           42 LOAD_ATTR str: join
           43 LOAD_GLOBAL str: TEMPDIR
           44 LOAD_FAST str: TESTCWD
           45 CALL_FUNCTION 2
           46 STORE_FAST str: TESTCWD
 L. 25     47 LOAD_GLOBAL str: support
           48 LOAD_ATTR str: temp_cwd
           49 LOAD_FAST str: TESTCWD
           50 LOAD_CONST str: quiet
           51 LOAD_GLOBAL str: True
           52 CALL_FUNCTION 257
           53 SETUP_WITH 6
           54 POP_TOP
 L. 26     55 LOAD_GLOBAL str: main
           56 CALL_FUNCTION 0
           57 POP_TOP
           58 POP_BLOCK
           59 LOAD_CONST obj: N
           60 WITH_CLEANUP
           61 END_FINALLY to 62
           62 LOAD_CONST obj: N
           63 RETURN_VALUE

class saved_test_environment:

build class function saved_test_environment():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L. 13      2 LOAD_CONST str: Save bits of the test environment and restore them at block exit.

        with saved_test_environment(testname, verbose, quiet):
            #stuff

    Unless quiet is True, a warning is printed to stderr if any of
    the saved items was changed by the test.  The attribute 'changed'
    is initially False, but is set to True if a change is detected.

    If verbose is more than 1, the before and after state of changed
    items is also printed.
    
            3 STORE_NAME str: __doc__
 L. 15      4 LOAD_NAME str: False
            5 STORE_NAME str: changed
 L. 17      6 LOAD_CONST long: 0
            7 LOAD_NAME str: False
            8 LOAD_NAME str: False
            9 LOAD_CONST obj: c
           10 MAKE_FUNCTION 3
           11 STORE_NAME str: __init__
 L. 35     12 LOAD_CONST (str: sys.argv,str: cwd,str: sys.stdin,str: sys.stdout,str: sys.stderr,str: os.environ,str: sys.path,str: asyncore.socket_map,str: files,)
           13 STORE_NAME str: resources
 L. 38     14 LOAD_CONST obj: c
           15 MAKE_FUNCTION 0
           16 STORE_NAME str: get_sys_argv
 L. 40     17 LOAD_CONST obj: c
           18 MAKE_FUNCTION 0
           19 STORE_NAME str: restore_sys_argv
 L. 44     20 LOAD_CONST obj: c
           21 MAKE_FUNCTION 0
           22 STORE_NAME str: get_cwd
 L. 46     23 LOAD_CONST obj: c
           24 MAKE_FUNCTION 0
           25 STORE_NAME str: restore_cwd
 L. 49     26 LOAD_CONST obj: c
           27 MAKE_FUNCTION 0
           28 STORE_NAME str: get_sys_stdout
 L. 51     29 LOAD_CONST obj: c
           30 MAKE_FUNCTION 0
           31 STORE_NAME str: restore_sys_stdout
 L. 54     32 LOAD_CONST obj: c
           33 MAKE_FUNCTION 0
           34 STORE_NAME str: get_sys_stderr
 L. 56     35 LOAD_CONST obj: c
           36 MAKE_FUNCTION 0
           37 STORE_NAME str: restore_sys_stderr
 L. 59     38 LOAD_CONST obj: c
           39 MAKE_FUNCTION 0
           40 STORE_NAME str: get_sys_stdin
 L. 61     41 LOAD_CONST obj: c
           42 MAKE_FUNCTION 0
           43 STORE_NAME str: restore_sys_stdin
 L. 64     44 LOAD_CONST obj: c
           45 MAKE_FUNCTION 0
           46 STORE_NAME str: get_os_environ
 L. 66     47 LOAD_CONST obj: c
           48 MAKE_FUNCTION 0
           49 STORE_NAME str: restore_os_environ
 L. 71     50 LOAD_CONST obj: c
           51 MAKE_FUNCTION 0
           52 STORE_NAME str: get_sys_path
 L. 73     53 LOAD_CONST obj: c
           54 MAKE_FUNCTION 0
           55 STORE_NAME str: restore_sys_path
 L. 77     56 LOAD_CONST obj: c
           57 MAKE_FUNCTION 0
           58 STORE_NAME str: get_asyncore_socket_map
 L. 81     59 LOAD_CONST obj: c
           60 MAKE_FUNCTION 0
           61 STORE_NAME str: restore_asyncore_socket_map
 L. 87     62 LOAD_CONST obj: c
           63 MAKE_FUNCTION 0
           64 STORE_NAME str: get_support_TESTFN
 L. 95     65 LOAD_CONST obj: c
           66 MAKE_FUNCTION 0
           67 STORE_NAME str: restore_support_TESTFN
 L.102     68 LOAD_CONST obj: c
           69 MAKE_FUNCTION 0
           70 STORE_NAME str: get_files
 L.105     71 LOAD_CONST obj: c
           72 MAKE_FUNCTION 0
           73 STORE_NAME str: restore_files
 L.113     74 LOAD_CONST obj: c
           75 MAKE_FUNCTION 0
           76 STORE_NAME str: resource_info
 L.120     77 LOAD_CONST obj: c
           78 MAKE_FUNCTION 0
           79 STORE_NAME str: __enter__
 L.125     80 LOAD_CONST obj: c
           81 MAKE_FUNCTION 0
           82 STORE_NAME str: __exit__
           83 LOAD_LOCALS
           84 RETURN_VALUE

function __init__(self,testname,verbose,quiet,pgo):

 L.  2      0 LOAD_FAST str: testname
            1 LOAD_FAST str: self
            2 STORE_ATTR str: testname
 L.  3      3 LOAD_FAST str: verbose
            4 LOAD_FAST str: self
            5 STORE_ATTR str: verbose
 L.  4      6 LOAD_FAST str: quiet
            7 LOAD_FAST str: self
            8 STORE_ATTR str: quiet
 L.  5      9 LOAD_FAST str: pgo
           10 LOAD_FAST str: self
           11 STORE_ATTR str: pgo
           12 LOAD_CONST obj: N
           13 RETURN_VALUE

function get_sys_argv(self):

 L.  2      0 LOAD_GLOBAL str: id
            1 LOAD_GLOBAL str: sys
            2 LOAD_ATTR str: argv
            3 CALL_FUNCTION 1
            4 LOAD_GLOBAL str: sys
            5 LOAD_ATTR str: argv
            6 LOAD_GLOBAL str: sys
            7 LOAD_ATTR str: argv
            8 SLICE
            9 BUILD_TUPLE 3
           10 RETURN_VALUE

function restore_sys_argv(self,saved_argv):

 L.  2      0 LOAD_FAST str: saved_argv
            1 LOAD_CONST long: 1
            2 BINARY_SUBSCR
            3 LOAD_GLOBAL str: sys
            4 STORE_ATTR str: argv
 L.  3      5 LOAD_FAST str: saved_argv
            6 LOAD_CONST long: 2
            7 BINARY_SUBSCR
            8 LOAD_GLOBAL str: sys
            9 LOAD_ATTR str: argv
           10 STORE_SLICE
           11 LOAD_CONST obj: N
           12 RETURN_VALUE

function get_cwd(self):

 L.  2      0 LOAD_GLOBAL str: os
            1 LOAD_ATTR str: getcwd
            2 CALL_FUNCTION 0
            3 RETURN_VALUE

function restore_cwd(self,saved_cwd):

 L.  2      0 LOAD_GLOBAL str: os
            1 LOAD_ATTR str: chdir
            2 LOAD_FAST str: saved_cwd
            3 CALL_FUNCTION 1
            4 POP_TOP
            5 LOAD_CONST obj: N
            6 RETURN_VALUE

function get_sys_stdout(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: stdout
            2 RETURN_VALUE

function restore_sys_stdout(self,saved_stdout):

 L.  2      0 LOAD_FAST str: saved_stdout
            1 LOAD_GLOBAL str: sys
            2 STORE_ATTR str: stdout
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

function get_sys_stderr(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: stderr
            2 RETURN_VALUE

function restore_sys_stderr(self,saved_stderr):

 L.  2      0 LOAD_FAST str: saved_stderr
            1 LOAD_GLOBAL str: sys
            2 STORE_ATTR str: stderr
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

function get_sys_stdin(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: stdin
            2 RETURN_VALUE

function restore_sys_stdin(self,saved_stdin):

 L.  2      0 LOAD_FAST str: saved_stdin
            1 LOAD_GLOBAL str: sys
            2 STORE_ATTR str: stdin
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

function get_os_environ(self):

 L.  2      0 LOAD_GLOBAL str: id
            1 LOAD_GLOBAL str: os
            2 LOAD_ATTR str: environ
            3 CALL_FUNCTION 1
            4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: environ
            6 LOAD_GLOBAL str: dict
            7 LOAD_GLOBAL str: os
            8 LOAD_ATTR str: environ
            9 CALL_FUNCTION 1
           10 BUILD_TUPLE 3
           11 RETURN_VALUE

function restore_os_environ(self,saved_environ):

 L.  2      0 LOAD_FAST str: saved_environ
            1 LOAD_CONST long: 1
            2 BINARY_SUBSCR
            3 LOAD_GLOBAL str: os
            4 STORE_ATTR str: environ
 L.  3      5 LOAD_GLOBAL str: os
            6 LOAD_ATTR str: environ
            7 LOAD_ATTR str: clear
            8 CALL_FUNCTION 0
            9 POP_TOP
 L.  4     10 LOAD_GLOBAL str: os
           11 LOAD_ATTR str: environ
           12 LOAD_ATTR str: update
           13 LOAD_FAST str: saved_environ
           14 LOAD_CONST long: 2
           15 BINARY_SUBSCR
           16 CALL_FUNCTION 1
           17 POP_TOP
           18 LOAD_CONST obj: N
           19 RETURN_VALUE

function get_sys_path(self):

 L.  2      0 LOAD_GLOBAL str: id
            1 LOAD_GLOBAL str: sys
            2 LOAD_ATTR str: path
            3 CALL_FUNCTION 1
            4 LOAD_GLOBAL str: sys
            5 LOAD_ATTR str: path
            6 LOAD_GLOBAL str: sys
            7 LOAD_ATTR str: path
            8 SLICE
            9 BUILD_TUPLE 3
           10 RETURN_VALUE

function restore_sys_path(self,saved_path):

 L.  2      0 LOAD_FAST str: saved_path
            1 LOAD_CONST long: 1
            2 BINARY_SUBSCR
            3 LOAD_GLOBAL str: sys
            4 STORE_ATTR str: path
 L.  3      5 LOAD_FAST str: saved_path
            6 LOAD_CONST long: 2
            7 BINARY_SUBSCR
            8 LOAD_GLOBAL str: sys
            9 LOAD_ATTR str: path
           10 STORE_SLICE
           11 LOAD_CONST obj: N
           12 RETURN_VALUE

function get_asyncore_socket_map(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: modules
            2 LOAD_ATTR str: get
            3 LOAD_CONST str: asyncore
            4 CALL_FUNCTION 1
            5 STORE_FAST str: asyncore
 L.  4      6 LOAD_FAST str: asyncore
            7 POP_JUMP_IF_FALSE 39 to 13
            8 LOAD_FAST str: asyncore
            9 LOAD_ATTR str: socket_map
           10 LOAD_ATTR str: copy
           11 CALL_FUNCTION 0
           12 JUMP_IF_TRUE_OR_POP 42
           13 BUILD_MAP 0
           14 RETURN_VALUE

function restore_asyncore_socket_map(self,saved_map):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: modules
            2 LOAD_ATTR str: get
            3 LOAD_CONST str: asyncore
            4 CALL_FUNCTION 1
            5 STORE_FAST str: asyncore
 L.  3      6 LOAD_FAST str: asyncore
            7 LOAD_CONST obj: N
            8 COMPARE_OP 9
            9 POP_JUMP_IF_FALSE 65 to 23
 L.  4     10 LOAD_FAST str: asyncore
           11 LOAD_ATTR str: close_all
           12 LOAD_CONST str: ignore_all
           13 LOAD_GLOBAL str: True
           14 CALL_FUNCTION 256
           15 POP_TOP
 L.  5     16 LOAD_FAST str: asyncore
           17 LOAD_ATTR str: socket_map
           18 LOAD_ATTR str: update
           19 LOAD_FAST str: saved_map
           20 CALL_FUNCTION 1
           21 POP_TOP
           22 JUMP_FORWARD 0 to 23
           23 LOAD_CONST obj: N
           24 RETURN_VALUE

function get_support_TESTFN(self):

 L.  2      0 LOAD_GLOBAL str: os
            1 LOAD_ATTR str: path
            2 LOAD_ATTR str: isfile
            3 LOAD_GLOBAL str: support
            4 LOAD_ATTR str: TESTFN
            5 CALL_FUNCTION 1
            6 POP_JUMP_IF_FALSE 30 to 10
 L.  3      7 LOAD_CONST str: f
            8 STORE_FAST str: result
            9 JUMP_FORWARD 36 to 22
 L.  4     10 LOAD_GLOBAL str: os
           11 LOAD_ATTR str: path
           12 LOAD_ATTR str: isdir
           13 LOAD_GLOBAL str: support
           14 LOAD_ATTR str: TESTFN
           15 CALL_FUNCTION 1
           16 POP_JUMP_IF_FALSE 60 to 20
 L.  5     17 LOAD_CONST str: d
           18 STORE_FAST str: result
           19 JUMP_FORWARD 6 to 22
 L.  7     20 LOAD_CONST obj: N
           21 STORE_FAST str: result
 L.  8     22 LOAD_FAST str: result
           23 RETURN_VALUE

function restore_support_TESTFN(self,saved_value):

 L.  2      0 LOAD_FAST str: saved_value
            1 LOAD_CONST obj: N
            2 COMPARE_OP 8
            3 POP_JUMP_IF_FALSE 95 to 33
 L.  3      4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: path
            6 LOAD_ATTR str: isfile
            7 LOAD_GLOBAL str: support
            8 LOAD_ATTR str: TESTFN
            9 CALL_FUNCTION 1
           10 POP_JUMP_IF_FALSE 52 to 18
 L.  4     11 LOAD_GLOBAL str: os
           12 LOAD_ATTR str: unlink
           13 LOAD_GLOBAL str: support
           14 LOAD_ATTR str: TESTFN
           15 CALL_FUNCTION 1
           16 POP_TOP
           17 JUMP_ABSOLUTE 95 to 33
 L.  5     18 LOAD_GLOBAL str: os
           19 LOAD_ATTR str: path
           20 LOAD_ATTR str: isdir
           21 LOAD_GLOBAL str: support
           22 LOAD_ATTR str: TESTFN
           23 CALL_FUNCTION 1
           24 POP_JUMP_IF_FALSE 95 to 33
 L.  6     25 LOAD_GLOBAL str: shutil
           26 LOAD_ATTR str: rmtree
           27 LOAD_GLOBAL str: support
           28 LOAD_ATTR str: TESTFN
           29 CALL_FUNCTION 1
           30 POP_TOP
           31 JUMP_ABSOLUTE 95 to 33
           32 JUMP_FORWARD 0 to 33
           33 LOAD_CONST obj: N
           34 RETURN_VALUE

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

function restore_files(self,saved_value):

 L.  2      0 LOAD_GLOBAL str: support
            1 LOAD_ATTR str: TESTFN
            2 STORE_FAST str: fn
 L.  3      3 LOAD_FAST str: fn
            4 LOAD_FAST str: saved_value
            5 COMPARE_OP 7
            6 POP_JUMP_IF_FALSE 108 to 38
            7 LOAD_FAST str: fn
            8 LOAD_CONST str: /
            9 BINARY_ADD
           10 LOAD_FAST str: saved_value
           11 COMPARE_OP 7
           12 POP_JUMP_IF_FALSE 108 to 38
 L.  4     13 LOAD_GLOBAL str: os
           14 LOAD_ATTR str: path
           15 LOAD_ATTR str: isfile
           16 LOAD_FAST str: fn
           17 CALL_FUNCTION 1
           18 POP_JUMP_IF_FALSE 71 to 25
 L.  5     19 LOAD_GLOBAL str: support
           20 LOAD_ATTR str: unlink
           21 LOAD_FAST str: fn
           22 CALL_FUNCTION 1
           23 POP_TOP
           24 JUMP_ABSOLUTE 108 to 38
 L.  6     25 LOAD_GLOBAL str: os
           26 LOAD_ATTR str: path
           27 LOAD_ATTR str: isdir
           28 LOAD_FAST str: fn
           29 CALL_FUNCTION 1
           30 POP_JUMP_IF_FALSE 108 to 38
 L.  7     31 LOAD_GLOBAL str: support
           32 LOAD_ATTR str: rmtree
           33 LOAD_FAST str: fn
           34 CALL_FUNCTION 1
           35 POP_TOP
           36 JUMP_ABSOLUTE 108 to 38
           37 JUMP_FORWARD 0 to 38
           38 LOAD_CONST obj: N
           39 RETURN_VALUE

function resource_info(self):

 L.  2      0 SETUP_LOOP 34
            1 LOAD_FAST str: self
            2 LOAD_ATTR str: resources
            3 GET_ITER
            4 FOR_ITER 76 to 33
            5 STORE_FAST str: name
 L.  3      6 LOAD_FAST str: name
            7 LOAD_ATTR str: replace
            8 LOAD_CONST str: .
            9 LOAD_CONST str: _
           10 CALL_FUNCTION 2
           11 STORE_FAST str: method_suffix
 L.  4     12 LOAD_CONST str: get_
           13 LOAD_FAST str: method_suffix
           14 BINARY_ADD
           15 STORE_FAST str: get_name
 L.  5     16 LOAD_CONST str: restore_
           17 LOAD_FAST str: method_suffix
           18 BINARY_ADD
           19 STORE_FAST str: restore_name
 L.  6     20 LOAD_FAST str: name
           21 LOAD_GLOBAL str: getattr
           22 LOAD_FAST str: self
           23 LOAD_FAST str: get_name
           24 CALL_FUNCTION 2
           25 LOAD_GLOBAL str: getattr
           26 LOAD_FAST str: self
           27 LOAD_FAST str: restore_name
           28 CALL_FUNCTION 2
           29 BUILD_TUPLE 3
           30 YIELD_VALUE
           31 POP_TOP
           32 CONTINUE_LOOP 10 to 4
           33 POP_BLOCK
           34 LOAD_CONST obj: N
           35 RETURN_VALUE

function __enter__(self):

 L.  2      0 LOAD_GLOBAL str: dict
            1 LOAD_CONST obj: c
            2 MAKE_FUNCTION 0
 L.  3      3 LOAD_FAST str: self
            4 LOAD_ATTR str: resource_info
            5 CALL_FUNCTION 0
            6 GET_ITER
            7 CALL_FUNCTION 1
            8 CALL_FUNCTION 1
            9 LOAD_FAST str: self
           10 STORE_ATTR str: saved_values
 L.  4     11 LOAD_FAST str: self
           12 RETURN_VALUE

function <genexpr>(.0):

 L.  1      0 LOAD_FAST str: .0
            1 FOR_ITER 29 to 13
            2 UNPACK_SEQUENCE 3
            3 STORE_FAST str: name
            4 STORE_FAST str: get
            5 STORE_FAST str: restore
            6 LOAD_FAST str: name
            7 LOAD_FAST str: get
            8 CALL_FUNCTION 0
            9 BUILD_TUPLE 2
           10 YIELD_VALUE
           11 POP_TOP
           12 JUMP_ABSOLUTE 3 to 1
           13 LOAD_CONST obj: N
           14 RETURN_VALUE

function __exit__(self,exc_type,exc_val,exc_tb):

 L.  2      0 LOAD_FAST str: self
            1 LOAD_ATTR str: saved_values
            2 STORE_FAST str: saved_values
 L.  3      3 LOAD_FAST str: self
            4 DELETE_ATTR 0
 L.  6      5 LOAD_FAST str: self
            6 DUP_TOP
            7 LOAD_ATTR str: changed
            8 LOAD_GLOBAL str: support
            9 LOAD_ATTR str: environment_altered
           10 INPLACE_OR
           11 ROT_TWO
           12 STORE_ATTR str: changed
 L.  8     13 SETUP_LOOP 77
           14 LOAD_FAST str: self
           15 LOAD_ATTR str: resource_info
           16 CALL_FUNCTION 0
           17 GET_ITER
           18 FOR_ITER 149 to 77
           19 UNPACK_SEQUENCE 3
           20 STORE_FAST str: name
           21 STORE_FAST str: get
           22 STORE_FAST str: restore
 L.  9     23 LOAD_FAST str: get
           24 CALL_FUNCTION 0
           25 STORE_FAST str: current
 L. 10     26 LOAD_FAST str: saved_values
           27 LOAD_ATTR str: pop
           28 LOAD_FAST str: name
           29 CALL_FUNCTION 1
           30 STORE_FAST str: original
 L. 12     31 LOAD_FAST str: current
           32 LOAD_FAST str: original
           33 COMPARE_OP 3
           34 POP_JUMP_IF_TRUE 46 to 36
           35 CONTINUE_LOOP 1 to 18
 L. 13     36 LOAD_GLOBAL str: True
           37 LOAD_FAST str: self
           38 STORE_ATTR str: changed
 L. 14     39 LOAD_FAST str: restore
           40 LOAD_FAST str: original
           41 CALL_FUNCTION 1
           42 POP_TOP
 L. 15     43 LOAD_FAST str: self
           44 LOAD_ATTR str: quiet
           45 UNARY_NOT
           46 POP_JUMP_IF_FALSE 195 to 76
           47 LOAD_FAST str: self
           48 LOAD_ATTR str: pgo
           49 UNARY_NOT
           50 POP_JUMP_IF_FALSE 195 to 76
 L. 16     51 LOAD_GLOBAL str: sys
           52 LOAD_ATTR str: stderr
           53 DUP_TOP
 L. 17     54 LOAD_CONST str: Warning -- {} was modified by {}
           55 LOAD_ATTR str: format
 L. 18     56 LOAD_FAST str: name
           57 LOAD_FAST str: self
           58 LOAD_ATTR str: testname
           59 CALL_FUNCTION 2
           60 ROT_TWO
           61 PRINT_ITEM_TO
           62 PRINT_NEWLINE_TO
 L. 19     63 LOAD_GLOBAL str: sys
           64 LOAD_ATTR str: stderr
           65 DUP_TOP
 L. 20     66 LOAD_CONST str:   Before: {}
  After:  {} 
           67 LOAD_ATTR str: format
 L. 21     68 LOAD_FAST str: original
           69 LOAD_FAST str: current
           70 CALL_FUNCTION 2
           71 ROT_TWO
           72 PRINT_ITEM_TO
           73 PRINT_NEWLINE_TO
           74 JUMP_ABSOLUTE 195 to 76
           75 DUMMY 46 to 18
           76 CONTINUE_LOOP 46 to 18
           77 POP_BLOCK
 L. 26     78 LOAD_GLOBAL str: False
           79 RETURN_VALUE

method __init__(self,testname,verbose,quiet,pgo):

 L.  2      0 LOAD_FAST str: testname
            1 LOAD_FAST str: self
            2 STORE_ATTR str: testname
 L.  3      3 LOAD_FAST str: verbose
            4 LOAD_FAST str: self
            5 STORE_ATTR str: verbose
 L.  4      6 LOAD_FAST str: quiet
            7 LOAD_FAST str: self
            8 STORE_ATTR str: quiet
 L.  5      9 LOAD_FAST str: pgo
           10 LOAD_FAST str: self
           11 STORE_ATTR str: pgo
           12 LOAD_CONST obj: N
           13 RETURN_VALUE

method get_sys_argv(self):

 L.  2      0 LOAD_GLOBAL str: id
            1 LOAD_GLOBAL str: sys
            2 LOAD_ATTR str: argv
            3 CALL_FUNCTION 1
            4 LOAD_GLOBAL str: sys
            5 LOAD_ATTR str: argv
            6 LOAD_GLOBAL str: sys
            7 LOAD_ATTR str: argv
            8 SLICE
            9 BUILD_TUPLE 3
           10 RETURN_VALUE

method restore_sys_argv(self,saved_argv):

 L.  2      0 LOAD_FAST str: saved_argv
            1 LOAD_CONST long: 1
            2 BINARY_SUBSCR
            3 LOAD_GLOBAL str: sys
            4 STORE_ATTR str: argv
 L.  3      5 LOAD_FAST str: saved_argv
            6 LOAD_CONST long: 2
            7 BINARY_SUBSCR
            8 LOAD_GLOBAL str: sys
            9 LOAD_ATTR str: argv
           10 STORE_SLICE
           11 LOAD_CONST obj: N
           12 RETURN_VALUE

method get_cwd(self):

 L.  2      0 LOAD_GLOBAL str: os
            1 LOAD_ATTR str: getcwd
            2 CALL_FUNCTION 0
            3 RETURN_VALUE

method restore_cwd(self,saved_cwd):

 L.  2      0 LOAD_GLOBAL str: os
            1 LOAD_ATTR str: chdir
            2 LOAD_FAST str: saved_cwd
            3 CALL_FUNCTION 1
            4 POP_TOP
            5 LOAD_CONST obj: N
            6 RETURN_VALUE

method get_sys_stdout(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: stdout
            2 RETURN_VALUE

method restore_sys_stdout(self,saved_stdout):

 L.  2      0 LOAD_FAST str: saved_stdout
            1 LOAD_GLOBAL str: sys
            2 STORE_ATTR str: stdout
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

method get_sys_stderr(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: stderr
            2 RETURN_VALUE

method restore_sys_stderr(self,saved_stderr):

 L.  2      0 LOAD_FAST str: saved_stderr
            1 LOAD_GLOBAL str: sys
            2 STORE_ATTR str: stderr
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

method get_sys_stdin(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: stdin
            2 RETURN_VALUE

method restore_sys_stdin(self,saved_stdin):

 L.  2      0 LOAD_FAST str: saved_stdin
            1 LOAD_GLOBAL str: sys
            2 STORE_ATTR str: stdin
            3 LOAD_CONST obj: N
            4 RETURN_VALUE

method get_os_environ(self):

 L.  2      0 LOAD_GLOBAL str: id
            1 LOAD_GLOBAL str: os
            2 LOAD_ATTR str: environ
            3 CALL_FUNCTION 1
            4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: environ
            6 LOAD_GLOBAL str: dict
            7 LOAD_GLOBAL str: os
            8 LOAD_ATTR str: environ
            9 CALL_FUNCTION 1
           10 BUILD_TUPLE 3
           11 RETURN_VALUE

method restore_os_environ(self,saved_environ):

 L.  2      0 LOAD_FAST str: saved_environ
            1 LOAD_CONST long: 1
            2 BINARY_SUBSCR
            3 LOAD_GLOBAL str: os
            4 STORE_ATTR str: environ
 L.  3      5 LOAD_GLOBAL str: os
            6 LOAD_ATTR str: environ
            7 LOAD_ATTR str: clear
            8 CALL_FUNCTION 0
            9 POP_TOP
 L.  4     10 LOAD_GLOBAL str: os
           11 LOAD_ATTR str: environ
           12 LOAD_ATTR str: update
           13 LOAD_FAST str: saved_environ
           14 LOAD_CONST long: 2
           15 BINARY_SUBSCR
           16 CALL_FUNCTION 1
           17 POP_TOP
           18 LOAD_CONST obj: N
           19 RETURN_VALUE

method get_sys_path(self):

 L.  2      0 LOAD_GLOBAL str: id
            1 LOAD_GLOBAL str: sys
            2 LOAD_ATTR str: path
            3 CALL_FUNCTION 1
            4 LOAD_GLOBAL str: sys
            5 LOAD_ATTR str: path
            6 LOAD_GLOBAL str: sys
            7 LOAD_ATTR str: path
            8 SLICE
            9 BUILD_TUPLE 3
           10 RETURN_VALUE

method restore_sys_path(self,saved_path):

 L.  2      0 LOAD_FAST str: saved_path
            1 LOAD_CONST long: 1
            2 BINARY_SUBSCR
            3 LOAD_GLOBAL str: sys
            4 STORE_ATTR str: path
 L.  3      5 LOAD_FAST str: saved_path
            6 LOAD_CONST long: 2
            7 BINARY_SUBSCR
            8 LOAD_GLOBAL str: sys
            9 LOAD_ATTR str: path
           10 STORE_SLICE
           11 LOAD_CONST obj: N
           12 RETURN_VALUE

method get_asyncore_socket_map(self):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: modules
            2 LOAD_ATTR str: get
            3 LOAD_CONST str: asyncore
            4 CALL_FUNCTION 1
            5 STORE_FAST str: asyncore
 L.  4      6 LOAD_FAST str: asyncore
            7 POP_JUMP_IF_FALSE 39 to 13
            8 LOAD_FAST str: asyncore
            9 LOAD_ATTR str: socket_map
           10 LOAD_ATTR str: copy
           11 CALL_FUNCTION 0
           12 JUMP_IF_TRUE_OR_POP 42
           13 BUILD_MAP 0
           14 RETURN_VALUE

method restore_asyncore_socket_map(self,saved_map):

 L.  2      0 LOAD_GLOBAL str: sys
            1 LOAD_ATTR str: modules
            2 LOAD_ATTR str: get
            3 LOAD_CONST str: asyncore
            4 CALL_FUNCTION 1
            5 STORE_FAST str: asyncore
 L.  3      6 LOAD_FAST str: asyncore
            7 LOAD_CONST obj: N
            8 COMPARE_OP 9
            9 POP_JUMP_IF_FALSE 65 to 23
 L.  4     10 LOAD_FAST str: asyncore
           11 LOAD_ATTR str: close_all
           12 LOAD_CONST str: ignore_all
           13 LOAD_GLOBAL str: True
           14 CALL_FUNCTION 256
           15 POP_TOP
 L.  5     16 LOAD_FAST str: asyncore
           17 LOAD_ATTR str: socket_map
           18 LOAD_ATTR str: update
           19 LOAD_FAST str: saved_map
           20 CALL_FUNCTION 1
           21 POP_TOP
           22 JUMP_FORWARD 0 to 23
           23 LOAD_CONST obj: N
           24 RETURN_VALUE

method get_support_TESTFN(self):

 L.  2      0 LOAD_GLOBAL str: os
            1 LOAD_ATTR str: path
            2 LOAD_ATTR str: isfile
            3 LOAD_GLOBAL str: support
            4 LOAD_ATTR str: TESTFN
            5 CALL_FUNCTION 1
            6 POP_JUMP_IF_FALSE 30 to 10
 L.  3      7 LOAD_CONST str: f
            8 STORE_FAST str: result
            9 JUMP_FORWARD 36 to 22
 L.  4     10 LOAD_GLOBAL str: os
           11 LOAD_ATTR str: path
           12 LOAD_ATTR str: isdir
           13 LOAD_GLOBAL str: support
           14 LOAD_ATTR str: TESTFN
           15 CALL_FUNCTION 1
           16 POP_JUMP_IF_FALSE 60 to 20
 L.  5     17 LOAD_CONST str: d
           18 STORE_FAST str: result
           19 JUMP_FORWARD 6 to 22
 L.  7     20 LOAD_CONST obj: N
           21 STORE_FAST str: result
 L.  8     22 LOAD_FAST str: result
           23 RETURN_VALUE

method restore_support_TESTFN(self,saved_value):

 L.  2      0 LOAD_FAST str: saved_value
            1 LOAD_CONST obj: N
            2 COMPARE_OP 8
            3 POP_JUMP_IF_FALSE 95 to 33
 L.  3      4 LOAD_GLOBAL str: os
            5 LOAD_ATTR str: path
            6 LOAD_ATTR str: isfile
            7 LOAD_GLOBAL str: support
            8 LOAD_ATTR str: TESTFN
            9 CALL_FUNCTION 1
           10 POP_JUMP_IF_FALSE 52 to 18
 L.  4     11 LOAD_GLOBAL str: os
           12 LOAD_ATTR str: unlink
           13 LOAD_GLOBAL str: support
           14 LOAD_ATTR str: TESTFN
           15 CALL_FUNCTION 1
           16 POP_TOP
           17 JUMP_ABSOLUTE 95 to 33
 L.  5     18 LOAD_GLOBAL str: os
           19 LOAD_ATTR str: path
           20 LOAD_ATTR str: isdir
           21 LOAD_GLOBAL str: support
           22 LOAD_ATTR str: TESTFN
           23 CALL_FUNCTION 1
           24 POP_JUMP_IF_FALSE 95 to 33
 L.  6     25 LOAD_GLOBAL str: shutil
           26 LOAD_ATTR str: rmtree
           27 LOAD_GLOBAL str: support
           28 LOAD_ATTR str: TESTFN
           29 CALL_FUNCTION 1
           30 POP_TOP
           31 JUMP_ABSOLUTE 95 to 33
           32 JUMP_FORWARD 0 to 33
           33 LOAD_CONST obj: N
           34 RETURN_VALUE

method get_files(self):

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

method restore_files(self,saved_value):

 L.  2      0 LOAD_GLOBAL str: support
            1 LOAD_ATTR str: TESTFN
            2 STORE_FAST str: fn
 L.  3      3 LOAD_FAST str: fn
            4 LOAD_FAST str: saved_value
            5 COMPARE_OP 7
            6 POP_JUMP_IF_FALSE 108 to 38
            7 LOAD_FAST str: fn
            8 LOAD_CONST str: /
            9 BINARY_ADD
           10 LOAD_FAST str: saved_value
           11 COMPARE_OP 7
           12 POP_JUMP_IF_FALSE 108 to 38
 L.  4     13 LOAD_GLOBAL str: os
           14 LOAD_ATTR str: path
           15 LOAD_ATTR str: isfile
           16 LOAD_FAST str: fn
           17 CALL_FUNCTION 1
           18 POP_JUMP_IF_FALSE 71 to 25
 L.  5     19 LOAD_GLOBAL str: support
           20 LOAD_ATTR str: unlink
           21 LOAD_FAST str: fn
           22 CALL_FUNCTION 1
           23 POP_TOP
           24 JUMP_ABSOLUTE 108 to 38
 L.  6     25 LOAD_GLOBAL str: os
           26 LOAD_ATTR str: path
           27 LOAD_ATTR str: isdir
           28 LOAD_FAST str: fn
           29 CALL_FUNCTION 1
           30 POP_JUMP_IF_FALSE 108 to 38
 L.  7     31 LOAD_GLOBAL str: support
           32 LOAD_ATTR str: rmtree
           33 LOAD_FAST str: fn
           34 CALL_FUNCTION 1
           35 POP_TOP
           36 JUMP_ABSOLUTE 108 to 38
           37 JUMP_FORWARD 0 to 38
           38 LOAD_CONST obj: N
           39 RETURN_VALUE

method resource_info(self):

 L.  2      0 SETUP_LOOP 34
            1 LOAD_FAST str: self
            2 LOAD_ATTR str: resources
            3 GET_ITER
            4 FOR_ITER 76 to 33
            5 STORE_FAST str: name
 L.  3      6 LOAD_FAST str: name
            7 LOAD_ATTR str: replace
            8 LOAD_CONST str: .
            9 LOAD_CONST str: _
           10 CALL_FUNCTION 2
           11 STORE_FAST str: method_suffix
 L.  4     12 LOAD_CONST str: get_
           13 LOAD_FAST str: method_suffix
           14 BINARY_ADD
           15 STORE_FAST str: get_name
 L.  5     16 LOAD_CONST str: restore_
           17 LOAD_FAST str: method_suffix
           18 BINARY_ADD
           19 STORE_FAST str: restore_name
 L.  6     20 LOAD_FAST str: name
           21 LOAD_GLOBAL str: getattr
           22 LOAD_FAST str: self
           23 LOAD_FAST str: get_name
           24 CALL_FUNCTION 2
           25 LOAD_GLOBAL str: getattr
           26 LOAD_FAST str: self
           27 LOAD_FAST str: restore_name
           28 CALL_FUNCTION 2
           29 BUILD_TUPLE 3
           30 YIELD_VALUE
           31 POP_TOP
           32 CONTINUE_LOOP 10 to 4
           33 POP_BLOCK
           34 LOAD_CONST obj: N
           35 RETURN_VALUE

method __enter__(self):

 L.  2      0 LOAD_GLOBAL str: dict
            1 LOAD_CONST obj: c
            2 MAKE_FUNCTION 0
 L.  3      3 LOAD_FAST str: self
            4 LOAD_ATTR str: resource_info
            5 CALL_FUNCTION 0
            6 GET_ITER
            7 CALL_FUNCTION 1
            8 CALL_FUNCTION 1
            9 LOAD_FAST str: self
           10 STORE_ATTR str: saved_values
 L.  4     11 LOAD_FAST str: self
           12 RETURN_VALUE

function <genexpr>(.0):

 L.  1      0 LOAD_FAST str: .0
            1 FOR_ITER 29 to 13
            2 UNPACK_SEQUENCE 3
            3 STORE_FAST str: name
            4 STORE_FAST str: get
            5 STORE_FAST str: restore
            6 LOAD_FAST str: name
            7 LOAD_FAST str: get
            8 CALL_FUNCTION 0
            9 BUILD_TUPLE 2
           10 YIELD_VALUE
           11 POP_TOP
           12 JUMP_ABSOLUTE 3 to 1
           13 LOAD_CONST obj: N
           14 RETURN_VALUE

method __exit__(self,exc_type,exc_val,exc_tb):

 L.  2      0 LOAD_FAST str: self
            1 LOAD_ATTR str: saved_values
            2 STORE_FAST str: saved_values
 L.  3      3 LOAD_FAST str: self
            4 DELETE_ATTR 0
 L.  6      5 LOAD_FAST str: self
            6 DUP_TOP
            7 LOAD_ATTR str: changed
            8 LOAD_GLOBAL str: support
            9 LOAD_ATTR str: environment_altered
           10 INPLACE_OR
           11 ROT_TWO
           12 STORE_ATTR str: changed
 L.  8     13 SETUP_LOOP 77
           14 LOAD_FAST str: self
           15 LOAD_ATTR str: resource_info
           16 CALL_FUNCTION 0
           17 GET_ITER
           18 FOR_ITER 149 to 77
           19 UNPACK_SEQUENCE 3
           20 STORE_FAST str: name
           21 STORE_FAST str: get
           22 STORE_FAST str: restore
 L.  9     23 LOAD_FAST str: get
           24 CALL_FUNCTION 0
           25 STORE_FAST str: current
 L. 10     26 LOAD_FAST str: saved_values
           27 LOAD_ATTR str: pop
           28 LOAD_FAST str: name
           29 CALL_FUNCTION 1
           30 STORE_FAST str: original
 L. 12     31 LOAD_FAST str: current
           32 LOAD_FAST str: original
           33 COMPARE_OP 3
           34 POP_JUMP_IF_TRUE 46 to 36
           35 CONTINUE_LOOP 1 to 18
 L. 13     36 LOAD_GLOBAL str: True
           37 LOAD_FAST str: self
           38 STORE_ATTR str: changed
 L. 14     39 LOAD_FAST str: restore
           40 LOAD_FAST str: original
           41 CALL_FUNCTION 1
           42 POP_TOP
 L. 15     43 LOAD_FAST str: self
           44 LOAD_ATTR str: quiet
           45 UNARY_NOT
           46 POP_JUMP_IF_FALSE 195 to 76
           47 LOAD_FAST str: self
           48 LOAD_ATTR str: pgo
           49 UNARY_NOT
           50 POP_JUMP_IF_FALSE 195 to 76
 L. 16     51 LOAD_GLOBAL str: sys
           52 LOAD_ATTR str: stderr
           53 DUP_TOP
 L. 17     54 LOAD_CONST str: Warning -- {} was modified by {}
           55 LOAD_ATTR str: format
 L. 18     56 LOAD_FAST str: name
           57 LOAD_FAST str: self
           58 LOAD_ATTR str: testname
           59 CALL_FUNCTION 2
           60 ROT_TWO
           61 PRINT_ITEM_TO
           62 PRINT_NEWLINE_TO
 L. 19     63 LOAD_GLOBAL str: sys
           64 LOAD_ATTR str: stderr
           65 DUP_TOP
 L. 20     66 LOAD_CONST str:   Before: {}
  After:  {} 
           67 LOAD_ATTR str: format
 L. 21     68 LOAD_FAST str: original
           69 LOAD_FAST str: current
           70 CALL_FUNCTION 2
           71 ROT_TWO
           72 PRINT_ITEM_TO
           73 PRINT_NEWLINE_TO
           74 JUMP_ABSOLUTE 195 to 76
           75 DUMMY 46 to 18
           76 CONTINUE_LOOP 46 to 18
           77 POP_BLOCK
 L. 26     78 LOAD_GLOBAL str: False
           79 RETURN_VALUE


class _ExpectedSkips:

build class function _ExpectedSkips():

 L.  1      0 LOAD_NAME str: __name__
            1 STORE_NAME str: __module__
 L.  2      2 LOAD_CONST obj: c
            3 MAKE_FUNCTION 0
            4 STORE_NAME str: __init__
 L. 57      5 LOAD_CONST obj: c
            6 MAKE_FUNCTION 0
            7 STORE_NAME str: isvalid
 L. 61      8 LOAD_CONST obj: c
            9 MAKE_FUNCTION 0
           10 STORE_NAME str: getexpected
           11 LOAD_LOCALS
           12 RETURN_VALUE

function __init__(self):

 L.  2      0 LOAD_CONST long: -1
            1 LOAD_CONST obj: N
            2 IMPORT_NAME str: os.path
            3 STORE_FAST str: os
 L.  3      4 LOAD_CONST long: -1
            5 LOAD_CONST (str: test_timeout,)
            6 IMPORT_NAME str: test
            7 IMPORT_FROM str: test_timeout
            8 STORE_FAST str: test_timeout
            9 POP_TOP
 L.  5     10 LOAD_GLOBAL str: False
           11 LOAD_FAST str: self
           12 STORE_ATTR str: valid
 L.  6     13 LOAD_GLOBAL str: sys
           14 LOAD_ATTR str: platform
           15 LOAD_GLOBAL str: _expectations
           16 COMPARE_OP 6
           17 POP_JUMP_IF_FALSE 556 to 198
 L.  7     18 LOAD_GLOBAL str: _expectations
           19 LOAD_GLOBAL str: sys
           20 LOAD_ATTR str: platform
           21 BINARY_SUBSCR
           22 STORE_FAST str: s
 L.  8     23 LOAD_GLOBAL str: set
           24 LOAD_FAST str: s
           25 LOAD_ATTR str: split
           26 CALL_FUNCTION 0
           27 CALL_FUNCTION 1
           28 LOAD_FAST str: self
           29 STORE_ATTR str: expected
 L. 11     30 LOAD_FAST str: self
           31 LOAD_ATTR str: expected
           32 LOAD_ATTR str: add
           33 LOAD_CONST str: test_linuxaudiodev
           34 CALL_FUNCTION 1
           35 POP_TOP
 L. 13     36 LOAD_FAST str: os
           37 LOAD_ATTR str: path
           38 LOAD_ATTR str: supports_unicode_filenames
           39 POP_JUMP_IF_TRUE 133 to 47
 L. 14     40 LOAD_FAST str: self
           41 LOAD_ATTR str: expected
           42 LOAD_ATTR str: add
           43 LOAD_CONST str: test_pep277
           44 CALL_FUNCTION 1
           45 POP_TOP
           46 JUMP_FORWARD 0 to 47
 L. 16     47 LOAD_FAST str: test_timeout
           48 LOAD_ATTR str: skip_expected
           49 POP_JUMP_IF_FALSE 161 to 57
 L. 17     50 LOAD_FAST str: self
           51 LOAD_ATTR str: expected
           52 LOAD_ATTR str: add
           53 LOAD_CONST str: test_timeout
           54 CALL_FUNCTION 1
           55 POP_TOP
           56 JUMP_FORWARD 0 to 57
 L. 19     57 LOAD_GLOBAL str: sys
           58 LOAD_ATTR str: maxint
           59 LOAD_CONST long: -1
           60 COMPARE_OP 2
           61 POP_JUMP_IF_FALSE 195 to 69
 L. 20     62 LOAD_FAST str: self
           63 LOAD_ATTR str: expected
           64 LOAD_ATTR str: add
           65 LOAD_CONST str: test_imageop
           66 CALL_FUNCTION 1
           67 POP_TOP
           68 JUMP_FORWARD 0 to 69
 L. 22     69 LOAD_GLOBAL str: sys
           70 LOAD_ATTR str: platform
           71 LOAD_CONST str: darwin
           72 COMPARE_OP 3
           73 POP_JUMP_IF_FALSE 270 to 96
 L. 23     74 LOAD_CONST str: test_macos
           75 LOAD_CONST str: test_macostools
           76 LOAD_CONST str: test_aepack
 L. 24     77 LOAD_CONST str: test_plistlib
           78 LOAD_CONST str: test_scriptpackages
 L. 25     79 LOAD_CONST str: test_applesingle
           80 BUILD_LIST 6
           81 STORE_FAST str: MAC_ONLY
 L. 26     82 SETUP_LOOP 112
           83 LOAD_FAST str: MAC_ONLY
           84 GET_ITER
           85 FOR_ITER 22 to 94
           86 STORE_FAST str: skip
 L. 27     87 LOAD_FAST str: self
           88 LOAD_ATTR str: expected
           89 LOAD_ATTR str: add
           90 LOAD_FAST str: skip
           91 CALL_FUNCTION 1
           92 POP_TOP
           93 CONTINUE_LOOP 241 to 85
           94 POP_BLOCK
           95 JUMP_FORWARD 46 to 112
 L. 28     96 LOAD_GLOBAL str: len
           97 LOAD_CONST unicode: 
           98 LOAD_ATTR str: encode
           99 LOAD_CONST str: unicode-internal
          100 CALL_FUNCTION 1
          101 CALL_FUNCTION 1
          102 LOAD_CONST long: 4
          103 COMPARE_OP 2
          104 POP_JUMP_IF_FALSE 316 to 112
 L. 29    105 LOAD_FAST str: self
          106 LOAD_ATTR str: expected
          107 LOAD_ATTR str: add
          108 LOAD_CONST str: test_macostools
          109 CALL_FUNCTION 1
          110 POP_TOP
          111 JUMP_FORWARD 0 to 112
 L. 32    112 LOAD_GLOBAL str: sys
          113 LOAD_ATTR str: platform
          114 LOAD_CONST str: win32
          115 COMPARE_OP 3
          116 POP_JUMP_IF_FALSE 391 to 139
 L. 35    117 LOAD_CONST str: test_unicode_file
          118 LOAD_CONST str: test_winreg
 L. 36    119 LOAD_CONST str: test_winsound
          120 LOAD_CONST str: test_startfile
 L. 37    121 LOAD_CONST str: test_sqlite
          122 LOAD_CONST str: test_msilib
          123 BUILD_LIST 6
          124 STORE_FAST str: WIN_ONLY
 L. 38    125 SETUP_LOOP 139
          126 LOAD_FAST str: WIN_ONLY
          127 GET_ITER
          128 FOR_ITER 22 to 137
          129 STORE_FAST str: skip
 L. 39    130 LOAD_FAST str: self
          131 LOAD_ATTR str: expected
          132 LOAD_ATTR str: add
          133 LOAD_FAST str: skip
          134 CALL_FUNCTION 1
          135 POP_TOP
          136 CONTINUE_LOOP 362 to 128
          137 POP_BLOCK
          138 JUMP_FORWARD 0 to 139
 L. 41    139 LOAD_GLOBAL str: sys
          140 LOAD_ATTR str: platform
          141 LOAD_CONST str: irix
          142 COMPARE_OP 3
          143 POP_JUMP_IF_FALSE 466 to 166
 L. 42    144 LOAD_CONST str: test_imageop
          145 LOAD_CONST str: test_al
          146 LOAD_CONST str: test_cd
          147 LOAD_CONST str: test_cl
 L. 43    148 LOAD_CONST str: test_gl
          149 LOAD_CONST str: test_imgfile
          150 BUILD_LIST 6
          151 STORE_FAST str: IRIX_ONLY
 L. 44    152 SETUP_LOOP 166
          153 LOAD_FAST str: IRIX_ONLY
          154 GET_ITER
          155 FOR_ITER 22 to 164
          156 STORE_FAST str: skip
 L. 45    157 LOAD_FAST str: self
          158 LOAD_ATTR str: expected
          159 LOAD_ATTR str: add
          160 LOAD_FAST str: skip
          161 CALL_FUNCTION 1
          162 POP_TOP
          163 CONTINUE_LOOP 437 to 155
          164 POP_BLOCK
          165 JUMP_FORWARD 0 to 166
 L. 47    166 LOAD_GLOBAL str: sys
          167 LOAD_ATTR str: platform
          168 LOAD_CONST str: sunos5
          169 COMPARE_OP 3
          170 POP_JUMP_IF_FALSE 516 to 184
 L. 48    171 LOAD_FAST str: self
          172 LOAD_ATTR str: expected
          173 LOAD_ATTR str: add
          174 LOAD_CONST str: test_sunaudiodev
          175 CALL_FUNCTION 1
          176 POP_TOP
 L. 49    177 LOAD_FAST str: self
          178 LOAD_ATTR str: expected
          179 LOAD_ATTR str: add
          180 LOAD_CONST str: test_nis
          181 CALL_FUNCTION 1
          182 POP_TOP
          183 JUMP_FORWARD 0 to 184
 L. 51    184 LOAD_GLOBAL str: sys
          185 LOAD_ATTR str: py3kwarning
          186 POP_JUMP_IF_TRUE 544 to 194
 L. 52    187 LOAD_FAST str: self
          188 LOAD_ATTR str: expected
          189 LOAD_ATTR str: add
          190 LOAD_CONST str: test_py3kwarn
          191 CALL_FUNCTION 1
          192 POP_TOP
          193 JUMP_FORWARD 0 to 194
 L. 54    194 LOAD_GLOBAL str: True
          195 LOAD_FAST str: self
          196 STORE_ATTR str: valid
          197 JUMP_FORWARD 0 to 198
          198 LOAD_CONST obj: N
          199 RETURN_VALUE

function isvalid(self):

 L.  3      0 LOAD_FAST str: self
            1 LOAD_ATTR str: valid
            2 RETURN_VALUE

function getexpected(self):

 L.  7      0 LOAD_FAST str: self
            1 LOAD_ATTR str: isvalid
            2 CALL_FUNCTION 0
            3 POP_JUMP_IF_TRUE 18 to 6
            4 LOAD_GLOBAL str: AssertionError
            5 RAISE_VARARGS 1
 L.  8      6 LOAD_FAST str: self
            7 LOAD_ATTR str: expected
            8 RETURN_VALUE

method __init__(self):

 L.  2      0 LOAD_CONST long: -1
            1 LOAD_CONST obj: N
            2 IMPORT_NAME str: os.path
            3 STORE_FAST str: os
 L.  3      4 LOAD_CONST long: -1
            5 LOAD_CONST (str: test_timeout,)
            6 IMPORT_NAME str: test
            7 IMPORT_FROM str: test_timeout
            8 STORE_FAST str: test_timeout
            9 POP_TOP
 L.  5     10 LOAD_GLOBAL str: False
           11 LOAD_FAST str: self
           12 STORE_ATTR str: valid
 L.  6     13 LOAD_GLOBAL str: sys
           14 LOAD_ATTR str: platform
           15 LOAD_GLOBAL str: _expectations
           16 COMPARE_OP 6
           17 POP_JUMP_IF_FALSE 556 to 198
 L.  7     18 LOAD_GLOBAL str: _expectations
           19 LOAD_GLOBAL str: sys
           20 LOAD_ATTR str: platform
           21 BINARY_SUBSCR
           22 STORE_FAST str: s
 L.  8     23 LOAD_GLOBAL str: set
           24 LOAD_FAST str: s
           25 LOAD_ATTR str: split
           26 CALL_FUNCTION 0
           27 CALL_FUNCTION 1
           28 LOAD_FAST str: self
           29 STORE_ATTR str: expected
 L. 11     30 LOAD_FAST str: self
           31 LOAD_ATTR str: expected
           32 LOAD_ATTR str: add
           33 LOAD_CONST str: test_linuxaudiodev
           34 CALL_FUNCTION 1
           35 POP_TOP
 L. 13     36 LOAD_FAST str: os
           37 LOAD_ATTR str: path
           38 LOAD_ATTR str: supports_unicode_filenames
           39 POP_JUMP_IF_TRUE 133 to 47
 L. 14     40 LOAD_FAST str: self
           41 LOAD_ATTR str: expected
           42 LOAD_ATTR str: add
           43 LOAD_CONST str: test_pep277
           44 CALL_FUNCTION 1
           45 POP_TOP
           46 JUMP_FORWARD 0 to 47
 L. 16     47 LOAD_FAST str: test_timeout
           48 LOAD_ATTR str: skip_expected
           49 POP_JUMP_IF_FALSE 161 to 57
 L. 17     50 LOAD_FAST str: self
           51 LOAD_ATTR str: expected
           52 LOAD_ATTR str: add
           53 LOAD_CONST str: test_timeout
           54 CALL_FUNCTION 1
           55 POP_TOP
           56 JUMP_FORWARD 0 to 57
 L. 19     57 LOAD_GLOBAL str: sys
           58 LOAD_ATTR str: maxint
           59 LOAD_CONST long: -1
           60 COMPARE_OP 2
           61 POP_JUMP_IF_FALSE 195 to 69
 L. 20     62 LOAD_FAST str: self
           63 LOAD_ATTR str: expected
           64 LOAD_ATTR str: add
           65 LOAD_CONST str: test_imageop
           66 CALL_FUNCTION 1
           67 POP_TOP
           68 JUMP_FORWARD 0 to 69
 L. 22     69 LOAD_GLOBAL str: sys
           70 LOAD_ATTR str: platform
           71 LOAD_CONST str: darwin
           72 COMPARE_OP 3
           73 POP_JUMP_IF_FALSE 270 to 96
 L. 23     74 LOAD_CONST str: test_macos
           75 LOAD_CONST str: test_macostools
           76 LOAD_CONST str: test_aepack
 L. 24     77 LOAD_CONST str: test_plistlib
           78 LOAD_CONST str: test_scriptpackages
 L. 25     79 LOAD_CONST str: test_applesingle
           80 BUILD_LIST 6
           81 STORE_FAST str: MAC_ONLY
 L. 26     82 SETUP_LOOP 112
           83 LOAD_FAST str: MAC_ONLY
           84 GET_ITER
           85 FOR_ITER 22 to 94
           86 STORE_FAST str: skip
 L. 27     87 LOAD_FAST str: self
           88 LOAD_ATTR str: expected
           89 LOAD_ATTR str: add
           90 LOAD_FAST str: skip
           91 CALL_FUNCTION 1
           92 POP_TOP
           93 CONTINUE_LOOP 241 to 85
           94 POP_BLOCK
           95 JUMP_FORWARD 46 to 112
 L. 28     96 LOAD_GLOBAL str: len
           97 LOAD_CONST unicode: 
           98 LOAD_ATTR str: encode
           99 LOAD_CONST str: unicode-internal
          100 CALL_FUNCTION 1
          101 CALL_FUNCTION 1
          102 LOAD_CONST long: 4
          103 COMPARE_OP 2
          104 POP_JUMP_IF_FALSE 316 to 112
 L. 29    105 LOAD_FAST str: self
          106 LOAD_ATTR str: expected
          107 LOAD_ATTR str: add
          108 LOAD_CONST str: test_macostools
          109 CALL_FUNCTION 1
          110 POP_TOP
          111 JUMP_FORWARD 0 to 112
 L. 32    112 LOAD_GLOBAL str: sys
          113 LOAD_ATTR str: platform
          114 LOAD_CONST str: win32
          115 COMPARE_OP 3
          116 POP_JUMP_IF_FALSE 391 to 139
 L. 35    117 LOAD_CONST str: test_unicode_file
          118 LOAD_CONST str: test_winreg
 L. 36    119 LOAD_CONST str: test_winsound
          120 LOAD_CONST str: test_startfile
 L. 37    121 LOAD_CONST str: test_sqlite
          122 LOAD_CONST str: test_msilib
          123 BUILD_LIST 6
          124 STORE_FAST str: WIN_ONLY
 L. 38    125 SETUP_LOOP 139
          126 LOAD_FAST str: WIN_ONLY
          127 GET_ITER
          128 FOR_ITER 22 to 137
          129 STORE_FAST str: skip
 L. 39    130 LOAD_FAST str: self
          131 LOAD_ATTR str: expected
          132 LOAD_ATTR str: add
          133 LOAD_FAST str: skip
          134 CALL_FUNCTION 1
          135 POP_TOP
          136 CONTINUE_LOOP 362 to 128
          137 POP_BLOCK
          138 JUMP_FORWARD 0 to 139
 L. 41    139 LOAD_GLOBAL str: sys
          140 LOAD_ATTR str: platform
          141 LOAD_CONST str: irix
          142 COMPARE_OP 3
          143 POP_JUMP_IF_FALSE 466 to 166
 L. 42    144 LOAD_CONST str: test_imageop
          145 LOAD_CONST str: test_al
          146 LOAD_CONST str: test_cd
          147 LOAD_CONST str: test_cl
 L. 43    148 LOAD_CONST str: test_gl
          149 LOAD_CONST str: test_imgfile
          150 BUILD_LIST 6
          151 STORE_FAST str: IRIX_ONLY
 L. 44    152 SETUP_LOOP 166
          153 LOAD_FAST str: IRIX_ONLY
          154 GET_ITER
          155 FOR_ITER 22 to 164
          156 STORE_FAST str: skip
 L. 45    157 LOAD_FAST str: self
          158 LOAD_ATTR str: expected
          159 LOAD_ATTR str: add
          160 LOAD_FAST str: skip
          161 CALL_FUNCTION 1
          162 POP_TOP
          163 CONTINUE_LOOP 437 to 155
          164 POP_BLOCK
          165 JUMP_FORWARD 0 to 166
 L. 47    166 LOAD_GLOBAL str: sys
          167 LOAD_ATTR str: platform
          168 LOAD_CONST str: sunos5
          169 COMPARE_OP 3
          170 POP_JUMP_IF_FALSE 516 to 184
 L. 48    171 LOAD_FAST str: self
          172 LOAD_ATTR str: expected
          173 LOAD_ATTR str: add
          174 LOAD_CONST str: test_sunaudiodev
          175 CALL_FUNCTION 1
          176 POP_TOP
 L. 49    177 LOAD_FAST str: self
          178 LOAD_ATTR str: expected
          179 LOAD_ATTR str: add
          180 LOAD_CONST str: test_nis
          181 CALL_FUNCTION 1
          182 POP_TOP
          183 JUMP_FORWARD 0 to 184
 L. 51    184 LOAD_GLOBAL str: sys
          185 LOAD_ATTR str: py3kwarning
          186 POP_JUMP_IF_TRUE 544 to 194
 L. 52    187 LOAD_FAST str: self
          188 LOAD_ATTR str: expected
          189 LOAD_ATTR str: add
          190 LOAD_CONST str: test_py3kwarn
          191 CALL_FUNCTION 1
          192 POP_TOP
          193 JUMP_FORWARD 0 to 194
 L. 54    194 LOAD_GLOBAL str: True
          195 LOAD_FAST str: self
          196 STORE_ATTR str: valid
          197 JUMP_FORWARD 0 to 198
          198 LOAD_CONST obj: N
          199 RETURN_VALUE

method isvalid(self):

 L.  3      0 LOAD_FAST str: self
            1 LOAD_ATTR str: valid
            2 RETURN_VALUE

method getexpected(self):

 L.  7      0 LOAD_FAST str: self
            1 LOAD_ATTR str: isvalid
            2 CALL_FUNCTION 0
            3 POP_JUMP_IF_TRUE 18 to 6
            4 LOAD_GLOBAL str: AssertionError
            5 RAISE_VARARGS 1
 L.  8      6 LOAD_FAST str: self
            7 LOAD_ATTR str: expected
            8 RETURN_VALUE


