CC ?= gcc
AR ?= ar
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
CPPFLAGS ?= -I.

FONTES = lista.c pilha.c fila.c grafo.c caminho.c
OBJETOS = $(FONTES:%.c=build/%.o)

.PHONY: all test stress sanitize clean

all: build/libtads.a

build:
	mkdir -p build

build/%.o: %.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/libtads.a: $(OBJETOS)
	$(AR) rcs $@ $^

build/teste_tads: $(FONTES) tests/main_teste.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

test: build/teste_tads
	./build/teste_tads

build/stress_grafo: lista.c grafo.c tests/stress_grafo.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

stress: build/stress_grafo
	./build/stress_grafo

sanitize: | build
	$(CC) $(CPPFLAGS) -std=c11 -Wall -Wextra -Wpedantic -Werror \
		-fsanitize=address,undefined -fno-omit-frame-pointer \
		$(FONTES) tests/main_teste.c -o build/teste_sanitize
	./build/teste_sanitize

clean:
	rm -rf build grafo_teste.txt
