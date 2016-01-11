libCalendarFastCGI.so: main.cpp
		g++ --std=c++11 -O2 -fPIC -I. storage.cpp events.cpp main.cpp -pthread \
        -Irapidjson/include -lfastcgi-daemon2 -shared -o libCalendarFastCGI.so
