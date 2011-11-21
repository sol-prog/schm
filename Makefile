obj = Cell.o PList.o Procedures.o utils.o Object.o Procedure.o schm.o
src = Cell.cpp PList.cpp Procedures.cpp utils.cpp Object.cpp Procedure.cpp schm.cpp

schm: $(obj)
	g++ -o schm $(obj)

Cell.o: PList.h Procedure.h Cell.h
PList.o: PList.h
Procedures.o: Procedures.h
utils.o: utils.h
Object.o: PList.h Procedure.h Object.h
Procedure.o: PList.h Procedure.h
schm.o: utils.h PList.h Procedure.h Object.h Procedures.h Cell.h

$(obj): $(src)
	g++ -c $(src)

clean:
	rm $(obj) schm
