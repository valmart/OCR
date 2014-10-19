#include "platform.h"

void sleep_ms(int sleepMs)
{
	#ifdef WINDOWS
		Sleep(sleepMs);
	#else
		usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
	#endif
}

std::string getExeDir()
{
	#ifdef WINDOWS
		TCHAR szEXEPath[2048];
		std::stringstream ss;
		GetModuleFileName(NULL, szEXEPath, 2048);
		ss << szEXEPath;

		std::string exeFile = ss.str();
		std::string directory;
		const size_t last_slash_idx = exeFile.rfind('\\');
		if (std::string::npos != last_slash_idx)
		{
			directory = exeFile.substr(0, last_slash_idx);
		}
		return directory;
	#else
                char buffer[2048];
                
                readlink("/proc/self/exe", buffer, 2048);
                
		std::stringstream ss;
		ss << buffer;
		std::string exeFile = ss.str();
		std::string directory;
                
                const size_t last_slash_idx = exeFile.rfind('/');
		if (std::string::npos != last_slash_idx)
		{
			directory = exeFile.substr(0, last_slash_idx);
		}
		return directory;
	#endif
}