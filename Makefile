SRCDIR := src
BUILDDIR := build
INCDIR := include
TARGET := bin/main

CC := g++
SRCEXT := cpp
# All cpp files from sources directory
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# Generate object paths from source paths
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# FIXME: this is a temporary hack!
INCLUDES := $(shell find $(INCDIR) -type f -name *.h)
CFLAGS := -g -std=c++11
# TODO: this is now unused, use in linking phase
LIB := $(pkg-config --libs allegro-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 allegro_font-5 allegro_color-5)
INC := -I include

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $^ -o $(TARGET) `pkg-config --libs allegro-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 allegro_font-5 allegro_color-5 allegro_ttf-5 allegro_primitives-5`

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(INCLUDES)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
