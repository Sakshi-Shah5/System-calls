#include "types.h"
#include "stat.h"
#include "user.h"

#ifdef STUB_FUNCS
int get_syscall_count(int call_type) { return 0; }
int reset_syscall_count(void) { return 0; }
#endif

void usage(char *bn)
{
    printf(1, "Usage: %s syscall-type \n"
              "\tsyscall type: \n"
              "\t\t0: fork() \n"
              "\t\t1: wait() \n"
              "\t\t2: exit() \n",
           bn);
}

int rand_between(int low, int high)
{
    if (high <= low)
    {
        high = low + 10;
    }
    return low + uptime() % (high - low + 1);
}

void test_loop(int loop)
{
    int fork_cnt = 0, wait_cnt = 0, exit_cnt = 0;
    int i = 0;
    reset_syscall_count();
    for (i = 0; i < loop; i++)
    {
        int fret = fork();
        if (fret < 0)
        {
            printf(1, "fork() failed\n");
            exit();
        }
        else if (0 == fret)
        {
            exit();
        }
        else
        {
            wait();
        }
    }
    fork_cnt = get_syscall_count(0);
    wait_cnt = get_syscall_count(1);
    exit_cnt = get_syscall_count(2);
    printf(1, "Expected result: fork [%d] wait [%d] exit [%d] \n", loop, loop, loop);
    printf(1, "Actual result: fork [%d] wait [%d] exit [%d] \n", fork_cnt, wait_cnt, exit_cnt);
}

int main(int argc , char * argv[])
{
    printf(1,">>>Test 1:\n");
    test_loop(rand_between(5,20));

    printf(1,"\n>>>Test 2:\n");
    test_loop(rand_between(5,20));

    printf(1,"\n>>>Test 3:\n");
    printf(1, "Expected return value [-1]\n");
    printf(1, "Actual return value [%d] \n",  get_syscall_count(3));

    exit();
}