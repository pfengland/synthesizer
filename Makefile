TARGET=synthesizer
OBJECTS=main.o synthesizer.o midiclient.o audioclient.o audio_buffer.o window.o viewlist.o view.o synthwindow.o dynamicarray.o synth.o knob.o synthview.o
CFLAGS=-Wall -g --std=gnu99 `sdl-config --cflags`
LDLIBS=-ljack -lasound -lpthread -lSDL -lX11 -lSDL_ttf -lsndfile -lSDL_gfx -lm
CC=gcc

$(TARGET) : $(OBJECTS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
