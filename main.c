#include <stdio.h>
#include <stdlib.h>

void llc(unsigned char trama[], unsigned char tam_trama);

void main(void)
{

    unsigned char trama[] = {0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x04, 0xf0, 0xf1, 0x01, 0x03, 0x00, 0xff, 0xaa, 0xbb, 0xcc, 0xdd};
    unsigned char tam_trama = sizeof(trama) / sizeof(trama[0]);

    llc(trama, tam_trama);
}

void llc(unsigned char trama[], unsigned char tam_trama)
{

    printf("\nMAC DESTINO   %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[0], trama[1], trama[2], trama[3], trama[4], trama[5]);
    printf("\nMAC ORIGEN    %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[6], trama[7], trama[8], trama[9], trama[10], trama[11]);

    unsigned short int TOT = trama[12] << 8 | trama[13];

    //printf("\n %0.2x - %0.2x %0.4x\n", trama[12], trama[13], TOT);

    if (TOT < 1500)
    {
        printf("\nTAMANIO       %d bytes \n**********    LLC    **********", TOT);
        unsigned char s[][5] = {"RR", "RNR", "REJ", "SREJ"};

        switch (trama[16] & 3)
        {
        case 0:
        case 2: //T - I
            printf("\n T-I, N(s)= %d , N(r)= %d ", trama[16] >> 1, trama[17] >> 1);
            if (trama[17] & 1)
            {
                if (trama[15] & 1)
                    printf(", f ");
                else
                    printf(", p ");
            }
            break;
        case 1: //T - S
            printf("\n T-S, %s , N(r)= %d ", s[(trama[16] >> 2) & 3], trama[17] >> 1);
            if (trama[17] & 1)
            {
                if (trama[15] & 1)
                    printf(", f ");
                else
                    printf(", p ");
            }
            break;
        case 3: //T - U
            break;
        }
    }
    else if (TOT == 2048)
    {
        printf(" IP ");
    }
    else if (TOT == 2054)
    {
        printf(" ARP ");
    }
    else
        printf(" OTRO ");
}
