# Install script for directory: /opt/svyazcom/cdr_sca/g3log

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibrariesx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-2")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-2"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg3logger.so.1.3.0-2")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/opt/svyazcom/cdr_sca/build/g3log/libg3logger.so.1.3.0-2")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-2")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-2")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibrariesx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg3logger.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg3logger.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg3logger.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg3logger.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/opt/svyazcom/cdr_sca/build/g3log/libg3logger.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg3logger.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg3logger.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg3logger.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g3log/g2log.hpp;/usr/local/include/g3log/active.hpp;/usr/local/include/g3log/atomicbool.hpp;/usr/local/include/g3log/crashhandler.hpp;/usr/local/include/g3log/filesink.hpp;/usr/local/include/g3log/future.hpp;/usr/local/include/g3log/g3log.hpp;/usr/local/include/g3log/logcapture.hpp;/usr/local/include/g3log/loglevels.hpp;/usr/local/include/g3log/logmessage.hpp;/usr/local/include/g3log/logworker.hpp;/usr/local/include/g3log/moveoncopy.hpp;/usr/local/include/g3log/shared_queue.hpp;/usr/local/include/g3log/sink.hpp;/usr/local/include/g3log/sinkhandle.hpp;/usr/local/include/g3log/sinkwrapper.hpp;/usr/local/include/g3log/stacktrace_windows.hpp;/usr/local/include/g3log/stlpatch_future.hpp;/usr/local/include/g3log/time.hpp;/usr/local/include/g3log/generated_definitions.hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/g3log" TYPE FILE FILES
    "/opt/svyazcom/cdr_sca/g3log/src/g2log.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/active.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/atomicbool.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/crashhandler.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/filesink.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/future.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/g3log.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/logcapture.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/loglevels.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/logmessage.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/logworker.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/moveoncopy.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/shared_queue.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/sink.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/sinkhandle.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/sinkwrapper.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/stacktrace_windows.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/stlpatch_future.hpp"
    "/opt/svyazcom/cdr_sca/g3log/src/g3log/time.hpp"
    "/opt/svyazcom/cdr_sca/build/g3log/include/g3log/generated_definitions.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/cmake/g3logger/g3loggerConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib/cmake/g3logger" TYPE FILE FILES "/opt/svyazcom/cdr_sca/g3log/cmake/g3loggerConfig.cmake")
endif()

