

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#include <unistd.h>

#ifdef _POSIX_VERSION

#define HAS_POSIX_THREADS

#include <pthread.h>
extern	pthread_mutex_t	*my_mutex;
typedef void*    pthread_addr_t;
#define	LOCK	pthread_mutex_lock (my_mutex)
#define	UNLOCK	pthread_mutex_unlock (my_mutex)

#else

#define	LOCK
#define	UNLOCK

#endif

#else 

#define LOCK
#define UNLOCK

#endif

extern	int		numthreads;

typedef void (*threadfunc_t) (void *);

void InitThreads (void);
void RunThreadsOn ( threadfunc_t func );
