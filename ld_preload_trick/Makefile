all: hook_fork.so hook_rand.so hook_strcmp.so rand_check strcmp_check

hook_fork.so: hook_fork.c
	gcc -shared -fPIC -o hook_fork.so hook_fork.c -ldl
hook_rand.so: hook_rand.c
	gcc -shared -fPIC -o hook_rand.so hook_rand.c -ldl	
hook_strcmp.so: hook_strcmp.c
	gcc -shared -fPIC -o hook_strcmp.so hook_strcmp.c -ldl

rand_check: rand_example.c
	gcc -o rand_check rand_example.c

strcmp_check: strcmp_example.c
	gcc -o strcmp_check strcmp_example.c

clean:
	rm *.so rand_check strcmp_check
