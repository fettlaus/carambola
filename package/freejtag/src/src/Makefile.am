#AM_LDFLAGS = $(BOOST_THREAD_LDFLAGS)
#LDADD = $(BOOST_THREAD_LIBS)
#AM_CPPFLAGS = $(BOOST_CPPFLAGS)

bin_PROGRAMS=freejtag
freejtag_SOURCES=freejtag.cpp \
				settings.cpp \
				tcp/telnet.cpp \
				tcp/Connection.cpp \
				tcp/Message.cpp \
				tcp/MessageType.cpp \
				tcp/MessageQueue.hpp
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS=$(BOOST_CPPFLAGS)
AM_LDFLAGS=$(BOOST_THREADS_LDFLAGFS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS) $(BOOST_SYSTEM_LDFLAGS)
LDADD=$(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_SYSTEM_LIBSs)