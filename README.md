[![flex](https://img.shields.io/badge/flex-lex-9fcbfa)](https://ccm.net/faq/30635-how-to-install-flex-and-bison-under-ubuntu)
[![bison](https://img.shields.io/badge/bison-yacc-f09367)](https://ccm.net/faq/30635-how-to-install-flex-and-bison-under-ubuntu)
[![c](https://img.shields.io/badge/C-gcc-blue)](http://www.mingw.org/)

# Linguagem Elvira

Neste projeto é desenvolvida uma linguagem de programação funcional (elvira) utilizando a linguagem C. Ela deve ser executada no **linux**, pois as versões do lex e yacc para windows são incompatíveis com as implementações do projeto.

## Backend
É implementado de acordo com as regras da [lógica combinatorial](https://en.wikipedia.org/wiki/Combinatory_logic). Também são implementados os algoritmos de [garbage collection](https://en.wikipedia.org/wiki/Garbage_collection_(computer_science)) **Mark Scan**, **Fenichel Yochelson** e **Cheney**. 

## Frontend
É utilizado o lex e yacc para a implementação da [análise léxica](https://pt.wikipedia.org/wiki/An%C3%A1lise_l%C3%A9xica) e [análise sintática](https://pt.wikibooks.org/wiki/Constru%C3%A7%C3%A3o_de_compiladores/An%C3%A1lise_sint%C3%A1tica) da linguagem. Estas análises convertem o programa de entrada para o [lambda cálculo](https://en.wikipedia.org/wiki/Lambda_calculus), que em seguida convertido para a lógica combinatorial e executado no backend.

## Execução

É necessário ter o gcc (C compiler), lex (flex) e yacc (bison) instalados na máquina.

```
cd frontend
./elvira.sh
```

## Linguagem Elvira

A linguagem é bem simples, apenas reconhece funções com um parâmetro.

Definição de uma função:
```
sucessor(x) = x+1
triplo(n) = n*3
fibonacci(y) = if y < 2 then y else fib(y-1) + fib(y-2)
fatorial(k) = if k = 0 then 1 else x * fatorial(k-1)
```

Chamada de função:
```
sucessor(3)
4

triplo(10)
30

fibonacci(5)
5

fibonacci(sucessor(4))
5
```
