#ifndef ERRORS_H
#define ERRORS_H

#include "Classes/ErrorCategory.h"

static const TErrorCategory PWCategory("PathWalker Error", std::string("PathWalker Error"));
static const std::error_code ReadFileError(1, PWCategory);

#endif // ERRORS_H
