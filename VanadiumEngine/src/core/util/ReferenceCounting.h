#pragma once

class ReferenceCounting
{
public:
	virtual void Dispose() {};

	ReferenceCounting() {
		m_references = new unsigned int;
		*m_references = 0;
		Inc();
	};

	ReferenceCounting(const ReferenceCounting& other)
	{
		m_references = other.m_references;
		Inc();
	}

	ReferenceCounting& operator=(ReferenceCounting& other)
	{
		std::cout << "cpy";
	}

	~ReferenceCounting() {
		Dec();
		if (m_references == 0)
			Dispose();
	};

private:
	void Inc()
	{
		(*m_references)++;
	}

	void Dec()
	{
		(*m_references)--;
	}

	unsigned int* m_references = 0;
};