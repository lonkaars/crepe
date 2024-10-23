#pragma once

#include <string>
class Resource {
public:
	virtual ~Resource() = default;

	const std::string & getContent() const { return this->m_content; }

protected:
	std::string m_content;
};
