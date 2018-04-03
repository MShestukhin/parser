TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lpq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lpq
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lpq

INCLUDEPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/libpq.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/libpq.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/pq.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/pq.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/libpq.a



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lconfig++
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lconfig++
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lconfig++

INCLUDEPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/libconfig++.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/libconfig++.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/config++.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/config++.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/libconfig++.a
