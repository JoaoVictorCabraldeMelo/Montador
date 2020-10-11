Nome: João Victor Cabral de Melo 
Matrícula: 16/0127670
Implementado: MACRO
Comando: g++ -std=c++17 -Ofast *.cpp -Wall -o Montador

Este trabalho foi compilado com o comando g++ -std=c++17 -Ofast *.cpp -Wall -o Montador tentei dividir o máximo porém código 
ficou confuso devido a não modularização.
Inicialmente inicializa a leitura dos comandos -p e -o pelo arquivo fileReader.cpp sendo o Montador.cpp a main
Depois de ser lido o programa se o comando tiver sido -p sera mostrado um arquivo com extensão .pre
com suas diretivas expansionadas por exemplo CONST IF EQU MACRO 
Se passar o comando -o para o executável então tera um opcode e o valor da tabela de símbolos em um arquivo .obj separados por um espaço será também
gerado um arquivo um arquivo .pre porém neste arquivo não contéra o pre processamento do assembly pois neste caso foi salvado para a memória


