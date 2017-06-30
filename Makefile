SRCDIR := src
BUILDDIR := build
TARGET := bin/main

CC := g++
SRCEXT := cpp
# All cpp files from sources directory
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
# Generate object paths from source paths
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
#OBJS=sprite.o menu.o unit.o unitStructure.o unitManager.o cursor.o geometry.o
CFLAGS := -g -std=c++11
LIB := $(pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0)
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0 allegro_primitives-5.0`"; $(CC) $^ -o $(TARGET) `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0 allegro_primitives-5.0`

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean

#main: main.cpp $(OBJS) fastsqrt.h
#	g++ $(CPPFLAGS) main.cpp $(OBJS) -o main `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0 allegro_primitives-5.0`

# sprite.o: sprite.h sprite.cpp
# 	g++ -c sprite.cpp -o sprite.o `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0`

# menu.o: menu.h menu.cpp
# 	g++ -c menu.cpp -o menu.o `pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`

#%.o: %.cpp %.h static_queue.h
	# g++ -c $(CPPFLAGS) -o $@ $< `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0 allegro_primitives-5.0`

# clean:
# 	rm -f main
# 	rm -f *.o