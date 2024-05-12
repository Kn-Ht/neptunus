#ifndef MONITOR_INFO_H
#define MONITOR_INFO_H

#include "../raywrapper.h"
#include <stdbool.h>

struct MonitorInfo {
    int id;
    int refresh_rate;
    int width;
    int height;
    int phys_width;
    int phys_height;
    const char* name;
};

static struct MonitorInfo monitor_info;

void get_monitor_info() {
    int monitor = GetCurrentMonitor();

    monitor_info.id = monitor;
    monitor_info.refresh_rate = GetMonitorRefreshRate(monitor);
    monitor_info.width = GetMonitorWidth(monitor);
    monitor_info.height = GetMonitorHeight(monitor);
    monitor_info.phys_width = GetMonitorPhysicalWidth(monitor);
    monitor_info.phys_height = GetMonitorPhysicalHeight(monitor);
    monitor_info.name = GetMonitorName(monitor);
}

bool monitor_changed() {
    return GetCurrentMonitor() != monitor_info.id;
}

#endif // MONITOR_INFO_H