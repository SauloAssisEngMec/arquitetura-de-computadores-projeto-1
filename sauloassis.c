// Como executar no terminal:
// gcc -Wall -O3 nomesobrenome_123456789012_exemplo.c -o nomesobrenome_123456789012_exemplo
// ./nomesobrenome_123456789012_exemplo entrada saida

// gcc -Wall -O3 sauloassis_201700034387_poxim1.c -o sauloassis_201700034387_poxim1
//./sauloassis_201700034387_poxim1 3_exemplo.hex output.out
// ./sauloassis 2_exemplo.hex 2_exemplo.out

// Numeros padronizados
#include <stdint.h>
// Biblioteca padrao
#include <stdlib.h>
// Entrada/saida padrao
#include <stdio.h>

#include <string.h>

// Funcao principal
int main(int argc, char *argv[])
{
    // Exibindo a quantidade de argumentos
    printf("Quantidade de argumentos (argc): %i\n", argc);
    // Iterando sobre o(s) argumento(s) do programa
    for (uint32_t i = 0; i < argc; i++)
    {
        // Mostrando o argumento i
        printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
    }
    // Abrindo os arquivos com as permissoes corretas
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (argc != 3)
    {
        printf("espera-se um arquivo input e output\n");
        return 1;
    }
    if (input == NULL || output == NULL)
    {
        printf("Error! arquivo nao foi lido\n");
        exit(-1); // must include stdlib.h
    }

    // 32 registradores inicializados com zero
    uint32_t R[32] = {0};
    uint64_t RR[64] = {0};
    // Memoria com 32 KiB inicializada com zero
    // uint8_t *MEM8 = (uint8_t *)(calloc(32, 1024));
    uint32_t *MEM32 = (uint32_t *)(calloc(8, 1024));

    // contar o numero de linhas do input file pra automatizar a entrada de dados

    // int linha_atual = 0;
    // char ccc;
    // do
    // {
    //     ccc = fgetc(input);
    //     if (ccc == '\n')
    //     {
    //         linha_atual++;
    //     }
    // } while (ccc != EOF);

    // printf("o numero de linhas do input é: %d \n", linha_atual);

    uint32_t Data[64];     // mudar para o numero de inputs
    char data[1000] = {0}; // salvar os dados no arquivo output

    for (int i = 0; i < 64; i++) // mudar para o numero de inputs
    {
        fscanf(input, "0x%08X\n", &Data[i]); //
        // printf("0x%08X\n", Data[i]);
        MEM32[i] = Data[i]; //
    }
    // fclose(input);

    // Depois de carregamento do arquivo 1_intro.hex, o vetor de memoria contem o conteudo abaixo:

    // Imprimindo o conteudo das memorias em bytes

    // printf("\nMEM8:\n");
    // for (uint8_t i = 0; i < 64; i = i + 4)
    // {
    //     // Impressao lado a lado
    //     printf("0x%08X: 0x%02X 0x%02X 0x%02X 0x%02X\n", i, MEM8[i], MEM8[i + 1], MEM8[i + 2], MEM8[i + 3]);
    // }
    printf("\nMEM32:\n");
    for (uint32_t i = 0; i < 64; i = i + 1) // mudar para o numero de inputs
    {
        // Impressao lado a lado
        printf("0x%08X: 0x%08X (0x%02X 0x%02X 0x%02X 0x%02X)\n", i << 2, MEM32[i], ((uint8_t *)(MEM32))[(i << 2) + 3], ((uint8_t *)(MEM32))[(i << 2) + 2], ((uint8_t *)(MEM32))[(i << 2) + 1], ((uint8_t *)(MEM32))[(i << 2) + 0]);
    }

    //

    // Separador da saida esperada
    printf("\nSaida esperada\n\n      |       \n      V       \n\n");
    // Exibindo a inicializacao da execucao
    printf("[START OF SIMULATION]\n");
    sprintf(data, "[START OF SIMULATION]\n");
    // printf(data);
    //  fputs(data, output);
    fprintf(output, "%s", data);
    // Setando a condicao de execucao para verdadeiro
    uint8_t executa = 1;
    // Enquanto executa for verdadeiro
    while (executa)
    {
        // Cadeia de caracteres da instrucao
        char sinal[10] = {0};

        char name[30] = {0};
        char instrucao[30] = {0};
        // Declarando operandos
        uint8_t z = 0, x = 0, i = 0, y = 0, l = 0, ll = 0;
        uint32_t pc = 0, sp = 0, xyl = 0, cmp = 0, cmpi = 0, ii = 0;
        uint64_t concatenacao = (((uint64_t)(R[z])) << 32) + (uint64_t)(R[y]);
        // uint64_t Rz = (((uint64_t)(1)) << 32) + (uint64_t)(R[z]);

        // Carregando a instrucao de 32 bits (4 bytes) da memoria indexada pelo PC (R29) no registrador IR (R28)
        // E feita a leitura redundante com MEM8 e MEM32 para mostrar formas equivalentes de acesso
        // Se X (MEM8) for igual a Y (MEM32), entao X e Y sao iguais a X | Y (redundancia)
        // R[28] = ((MEM8[R[29] + 0] << 24) | (MEM8[R[29] + 1] << 16) | (MEM8[R[29] + 2] << 8) | (MEM8[R[29] + 3] << 0)) | MEM32[R[29] >> 2];
        R[28] = MEM32[R[29] >> 2];

        //  printf("R[29] = 0x%08X\n", R[29]);
        //  printf("R[28] = 0x%08X\n", R[28]);

        // Obtendo o codigo da operacao (6 bits mais significativos)
        uint8_t opcode = (R[28] & (0b111111 << 26)) >> 26;
        uint8_t opcode2 = (R[28] & (0b111 << 8)) >> 8;
        //  Decodificando a instrucao buscada na memoria
        //  printf(" opcode = 0x%08X\n", opcode);

        switch (opcode)
        {

        // bun
        case 0b110111:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);

            // Formatacao da instrucao
            sprintf(instrucao, "bun %i", R[28] & 0x3FFFFFF);

            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);

            // formatação para salvar no arquivo
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // l8
        case 0b011000:
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;
            // Execucao do comportamento com MEM8 e MEM32
            // R[z] = MEM8[R[x] + i] | (((uint8_t *)(MEM32))[(R[x] + i) >> 2]);
            R[z] = (((uint8_t *)(MEM32))[(R[x] + i) >> 2]);
            // Formatacao da instrucao
            sprintf(instrucao, "l8 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z, R[x] + i, R[z]);
            sprintf(data, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z, R[x] + i, R[z]);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);
            break;

        // l16
        case 0b011001:
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;
            // Execucao do comportamento com MEM8 e MEM32
            // R[z] = MEM8[R[x] + i] | (((uint8_t *)(MEM32))[(R[x] + i) >> 2]);
            R[z] = (((uint16_t *)(MEM32))[(R[x] + i) >> 1]); //
            // Formatacao da instrucao
            sprintf(instrucao, "l16 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%04X\n", R[29], instrucao, z, (R[x] + i) << 1, R[z]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%04X\n", R[29], instrucao, z, (R[x] + i) << 1, R[z]);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // l32
        case 0b011010:
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;
            // Execucao do comportamento com MEM8 e MEM32
            // R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) | (MEM8[((R[x] + i) << 2) + 1] << 16) | (MEM8[((R[x] + i) << 2) + 2] << 8) | (MEM8[((R[x] + i) << 2) + 3] << 0)) | MEM32[R[x] + i];
            R[z] = MEM32[R[x] + i];
            // Formatacao da instrucao
            sprintf(instrucao, "l32 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);

            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%08X\n", R[29], instrucao, z, (R[x] + i) << 2, R[z]);
            sprintf(data, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%08X\n", R[29], instrucao, z, (R[x] + i) << 2, R[z]);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // mov
        case 0b000000:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            xyl = R[28] & 0x1FFFFF;
            // Execucao do comportamento
            R[z] = xyl;
            // Formatacao da instrucao
            sprintf(instrucao, "mov r%u,%u", z, xyl);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // movs
        case 0b000001:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            xyl = R[28] & 0x1FFFFF;

            //   extensão de sinal de xyl (duvida2)
            if (xyl & (1 << 20))
            {
                xyl = xyl | (0b11111111111 << 21);
            }

            // nçao apaguei essas variaveis porque usei em outros cases kkk, mesmo aqui não precisando mais delas
            int algarismo = 20; // Posição do bit a ser verificado

            int mascara = 1 << algarismo;

            R[z] = xyl;
            // Formatacao da instrucao ((xyl & 1 << 32) = 1) ? ("-") : ("")
            sprintf(instrucao, "movs r%u,%i", z, R[z]);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // add
        case 0b000010:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            uint64_t result = (uint64_t)(R[x]) + (uint64_t)(R[y]);
            // Execucao do comportamento

            // uint64_t result = R[x] + R[y];
            // printf("0x%0X", result);

            //  ZN ← (R[z] = 0)
            //  SN ← (R[z]31 = 1)
            //  CY ← (R[z]32 = 1)

            // Posição do bit a ser verificado

            algarismo = 32;
            int mascara2 = 1 << 32;

            if (result == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            };

            if ((result & mascara) == 1)
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            };

            if (result >> 32 & 0b1)
            {
                R[31] = R[31] | 0b1;

                // printf("entrou");
            }
            else
            {
                R[31] = R[31] & ~0b1;
            };

            // printf("R[31]=%08X\n", R[31]);

            //  OV ← (R[x]31 = R[y]31 ∧ R[z]31 ̸= R[x]31)

            // if (R[x])
            // {

            //     R[31] = R[31] | 0b1000;
            //     sprintf(name, "OV");
            // }

            // Formatacao da instrucao
            // pra represnetar o SR usa-se um ternario?
            // add r3,r1,r2
            sprintf(instrucao, "add r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	R3=R1+R2=0x00023456,SR=0x00000001
            printf("0x%08X:\t%-25s\tR%u=R%u+R%u=0x%08X,%s=0x%08X\n", R[29], instrucao, z, x, y, result, "SR", R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u+R%u=0x%08X,%s=0x%08X\n", R[29], instrucao, z, x, y, result, "SR", R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // sub
        case 0b000011:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            // Execucao do comportamento
            // printf("R[x]=%u\n", R[x]);
            // printf("R[y]=%u\n", R[y]);
            // R[y]

            // // Execucao do comportamento
            // R[z] = R[x] - R[y];
            uint64_t sub = (uint64_t)(R[x]) - (uint64_t)(R[y]);

            // printf("R[z]=%u\n", R[z]);
            //  ZN ← (R[z] = 0)
            //  SN ← (R[z]31 = 1)

            //  CY ← (R[z]32 = 1)

            if (sub == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            };

            if ((sub & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            };

            if (sub >> 32 & 0b1)
            {
                R[31] = R[31] | 0b1;

                // printf("entrou");
            }
            else
            {
                R[31] = R[31] & ~0b1;
            };

            //  OV ← (R[x]31 = R[y]31 ∧ R[z]31 ̸= R[x]31)

            // if (R[x])
            // {

            //     R[31] = R[31] | 0b1000;
            //     sprintf(name, "OV");
            // }

            // Formatacao da instrucao
            // pra represnetar o SR usa-se um ternario?
            // sub r3,r1,r2
            sprintf(instrucao, "sub r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	R3=R1+R2=0x00023456,SR=0x00000001
            printf("0x%08X:\t%-25s\tR%u=R%u-R%u=0x%08X,%s=0x%08X\n", R[29], instrucao, z, x, y, sub, "SR", R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u-R%u=0x%08X,%s=0x%08X\n", R[29], instrucao, z, x, y, sub, "SR", R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // Casos do anti projeto
        case 0b000100:
            // Obtendo o codigo da operacao

            switch (opcode2)
            {
            // mul
            case 0b000:
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F;

                // Execucao do comportamento
                R[z] = R[x] * R[y];
                // Formatacao da instrucao

                // ZN ← (R[l4−0] : R[z] = 0)
                // CY ← (R[l4−0] ̸= 0)

                if (R[z] == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                }

                if (R[l] != 0)
                {

                    R[31] = R[31] | 0b1;
                    // sprintf(name, "OV");
                }
                else
                {
                    R[31] = R[31] & ~0b1;
                }

                // OV
                // muli rz,rx,s
                sprintf(instrucao, "mul r%u,r%u,%u", z, x, i);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                //	Rz=Rx*0x????????=0x????????,SR=0x????????
                printf("0x%08X:\t%-25s\tR%u=R%u*%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u=R%u*%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;
            // sll
            case 0b001:
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F;

                // Execucao do comportamento (duvida1)

                concatenacao = concatenacao << (l + 1);
                R[z] = concatenacao << 32;
                R[x] = concatenacao & 0xFFFFFFFF;

                //  ZN ← (R[z] : R[x] = 0)
                // ▶ CY ← (R[z] ̸= 0)

                if (concatenacao == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                };

                if (R[z] != 0)
                {
                    R[31] = R[31] | 0b1;
                    // sprintf(name, "CY");
                }
                else
                {
                    R[31] = R[31] & ~0b1;
                };

                // Formatacao da instrucao
                // sll r10,r9,r9,2          	R10:R9=R10:R9>>3=0x0000000000000000,SR=0x00000060
                sprintf(instrucao, "sll r%u,r%u,r%u,%u", z, x, y, l);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                printf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, l + 1, R[z], "SR", R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, l + 1, R[z], "SR", R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;

            // muls  não finalizei
            case 0b010:
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F;

                // Execucao do comportamento
                R[z] = R[x] * R[y]; //
                // Formatacao da instrucao

                //   ZN ← (R[l4−0] : R[z] = 0)
                //  OV ← (R[l4−0] ̸= 0)

                // if ( == 0)
                // {

                //     R[31] = R[31] | 0b1000000;
                //     // sprintf(name, "ZN");
                // }
                // else
                // {
                //     R[31] = R[31] & ~0b1000000;
                // }

                if (R[l] != 0)
                {

                    R[31] = R[31] | 0b1000;
                    // sprintf(name, "OV");
                }
                else
                {
                    R[31] = R[31] & ~0b1000;
                }

                // OV
                // muli rz,rx,s
                sprintf(instrucao, "muls r%u,r%u,%u", z, x, i);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                //	Rz=Rx*0x????????=0x????????,SR=0x????????
                printf("0x%08X:\t%-25s\tR%u=R%u*R%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u=R%u*%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;

            // sla
            case 0b011:
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F;

                // Execucao do comportamento (duvida1)

                concatenacao = concatenacao << (l + 1);
                R[z] = concatenacao << 32;
                R[x] = concatenacao & 0xFFFFFFFF;

                // printf("R[z] = 0x%08X\n", R[z]);
                // printf("R[x] = 0x%08X\n", R[x]);

                // ZN ← (R[z] : R[x] = 0)
                //  OV ← (R[z] ̸= 0)

                if (concatenacao == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                };

                if (R[z] != 0)
                {
                    R[31] = R[31] | 0b1000;
                    // sprintf(name, "OV");
                }
                else
                {
                    R[31] = R[31] & ~0b1000;
                };

                // Formatacao da instrucao
                // sla r10,r9,r9,2          	R10:R9=R10:R9>>3=0x0000000000000000,SR=0x00000060
                sprintf(instrucao, "sla r%u,r%u,r%u,%u", z, x, y, l);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                printf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, (l + 1), R[z], "SR", R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, (l + 1), R[z], "SR", R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;

            // div
            case 0b100:
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F; // 7FF

                //  Execucao do comportamento
                if (R[y] != 0)
                {

                    R[l] = R[x] % R[y]; // mod
                    R[z] = R[x] / R[y];
                }
                else
                {

                    R[l] = 0x00000000;
                    R[z] = 0x00000000;
                }

                // ZN ← (R[z] = 0)
                //  ZD ← (R[y] = 0)
                //  CY ← (R[l4−0] ̸= 0)

                if (R[z] == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                };

                if (R[y] == 0)
                {
                    R[31] = R[31] | 0b100000;
                    // sprintf(name, "ZD");
                }
                else
                {
                    R[31] = R[31] & ~0b100000;
                };

                if (R[l] != 0)
                {
                    R[31] = R[31] | 0b1;
                    // R[z] = (uint32_t)R[z];
                    // sprintf(name, "CY");
                }
                else
                {
                    R[31] = R[31] & ~0b1;
                };

                // printf("R[31]=%08X\n", R[31]);
                //  OV ← (R[x]31 = R[y]31 ∧ R[z]31 ̸= R[x]31)

                // if (R[x])
                // {

                //     R[31] = R[31] | 0b1000;
                //     sprintf(name, "OV");
                // }

                // Formatacao da instrucao
                sprintf(instrucao, "div r%u,r%u,r%u,r%u", l, z, x, y);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                // Rl=Rx%Ry=0x????????,Rz=Rx/Ry=0x????????,SR=0x????????
                printf("0x%08X:\t%-25s\tR%u=R%u%%R%u=0x%08X,R%u=R%u/R%u=0x%08X, %s=0x%08X\n", R[29], instrucao, l, x, y, R[l], z, x, y, R[z], "SR", R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u=R%u%%R%u=0x%08X,R%u=R%u/R%u=0x%08X, %s=0x%08X\n", R[29], instrucao, l, x, y, R[l], z, x, y, R[z], "SR", R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;

            // srl
            case 0b101:
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F;

                // Execucao do comportamento (duvida1)

                concatenacao = concatenacao >> (l + 1);
                R[z] = concatenacao >> 32;
                R[x] = concatenacao & 0xFFFFFFFF;

                //  ZN ← (R[z] : R[x] = 0)
                // CY ← (R[z] ̸= 0)

                if (concatenacao == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                };

                if (R[z] != 0)
                {
                    R[31] = R[31] | 0b1;
                    // sprintf(name, "CY");
                }
                else
                {
                    R[31] = R[31] & ~0b1;
                };

                // Formatacao da instrucao
                // srl r10,r9,r9,2          	R10:R9=R10:R9>>3=0x0000000000000000,SR=0x00000060
                sprintf(instrucao, "srl r%u,r%u,r%u,%u", z, x, y, l);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                printf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u>>%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, l, R[z], "SR", R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u>>%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, l, R[z], "SR", R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;

            // divs
            case 0b110:
                // Obtendo operandos
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F; // 7FF

                //  Execucao do comportamento
                if (R[y] != 0)
                {

                    R[l] = R[x] % R[y]; // mod
                    R[z] = R[x] / R[y];
                }
                else
                {

                    R[l] = 0x00000000;
                    R[z] = 0x00000000;
                }
                // ZN ← (R[z] = 0)
                // ZD ← (R[y] = 0)
                //  OV ← (R[l4−0] ̸= 0)

                if (R[z] == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                };

                if (R[y] == 0)
                {
                    R[31] = R[31] | 0b100000;
                    // sprintf(name, "ZD");
                }
                else
                {
                    R[31] = R[31] & ~0b100000;
                };

                if (R[l] != 0)
                {
                    R[31] = R[31] | 0b1000;
                    // R[z] = (uint32_t)R[z];
                    // sprintf(name, "OV");
                }
                else
                {
                    R[31] = R[31] & ~0b1000;
                };

                // printf("R[31]=%08X\n", R[31]);
                //  OV ← (R[x]31 = R[y]31 ∧ R[z]31 ̸= R[x]31)

                // if (R[x])
                // {

                //     R[31] = R[31] | 0b1000;
                //     sprintf(name, "OV");
                // }

                // Formatacao da instrucao
                sprintf(instrucao, "divs r%u,r%u,r%u,r%u", l, z, x, y);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                // Rl=Rx%Ry=0x????????,Rz=Rx/Ry=0x????????,SR=0x????????
                printf("0x%08X:\t%-25s\tR%u=R%u%%R%u=0x%08X,R%u=R%u/R%u=0x%08X, %s=0x%08X\n", R[29], instrucao, l, x, y, R[l], z, x, y, R[z], "SR", R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u=R%u%%R%u=0x%08X,R%u=R%u/R%u=0x%08X, %s=0x%08X\n", R[29], instrucao, l, x, y, R[l], z, x, y, R[z], "SR", R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;

            // sra
            case 0b111:
                // Obtendo operandos
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                l = R[28] & 0x1F;

                // Execucao do comportamento (duvida1)

                concatenacao = concatenacao >> (l + 1);
                R[z] = concatenacao >> 32;
                R[x] = concatenacao & 0xFFFFFFFF;

                //  ZN ← (R[z] : R[x] = 0)
                // OV

                if (concatenacao == 0)
                {

                    R[31] = R[31] | 0b1000000;
                    // sprintf(name, "ZN");
                }
                else
                {
                    R[31] = R[31] & ~0b1000000;
                };

                if (R[z] != 0)
                {
                    R[31] = R[31] | 0b1000;
                    // sprintf(name, "OV");
                }
                else
                {
                    R[31] = R[31] & ~0b1000;
                };

                // Formatacao da instrucao
                // sll r10,r9,r9,2          	R10:R9=R10:R9>>3=0x0000000000000000,SR=0x00000060
                sprintf(instrucao, "sra r%u,r%u,r%u,%u", z, x, y, l);
                // Formatacao de saida em tela (deve mudar para o arquivo de saida)
                printf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u>>%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, l + 1, R[z], "SR", R[31]);

                sprintf(data, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u>>%u=0x%08X,%s=0x%08X \n", R[29], instrucao, z, x, z, y, l + 1, R[z], "SR", R[31]);
                // printf(data);
                //  fputs(data, output);
                fprintf(output, "%s", data);

                break;
            }
            break;

        // cmp
        case 0b000101:
            // Obtendo operandos
            pc = R[29];
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;
            xyl = R[28] & 0x1FFFFF;
            R[28] = MEM32[R[29] >> 2];
            // Execucao do comportamento
            cmp = R[x] - R[y];

            //  ZN ← (CMP = 0)
            //  SN ← (CMP31 = 1)

            //  CY ← (CMP32 = 1)
            if (cmp == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((cmp & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            if ((cmp & 1 << 32))
            {
                R[31] = R[31] | 0b1;
                // sprintf(name, "CY");
            }
            else
            {
                R[31] = R[31] & ~0b1;
            }

            // printf("R[31]=%08X\n", R[31]);

            //  //  OV ← (R[x]31 ̸= R[y]31) ∧ (CMP31 ̸= R[x]31)

            if (R[x])
            {

                R[31] = R[31] | 0b1000;
                // sprintf(name, "OV");
            }
            else
            {
                R[31] = R[31] & ~0b1000;
            }

            // Formatacao da instrucao
            sprintf(instrucao, "cmp r%u,%u", x, R[31]);
            // sprintf(instrucao, "cmp ir,pc");
            //  Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // cmp ir,pc                	SR=0x00000020
            printf("0x%08X:\t%-25s\t%s=0x%08X\n", R[29], instrucao, "SR", R[31]);

            sprintf(data, "0x%08X:\t%-25s\t%s=0x%08X\n", R[29], instrucao, "SR", R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bit a bit and
        case 0b000110:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;
            // Execucao do comportamento
            R[z] = R[x] & R[y];
            // Formatacao da instrucao
            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((R[z] & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            // and r13,r1,r5
            sprintf(instrucao, "and r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=R%u&R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u&R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bit a bit or
        case 0b000111:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;
            // Execucao do comportamento
            R[z] = R[x] | R[y];
            // Formatacao da instrucao
            // and r13,r1,r5
            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((R[z] & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            // and r13,r1,r5
            sprintf(instrucao, "or r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=R%u|R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u|R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

            // bit a bit not
        case 0b001000:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // Execucao do comportamento
            R[z] = ~R[x];
            // Formatacao da instrucao

            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((R[z] & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            //
            sprintf(instrucao, "not r%u,r%u", z, x);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // not rz,rx                	Rz=~Ry=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=~R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=~R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bit a bit xor
        case 0b001001:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;
            // Execucao do comportamento
            R[z] = R[x] ^ R[y];
            // Formatacao da instrucao
            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((R[z] & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            sprintf(instrucao, "xor r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=R%u^R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u^R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // addi
        case 0b010010:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            R[z] = R[x] + i;
            // Formatacao da instrucao
            // pra represnetar o SR usa-se um ternario?
            // addi rz,rx,s

            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((R[z] & mascara) == 1)
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            if ((R[z] & mascara2) == 1)
            {
                R[31] = R[31] | 0b1;
                // sprintf(name, "CY");
            }
            else
            {
                R[31] = R[31] & ~0b1;
            }

            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // addi r17,r17,1           	R17=R17+0x00000001=0x00000001,SR=0x00000020

            sprintf(instrucao, "addi r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	Rz=Rx+0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u+%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u+%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

            // subi
        case 0b010011:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            R[z] = R[x] - i;

            // status do processo
            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((R[z] & mascara) == 1)
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            if ((R[z] & mascara2) == 1)
            {
                R[31] = R[31] | 0b1;
                // sprintf(name, "CY");
            }
            else
            {
                R[31] = R[31] & ~0b1;
            }
            // Formatacao da instrucao
            // pra represnetar o SR usa-se um ternario?

            sprintf(instrucao, "subi r%u,r%u,%i", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	Rz=Rx+0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u-%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u-%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // muli
        case 0b010100:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            R[z] = R[x] * i;
            // Formatacao da instrucao

            // ▶ ZN ← (R[z] = 0)
            // ▶ OV ← (R[z]63−32 ̸= 0)

            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }
            // if (R[z] == 0)
            // {

            //     R[31] = R[31] | 0b1000;
            //     // sprintf(name, "OV");
            // }
            // else
            // {
            //     R[31] = R[31] & ~0b1000;
            // }

            // OV
            // muli rz,rx,s
            sprintf(instrucao, "muli r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            //	Rz=Rx*0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u*%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u*%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // divi
        case 0b010101:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            if (R[i] != 0)
            {

                R[z] = R[x] / i;
            }
            else
            {

                R[z] = 0x00000000;
            }

            //  ZN ← (R[z] = 0)
            // ZD ← (i = 0)
            // OV ← 0
            if (R[z] == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            };

            if (R[y] == 0)
            {
                R[31] = R[31] | 0b100000;
                // sprintf(name, "ZD");
            }
            else
            {
                R[31] = R[31] & ~0b100000;
            };

            if (R[l] != 0)
            {
                R[31] = R[31] | 0b1000;
                // R[z] = (uint32_t)R[z];
                // sprintf(name, "OV");
            }
            else
            {
                R[31] = R[31] & ~0b1000;
            };

            // Formatacao da instrucao
            // divi rz,rx,s
            sprintf(instrucao, "divi r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            //	Rz=Rx/0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u/%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u/%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // modi
        case 0b010110:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            R[z] = R[x] % i;
            // Formatacao da instrucao
            // divi rz,rx,s
            sprintf(instrucao, "modi r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            //	Rz=Rx/0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u%%%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u%%%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // cmpi
        case 0b010111:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            cmpi = R[x] - i;

            if (cmpi == 0)
            {

                R[31] = R[31] | 0b1000000;
                // sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] & ~0b1000000;
            }

            if ((cmpi & 1 << 31))
            {
                R[31] = R[31] | 0b10000;
                // sprintf(name, "SN");
            }
            else
            {
                R[31] = R[31] & ~0b10000;
            }

            if ((cmpi & 1 << 32))
            {
                R[31] = R[31] | 0b1;
                // sprintf(name, "CY");
            }
            else
            {
                R[31] = R[31] & ~0b1;
            }

            // printf("R[31]=%08X\n", R[31]);

            //  //  OV ← (R[x]31 ̸= R[y]31) ∧ (CMP31 ̸= R[x]31)

            if (R[x])
            {

                R[31] = R[31] | 0b1000;
                // sprintf(name, "OV");
            }
            else
            {
                R[31] = R[31] & ~0b1000;
            }
            // Formatacao da instrucao
            // divi rz,rx,s
            sprintf(instrucao, "cmpi r%u,%u", x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            //	Rz=Rx/0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tSR=0x%08X\n", R[29], instrucao, x, i, R[z], R[31]);

            sprintf(data, "0x%08X:\t%-25s\tSR=0x%08X\n", R[29], instrucao, x, i, R[z], R[31]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);
            break;

        // s8
        case 0b011011:
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF; // 1111111111111111 = i16/15
            // Execucao do comportamento com MEM8 e MEM32
            // R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) | (MEM8[((R[x] + i) << 2) + 1] << 16) | (MEM8[((R[x] + i) << 2) + 2] << 8) | (MEM8[((R[x] + i) << 2) + 3] << 0)) | MEM32[R[x] + i];
            (((uint8_t *)(MEM32))[(R[x] + i) >> 2]) = R[z];
            // Formatacao da instrucao
            sprintf(instrucao, "s8 [r%u%s%i],r%u", x, (i >= 0) ? ("+") : (""), i, z);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%02X\n", R[29], instrucao, R[x] + i, z, R[z]);
            sprintf(data, "0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%02X\n", R[29], instrucao, R[x] + i, z, R[z]);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // s16
        case 0b011100:
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF; // 1111111111111111 = i16/15
            // Execucao do comportamento com MEM8 e MEM32
            // R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) | (MEM8[((R[x] + i) << 2) + 1] << 16) | (MEM8[((R[x] + i) << 2) + 2] << 8) | (MEM8[((R[x] + i) << 2) + 3] << 0)) | MEM32[R[x] + i];
            (((uint16_t *)(MEM32))[(R[x] + i) >> 1]) = R[z];
            // Formatacao da instrucao
            sprintf(instrucao, "s16 [r%u%s%i],r%u", x, (i >= 0) ? ("+") : (""), i, z);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)

            printf("0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%04X\n", R[29], instrucao, (R[x] + i) << 1, z, R[z]);
            sprintf(data, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%04X\n", R[29], instrucao, z, (R[x] + i) << 1, R[z]);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // s32
        case 0b011101:
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF; // 1111111111111111 = i16/15
            // Execucao do comportamento com MEM8 e MEM32
            // R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) | (MEM8[((R[x] + i) << 2) + 1] << 16) | (MEM8[((R[x] + i) << 2) + 2] << 8) | (MEM8[((R[x] + i) << 2) + 3] << 0)) | MEM32[R[x] + i];
            MEM32[R[x] + i] = R[z];
            // Formatacao da instrucao
            sprintf(instrucao, "s32 [r%u%s%i],r%u", x, (i >= 0) ? ("+") : (""), i, z);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%08X\n", R[29], instrucao, (R[x] + i) << 2, z, R[z]);
            sprintf(data, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%08X\n", R[29], instrucao, z, (R[x] + i) << 2, R[z]);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // OPERACOES DE DESVIO CONDICIONAIS

        // bae
        case 0b101010:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bae %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bat
        case 0b101011:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);

            // Formatacao da instrucao
            sprintf(instrucao, "bat %i", R[28] & 0x3FFFFFF);

            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);

            // formatação para salvar no arquivo
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            // fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bbe
        case 0b101100:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bbe %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bbt
        case 0b101101:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bbt %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // beq
        case 0b101110:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "beq %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bge
        case 0b101111:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bge %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bgt
        case 0b110000:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bgt %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // biv
        case 0b110001:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "biv %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // ble
        case 0b110010:
            /// Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "ble %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // blt
        case 0b110011:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "blt %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bne
        case 0b110100:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bne %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bni
        case 0b110101:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bni %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bnz
        case 0b110110:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bnz %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // bzd
        case 0b111000:
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // Formatacao da instrucao
            sprintf(instrucao, "bzd %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // NÃO DEU TEMPO DE FINALIZAR ESSAS INSTRUÇOES E AGLUMAS OUTRAS ACIMA,

        // call tipo f
        case 0b011110:
            // Armazenando
            pc = R[29];
            sp = R[30];
            i = R[28] & 0xFFFF;
            // Execucao do comportamento com MEM8 e MEM32

            MEM32[sp] = pc + 4;
            sp = sp - 4;
            pc = MEM32[R[x] + i];

            // Formatacao da instrucao
            // call [rx+-s]             	PC=0x????????,MEM[0x????????]=0x????????
            sprintf(instrucao, "call [r%i -%i]", x, R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X,MEM[0x%08X]=0x%08X\n", pc, instrucao, sp, MEM32[sp]);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X,MEM[0x%08X]=0x%08X\n", pc, instrucao, sp, MEM32[sp]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // call tipo s
        case 0b111001:
            // Armazenando
            pc = R[29];
            sp = R[30];
            ii = R[28] & 0x1FFFFFF;

            // Execucao do comportamento

            MEM32[sp] = pc + 4;
            sp = sp - 4;
            pc = pc + 4 + ii;

            // Formatacao da instrucao
            sprintf(instrucao, "call %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X,MEM[0x%08X]=0x%08X\n", pc, instrucao, sp, MEM32[sp]);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X,MEM[0x%08X]=0x%08X\n", pc, instrucao, sp, MEM32[sp]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // ret
        case 0b011111:
            // Armazenando o PC antigo
            pc = R[29];
            sp = R[30];
            // Execucao do comportamento
            sp = sp + 4;
            pc = MEM32[sp];
            // Formatacao da instrucao
            sprintf(instrucao, "ret %i");
            // PC=MEM[0x????????]=0x????????
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=MEM[0x%08X]=0x%08Xpc\n", pc, instrucao, sp, pc);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=MEM[0x%08X]=0x%08Xpc\n", pc, instrucao, sp, pc);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // push
        case 0b001010:
            // Armazenando o PC antigo
            sp = R[30];
            ii = R[28] & 0x1FFFFFF;
            if (ii != 0)
            {
                MEM32[sp] = R[ii];
                sp = sp - 4;
            }
            // Execucao do comportamento

            // Formatacao da instrucao
            sprintf(instrucao, "push %i", R[28] & 0x3FFFFFF);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // pop
        case 0b001011:
            // Armazenando o PC antigo
            ii = R[28] & 0x1FFFFFF;

            sp = R[30];
            sp = sp + 4;

            R[ii] = MEM32[sp];
            // Execucao do comportamento
            // pop rv,rw,rx,ry,rz       	{Rv,Rw,Rx,Ry,Rz}=MEM[0x????????]{0x????????,0x????????,0x????????,0x????????,0x????????}
            // Formatacao da instrucao
            sprintf(instrucao, "pop r%u,r%u,r%u", ii, x, y, z);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // Formatacao  para o arquivo de saida)
            sprintf(data, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

            // int
        case 0b111111:
            // Parar a execucao
            executa = 0;
            // Formatacao da instrucao
            sprintf(instrucao, "int 0");
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tCR=0x00000000,PC=0x00000000\n", R[29], instrucao);

            sprintf(data, "0x%08X:\t%-25s\tCR=0x00000000,PC=0x00000000\n", R[29], instrucao);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);
            break;
        // Instrucao desconhecida
        default:
            // Exibindo mensagem de erro
            printf("[INVALID INSTRUCTION @ 0x00000050]!\n");
            sprintf(data, "[INVALID INSTRUCTION @ 0x%08X]!\n", R[29]);
            fprintf(output, "%s", data);
            // Parar a execucao
            executa = 0;
        }
        // PC = PC + 4 (proxima instrucao)
        R[29] = R[29] + 4;
    }
    // Exibindo a finalizacao da execucao
    printf("[END OF SIMULATION]\n");
    sprintf(data, "[END OF SIMULATION]\n");
    // printf(data);
    //  fputs(data, output);
    fprintf(output, "%s", data);

    // Fechando os arquivos
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}
