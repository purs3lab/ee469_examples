all: fork_sync milk_problem milk_problem_note milk_problem_starvation

fork_sync:
	gcc fork_sync.c -o fork_sync -D_GNU_SOURCE
milk_problem:
	gcc milk_problem.c -o milk_problem -D_GNU_SOURCE -lpthread
milk_problem_note:
	gcc milk_problem_note.c -o milk_problem_note -D_GNU_SOURCE -lpthread
milk_problem_starvation:
	gcc milk_problem_starvation.c -o milk_problem_starvation -D_GNU_SOURCE -lpthread
clean:
	rm fork_sync milk_problem milk_problem_note milk_problem_starvation
