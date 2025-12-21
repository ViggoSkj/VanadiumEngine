#pragma once
#include "pch.h"
#include <functional>
#include <thread>

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
    FileWatcher(FileWatcher&& other) noexcept
        : m_path(std::move(other.m_path))
        , m_onChange(std::move(other.m_onChange))
        , m_watcherThread(std::move(other.m_watcherThread))
        , m_running(other.m_running.load())
    {
        // mark source as stopped so its destructor doesn't try to stop again
        other.m_running = false;
    }

    FileWatcher& operator=(FileWatcher&& other) noexcept
    {
        if (this != &other)
        {
            m_path = std::move(other.m_path);
            m_onChange = std::move(other.m_onChange);
            m_watcherThread = std::move(other.m_watcherThread);
            m_running = other.m_running.load();
            other.m_running = false;
        }
        return *this;
    }

private:
	std::filesystem::path m_path;
	std::function<void()> m_onChange;
	std::thread m_watcherThread;
	std::atomic<bool> m_running;
};