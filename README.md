# ARQUITETURA POXIM
▶ Paradgma de arquitetura: Complexity-Reduced Instruction Set Processor (CRISP)
▶ Didática, hipotética e simples com 32 bits
▶ Memória Von Neumann de 32 KiB
▶ 3 formatos de instruções

### 1 - Formatos de instruçoes 
Formato: U (OP, Z, X, Y, L)
▶ 6 bits para operação (OP)
▶ 5 bits para operandos (Z, X, Y)
▶ 11 bits para uso livre (L)

### 2 - Formato F (OP, Z, X, I16)
▶ 6 bits para operação (OP)
▶ 5 bits para operandos (Z, X)
▶ 16 bits para imediato (I16)

### 3 - Formato S (OP, I26)
▶ 6 bits para operação (OP)
▶ 26 bits para imediato (I26)

 ### Operações aritméticas e lógicas
▶ Adição (add, addi)
▶ Atribuição imediata (mov, movs)
▶ Bit a bit (and, or, not, xor)
▶ Comparação (cmp, cmpi)
▶ Deslocamento (sla, sll, sra, srl)
▶ Divisão (div, divs, divi)
▶ Multiplicação (mul, muls, muli)
▶ Subtração (sub, subi)
