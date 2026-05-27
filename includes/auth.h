#ifndef AUTH_H
#define AUTH_H

#include "app.h"

int auth_login(AppContext *ctx);
void auth_logout(AppContext *ctx);

#endif