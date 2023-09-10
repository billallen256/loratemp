#ifndef _METRIC_H_
#define _METRIC_H_

#include<stdio.h>

#define METRIC_BUFFER_SIZE 50

#define Metric_str(buffer, name, value, type) sprintf((buffer), "%s:%d|%s", (name), (value), (type))

#endif