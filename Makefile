# Nome do executável
TARGET = hashtag_suggester

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Fontes e objetos (tudo está no mesmo arquivo neste caso)
SRC = Hashtag\ Suggester.cpp
OBJ = $(SRC:.cpp=.o)

# Regra principal: compila o programa
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Executa o programa após compilar
run: all
	./$(TARGET)

# Limpa os arquivos gerados (executável e .o, se houver)
clean:
	rm -f $(TARGET) *.o

# ------------------------------------------------------------
# Comandos:
#   make       -> compila o projeto
#   make run   -> compila e executa
#   make clean -> limpa arquivos temporários
# ------------------------------------------------------------
