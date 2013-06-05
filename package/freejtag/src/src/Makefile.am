#AM_LDFLAGS = $(BOOST_THREAD_LDFLAGS)
#LDADD = $(BOOST_THREAD_LIBS)
#AM_CPPFLAGS = $(BOOST_CPPFLAGS)

bin_PROGRAMS=freejtag
freejtag_SOURCES=common/TimeKeeper.cpp \
				network/Message.cpp \
				network/tcp/Connection.cpp \
				network/tcp/ConnectionBundle.cpp \
				network/tcp/NetworkService.cpp \
				network/udp/DatagramService.cpp \
				uart/UARTConnection.cpp \
				uart/UARTService.cpp \
				uart/UARTTypes.cpp \
				settings.cpp \
				Freejtag.cpp
				
				
AM_CPPFLAGS+=$(BOOST_CPPFLAGS)
AM_LDFLAGS=$(BOOST_THREADS_LDFLAGS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS) $(BOOST_SYSTEM_LDFLAGS) $(BOOST_DATE_TIME_LDFLAGS)
LDADD=$(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_SYSTEM_LIBS) $(BOOST_DATE_TIME_LIBS) $(BOOST_CHRONO_LIBS)