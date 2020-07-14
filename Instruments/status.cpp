#include "status.h"

void Status::gpibStatus(GPIB gpib)
{
    emit(gpib.checkstatus());
}
