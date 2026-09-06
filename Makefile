CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

TARGET = taskforge

SRCS = main.cpp \
       ShippingComponent.cpp \
       ShipmentGroup.cpp \
       Package.cpp \
       BFSIterator.cpp \
       DestinationIterator.cpp \
       PackageDecorator.cpp \
       Fragile.cpp \
       Hazardous.cpp \
       Refridgerated.cpp \
       PackageState.cpp \
       NotDelivered.cpp \
       OnRoute.cpp \
       Delayed.cpp \
       Delivered.cpp \
       PackageJourney.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run valgrind clean