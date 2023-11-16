all:
	mkdir -p build
	gcc -c -g layer.c -o build/layer.c.o
	gcc -c -g neuron.c -o build/neuron.c.o
	gcc -c -g main.c -o build/main.c.o
	gcc -c -g maths.c -o build/maths.c.o
	gcc -g -lm build/*.o -o neuralnetwork
	./neuralnetwork

debug:
	make
	gdb ./neuralnetwork

clean:
	rm -rf build
