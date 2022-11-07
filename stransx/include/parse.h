#ifndef NINTY8_MINI_PROJECTS_R5_INTERPRETER_PARSE_H
#define NINTY8_MINI_PROJECTS_R5_INTERPRETER_PARSE_H

#include "datum.h"
#include "token.h"

std::unique_ptr<datum> parse(std::deque<std::unique_ptr<token>> &tokens);

#endif // header guard
