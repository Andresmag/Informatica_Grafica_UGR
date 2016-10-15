# Fichero Makefile
# Práctica 1 con ampliación del examen
# Andrés Molina López 2016-2017

# Variables de los directorios
BIN=bin
OBJ=obj
INC=include
SRC=src

# Compilador y opciones
CXX=g++
CXX_FLAGS=-c -I$(INC)
LD_FLAGS=-lGLU -lGL -lglut

# Orden de ejecucion
all:  preambulo \
		clean \
		$(BIN)/practica1 \
		fin

# Preambulo
preambulo:
	@echo
	@echo -------------------------------------------
	@echo Practica 1
	@echo Informatica Grafica
	@echo
	@echo Autor: Andres Molina Lopez
	@echo Universidad de Granada
	@echo -------------------------------------------
	@echo
	
# Fin
fin:
	@echo
	@echo Programa creado en la carpeta bin con nombre practica1
	@echo

# Reglas de compilacion
$(BIN)/practica1: $(OBJ)/practica1.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(OBJ)/poligono.o $(OBJ)/O3D.o $(OBJ)/OB3D.o
	$(CXX) $(OBJ)/practica1.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(OBJ)/poligono.o $(OBJ)/O3D.o $(OBJ)/OB3D.o -o $@ $(LD_FLAGS)
	
$(OBJ)/practica1.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/practica1.cpp -o $@
	
$(OBJ)/cubo.o: 
	$(CXX) $(CXX_FLAGS) $(SRC)/cubo.cpp -o $@
	
$(OBJ)/tetraedro.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/tetraedro.cpp -o $@
	
$(OBJ)/poligono.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/poligono.cpp -o $@
	
$(OBJ)/O3D.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/O3D.cpp -o $@
	
$(OBJ)/OB3D.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/OB3D.cpp -o $@
	
	
# Borrador
clean:
	rm $(OBJ)/*
	rm $(BIN)/*
	
