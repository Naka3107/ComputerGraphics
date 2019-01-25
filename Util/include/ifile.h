#pragma once

#include <string>

class ifile
{
public:
	bool read(const std::string& filename);
	const std::string get_contents() const;

private:
	std::string _contents;
};