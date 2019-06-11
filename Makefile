#  Makefile 
#  Auteur : Farès BELHADJ
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 03/02/2014

SHELL = /bin/sh
# définition des commandes utilisées
CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# déclaration des options du compilateur
PG_FLAGS =
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_mixer -lSDL2_image
CPPFLAGS = -I. $(SDL_CFLAGS)
CFLAGS = -Wall -O3
LDFLAGS = -lm $(SDL_LDFLAGS) -lassimp -lGL4Dummies -lSDL2_ttf

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	MACOSX_DEPLOYMENT_TARGET = 10.8
        CFLAGS += -I/usr/X11R6/include -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
        LDFLAGS += -framework OpenGL -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
else
        LDFLAGS +=  -L/usr/lib -L/usr/X11R6/lib -lGL -lGLU
endif

#définition des fichiers et dossiers
PROGNAME = demoHelper
PACKAGE=$(PROGNAME)
VERSION = 1.43
distdir = $(PACKAGE)-$(VERSION)
HEADERS = audioHelper.h animations.h assimp.h assimp1.h assimp2.h assimp3.h assimp4.h
SOURCES = audioHelper.c assimp.c assimp1.c assimp2.c assimp3.c assimp4.c credits2.c makeLabyrinth.c animations.c window.c base.c chorale.c Laby.c
OBJ = $(SOURCES:.c=.o)
DOXYFILE = documentation/Doxyfile
EXTRAFILES = COPYING shaders/basic.vs shaders/mix.fs shaders/basic.fs	\
shaders/base.vs shaders/base.fs shaders/earth.vs shaders/earth.fs	\
takeonme.mod images/land_ocean_ice_2048_glossmap.png			\
images/land_ocean_ice_2048.png images/moon.jpg
DISTFILES = $(SOURCES) Makefile $(HEADERS) $(DOXYFILE) $(EXTRAFILES)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)

distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)

doc: $(DOXYFILE)
	cat $< | sed -e "s/PROJECT_NAME *=.*/PROJECT_NAME = $(PROGNAME)/" | sed -e "s/PROJECT_NUMBER *=.*/PROJECT_NUMBER = $(VERSION)/" >> $<.new
	mv -f $<.new $<
	cd documentation && doxygen && cd ..

clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz gmon.out core.* documentation/*~ shaders/*~ GL4D/*~ documentation/html
