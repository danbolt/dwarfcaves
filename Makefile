SOURCE=src/*.cpp
MYPROGRAM=dwarfcaves

FLAGS=

CC=clang++

CPPFLAGS=-g -Wall -Werror -std=c++11
LDFLAGS=-g

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(CPPFLAGS) $(SOURCE) -o$(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)


