/*
** EPITECH PROJECT, 2023
** pi-display [WSL: Ubuntu]
** File description:
** Network
*/

#pragma once

#include <cstring>
#include <exception>
#include <string>

extern "C" {
    #include <arpa/inet.h>
    #include <errno.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <sys/socket.h>
    #include <netdb.h>
}

namespace Network {
    class PerrorException : public std::exception {
        public:
            PerrorException() noexcept
            {
                _errno = errno;
            }
            ~PerrorException() noexcept override = default;

            const char *what() const noexcept override
            {
                return strerror(_errno);
            }
            operator int() const noexcept
            {
                return _errno;
            }
            operator std::string() const noexcept
            {
                return what();
            }
            operator const char *() const noexcept
            {
                return what();
            }
        private:
            int _errno;
    };
    class GaiException : public std::exception {
        public:
            GaiException(int gai_errno) noexcept
            {
                _gai_errno = gai_errno;
            }
            ~GaiException() noexcept override = default;

            const char *what() const noexcept override
            {
                return gai_strerror(_gai_errno);
            }
            operator int() const noexcept
            {
                return _gai_errno;
            }
            operator std::string() const noexcept
            {
                return what();
            }
            operator const char *() const noexcept
            {
                return what();
            }
        private:
            int _gai_errno;
    };
    /**
     * @brief Read from a file descriptor (wrapper for read(2))
     * @param fd File descriptor
     * @param buf Buffer to write to
     * @param count Number of bytes to read
     * @return Number of bytes read
     * @throw PerrorException
    */
   template <typename T>
    ssize_t read(int fd, T *buf, size_t count)
    {
        ssize_t ret = ::read(fd, buf, count);

        if (ret == -1) {
            throw PerrorException();
        }
        return ret;
    }
    /**
     * @brief Connect to a socket (wrapper for connect(2))
     * @param sockfd Socket file descriptor
     * @param addr Address to connect to
     * @param addrlen Size of the address
     * @throw PerrorException
    */
    void connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    {
        int ret = ::connect(sockfd, addr, addrlen);
    
        if (ret == -1) {
            throw PerrorException();
        }
    }
    /**
     * @brief Open a socket (wrapper for socket(2))
     * @param domain Domain of the socket
     * @param type Type of the socket
     * @param protocol Protocol of the socket
     * @return File descriptor of the socket
     * @throw PerrorException
    */
    int socket(int domain, int type, int protocol)
    {
        int fd = ::socket(domain, type, protocol);

        if (fd == -1)
            throw PerrorException();
        return fd;
    }
    /**
     * @brief Monitor file descriptors (wrapper for select(2))
     * @param nfds Highest-numbered file descriptor in any of the three sets, plus 1
     * @param readfds Set of file descriptors to monitor for read
     * @param writefds Set of file descriptors to monitor for write
     * @param exceptfds Set of file descriptors to monitor for exceptions
     * @param timeout Timeout
     * @return Number of file descriptors ready
     * @throw PerrorException
     * @note If timeout is NULL, select() blocks until an event occurs
    */
    int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
    {
        int ret = ::select(nfds, readfds, writefds, exceptfds, timeout);

        if (ret == -1) {
            throw PerrorException();
        }
        return ret;
    }
    /**
     * @brief Close a file descriptor (wrapper for close(2))
     * @param fd File descriptor to close
     * @return 0 on success, -1 on error
     * @throw PerrorException
     * 
    */
    void close(int fd)
    {
        int ret = ::close(fd);

        if (ret == -1) {
            throw PerrorException();
        }
    }
    /**
     * @brief Write to a file descriptor (wrapper for write(2))
     * @param fd File descriptor
     * @param buf Buffer to write from
     * @param count Number of bytes to write
     * @return Number of bytes written
     * @throw PerrorException
    */
   template <typename T>
   ssize_t write(int fd, const T *buf, size_t count)
   {
         ssize_t ret = ::write(fd, buf, count);
    
         if (ret == -1) {
              throw PerrorException();
         }
         return ret;
   }
   /**
    * @brief Receive from a socket (wrapper for recv(2))
    * @param sockfd Socket file descriptor
    * @param buf Buffer to write to
    * @param len Size of the buffer
    * @param flags Flags
    * @param src_addr Source address
    * @param addrlen Size of the source address
    * @return Number of bytes received
    * @throw PerrorException
   */
  template <typename T>
  ssize_t recvfrom(int sockfd, T *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
  {
      ssize_t ret = ::recvfrom(sockfd, buf, len, flags, src_addr, addrlen);

      if (ret == -1) {
          throw PerrorException();
      }
      return ret;
  }
    /**
     * @brief Send to a socket (wrapper for send(2))
     * @param sockfd Socket file descriptor
     * @param buf Buffer to send
     * @param len Size of the buffer
     * @param flags Flags
     * @param dest_addr Destination address
     * @param addrlen Size of the destination address
     * @return Number of bytes sent
     * @throw PerrorException
    */
   template <typename T>
    ssize_t sendto(int sockfd, const T *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
    {
        ssize_t ret = ::sendto(sockfd, buf, len, flags, dest_addr, addrlen);

        if (ret == -1) {
            throw PerrorException();
        }
        return ret;
    }
    /**
     * @brief Get address information (wrapper for getaddrinfo(3))
     * @param node Node
     * @param service Service
     * @param hints Hints
     * @param res Result
     * @throw GaiException
    */
    void getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
    {
        int ret = ::getaddrinfo(node, service, hints, res);

        if (ret != 0) {
            throw GaiException(ret);
        }
    }
    /**
     * @brief Free address information (wrapper for freeaddrinfo(3))
     * @param res Result
    */
    void freeaddrinfo(struct addrinfo *res)
    {
        ::freeaddrinfo(res);
    }
    /**
     * @brief Receive from a socket (wrapper for recv(2))
     * @param sockfd Socket file descriptor
     * @param buf Buffer to write to
     * @param len Size of the buffer
     * @param flags Flags
     * @return Number of bytes received
     * @throw PerrorException
    */
    template <typename T>
    ssize_t recv(int sockfd, T *buf, size_t len, int flags)
    {
        ssize_t ret = ::recvfrom(sockfd, buf, len, flags, nullptr, nullptr);

        if (ret == -1) {
            throw PerrorException();
        }
        return ret;
    }
}
