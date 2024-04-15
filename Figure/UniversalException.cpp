//
// Created by artem on 09.04.24.
//

#include "UniversalException.h"

UniversalException::UniversalException() : error("Unnamed error in this project") {};

UniversalException::UniversalException(const char *error) : error(error) {};
