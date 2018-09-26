#ifndef LOGGER_H
#define LOGGER_H

#include <list>
#include <ctime>
#include <string>
#include <fstream>
#include <ostream>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#ifndef LOGGER_CPP
#define LOGGER_EXTERN extern
#define INITIALIZER(...)        /* nothing */
#else
#define LOGGER_EXTERN
#define INITIALIZER(...)        = __VA_ARGS__
#endif

#define LOG_ANY     0
#define LOG_ERROR   1
#define LOG_WARN    2
#define LOG_INFO    3
#define LOG_DEBUG   4

LOGGER_EXTERN std::string log_filepath;
LOGGER_EXTERN std::string log_filename;
LOGGER_EXTERN std::string log_dirname;
LOGGER_EXTERN std::ofstream log_stream;
LOGGER_EXTERN int log_level;
LOGGER_EXTERN std::string log_level_str;
LOGGER_EXTERN unsigned short log_start_day;
LOGGER_EXTERN bool log_rotate_by_day;

LOGGER_EXTERN std::list<std::string> log_memory_list;
LOGGER_EXTERN volatile bool log_memory INITIALIZER(false);
LOGGER_EXTERN boost::mutex log_memory_lock;
LOGGER_EXTERN std::ostringstream log_memory_stream;
LOGGER_EXTERN volatile size_t log_memory_size INITIALIZER(0);
LOGGER_EXTERN volatile size_t log_memory_max_size INITIALIZER(0);

LOGGER_EXTERN boost::mutex log_lock;
LOGGER_EXTERN ssize_t log_max_size;
LOGGER_EXTERN size_t log_chuncks;

std::ostream &log_action(const char *file, int line, int level);

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define _log_action(LEVEL, PARAMS) {\
    if (!log_level || LEVEL < log_level) {\
        boost::mutex::scoped_lock lock(log_lock);\
        log_action(__FILENAME__, __LINE__, LEVEL) << PARAMS << std::endl;\
    }\
}

#define log_any(PARAMS)     _log_action(LOG_ANY, PARAMS)
#define log_error(PARAMS)   _log_action(LOG_ERROR, PARAMS)
#define log_warning(PARAMS) _log_action(LOG_WARN, PARAMS)
#define log_info(PARAMS)    _log_action(LOG_INFO, PARAMS)
#define log_debug(PARAMS)   _log_action(LOG_DEBUG, PARAMS)

int logger_init();
int logger_configure(size_t chunks, const std::string& directory, const std::string& file_name, const std::string& level, ssize_t max_size, bool rotate_by_day = false);
int logger_configure(po::options_description &desc, const std::string& program_name);

#endif // LOGGER_H
