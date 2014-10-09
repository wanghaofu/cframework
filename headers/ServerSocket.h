// Definition of the ServerSocket class

#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"
#include <list>
#include <semaphore.h>
#include "ThreadReadWriteLock.h"

using std::list;

class ServerSocket : public Socket
{
	public:

		ServerSocket (const int port );
		ServerSocket (){};
		virtual ~ServerSocket();

		const ServerSocket& operator << ( const std::string& ) const;
		const ServerSocket& operator >> ( std::string& ) const;

		void accept ( ServerSocket& );

		void Run();
		void RecvFile(Socket* clientSocket);
	private:
		//accept multi-clients
		bool Accept();
		void AddClient(Socket* clientSocket);
		static void DeleteClient(Socket* clientSocket);
		static void* ProcessMessage(void* arg);
		static void SendMsgToAllUsers(const std::string& message);

		static list<Socket*> clientSockets;
		static bool serviceFlag;

		static ThreadReadWriteLock readWriteLock;

};


#endif


