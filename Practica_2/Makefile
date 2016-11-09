# Fichero Makefile
# Práctica 2
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
		$(BIN)/practica2 \
		fin

# Preambulo
preambulo:
	@echo
	@echo -------------------------------------------
	@echo Practica 2
	@echo Informatica Grafica
	@echo
	@echo Autor: Andres Molina Lopez
	@echo Universidad de Granada
	@echo -------------------------------------------
	@echo
	
# Fin
fin:
	@echo
	@echo Programa creado en la carpeta bin con nombre practica2
	@echo

# Reglas de compilacion
$(BIN)/practica2: $(OBJ)/practica2.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(OBJ)/PLY.o $(OBJ)/O3D.o $(OBJ)/OB3D.o $(OBJ)/file_ply_stl.o $(OBJ)/figura_rev.o $(OBJ)/esfera.o $(OBJ)/piramide.o
	$(CXX) $^ -o $@ $(LD_FLAGS)
	
$(OBJ)/practica2.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/practica2.cpp -o $@
	
$(OBJ)/cubo.o: 
	$(CXX) $(CXX_FLAGS) $(SRC)/cubo.cpp -o $@
	
$(OBJ)/tetraedro.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/tetraedro.cpp -o $@
	
$(OBJ)/PLY.o: 
	$(CXX) $(CXX_FLAGS) $(SRC)/PLY.cpp  -o $@
	
$(OBJ)/figura_rev.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/figura_rev.cpp  -o $@
	
$(OBJ)/O3D.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/O3D.cpp -o $@
	
$(OBJ)/OB3D.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/OB3D.cpp -o $@
	
$(OBJ)/file_ply_stl.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/file_ply_stl.cpp	-o $@

$(OBJ)/esfera.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/esfera.cpp	-o $@

$(OBJ)/piramide.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/piramide.cpp	-o $@
	
# Borrador
clean:
	-rm $(OBJ)/*
	-rm $(BIN)/*
	
