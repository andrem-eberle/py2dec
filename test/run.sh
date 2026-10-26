PY2DEC=../bin/py2dec

for i in $(ls);do
	if [[ "$i" == *.py ]]
	then
		if [ ! -e "${i}c" ]; then
			echo "compiling ${i}c"
			python2.7 -m compileall $i
		fi			
	fi
done;

for i in $(ls);do
	if [[ "$i" == *.pyc ]]
	then
		echo "$i"
		echo "$PY2DEC -o test-out/${i::-1} $i"
		$PY2DEC -o "test-out/${i::-1}" $i
		if [ $? -ne 0 ]; then
			echo "Error"
			exit
		fi
	fi
done;

