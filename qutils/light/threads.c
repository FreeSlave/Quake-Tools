
#include "cmdlib.h"
#include "threads.h"

#ifdef HAS_POSIX_THREADS

static threadfunc_t q_entry;

static void* ThreadEntryStub(void* pParam)
{
    q_entry(pParam);
    return NULL;
}

pthread_mutex_t	*my_mutex;

int		numthreads = -1;

#include <stddef.h>

#ifdef _SC_NPROCESSORS_ONLN
void ThreadSetDefault()
{
    if (numthreads == -1)
    {
        int res = sysconf(_SC_NPROCESSORS_ONLN); //The number of processors currently online (available).
        if (res < 1)
            numthreads = 1;
        else
            numthreads = res;
    }
}
#elif defined(__linux__)
#include <sched.h>
void ThreadSetDefault()
{
    if (numthreads == -1)
    {
        cpu_set_t cs;
        CPU_ZERO(&cs);
        if (sched_getaffinity(0, sizeof(cs), &cs) != 0)
        {
            numthreads = 1;
            return;
        }
        
        int count = 0;
        for (int i = 0; i < CPU_COUNT(&cs); i++)
        {
            if (CPU_ISSET(i, &cs))
                count++;
        }
        
        if (count < 1)
            numthreads = 1;
        else
            numthreads = count;
    }
}
#else
void ThreadSetDefault()
{
    if (numthreads == -1)
        numthreads = 1;
}
#endif

#else //not HAS_POSIX_THREADS

int     numthreads = 1;

void ThreadSetDefault()
{
    if (numthreads == -1)
        numthreads = 1;
}

#endif //HAS_POSIX_THREADS

void InitThreads (void)
{
    ThreadSetDefault();
#ifdef HAS_POSIX_THREADS
	pthread_mutexattr_t mattrib;
	
	my_mutex = (pthread_mutex_t*)malloc(sizeof(*my_mutex));
	if (pthread_mutexattr_init(&mattrib) == -1)
		Error("pthread_mutex_attr_init failed");
#ifdef __alpha
	if (pthread_mutexattr_setkind_np (&mattrib, MUTEX_FAST_NP) == -1)
		Error ("pthread_mutexattr_setkind_np failed");
#endif
	if (pthread_mutex_init(my_mutex, &mattrib) == -1)
		Error("pthread_mutex_init failed");
#endif
}

/*
===============
RunThreadsOn
===============
*/
void RunThreadsOn ( threadfunc_t func )
{
#ifdef HAS_POSIX_THREADS
	pthread_t	work_threads[256];
	pthread_addr_t	status;
	pthread_attr_t	attrib;
	int		i;
	
	if (numthreads == 1)
	{
		func (NULL);
		return;
	}
	
	q_entry = func;

#ifdef __alpha
	if (pthread_attr_create (&attrib) == -1)
		Error ("pthread_attr_create failed");
#else
    if (pthread_attr_init (&attrib) == -1)
        Error ("pthread_attr_init failed");
#endif
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
	if (pthread_attr_setstacksize (&attrib, 0x100000) == -1)
		Error ("pthread_attr_setstacksize failed");
#endif
    
	for (i=0 ; i<numthreads ; i++)
	{
  		if (pthread_create(&work_threads[i], &attrib, ThreadEntryStub, (pthread_addr_t)i) == -1)
			Error ("pthread_create failed");
	}
		
	for (i=0 ; i<numthreads ; i++)
	{
		if (pthread_join (work_threads[i], &status) == -1)
			Error ("pthread_join failed");
	}
	
	q_entry = NULL;
#else
	func (NULL);
#endif
}
