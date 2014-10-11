#include "ThreadReadWriteLock.h"
#include <pthread.h>

ThreadReadWriteLock::ThreadReadWriteLock()
{

}

ThreadReadWriteLock::~ThreadReadWriteLock()
{

}
bool ThreadReadWriteLock::SetWriteLock()
{
	return true;
}


void ThreadReadWriteLock::UnLock()
{

}

bool ThreadReadWriteLock::SetReadLock()
{

}