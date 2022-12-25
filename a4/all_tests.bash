#/bin/sh

cat tests/in01.txt | ./driver-original.py | diff tests/out01.txt -
cat tests/in02.txt | ./driver-original.py | diff tests/out02.txt -
cat tests/in03.txt | ./driver-original.py | diff tests/out03.txt -
cat tests/in04.txt | ./driver-original.py | diff tests/out04.txt -
cat tests/in05.txt | ./driver-original.py | diff tests/out05.txt -

cat tests/in06.txt | ./driver-original.py | diff tests/out06.txt -
cat tests/in07.txt | ./driver-original.py | diff tests/out07.txt -
cat tests/in08.txt | ./driver-original.py | diff tests/out08.txt -
cat tests/in09.txt | ./driver-original.py | diff tests/out09.txt -
cat tests/in10.txt | ./driver-original.py | diff tests/out10.txt -

cat tests/in11.txt | ./driver-original.py | diff tests/out11.txt -
cat tests/in12.txt | ./driver-original.py | diff tests/out12.txt -
cat tests/in13.txt | ./driver-original.py | diff tests/out13.txt -
cat tests/in14.txt | ./driver-original.py | diff tests/out14.txt -
cat tests/in15.txt | ./driver-original.py | diff tests/out15.txt -

./driver-new.py --input tests/in01.txt --output test_output/_out01.txt
diff tests/out01.txt test_output/_out01.txt
./driver-new.py --input tests/in02.txt --output test_output/_out02.txt
diff tests/out02.txt test_output/_out02.txt
./driver-new.py --input tests/in03.txt --output test_output/_out03.txt
diff tests/out03.txt test_output/_out03.txt
./driver-new.py --input tests/in04.txt --output test_output/_out04.txt
diff tests/out04.txt test_output/_out04.txt
./driver-new.py --input tests/in05.txt --output test_output/_out05.txt
diff tests/out05.txt test_output/_out05.txt


./driver-new.py --input tests/in06.txt --output test_output/_out06.txt
diff tests/out06.txt test_output/_out06.txt
./driver-new.py --input tests/in07.txt --output test_output/_out07.txt
diff tests/out07.txt test_output/_out07.txt
./driver-new.py --input tests/in08.txt --output test_output/_out08.txt
diff tests/out08.txt test_output/_out08.txt
./driver-new.py --input tests/in09.txt --output test_output/_out09.txt
diff tests/out09.txt test_output/_out09.txt
./driver-new.py --input tests/in10.txt --output test_output/_out10.txt
diff tests/out10.txt test_output/_out10.txt

./driver-new.py --input tests/in11.txt --output test_output/_out11.txt
diff tests/out11.txt test_output/_out11.txt
./driver-new.py --input tests/in12.txt --output test_output/_out12.txt
diff tests/out12.txt test_output/_out12.txt
./driver-new.py --input tests/in13.txt --output test_output/_out13.txt
diff tests/out13.txt test_output/_out13.txt
./driver-new.py --input tests/in14.txt --output test_output/_out14.txt
diff tests/out14.txt test_output/_out14.txt
./driver-new.py --input tests/in15.txt --output test_output/_out15.txt
diff tests/out15.txt test_output/_out15.txt
