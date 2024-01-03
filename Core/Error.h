#ifndef ERROR
#define ERROR

#include <iostream>

namespace Core
{
    class Error
    {
        private:
        std::string error;

        public:
        Error(std::string error);
    };
};

#endif