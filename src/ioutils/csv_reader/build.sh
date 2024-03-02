g++ -o main main.cpp -lpthread
./main | tee log.txt
rm main


# g++ -o server server.cpp -lpthread
# g++ -o client client.cpp -lpthread