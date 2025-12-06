#pragma once
#include "pch.h"
#include <fstream>

// what should it do?

// keep track of what the state was
// keep track of when the state was
// keep track of where the state changed

#define SNIFFER_SINK_REPORT(object) SnifferSink::Get().Report(object, __LINE__, __FILE__)

class SnifferSink
{
public:
	static SnifferSink& Get()
	{
		if (!s_instance) {
			s_instance = new SnifferSink();
		}
		return *s_instance;
	}

	template <typename T>
	void Report(T object, int line, std::string file1)
	{
		"SnifferSink Report: {}", object.ToString();
	}

	void Report(std::string string);
	void SetOutputFile(std::filesystem::path path);

private:
	SnifferSink() = default;
	static inline SnifferSink* s_instance = nullptr;

	std::filesystem::path m_outputFile;
	std::ofstream m_fileStream;
};