// Speaker Daemon
// Copyright (C) 2023 Polaris Industries Inc
// 
// Author: Daniel Beer <daniel.beer@igorinstitute.com>

#ifndef FD_H_
#define FD_H_

#include <unistd.h>
#include <algorithm>

class Fd {
public:
    Fd(int f = -1) : _fd(f) { }

    ~Fd()
    {
	if (_fd >= 0)
	    ::close(_fd);
    }

    Fd(const Fd&) = delete;
    Fd& operator=(const Fd&) = delete;

    int get() const { return _fd; }

    void swap(Fd& f)
    {
	std::swap(_fd, f._fd);
    }

    Fd(Fd&& r) : _fd(r._fd) { r._fd = -1; }

    Fd& operator=(Fd&& r)
    {
	Fd take(std::move(r));
	swap(take);
	return *this;
    }

private:
    int		_fd;
};

#endif
