#/bin/sh

cat tests/in01.txt | ./concord2.py | diff tests/out01.txt -
cat tests/in02.txt | ./concord2.py | diff tests/out02.txt -
cat tests/in03.txt | ./concord2.py | diff tests/out03.txt -
cat tests/in04.txt | ./concord2.py | diff tests/out04.txt -
cat tests/in05.txt | ./concord2.py | diff tests/out05.txt -
cat tests/in06.txt | ./concord2.py | diff tests/out06.txt -
cat tests/in07.txt | ./concord2.py | diff tests/out07.txt -
cat tests/in08.txt | ./concord2.py | diff tests/out08.txt -
cat tests/in09.txt | ./concord2.py | diff tests/out09.txt -
cat tests/in10.txt | ./concord2.py | diff tests/out10.txt -

cat tests/in11.txt | ./concord2.py | diff tests/out11.txt -
cat tests/in12.txt | ./concord2.py | diff tests/out12.txt -
cat tests/in13.txt | ./concord2.py | diff tests/out13.txt -
cat tests/in14.txt | ./concord2.py | diff tests/out14.txt -
cat tests/in15.txt | ./concord2.py | diff tests/out15.txt -

