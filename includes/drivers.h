#ifndef DRIVERS_H
#define DRIVERS_H

#include "app.h"

void drivers_list(AppContext *ctx);
void drivers_add(AppContext *ctx);
void drivers_update(AppContext *ctx);
void drivers_delete(AppContext *ctx);
void driver_show_own_data(AppContext *ctx);

#endif