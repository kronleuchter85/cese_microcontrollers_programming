/*
 * local_operations_service.h
 *
 *  Created on: 16 Apr 2022
 *      Author: gonzalo
 */

#ifndef SERVICES_INC_LOCAL_OPERATIONS_SERVICE_H_
#define SERVICES_INC_LOCAL_OPERATIONS_SERVICE_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "stdbool.h"

bool local_operations_service_is_show_sequence();

void local_operations_service_config();

void local_operations_service_execute();

#endif /* SERVICES_INC_LOCAL_OPERATIONS_SERVICE_H_ */
