TEMPLATE = subdirs

SUBDIRS = \
	Task \
	qtmqtt \
	
Task.depends = qtmqtt
