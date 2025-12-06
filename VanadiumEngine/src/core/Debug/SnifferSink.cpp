#include "pch.h"
#include "SnifferSink.h"
#include "Core/Debug/Log.h"

void SnifferSink::Report(std::string string)
{
	if (m_fileStream.is_open())
	{
		m_fileStream << string << std::endl;
	}
	else {
	}
}

void SnifferSink::SetOutputFile(std::filesystem::path path)
{
	m_outputFile = path;
	m_fileStream = std::ofstream(m_outputFile);
}