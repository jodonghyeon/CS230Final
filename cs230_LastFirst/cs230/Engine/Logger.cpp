/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Donghyeon Jo
Created:    March 11, 2024
Updated:    March 14, 2024
*/

#include <iostream>
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start_time) : min_level(severity), out_stream("Trace.log"),start_time(start_time) {
    SetTraceLogLevel(LOG_NONE);
    if (use_console == true) {
        out_stream.set_rdbuf(std::cout.rdbuf());
    }
}

double CS230::Logger::second_since_start()
{
    return std::chrono::duration<double>(std::chrono::system_clock::now() - start_time).count();
}

CS230::Logger::~Logger() {
    out_stream.flush();
    out_stream.close();
}

void CS230::Logger::log(CS230::Logger::Severity severity, std::string message) {

    if (severity >= min_level)
    {
        const std::string enum_str[4] = { "Verbose","Debug","Event","Error" };
        int i = static_cast<int>(severity);
        out_stream.precision(4);
        out_stream << '[' << std::fixed << second_since_start() << "]\t";
        out_stream << enum_str[i] << "\t" << message << std::endl;
    }
    return;
}
