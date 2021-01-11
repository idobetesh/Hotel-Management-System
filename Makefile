main: Employee.o Manager.o DBConnector.o Customer.o main.o
	g++ Employee.o Manager.o DBConnector.o Customer.o main.o -l sqlite3 -o main

Employee.o: Employee.cpp
	g++ -c Employee.cpp	

Manager.o: Manager.cpp
	g++ -c Manager.cpp	

DBConnector.o: DBConnector.cpp
	g++ -c DBConnector.cpp	

Customer.o: Customer.cpp
	g++ -c Customer.cpp	

main.o: main.cpp
	g++ -c main.cpp	

clean:
	rm *.o main