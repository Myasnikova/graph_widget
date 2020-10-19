TEMPLATE 	= app

QT += core gui 
greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets

HEADERS +=  graph.h \
			graph_view.h \
			node.h
	
SOURCES +=  graph.cpp \
			main.cpp \
			graph_view.cpp\
			node.cpp
			
FORMS += graph_view.ui \