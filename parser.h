#pragma once

#include "lexer.h"
#include "ad.h"
#include  "at.h"
#include <stdbool.h>

bool typeBase(Type *t);
bool expr(Ret *r);
bool stmCompound(bool newDomain);
void parse(Token *tokens);
