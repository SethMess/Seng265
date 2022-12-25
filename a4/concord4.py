import sys
import re

class concord:

	def __init__(self, input=None, output=None):
		'''Creates all the used lists and calls full_concordance if there is a file passed'''
		self.input = input
		self.output = output
		self.all_input = []
		self.ex_words = []
		self.all_lines = []
		self.clean_words = []
		self.final_lines = []
		if (self.input is not None and self.output is not None):
			self.full_concordance()

	def full_concordance(self):
		'''Calls all the functions and outputs to a file if needed'''
		self.__get_input()
		self.__sort_input()
		self.__order_output()
		if(self.output != None):
			#writes to output file
			self.__write_to_file()

		#returns the final list
		return self.final_lines

	def __get_input(self):
		'''This function reads from stdin or from a file depending on how the class is called'''
		if(self.input == None):
			#stdin input
			for line in sys.stdin:
				self.all_input.append(line.strip())
		else:
			#file input
			f = open(str(self.input), "r")
			self.all_input = f.readlines()
			f.close
			self.all_input = [line.strip() for line in self.all_input]

		#error handling
		if(self.all_input[0] == "1"):
			print("Input is version 1, concord4.py expected version 2")
			exit()

		#separates the exlcusion words from the sentences
		self.ex_words = self.all_input[2:self.all_input.index("\"\"\"\"")]
		self.all_lines = self.all_input[self.all_input.index("\"\"\"\"") + 1:]
		

		
	def __sort_input(self):
		'''This function makes a list of all non exclusion words and sorts it'''
		temp_words = []
		#splits all input into a list of words
		for line in self.all_lines:
			temp_words.extend(line.split()) 
		self.ex_words = " ".join(self.ex_words).lower()
		self.ex_words = self.ex_words.split()
		#adds non exlusion words to clean words
		[self.clean_words.append(word.lower()) for word in temp_words if (word.lower() not in self.ex_words)]
		
		#removes duplicates and sorts
		self.clean_words = set(self.clean_words)
		self.clean_words = list(self.clean_words)
		self.clean_words.sort()


	def __order_output(self):
		'''This function substitues a word with its uppercase version then calls a function to format the line3'''		

		for word in self.clean_words:
			for line in self.all_lines:
				matchword = re.search(r"\b" + re.escape(word) + r"\b", line, re.IGNORECASE)
				if matchword:
					cur_line = re.sub(r"\b" + re.escape(word) + r"\b", word.upper(), line, flags=re.I)
					#calls formatting function
					if(word != "" and (" " not in word)):
						self.__format_line(cur_line, word)
		#end of nest

	def __format_line(self, line, word):
		'''This function does the main formatting needed for the concord formatting'''
		before_word_length = 20
		after_word_length = 31
		num_spaces = 29 + 0
		#template
		line_format = "==SPACES====BEFORE_WORD====AFTER_WORD=="
		#matches before word and after word
		match = re.search(r"^(.*)(\b" + word + r"\b.*)$", line, re.IGNORECASE)
		if match:
			before_word = match.group(1)
			after_word = match.group(2)
			
			while(len(before_word) > before_word_length):   #removes extra words from the front
				before_word = before_word.split()
				before_word = before_word[1:]
				before_word = ' '.join(before_word)
				before_word = before_word + " "

			while(len(after_word) > after_word_length): #removes extra words from the end
				after_word = after_word.split()
				after_word = after_word[:-1]
				after_word = ' '.join(after_word)
			
			#substitues all parts of the final line back into the template
			together = (before_word + after_word)
			index = together.index(word.upper())
			num_spaces = num_spaces - index
			final_line = re.sub(r"==SPACES==", " "*num_spaces, line_format)
			final_line = re.sub(r"==BEFORE_WORD==", before_word, final_line)
			final_line = re.sub(r"==AFTER_WORD==", after_word, final_line)
			self.final_lines.append(final_line)


	def __write_to_file(self):
		'''This function writes to the output file given to the function'''
		f = open(str(self.output), "w")
		for line in self.final_lines:
			f.write(line)
			f.write("\n")
		f.close()




