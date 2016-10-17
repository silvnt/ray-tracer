rayTrace: main.cpp imagem.cpp objeto.cpp
	g++ -std=c++11 -o $@ main.cpp imagem.cpp objeto.cpp objArq.cpp alumiador.cpp -O2 -larmadillo

clean:
	$(RM) rayTrace
