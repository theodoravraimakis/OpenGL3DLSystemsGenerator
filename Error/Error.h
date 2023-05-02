#ifndef FINALYEARPROJECT_ERROR_H
#define FINALYEARPROJECT_ERROR_H

#include <string>
#include <exception>

class Error : public std::exception
{
public:
    explicit Error( char const*, ... );

public:
    char const* what() const noexcept override;

private:
    std::string mMsg;
};


#endif //FINALYEARPROJECT_ERROR_H
