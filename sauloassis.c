// Como executar no terminal:
// gcc -Wall -O3 nomesobrenome_123456789012_exemplo.c -o nomesobrenome_123456789012_exemplo
// ./nomesobrenome_123456789012_exemplo entrada saida

// gcc -Wall -O3 sauloassis.c -o sauloassis
//./sauloassis 1_intro.hex 1_intro.out
// ./sauloassis 2_exemplo.hex 2_exemplo.out

// Numeros padronizados
#include <stdint.h>
// Biblioteca padrao
#include <stdlib.h>
// Entrada/saida padrao
#include <stdio.h>

#include <string.h>

#define DATA_SIZE 1000

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
    // Memoria com 32 KiB inicializada com zero
    // uint8_t *MEM8 = (uint8_t *)(calloc(32, 1024));
    uint32_t *MEM32 = (uint32_t *)(calloc(32, 1024));

    // mostrando dados recebidos do input
    printf("Dados do input file\n");
    // char buffer[78];

    // while (!feof(input))
    // {

    //     fread(buffer, sizeof(buffer), 1, input);
    //     // Print the read data
    //     printf("%s", buffer);
    // }

    // fclose(input);
    // // como atribuir os inputs as variavies em MEM[32]

    // for (int i = 0; i < 31; i++)
    // {
    //     // v[i] = i;
    //     // MEM32[i] =
    // }
    uint32_t Data[31]; // mudar para o numero de inputs

    for (int i = 0; i < 31; i++) // mudar para o numero de inputs
    {
        fscanf(input, "0x%08X\n", &Data[i]); //
        printf("0x%08X\n", Data[i]);         //
    }
    // fclose(input);

    for (int i = 0; i < 31; i++) // mudar para o numero de inputs
    {

        MEM32[i] = Data[i];
    }

    // Depois de carregamento do arquivo 1_intro.hex, o vetor de memoria contem o conteudo abaixo:

    // Imprimindo o conteudo das memorias em bytes

    // printf("\nMEM8:\n");
    // for (uint8_t i = 0; i < 48; i = i + 4)
    // {
    //     // Impressao lado a lado
    //     printf("0x%08X: 0x%02X 0x%02X 0x%02X 0x%02X\n", i, MEM8[i], MEM8[i + 1], MEM8[i + 2], MEM8[i + 3]);
    // }
    printf("\nMEM32:\n");
    for (uint32_t i = 0; i < 32; i = i + 1) // mudar para o numero de inputs
    {
        // Impressao lado a lado
        printf("0x%08X: 0x%08X (0x%02X 0x%02X 0x%02X 0x%02X)\n", i << 2, MEM32[i], ((uint8_t *)(MEM32))[(i << 2) + 3], ((uint8_t *)(MEM32))[(i << 2) + 2], ((uint8_t *)(MEM32))[(i << 2) + 1], ((uint8_t *)(MEM32))[(i << 2) + 0]);
    }

    //

    // Separador da saida esperada
    printf("\nSaida esperada\n\n      |       \n      V       \n\n");
    // Exibindo a inicializacao da execucao
    printf("[START OF SIMULATION]\n");
    // Setando a condicao de execucao para verdadeiro
    uint8_t executa = 1;
    // Enquanto executa for verdadeiro
    while (executa)
    {
        // Cadeia de caracteres da instrucao
        char data[1000];
        char name[30];
        char instrucao[30] = {0};
        // Declarando operandos
        uint8_t z = 0, x = 0, i = 0, y = 0;
        uint32_t pc = 0, xyl = 0, cmp = 0;
        // Carregando a instrucao de 32 bits (4 bytes) da memoria indexada pelo PC (R29) no registrador IR (R28)
        // E feita a leitura redundante com MEM8 e MEM32 para mostrar formas equivalentes de acesso
        // Se X (MEM8) for igual a Y (MEM32), entao X e Y sao iguais a X | Y (redundancia)
        // R[28] = ((MEM8[R[29] + 0] << 24) | (MEM8[R[29] + 1] << 16) | (MEM8[R[29] + 2] << 8) | (MEM8[R[29] + 3] << 0)) | MEM32[R[29] >> 2];
        R[28] = MEM32[R[29] >> 2];
        printf("R[29] = 0x%08X\n", R[29]);
        printf("R[28] = 0x%08X\n", R[28]);

        // Obtendo o codigo da operacao (6 bits mais significativos)
        uint8_t opcode = (R[28] & (0b111111 << 26)) >> 26;
        // Decodificando a instrucao buscada na memoria
        printf(" opcode = 0x%08X\n", opcode);
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
            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
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
            R[z] = (((uint16_t *)(MEM32))[(R[x] + i) >> 1]); // 1 ou 2 ou 4?
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
            xyl = R[28] & 0x1FFFFF; /// somente essa instruão resulta movs r2,1048576

            if (xyl & (1 << 21))
            {
                xyl = xyl | (0b11111111111 << 21); // com essa instruão resulta movs r2,1048576
            }

            //   extensão de sinal de xyl

            // Execucao do comportamento
            R[z] = xyl;
            // Formatacao da instrucao
            sprintf(instrucao, "movs r%u,%s%u", z, (xyl >= 0) ? ("") : (""), xyl);
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

            // Execucao do comportamento
            R[z] = R[x] + R[y];

            //  ZN ← (R[z] = 0)
            //  SN ← (R[z]31 = 1)

            //  CY ← (R[z]32 = 1)

            switch (R[z])
            {
            case 0:

                R[31] = R[31] | 0b1000000;
                sprintf(name, "ZN");

                break;
            case 1:

                R[31] = R[31] | 0b10000;
                sprintf(name, "SN");

                break;

            case 3:

                R[31] = R[31] | 0b1;
                sprintf(name, "CY");

                break;

            default:
                break;
            };

            //  OV ← (R[x]31 = R[y]31 ∧ R[z]31 ̸= R[x]31)
            switch (R[x])
            {
            case 1:

                R[31] = R[31] | 0b1000;
                sprintf(name, "OV");

                break;
            }

            // Formatacao da instrucao
            // pra represnetar o SR usa-se um ternario?
            // add r3,r1,r2
            sprintf(instrucao, "add r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	R3=R1+R2=0x00023456,SR=0x00000001
            printf("0x%08X:\t%-25s\tR%u=R%u+R%u=0x%08X,%-25s=0x%08X\n", R[29], instrucao, z, x, y, R[z], name, R[31]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u+R%u=0x%08X\n", R[29], instrucao, z, x, y, R[z]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            // para resetar o SR fazer um swit case aqui?
            switch (R[31])
            {
            case 0b1000000:
                R[31] = R[31] & ~(0b1000000);

                sprintf(name, "");

                break;
            case 0b10000:
                R[31] = R[31] & ~(0b10000);

                sprintf(name, "");

                break;
            case 0b1000:

                R[31] = R[31] & ~(0b1000);
                sprintf(name, "");

                break;
            case 0b1:

                R[31] = R[31] & ~(0b1);
                sprintf(name, "");

                break;

            default:
                break;
            }

            break;

        // sub
        case 0b000011:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            // Execucao do comportamento
            R[z] = R[x] - R[y];
            // Formatacao da instrucao
            // add r3,r1,r2
            // pra represnetar o SR usa-se um ternario?
            sprintf(instrucao, "add r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	R3=R1+R2=0x00023456,SR=0x00000001
            printf("0x%08X:\t%-25s\tR%u=R%u-R%u=0x%08X\n", R[29], instrucao, z, x, y, R[z]);

            sprintf(data, "0x%08X:\t%-25s\tR%u=R%u-R%u=0x%08X\n", R[29], instrucao, z, x, y, R[z]);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // mul
        case 0b000100:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;
            i = R[28] & 0xFFFF;

            // Execucao do comportamento
            (uint64_t)(R[i]) << 32 | R[z];

            R[z] = R[x] * R[y];

            //  ZN ← (R[l4−0] : R[z] = 0)
            //  CY ← (R[l4−0] ̸= 0)

            if (R[i] = 0)
            {
                R[31] = R[31] | 0b1000000;
                sprintf(name, "ZN");
            }
            else
            {
                R[31] = R[31] | 0b1;
                sprintf(name, "CY");
            }

            // Formatacao da instrucao
            // mul r0,r5,r4,r3
            sprintf(instrucao, "mul r%u,r%u,r%u,r%u", z, x, y, z);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R0:R5=R4*R3=0x0000000023F4F31C,SR=0x00000008
            printf("0x%08X:\t%-25s\tR%u:R%u=R%u*R%u=0x%08X\n", R[29], instrucao, z, xyl);

            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // sll
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento
        //     R[z] = R[x] * R[y];
        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

        // muls
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento
        //     R[z] = R[x] * R[y];
        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

        // sla
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento
        //     R[z] = R[x] * R[y];
        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

        // div
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento
        //     R[i] = R[x] % R[y];   // mod
        //     R[z] = R[x] / R[y];

        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

        // srl
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento

        //     R[z] = R[x] * R[y];
        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

        // div
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento
        //     R[z] = R[x] * R[y];
        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

        // sra
        // case 0b000100:
        //     // Obtendo operandos
        //     z = (R[28] & (0b11111 << 21)) >> 21;
        //     x = (R[28] & (0b11111 << 16)) >> 16;
        //     y = (R[28] & (0b11111 << 11)) >> 11;
        //     i = R[28] & 0xFFFF;

        //     // Execucao do comportamento
        //     R[z] = R[x] * R[y];
        //     // Formatacao da instrucao
        //     sprintf(instrucao, "mul r%u,%u", z, xyl);
        //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
        //     printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

        //     sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
        //     // printf(data);
        //     //  fputs(data, output);
        //     fprintf(output, "%s", data);

        //     break;

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
            // Formatacao da instrucao
            sprintf(instrucao, "cmp r%u,%u", R[28], pc);
            // sprintf(instrucao, "cmp ir,pc");
            //  Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
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
            // and r13,r1,r5
            sprintf(instrucao, "and r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=R%u&R%u=0x%08X\n", R[29], instrucao, z, x, y, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            sprintf(instrucao, "and r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=R%u|R%u=0x%08X\n", R[29], instrucao, z, x, y, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            // and r13,r1,r5
            sprintf(instrucao, "and r%u,r%u", z, x);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=~R%u=0x%08X\n", R[29], instrucao, z, x, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            // and r13,r1,r5
            sprintf(instrucao, "and r%u,r%u,r%u", z, x, y);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // R13=R1&R5=0x00002410,SR=0x00000020
            printf("0x%08X:\t%-25s\tR%u=R%u^R%u=0x%08X\n", R[29], instrucao, z, x, y, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            sprintf(instrucao, "addi r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	Rz=Rx+0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u+%u=0x%08X\n", R[29], instrucao, z, x, i, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            // Formatacao da instrucao
            // pra represnetar o SR usa-se um ternario?
            // addi rz,rx,s
            sprintf(instrucao, "subi r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // 	Rz=Rx+0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u-%u=0x%08X\n", R[29], instrucao, z, x, i, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            // muli rz,rx,s
            sprintf(instrucao, "muli r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            //	Rz=Rx*0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u*%u=0x%08X\n", R[29], instrucao, z, x, i, R[z]);

            sprintf(data, "copriar e colar string acima");
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
            R[z] = R[x] / i;
            // Formatacao da instrucao
            // divi rz,rx,s
            sprintf(instrucao, "muli r%u,r%u,%u", z, x, i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            //	Rz=Rx/0x????????=0x????????,SR=0x????????
            printf("0x%08X:\t%-25s\tR%u=R%u/%u=0x%08X\n", R[29], instrucao, z, x, i, R[z]);

            sprintf(data, "copriar e colar string acima");
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // modi
        case 0b010110:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            xyl = R[28] & 0x1FFFFF;
            // Execucao do comportamento
            R[z] = xyl;
            // Formatacao da instrucao
            sprintf(instrucao, "modi r%u,%u", z, xyl);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            // printf(data);
            //  fputs(data, output);
            fprintf(output, "%s", data);

            break;

        // cmpi
        case 0b010111:
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            xyl = R[28] & 0x1FFFFF;
            // Execucao do comportamento
            R[z] = xyl;
            // Formatacao da instrucao
            sprintf(instrucao, "cmpi r%u,%u", z, xyl);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);

            sprintf(data, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
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

        // int
        case 0b111111:
            // Parar a execucao
            executa = 0;
            // Formatacao da instrucao
            sprintf(instrucao, "int 0");
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            printf("0x%08X:\t%-25s\tCR=0x00000000,PC=0x00000000\n", R[29], instrucao);
            break;
        // Instrucao desconhecida
        default:
            // Exibindo mensagem de erro
            printf("Instrucao desconhecida!\n");
            // Parar a execucao
            executa = 0;
        }
        // PC = PC + 4 (proxima instrucao)
        R[29] = R[29] + 4;
    }
    // Exibindo a finalizacao da execucao
    printf("[END OF SIMULATION]\n");
    // Fechando os arquivos
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}
