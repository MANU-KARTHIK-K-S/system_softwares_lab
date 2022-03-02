#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *input_smacropt, *nam_smacropt, *def_smacropt, *arg_smacropt, *op_smacropt;
    int len, i, pos = 1;
    char arguments[20], mnemonics[20], operand[20], label[20], name[20], mne1[20], opnd1[20], pos1[10], pos2[10];
    input_smacropt = fopen("input_smacro.txt", "r");
    nam_smacropt = fopen("nam_smacro.txt", "w+");
    def_smacropt = fopen("def_smacro.txt", "w+");
    arg_smacropt = fopen("arg_smacro.txt", "w+");
    op_smacropt = fopen("op_smacro.txt", "w+");
    fscanf(input_smacropt, "%s%s%s", label, mnemonics, operand);
    while (strcmp(mnemonics, "END") != 0)
    {
        if (strcmp(mnemonics, "MACRO") == 0)
        {
            fprintf(nam_smacropt, "%s\n", label);
            fseek(nam_smacropt, SEEK_SET, 0);
            fprintf(def_smacropt, "%s\t%s\n", label, operand);
            fscanf(input_smacropt, "%s%s%s", label, mnemonics, operand);
            while (strcmp(mnemonics, "MEND") != 0)
            {
                if (operand[0] == '&')
                {
                    itoa(pos, pos1, 5);
                    strcpy(pos2, "?");
                    strcpy(operand, strcat(pos2, pos1));
                    pos = pos + 1;
                }
                fprintf(def_smacropt, "%s\t%s\n", mnemonics, operand);
                fscanf(input_smacropt, "%s%s%s", label, mnemonics, operand);
            }
            fprintf(def_smacropt, "%s", mnemonics);
        }
        else
        {
            fscanf(nam_smacropt, "%s", name);
            if (strcmp(mnemonics, name) == 0)
            {
                len = strlen(operand);
                for (i = 0; i < len; i++)
                {
                    if (operand[i] != ',')
                        fprintf(arg_smacropt, "%c", operand[i]);
                    else
                        fprintf(arg_smacropt, "\n");
                }
                fseek(def_smacropt, SEEK_SET, 0);
                fseek(arg_smacropt, SEEK_SET, 0);
                fscanf(def_smacropt, "%s%s", mne1, opnd1);
                fprintf(op_smacropt, ".\t%s\t%s\n", mne1, operand);
                fscanf(def_smacropt, "%s%s", mne1, opnd1);
                while (strcmp(mne1, "MEND") != 0)
                {
                    if ((operand[0] == '?'))
                    {
                        fscanf(arg_smacropt, "%s", arguments);
                        fprintf(op_smacropt, "-\t%s\t%s\n", mne1, arguments);
                    }
                    else
                        fprintf(op_smacropt, "-\t%s\t%s\n", mne1, opnd1);
                    fscanf(def_smacropt, "%s%s", mne1, opnd1);
                }
            }
            else
                fprintf(op_smacropt, "%s\t%s\t%s\n", label, mnemonics, operand);
        }
        fscanf(input_smacropt, "%s%s%s", label, mnemonics, operand);
    }
    fprintf(op_smacropt, "%s\t%s\t%s", label, mnemonics, operand);
    fclose(input_smacropt);
    fclose(nam_smacropt);
    fclose(def_smacropt);
    fclose(arg_smacropt);
    fclose(op_smacropt);
    // printf("files to be viewed \n");
    // printf("1. argtab.txt\n");
    // printf("2. namtab.txt\n");
    // printf("3. deftab.txt\n");
    // printf("4. op.txt\n");
}
