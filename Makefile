
# LIBALLEGRO = $(pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_t)


main: main.cpp sprite.o menu.o unit.o fastsqrt.h
	g++ main.cpp sprite.o menu.o unit.o -o main `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`
	
# sprite.o: sprite.h sprite.cpp
# 	g++ -c sprite.cpp -o sprite.o `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0`

# menu.o: menu.h menu.cpp
# 	g++ -c menu.cpp -o menu.o `pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`

%.o: %.cpp *.h
	g++ -c -o $@ $< `pkg-config --libs allegro-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0 allegro_font-5.0 allegro_color-5.0 allegro_ttf-5.0`

clean:
	rm -f main
	rm -f *.o