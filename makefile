# Compilateur et options de compilation
CC=gcc
CFLAGS=-Wall `pkg-config --cflags gtk+-3.0 mysqlclient`

# Éditeur de liens et options de lien
LD=gcc
LDFLAGS=`pkg-config --libs gtk+-3.0 mysqlclient`

# Nom de l'exécutable
EXECUTABLE=my_program

# Dossier des fichiers d'en-tête
HEADER_DIR=headers

# Récupérer tous les fichiers d'en-tête du projet
HEADERS=$(wildcard $(HEADER_DIR)/*.h)

# Récupérer tous les fichiers C du projet, y compris les sous-dossiers
SOURCES=$(shell find . -name "*.c")

# Objets correspondants aux fichiers sources
OBJECTS=$(SOURCES:.c=.o)

# Règle pour compiler les fichiers sources en objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Cible pour compiler le programme
$(EXECUTABLE): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

# Cible pour nettoyer les fichiers objets et l'exécutable
clean:
	find . -name "*.o" -type f -delete