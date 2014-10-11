#include "ThreadReadWriteLock.h"
#include <pthread.h>

ThreadReadWriteLock::ThreadReadWriteLock()
{

}
//to not ok
ThreadReadWriteLock::~ThreadReadWriteLock()
{

}

//todo not ok
bool ThreadReadWriteLock::SetWriteLock()
{
	return true;
}

//todo not ok
void ThreadReadWriteLock::UnLock()
{

}
//todo not ok
bool ThreadReadWriteLock::SetReadLock()
{

}