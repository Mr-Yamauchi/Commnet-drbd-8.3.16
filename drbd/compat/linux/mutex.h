/* "Backport" of the mutex to older Linux-2.6.x kernels.
 */
#ifndef __LINUX_MUTEX_H
#define __LINUX_MUTEX_H

#include <asm/semaphore.h>

struct mutex {
	struct semaphore sem;
};

static inline void mutex_init(struct mutex *m)
{
	sema_init(&m->sem, 1);
}

static inline void mutex_lock(struct mutex *m)
{
	/* セマフォ構造体から資源をひとつとる。資源が0ならば、資源が取得できる（1になって、確保できるまで）待ち続ける。 */
	down(&m->sem);
}

static inline int mutex_lock_interruptible(struct mutex *m)
{
	/* 割り込み有、セマフォ待ち */
	return down_interruptible(&m->sem);
}

static inline void mutex_unlock(struct mutex *m)
{
	up(&m->sem);
}

static inline int mutex_is_locked(struct mutex *lock)
{
        return atomic_read(&lock->sem.count) != 1;
}

static inline int mutex_trylock(struct mutex *lock)
{
	return !down_trylock(&lock->sem);
}
#endif
