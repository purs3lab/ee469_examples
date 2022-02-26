.DEFAULT_GOAL := all

all: lock

lock:
	gcc lock_example.c -o lock -lpthread

run: lock
	./lock no
	./lock bad
	./lock xchg
	./lock cmpxchg
	./lock tts
	./lock backoff
	./lock mutex

clean:
	rm -rf lock
