all : steiner clean

CCC = g++-8
CCFLAGS = -O3 
LIBS= -lm
TARGETDIR=.
CPPFLAGS += \
        -I. \
		-std=c++11 \
		-Wunused

OBJS2 = \
		$(TARGETDIR)/main.o \
		$(TARGETDIR)/Params.o \
		$(TARGETDIR)/Population.o \
		$(TARGETDIR)/Individual.o \


$(TARGETDIR)/steiner: $(OBJS2)
	$(CCC)  $(CCFLAGS) -o $(TARGETDIR)/steiner $(OBJS2)

$(TARGETDIR)/Params.o: Params.h Params.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Params.cpp -o $(TARGETDIR)/Params.o

$(TARGETDIR)/Population.o: Population.h Population.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Population.cpp -o $(TARGETDIR)/Population.o

$(TARGETDIR)/Individual.o: Individual.h Individual.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Individual.cpp -o $(TARGETDIR)/Individual.o
	
$(TARGETDIR)/main.o: main.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c main.cpp -o $(TARGETDIR)/main.o

clean:
	$(RM) \
	$(TARGETDIR)/main.o \
	$(TARGETDIR)/Params.o \
	$(TARGETDIR)/Population.o \
	$(TARGETDIR)/Individual.o \