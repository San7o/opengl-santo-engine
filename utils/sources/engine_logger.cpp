/*
 * MIT License
 *
 * Copyright (c) 2024 Giovanni Santini

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "engine_logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>

using namespace brenta;

brenta::types::log_level logger::level = brenta::types::log_level::WARNING;
std::ofstream logger::log_file;

void logger::set_log_level(brenta::types::log_level level)
{
    logger::level = level;
}

void logger::init()
{
    set_log_file("logs/log.txt");
}

void logger::close()
{
    logger::log_file.close();
}

void logger::set_log_file(const std::string &file)
{
    logger::log_file.open(file, std::ios::app);
    if (!logger::log_file.is_open())
    {
        std::cout << "Error: Could not open log file" << std::endl;
    }

    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);
    log_file << "----------" << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S")
             << "----------" << std::endl;
}
