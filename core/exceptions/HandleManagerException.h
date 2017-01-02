#ifndef DGE_HANDLE_MANAGER_EXCEPTION
#define DGE_HANDLE_MANAGER_EXCEPTION

#include <exception>
#include <stdexcept>

// TODO: Modify HandleManagerException to provide actual information.

struct HandleManagerException : public std::exception
{
	const char* what() const throw()
	{
		return "Handle Manager exception.";
	}
};

#endif // !DGE_HANDLE_MANAGER_EXCEPTION

