#ifndef VEHICLES_H
#define VEHICLES_H

#include "app.h"

void vehicles_list(AppContext *ctx);
void vehicles_add(AppContext *ctx);
void vehicles_update(AppContext *ctx);
void vehicles_delete(AppContext *ctx);
void vehicle_show_own(AppContext *ctx);

#endif