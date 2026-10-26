import multiprocessing

def foo(conn):
    conn.send('123')
r, w = multiprocessing.Pipe(False)
p = multiprocessing.Process(args=(w,),target=foo)
p.start()
w.close()
print(r.recv())
r.close()
p.join()
