#!/usr/bin/env python
# RainbowTable.py -- A rainbow table generator.
# 	DEPENDS ON:
#		-SQLite3 installation
#		-File called rainbow.db with the following schema:
##			CREATE TABLE rainbow(hash VARCHAR(32) PRIMARY KEY, word VARCHAR(255));
#		
# 		@@@@@!Values for this database are HARDCODED!@@@@@
#
# Program takes no arguments, gives no stdout output.
# Program notes:
#	This is remarkably similar to tutorial code
#	because I've never done threading before.
#SOURCES USED:
#	http://themattreid.com/wordpress/2010/08/30/easy-python-threading-mysql-connections/
#	http://rguha.wordpress.com/2008/11/14/multi-threaded-database-access-with-python/
#	http://www.tutorialspoint.com/python/python_multithreading.htm
#	http://pymotw.com/2/threading/

import threading
import sqlite3
import hashlib
import Queue
import time
import os
import pdb
import sys

exitFlag = 0

class ThreaderDB (threading.Thread):
	def __init__(self, threadID, name, q):
		threading.Thread.__init__(self)
		self.threadID = threadID
		self.name = name
		self.q = q
	def run(self):
		print "Starting " + self.name
		processLine(self.name, self.q)
		print "Exiting " + self.name
	
def processLine(threadName, q):
	while not exitFlag:
		queueLock.acquire()
		if not workQueue.empty():
			word = q.get()
			queueLock.release()
			print "%s processing %s" % (threadName, word)
			hashedWord = hashlib.md5(word).hexdigest()
			db_operation(word, hashedWord, threadName)
		else:
			queueLock.release()
		time.sleep(.5) 
		#let up for a bit so we don't play survival of the fittest

def db_operation(word, hashedWord, threadName):
	insertPair = (hashedWord , word) #protect against SQL injection
	sql = "INSERT INTO rainbow (hash, word) VALUES (?,?);"
	try:
		db = sqlite3.connect('rainbow.db')  #???timeout value
		cursor = db.cursor()
		cursor.execute(sql, insertPair)
		db.commit()
		cursor.close()
		db.close()
		print "word inserted by " + threadName + ": " + word
	#except sqlite3.OperationalError:
		#print "______TAKE TWO ON: " + word  + "_______"
		#time.sleep(1)
		#Retry
		##take two so the word gets added eventually
		## and so the thread doesn't die
	except sqlite3.Error as e:
		print e
		#pdb.set_trace()            
		sys.exit (1)
	return
	
threadList = ["Thread-1", "Thread-2", "Thread-3","Thread-4","Thread-5"]
queueLock = threading.Lock()
workQueue = Queue.Queue()
threads = []
threadID = 1

for tName in threadList:
	thread = ThreaderDB(threadID, tName, workQueue)
	thread.start()
	threads.append(thread)
	threadID += 1

#add items to queue to be processed
queueLock.acquire()
 
if (os.path.isfile("/usr/share/dict/linux.words")):
	print "Loading dictionary... This might take a while."
	sysDict = []
	with open("/usr/share/dict/words", 'r') as f:
		for line in f:
			line = line.rstrip('\n')
			print line
			workQueue.put(line)
	if not (f.closed): #double check that `with` did its job
		f.close()
else:
	queueLock.release()
	print "Dictionary not found. Install the `words` package."
	sys.exit(1)
queueLock.release()
print "Dict Loaded."

while not workQueue.empty():
	pass

exitFlag=1;

for t in threads:
	t.join()
print "Main Thread Exiting...."
