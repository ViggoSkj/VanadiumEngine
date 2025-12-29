#include "pch.h"
#include "FileWatcher.h"

namespace Vanadium
{

	void Watch(std::filesystem::path path, std::function<void()> onChange, std::atomic<bool>& running)
	{
		std::chrono::file_time last = std::filesystem::last_write_time(path);

		while (running.load(std::memory_order_relaxed))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			if (last != std::filesystem::last_write_time(path))
			{
				last = std::filesystem::last_write_time(path);
				onChange();
			}
		}
	}

	FileWatcher::FileWatcher(std::filesystem::path path, std::function<void()> onChange)
		: m_path(path), m_onChange(onChange)
	{
		m_running.store(true, std::memory_order_relaxed);
		m_watcherThread = std::thread(Watch, path, onChange, std::ref(m_running));
	}

	FileWatcher::~FileWatcher()
	{
		m_running.store(false, std::memory_order_relaxed);
		if (m_watcherThread.joinable())
			m_watcherThread.join();
	}

	FileWatcher::FileWatcher(FileWatcher&& other) noexcept
		: m_path(std::move(other.m_path))
		, m_onChange(std::move(other.m_onChange))
		, m_running(other.m_running.load())

	{
		m_watcherThread = std::thread(Watch, m_path, m_onChange, std::ref(m_running));
	}
}