main : main.cpp
	@echo "***compiling***"
	g++ main.cpp -o main `pkg-config --libs opencv`

clean : main
	@echo "***deleting***"
	rm main

all : main clean