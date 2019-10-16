#include "ErrorCategory.h"

//-----------------------------------------------------------------------------
TErrorCategory::TErrorCategory(const char* inName, const std::string inMessage) : fName(inName)
{
    fMessage = inMessage;
}
//-----------------------------------------------------------------------------
const char* TErrorCategory::name() const noexcept
{ return fName; }
//-----------------------------------------------------------------------------
std::string TErrorCategory::message(int) const
{ return fMessage; }
//-----------------------------------------------------------------------------
