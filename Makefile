CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -lraylib -g

SOURCE = src/*.c
TARGET = muzilizer


all: $(TARGET)
	@echo "built successfully"


clean:
	rm -rf $(TARGET)

$(TARGET): $(SOURCE)
	@$(CC)  $(SOURCE) $(CFLAGS) -o $(TARGET)

