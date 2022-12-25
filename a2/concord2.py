#!/usr/bin/env python3

import sys

# This function loops through the list of all lines and the list of words 
# then passes the ones that match to the next output function
def output_looping(words, lines):
	
	for word in words:
		for line in lines:
			line_token = line.split()
			for token in line_token:	
				if(word == token.lower()):
					output(token, line)

# This function takes a work and a line that contains the word and prints out
# the line formatted acording the assignment specifications
def output(token, line):
	line_token = line.split()
					
	cur_index = line_token.index(token)
	before_word = ' '.join(line_token[:cur_index]) #string of everything before token
	while(len(before_word) > 19):	#removes extra words from the front
		before_word = before_word.split()
		before_word = before_word[1:]
		before_word = ' '.join(before_word)
	after_word = ' '.join(line_token[cur_index + 1:]) #string of everything after token
	while(len(token + ' ' + after_word) > 31):	#removes extra words from the end
		after_word = after_word.split()
		after_word = after_word[:-1]
		after_word = ' '.join(after_word)	

	all_together = before_word + token + after_word
	word_index = all_together.index(token)
	print(" " * (28 - len(before_word)), end="")	#prints out extra spaces for formatting

	#prints string output with word caped
	if(len(after_word) == 0):
		print(before_word + ' ' + token.upper())
	elif(len(before_word) == 0):	
		print(' ' + token.upper() + ' ' + after_word)
	else:
		print((before_word + ' ' + token.upper() + ' ' + after_word).strip())

# This function takes a list of all the exclusion words and a list of all the sentences
# then returns a list of all non exlusion words in the list of sentences
def sort_input(ex_words, index_lines):
	words_list = []
	for line in index_lines:
		words_list.extend(line.split()) #all words to loop ahrough

	#this section makes all exclusion words lower case
	ex_words = ' '.join(ex_words)
	ex_words = ex_words.lower()
	ex_words = ex_words.split()
		
	loop_words = []
	for word in words_list:
		if(word.lower() not in ex_words):
			loop_words.append(word.lower())

	loop_words = set(loop_words)	#this part removes duplicates
	loop_words = list(loop_words)
	loop_words.sort() #final list to loop through sorted
	return loop_words

# The main function :D
def main():

	#some variables used for reading input
	numlines = 0
	num_exwords = 0
	all_lines = []
	
	#reads the input from standard in
	for line in sys.stdin:
		all_lines.append(line.strip())

	#wrong version error handling
	if(all_lines[0] == "1"):
		print("Input is version 1, concord2.py expected version 2")
		exit()
	
	#breaks input into exclusion words and sentences
	excl_words = all_lines[2:all_lines.index("\"\"\"\"")]
	index_lines = all_lines[all_lines.index("\"\"\"\"") + 1:]
	
	#gets list of words with exclusions removed
	loop_words = sort_input(excl_words, index_lines)
	
	#call output function outputting
	output_looping(loop_words, index_lines)


if __name__ == "__main__":
	main()
