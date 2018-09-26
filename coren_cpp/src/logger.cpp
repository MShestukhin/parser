#define LOGGER_CPP 1
#include <fstream>
#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "logger.h"

namespace fs = boost::filesystem;
namespace pt = boost::posix_time;

typedef std::map<int, const char *>::const_iterator level_map_ci_t;
std::map<int, const char *> level_map;

std::string get_level_name(int level)
{
    level_map_ci_t lv = level_map.find(level);
    if (lv != level_map.end()) {
        return lv->second;
    }
    return boost::lexical_cast<std::string>(level);
}

std::string file_by_chunck(const std::string &fname, size_t ch)
{
    if (ch)
        return fname + std::string(".") + boost::lexical_cast<std::string>(ch);
    else
        return fname;
}

bool rotate_by_day(const pt::ptime& ts)
{
    unsigned short current_day = ts.date().day();
    return (log_start_day != current_day);
}

std::string add_date_to_file_name(const std::string &filename, const pt::ptime& ts)
{
    size_t pos = filename.find_last_of(".");
    std::string extr = filename.substr(pos);
    std::string name = filename.substr(0, pos);
    std::string date = boost::gregorian::to_iso_extended_string(ts.date());

    return name + "_" + date + extr;
}

void rotate_files(const std::string &file, size_t chunck)
{
    const std::string &cn = file_by_chunck(file, chunck);
    const std::string &nn = file_by_chunck(file, ++chunck);
    if ((chunck < log_chuncks) && fs::exists(nn))
    {
        rotate_files(file, chunck);
    }
    if (fs::exists(nn)) {
        fs::remove(nn);
    }
    fs::rename(cn, nn);
}

std::ostream &log_action(const char *file, int line, int level)
{
    if(!log_stream.is_open())
        logger_init();

    pt::ptime ts = pt::microsec_clock::local_time();

    if (log_rotate_by_day && rotate_by_day(ts))
    {
        log_stream.close();
        logger_init();
    }

    if (log_stream.is_open() && log_stream.tellp() >= log_max_size)
    {
        log_stream.close();
        rotate_files(log_filepath, 0);
        logger_init();
    }
    if (log_stream.is_open() && log_stream.rdstate() & std::ostream::failbit)
    {
        std::cout << "Log writing error" << std::endl;
        log_stream.close();
    }

    std::ostream &res = log_stream.is_open() ? log_stream : std::cout;

    res << ts << " " << get_level_name(level) << " [" << file << "]:" << line << "\t";

    return res;
}

int logger_configure(po::options_description &desc, const std::string& program_name)
{
    desc.add_options()
        ("log.dir", po::value<std::string>(&log_dirname)->default_value("./"), "log directory name")
        ("log.file", po::value<std::string>(&log_filename)->default_value(program_name+".log"), "log file name")
        ("log.max_size,s", po::value<ssize_t>(&log_max_size)->default_value(1073741824), "log max file size")
        ("log.chuncks", po::value<size_t>(&log_chuncks)->default_value(9), "max chuncks stored for log")
        ("log.level", po::value<std::string>(&log_level_str)->default_value("DEBUG"), "log level [DEBUG|INFO|WARNING|ERROR]")
    ;
    return 0;
}

int logger_configure(size_t chunks, const std::string& directory, const std::string& file_name, const std::string& level, ssize_t max_size, bool rotate_by_day)
{
    log_chuncks  = chunks;
    log_dirname  = directory;
    log_filename = file_name;
    log_level_str = level;
    log_max_size = max_size;
    log_rotate_by_day = rotate_by_day;

    return 0;
}

int logger_init()
{
    level_map[LOG_ANY]   = "ANY    ";
    level_map[LOG_ERROR] = "ERROR  ";
    level_map[LOG_WARN]  = "WARNING";
    level_map[LOG_INFO]  = "INFO   ";
    level_map[LOG_DEBUG] = "DEBUG  ";

    for(level_map_ci_t it = level_map.begin(); it != level_map.end(); ++it) {
        std::string str_level(it->second);
        boost::trim(str_level);
        boost::trim(log_level_str);
        boost::to_upper(log_level_str);
        if(str_level == log_level_str) log_level = it->first + 1;
    }

    if (log_dirname.empty()) {
        log_dirname = "./";
    }

    if (!fs::exists(log_dirname)) {
        fs::create_directories(log_dirname);
    }

    if (log_dirname[log_dirname.length()-1] != '/') {
        log_dirname += "/";
    }

    pt::ptime ts = pt::microsec_clock::local_time();
    log_start_day = ts.date().day();

    if (log_rotate_by_day) {
        log_filepath = log_dirname + add_date_to_file_name(log_filename, ts);
    } else {
        log_filepath = log_dirname + log_filename;
    }

    log_stream.open(log_filepath.c_str(), std::ios_base::out | std::ios_base::app);
    
    return 0;
}
