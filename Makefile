# Makefile for ChocAn Project

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Object files
OBJS = Member.o Provider.o Service.o ReportGenerator.o
TERMINAL_OBJS = $(OBJS) ProviderTerminal.o ManagerTerminal.o
TEST_MAIN_OBJS = $(OBJS) test_main.o
TEST_REPORTS_OBJS = $(OBJS) test_reports.o
CHOCAN_OBJS = $(OBJS) ChocAn.o
MAIN_OBJS = $(TERMINAL_OBJS) ChocAnMain.o

# Executables
all: test_main test_reports chocan main

test_main: $(TEST_MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o test_main $(TEST_MAIN_OBJS)

test_reports: $(TEST_REPORTS_OBJS)
	$(CXX) $(CXXFLAGS) -o test_reports $(TEST_REPORTS_OBJS)

chocan: $(CHOCAN_OBJS)
	$(CXX) $(CXXFLAGS) -o chocan $(CHOCAN_OBJS)

main: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o main $(MAIN_OBJS)

# Object file rules
Member.o: Member.cpp Member.h
	$(CXX) $(CXXFLAGS) -c Member.cpp

Provider.o: Provider.cpp Provider.h
	$(CXX) $(CXXFLAGS) -c Provider.cpp

Service.o: Service.cpp Service.h
	$(CXX) $(CXXFLAGS) -c Service.cpp

ReportGenerator.o: ReportGenerator.cpp ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c ReportGenerator.cpp

ProviderTerminal.o: ProviderTerminal.cpp ProviderTerminal.h ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c ProviderTerminal.cpp

ManagerTerminal.o: ManagerTerminal.cpp ManagerTerminal.h ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c ManagerTerminal.cpp

test_main.o: test_main.cpp Member.h Provider.h Service.h ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c test_main.cpp

test_reports.o: test_reports.cpp Member.h Provider.h Service.h ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c test_reports.cpp
	
ChocAn.o: ChocAn.cpp Member.h Provider.h Service.h ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c ChocAn.cpp

ChocAnMain.o: ChocAnMain.cpp ProviderTerminal.h ManagerTerminal.h ReportGenerator.h
	$(CXX) $(CXXFLAGS) -c ChocAnMain.cpp

# Clean rule
clean:
	rm -f *.o test_main test_reports chocan main

# Run targets
run-main: main
	./main

run-test: test_main
	./test_main

run-reports: test_reports
	./test_reports

run-chocan: chocan
	./chocan

.PHONY: all clean run-main run-test run-reports run-chocan
