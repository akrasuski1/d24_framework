#ifndef CONNECTION_UTILS_H_
#define CONNECTION_UTILS_H_

#include <iosfwd>

// Returns 0 if succeeded, otherwise error code.
int expectOK(std::iostream& net);
void waitTurn(std::iostream& net);
// Returns true if succeeded.
bool login(std::iostream& net);

#endif
