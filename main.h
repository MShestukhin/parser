#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <string.h>
#include </usr/local/pgsql/include/libpq-fe.h>
#include <vector>
#include <dirent.h>]
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <signal.h>
#include <libconfig.h++>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/support/date_time.hpp>
#include "structs.h"
#include "parser.h"
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
using namespace std;
namespace src = boost::log::sources;
namespace expr=boost::log::expressions;
using namespace logging::trivial;
void send_to_db(std::vector<line> massln);
bool myfunction (file_data i,file_data j);
void finish_prog_func(int sig);
void sig_abort_func(int sig);
void init();
int main();
#endif // MAIN_H
