# Fichero Makefile
# Práctica 4
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
		$(BIN)/practica5 \
		fin

# Preambulo
preambulo:
	@echo
	@echo -------------------------------------------
	@echo Practica 5
	@echo Informatica Grafica
	@echo
	@echo Autor: Andres Molina Lopez
	@echo Universidad de Granada
	@echo -------------------------------------------
	@echo
	
# Fin
fin:
	@echo
	@echo Programa creado en la carpeta bin con nombre practica5
	@echo

# Reglas de compilacion
$(BIN)/practica5: $(OBJ)/practica5.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(OBJ)/PLY.o $(OBJ)/O3D.o $(OBJ)/OB3D.o $(OBJ)/file_ply_stl.o $(OBJ)/figura_rev.o $(OBJ)/esfera.o $(OBJ)/piramide.o $(OBJ)/cilindro.o $(OBJ)/brazo.o $(OBJ)/brazo_completo.o $(OBJ)/cabezal.o $(OBJ)/pieza_central.o $(OBJ)/cuerpo.o $(OBJ)/base.o $(OBJ)/regulador.o $(OBJ)/tablero.o $(OBJ)/luz.o $(OBJ)/iluminacion.o $(OBJ)/camara.o
	$(CXX) $^ -o $@ $(LD_FLAGS)
	
$(OBJ)/practica5.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/practica5.cpp -o $@
	
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
	
$(OBJ)/cilindro.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/cilindro.cpp	-o $@
	
$(OBJ)/brazo.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/brazo.cpp	-o $@

$(OBJ)/brazo_completo.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/brazo_completo.cpp	-o $@
	
$(OBJ)/cabezal.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/cabezal.cpp	-o $@
	
$(OBJ)/pieza_central.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/pieza_central.cpp	-o $@
	
$(OBJ)/cuerpo.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/cuerpo.cpp	-o $@

$(OBJ)/base.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/base.cpp	-o $@
		
$(OBJ)/regulador.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/regulador.cpp	-o $@
	
$(OBJ)/tablero.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/tablero.cpp	-o $@

$(OBJ)/iluminacion.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/iluminacion.cpp	-o $@
	
$(OBJ)/luz.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/luz.cpp	-o $@
	
$(OBJ)/camara.o:
	$(CXX) $(CXX_FLAGS) $(SRC)/camara.cpp	-o $@
		
# Borrador
clean:
	-rm $(OBJ)/*
	-rm $(BIN)/*
	
