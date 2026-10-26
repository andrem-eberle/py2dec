from test.test_support import 'TestFailed',
PI = 3.14159265358979312
TWOPI = 6.28318530717958623
PI_str = '3.14159265358979324'
TWOPI_str = '6.28318530717958648'

def check_ok(x,x_str):
    
    if not x > 0.00000000000000000 :
        raise AssertionError
    x2 = eval(x_str)
    
    if not x2 > 0.00000000000000000 :
        raise AssertionError
    diff = abs( x - x2 )
    
    if ( x2 + ( diff / 8.00000000000000000 ) ) != x2 :
        raise TestFailed( 'Manifest const %s lost too much precision ' % x_str )
check_ok(PI, PI_str)
check_ok(TWOPI, TWOPI_str)
