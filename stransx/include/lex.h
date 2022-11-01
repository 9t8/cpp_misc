#ifndef NINTY8_MINI_PROJECTS_R5_INTERPRETER_LEX_H
#define NINTY8_MINI_PROJECTS_R5_INTERPRETER_LEX_H

#include "token.h"

#include <bits/stdc++.h>

void lex(std::istream &in, std::deque<std::unique_ptr<token>> &tokens);

#endif // header guard
