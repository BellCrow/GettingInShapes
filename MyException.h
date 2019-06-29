#pragma once
#include <exception>
#include <string>

class BaseException : public std::exception
{
public:
	BaseException(int lineNumber, const char* fileName) noexcept;
	~BaseException();

	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string ToString() const noexcept;
private:
	int m_line;
	std::string m_file;

protected:
	mutable std::string m_whatBuffer;
};
