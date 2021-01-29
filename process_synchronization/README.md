## Running process 100 times
Few times its better to run the program several times to check for concurrency:

```
for i in {1..100}; do COMMAND-HERE; done
```

For example:
```
    for i in {1..100}; do ./a.out; done
```
    
## Examples:
Compiling: `make all`

Run the program several times using the above command to see the concurrency issues. I have used `pthread_yield()` to force the scheduler to switch threads.

### `milk_problem.c`
The milk problem with out notes.
```
    for i in {1..100}; do ./milk_problem; done
```
You will see both persons will buy milk in certain runs.
### `milk_problem_note.c`
The milk problem with one note.
```
    for i in {1..100}; do ./milk_problem_note; done
```
You will stll see both persons will buy milk in certain runs.

### `milk_problem_starvation.c`
The milk problem with two notes that leads to starvation.
```
    for i in {1..100}; do ./milk_problem_starvation; done
```
You will stll see neither persons will buy milk in certain runs (starvation).

### `fork_sync.c`
Here, both parent and child try to change the same variable. 
Can concurreny happen here? Specifically, will the statement: "Another process changed values of was to" ever gets printed? If not, why?



