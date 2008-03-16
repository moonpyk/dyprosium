TARGET 		= Dyprosium
TEMPLATE 	= app

QT		+= network xml
CONFIG	+= release warn_off

INCLUDEPATH += \
	./GeneratedFiles \
    ./GeneratedFiles/Moc \
    .
    
DEPENDPATH	+= .

OBJECTS_DIR += ./GeneratedFiles/Objects
MOC_DIR		+= ./GeneratedFiles/Moc
UI_DIR		+= ./GeneratedFiles
RCC_DIR		+= ./GeneratedFiles

mac:ICON 			= Dyprosium.icns
win32:RC_FILE		= Dyprosium.rc

DESTDIR = ../bin

#TRANSLATIONS += ./Translations/

#Include file(s)
include(Dyprosium.pri)
