BIN=scat
DIR=/usr/local/bin

all: $(BIN)

install:
	mv $(BIN) $(DIR)

uninstall:
	rm $(DIR)/$(BIN)
