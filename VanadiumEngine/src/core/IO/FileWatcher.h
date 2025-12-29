#pragma once
#include "pch.h"
#include <functional>
#include <thread>
namespace Vanadium
{

	class FileWatcher
	{
	public:
		FileWatcher() = default;
		FileWatcher(std::filesystem::path path, std::function<void()> onChange);
		~FileWatcher();

		// non-copyable
		FileWatcher(const FileWatcher&) = delete;
		FileWatcher& operator=(const FileWatcher&) = delete;

		// movable
		FileWatcher(FileWatcher&& other) noexcept;

		FileWatcher& operator=(FileWatcher&& other) noexcept
		{
			if (this == &other) return *this;
			// stop and join any running thread we own
			if (m_running.load()) {
				m_running.store(false, std::memory_order_relaxed);
				if (m_watcherThread.joinable()) m_watcherThread.join();
			}
			m_path = std::move(other.m_path);
			m_onChange = std::move(other.m_onChange);
			m_running.store(other.m_running.load(), std::memory_order_relaxed);
			other.m_running = false;
			return *this;
		}

	private:
		std::filesystem::path m_path;
		std::function<void()> m_onChange;
		std::thread m_watcherThread;
		std::atomic<bool> m_running;
	};
}