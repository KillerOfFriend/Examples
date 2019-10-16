#ifndef ERRORCATEGORY_H
#define ERRORCATEGORY_H

#include <system_error>

#include "PathWalker_glob.h"

class PATHWALKER_LIB TErrorCategory : public std::error_category
{
public:
    TErrorCategory(const char* inName, const std::string inMessage);

    virtual const char* name() const noexcept override;
    virtual std::string message(int) const override;

private:
    const char* fName;
    std::string fMessage;
};

#endif // ERRORCATEGORY_H
