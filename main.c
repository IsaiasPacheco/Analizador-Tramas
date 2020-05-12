#include <stdio.h>
#include <stdlib.h>

int llc(unsigned char trama[]);
unsigned short int checksum( unsigned char trama[], unsigned char ihl);
unsigned short int checksumtcp( unsigned char trama[], unsigned char inicio, unsigned char ihl);
unsigned char num_trama = 1;

void main(void)
{

    unsigned char trama[][100] = {{  //t1
                                    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x10,
                                    0x08, 0x00, 0x06, 0x04, 0x00, 0x04, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xcc, 0x39, 0xfe                                 
                                    },
                                  {//t2 IP
                                   0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x46, 0x00,
                                   0x80, 0x42, 0x04, 0x55, 0x34, 0x11, 0x80, 0x11, 0x6b, 0xf0, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc,
                                   0x67, 0x02, 0xaa, 0xbb, 0xcc, 0xdd, 0x04, 0x0c, 0x00, 0x35, 0x00, 0x2e, 0x85, 0x7c, 0xe2, 0x1a,
                                   0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x03, 0x69,
                                   0x73, 0x63, 0x05, 0x65, 0x73, 0x63, 0x6f, 0x6d, 0x03, 0x69, 0x70, 0x6e, 0x02, 0x6d, 0x78, 0x00,
                                   0x00, 0x1c, 0x00, 0x01},
                                  {//t3 T - S
                                   0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x04, 0xf0, 0xf1,
                                   0x09, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x9b, 0x6d},

                                  {//t4 OTRO
                                   0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x80, 0x35, 0x00, 0x01,
                                   0x08, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x3a, 0xe1,
                                   0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xee, 0xdf, 0xb0},
                                  {//t5 T-U
                                   0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf0,
                                   0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0x90, 0x6d},

                                  {//T6 T - I
                                   0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x12, 0xf0, 0xf0,
                                   0x0a, 0x0b, 0x0e, 0x00, 0xff, 0xef, 0x14, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x7f, 0x23,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x99, 0x98, 0x6d},
                                  {//t7 T-U
                                   0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf1,
                                   0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0x90, 0x6d},
                                  {//t8
                                   0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf0,
                                   0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0x90, 0x6d},
                                   { //Trama extra 1
                                        0x00 ,0x1f ,0x45 ,0x9d ,0x1e ,0xa2 ,0x00 ,0x23 ,0x8b ,0x46 ,0xe9 ,0xad ,0x08 ,0x00 ,0x45 ,0x10,   
                                        0x00 ,0x3c ,0x04 ,0x57 ,0x00 ,0x00 ,0x80 ,0x01 ,0x98 ,0x25 ,0x94 ,0xcc ,0x39 ,0xcb ,0x94 ,0xcc,   
                                        0x3a ,0xe1 ,0x08 ,0x00 ,0x49 ,0x5c ,0x03 ,0x00 ,0x01 ,0x00 ,0x61 ,0x62 ,0x63 ,0x64 ,0x65 ,0x66,   
                                        0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,   
                                        0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69},
                                    { //Trama extra 2
                                        0x00,0x1f,0x45,0x9d,0x1e,0xa2,0x00,0x23,0x8b,0x46,0xe9,0xad,0x08,0x00,0x46,0x08,
                                        0x80,0x42,0x04,0x55,0x34,0x11,0x80,0x11,0x6b,0xf0,0x94,0xcc,0x39,0xcb,0x94,0xcc,
                                        0x67,0x02,0xaa,0xbb,0xcc,0xdd,0x04,0x0c,0x00,0x35,0x00,0x2e,0x85,0x7c,0xe2,0x1a,
                                        0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x77,0x77,0x77,0x03,0x69,
                                        0x73,0x63,0x05,0x65,0x73,0x63,0x6f,0x6d,0x03,0x69,0x70,0x6e,0x02,0x6d,0x78,0x00,
                                        0x00,0x1c,0x00,0x01
                                    }, {
                                        0x02,0xFF,0x53,0xC3,0xE9,0xAB,0x00,0xFF,0x66,0x7F,0xD4,0x3C,0x08,0x00,0x45,0x02,
                                        0x00,0x30,0x2C,0x00,0x40,0x00,0x80,0x06,0x4B,0x74,0xC0,0xA8,0x01,0x02,0xC0,0xA8,
                                        0x01,0x01,0x04,0x03,0x00,0x15,0x00,0x3B,0xCF,0x44,0x00,0x00,0x00,0x00,0x70,0x02,
                                        0x20,0x00,0x0C,0x34,0x00,0x00,0x02,0x04,0x05,0xB4,0x01,0x01,0x04,0x02
                                        },
                                        {
                                        0x00, 0x01, 0xF4, 0x43, 0xC9, 0x19, 0x00, 0x18, 0xE7, 0x33, 0x3D, 0xC3, 0x08, 0x00, 0x45, 0x00, 
                                        0x00, 0x28, 0xF6, 0x18, 0x40, 0x00, 0x80, 0x06, 0x6B, 0xA4, 0x94, 0xCC, 0x19, 0xF5, 0x40, 0xE9, 
                                        0xA9, 0x68, 0x08, 0x3A, 0x00, 0x50, 0x42, 0xFE, 0xD8, 0x4A, 0x6A, 0x66, 0xAC, 0xC8, 0x50, 0x10, 
                                        0x42, 0x0E, 0x00, 0x00, 0x00, 0x00
                                        },
                                        {
                                        0x00, 0x14, 0xd1, 0xc2, 0x38, 0xbe, 0x00, 0x18, 0xE7, 0x33, 0x3D, 0xC3, 0x08, 0x00, 0x45, 0x00,
                                        0x00, 0x30, 0x94, 0x71, 0x40, 0x00, 0x80, 0x06, 0xf9, 0x8c, 0xc0, 0xa8, 0x02, 0x3c, 0x4a, 0x7d,
                                        0x5f, 0x68, 0x10, 0x52, 0x00, 0x50, 0x03, 0xc7, 0x5a, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x70, 0x02,
                                        0x40, 0x00, 0x67, 0x4b, 0x00, 0x00, 0x02, 0x04, 0x05, 0xb4, 0x01, 0x01, 0x04, 0x02
                                        }
                                    };

    unsigned char i = 0;
    printf(" \n> Pacheco Castillo Isaias < \n");
    for (i = 0; i < 13; i++)
    {
        llc(trama[i]);
    }
}

int llc(unsigned char trama[])
{
    printf("\n\n\nNUM TRAMA      %d             Pacheco_Isaias\n**********    CABECERA ETHERNET    **********", num_trama);
    printf("\nMAC DESTINO   %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[0], trama[1], trama[2], trama[3], trama[4], trama[5]);
    printf("\nMAC ORIGEN    %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[6], trama[7], trama[8], trama[9], trama[10], trama[11]);
    unsigned short int TOT = trama[12] << 8 | trama[13];

    if (TOT < 1500)
    {
        printf("\nTAMANIO       %d bytes \n\n**********    CABECERA LLC         **********", TOT);
        unsigned char s[][5] = {"RR", "RNR", "REJ", "SREJ"};

        //Campo de control tramas U < Command >
        unsigned char uc[][6] = {"UI", "SIM", "NR0", "SART", "UP", "--", "--", "--", "DISC", "--", "NR2", "SARME", "--", "--", "--", "SABME", "SNRM", "--", "NR1", "RSET", "--", "--", "--", "XID", "--", "--", "NR3", "SNRME"};

        //Campo de control tramas U < Response >
        unsigned char ur[][6] = {"UI", "RIM", "NR0", "DM", "--", "--", "--", "--", "RD", "--", "NR2", "--", "UA", "--", "--", "--", "--", "FRMR", "NR1", "--", "--", "--", "--", "XID", "--", "--", "NR3", "--"};

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
            if (trama[16] & 16)
            {
                if (trama[15] & 1)
                    printf("\n T-U, %s , f", ur[(((trama[16] >> 2) & 3) | (trama[16] >> 3) & 28)]);
                else
                    printf("\n T-U, %s , p", uc[(((trama[16] >> 2) & 3) | (trama[16] >> 3) & 28)]);
            }
            else
                printf(" \n T-U");
            break;
        }
    }
    else if (TOT == 2048)
    {
         printf("\n\n**********    CABECERA IP         **********");
         printf("\nVersion               %d", trama[14]>>4);
         printf("\nIHL                   %d bytes", (trama[14]&0x0f)*4);

         if(trama[15]&16)
            printf("\nTOS                   Retraso minimo");
         if(trama[15]&8)
            printf("\nTOS                   Rendimiendo maximo");
         if(trama[15]&4)
            printf("\nTOS                   Confiabilidad maxima");
         if(trama[15]&2)
            printf("\nTOS                   Costo minimo");

        printf("\nTam Total             %d bytes", (trama[16]<<8)|trama[17]);

        printf("\nIdentificacion        0x%0.2x", (trama[18]<<8)|trama[19]);

        printf("\nFlags ");

        if(trama[20]&64)
            printf("\n                      No fragmentar ");
        else
            printf("\n                      Fragmentar ");
        
        if(trama[20]&32)
            printf("\n                      Mas fragmentos ");
        else
            printf("\n                      No hay mas fragmentos  ");

        printf("\nDesplazamiento        %d bytes", (((trama[20]&31)<<8|trama[21])*8) );

        printf("\nTime to live          %d saltos", trama[22]);


        if(trama[23] == 1 ){
            printf("\nProtocol              ICMP");
        }else if(trama[23] == 6 ){
            printf("\nProtocol              TCP");
        }else if(trama[23] == 17 ){
            printf("\nProtocol              UDP");
        }else{
            printf("\nProtocol              Otro");
        }
        

        if( (checksum(trama, (trama[14]&0x0f)*4)) == 0 )
            printf("\nChecksum              :)");
        else
            printf("\nEl Checksum es        0x%0.2x", checksum(trama, (trama[14]&0x0f)*4) );

        printf("\nIp origen             %0.2d.%0.2d.%0.2d.%0.2d", trama[26], trama[27], trama[28], trama[29]);
        printf("\nIp destino            %0.2d.%0.2d.%0.2d.%0.2d", trama[30], trama[31], trama[32], trama[33]);

        printf("\nOpciones              \n");

        unsigned char i = 0;
        for( i=34;  i< (((trama[14]&0x0f)*4)+14 ); i++ )
            printf("0x%0.2x ", trama[i]);
        
        unsigned char ihl = ((trama[14]&0x0f)*4)+14;
        //En ihl + 4 termina la parte ICMP y se impriman las opciones

        if( trama[23] == 1 ){
            printf("\n**********            ICMP            **********");
            if( trama[ihl] == 8 && trama[ihl+1] == 0){
                printf("\nType                  Solicitud ECO");
                printf("\nChecksum              0x%0.2x", trama[ihl+2]<<8|trama[ihl+3]);
                printf("\nIdentificador         %d", trama[ihl+4]<<8|trama[ihl+5]);
                printf("\nNo. Secuencia         %d", trama[ihl+6]<<8|trama[ihl+7]);
                printf("\nDatos        \n"       );
                for(i=ihl+7; i<ihl+7+47 ; i++ )
                    printf("0x%0.2x ", trama[i]);
            }
            else if( trama[ihl] == 0 && trama[ihl+1] == 0 ){
                printf("\nType                  Resuesta ECO");
                printf("\nChecksum              0x%0.2x", trama[ihl+2]<<8|trama[ihl+3]);
                printf("\nIdentificador         %d", trama[ihl+4]<<8|trama[ihl+5]);
                printf("\nNo. Secuencia         %d", trama[ihl+6]<<8|trama[ihl+7]);
                printf("\nDatos        \n"       );
                for(i=ihl+7; i<ihl+7+47 ; i++ )
                    printf("0x%0.2x ", trama[i]);
            }
            else if( trama[ihl] == 3 ){
                if( trama[ihl+1] == 0)
                    printf("\nType                  Red inalcanzable");
                else if( trama[ihl+1] == 1)
                    printf("\nType                  Host inalcanzable");
                else if( trama[ihl+1] == 2)
                    printf("\nType                  Protocolo inalcanzable");
                else if( trama[ihl+1] == 3)
                    printf("\nType                  Puerto inalcanzable");
                else
                    printf("\nType                  Destino inalcanzable");
                printf("\nChecksum              0x%0.2x", trama[ihl+2]<<8|trama[ihl+3]);
            }
            else if( trama[ihl] == 1 && trama[ihl+1] == 1 ){
                if( trama[ihl+1] == 1)
                    printf("\nType                  TTL excedido");
                if( trama[ihl+1] == 0 )
                    printf("\nType                  FRT excedido");
                printf("\nChecksum              0x%0.2x", trama[ihl+2]<<8|trama[ihl+3]);
            }
        }
        
        if( trama[23] == 6 ){
            printf("\n**********            TCP             **********");
            printf("\nTamanio               %d bytes", (trama[ihl+12]>>4)*4 );
            printf("\nChecksum              0x%x", ( checksumtcp(trama, ihl, (trama[ihl+12]>>4)*4) )  );
            
                
        }
            

    }
    else if (TOT == 2054)
    {
        printf("\n\n**********    CABECERA ARP         **********");
        if( (short int)(trama[14]<<8 | trama[15]) == 6 )
            printf("\nIEEE 802 LAN");
        else if( (short int)(trama[14]<<8 | trama[15]) == 1 )
            printf("\nETHERNET");
        else
            printf("\nOTRO");

        if ( (short int)(trama[16]<<8 | trama[17]) == 2048 )
            printf("\nIPV4");

        if( trama[18] == 6)
            printf("\nETHERNET/IEEE 802");

        if( trama[19] == 6)
            printf("\nIPV4");

        switch ( (short int)(trama[20]<<8 | trama[21]) )
        {
        case 1:
            printf("\nREQUEST");
            printf("\nDE:\nMAC ORIGEN    %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[22], trama[23], trama[24], trama[25], trama[26], trama[27]);
            printf("\nIP ORIGEN     %0.2d.%0.2d.%0.2d.%0.2d", trama[28],trama[29],trama[30],trama[31]);
            printf("\nDE:\nMAC DEST      00:00:00:00:00:00 ");
            printf("\nIP DEST       %0.2d.%0.2d.%0.2d.%0.2d", trama[38],trama[39],trama[40],trama[41]);
            break;
        case 2:
            printf("\nREPLY");
            printf("\nDE:\nMAC ORIGEN    %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[22], trama[23], trama[24], trama[25], trama[26], trama[27]);
            printf("\nIP ORIGEN     %0.2d.%0.2d.%0.2d.%0.2d", trama[28],trama[29],trama[30],trama[31]);
            printf("\nPARA:\nMAC DEST      %0.2d.%0.2d.%0.2d.%0.2d", trama[32],trama[33],trama[34],trama[35]);
            printf("\nIP DEST       %0.2d.%0.2d.%0.2d.%0.2d", trama[38],trama[39],trama[40],trama[41]);
            break;
        case 3:
            break;
            printf("\nREQUEST INV");
            printf("\nDE:\nMAC ORIGEN    %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[22], trama[23], trama[24], trama[25], trama[26], trama[27]);
            printf("\nIP ORIGEN     %0.2d.%0.2d.%0.2d.%0.2d", trama[28],trama[29],trama[30],trama[31]);
            printf("\nPARA:\nMAC DEST      %0.2d.%0.2d.%0.2d.%0.2d", trama[32],trama[33],trama[34],trama[35]);
            printf("\nIP DEST       0.0.0.0");
        case 4: 
            printf("\nREPLY INV");
            printf("\nDE:\nMAC ORIGEN    %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x ", trama[22], trama[23], trama[24], trama[25], trama[26], trama[27]);
            printf("\nIP ORIGEN     %0.2d.%0.2d.%0.2d.%0.2d", trama[28],trama[29],trama[30],trama[31]);
            printf("\nPARA:\nMAC DEST      %0.2d.%0.2d.%0.2d.%0.2d", trama[32],trama[33],trama[34],trama[35]);
            printf("\nIP DEST       %0.2d.%0.2d.%0.2d.%0.2d", trama[38],trama[39],trama[40],trama[41]);
            break;
        }
    }
    else
        printf("\n OTRO ");

    num_trama++;

    return 0;
}

unsigned short int checksum(unsigned char trama[], unsigned char ihl)
{

    int checksum = 0;
    unsigned char i = 0;

    //Se completa el tamaño de la trama
    if (!(ihl % 2 == 0))
    {
        trama[++ihl] = 0x00;
    }

    //Se inicia desde la cabecera IP
    for (i = 14; i < ihl+14; i = i + 2)
    {   
        //No se toman en cuenta los campos del checksum
        if(!(i==24)){
            checksum += trama[i] << 8 | trama[i + 1];
        }
    }

    
    // Verificar acarreo
    if (checksum >> 16 != 0)
    {
        //Se realiza la suma del checksum + acarreo
        checksum += checksum >> 16;
        //Se elimina el acarreo con una mascara
        checksum = checksum & 0x0ffff;
    }

    checksum = ~checksum; //Complemento a uno

    checksum = checksum & 0x0000ffff; //Mascara
    
    return checksum;
}

unsigned short int checksumtcp(unsigned char trama[], unsigned char inicio, unsigned char ihl )
{

    int checksum = 0;
    unsigned char i = 0;

    //Se completa el tamaño de la trama
    if (!(ihl % 2 == 0))
    {
        trama[++ihl] = 0x00;
    }

    //Se inicia desde la cabecera IP
    for (i = inicio; i < ihl+inicio; i = i + 2)
    {   
        //No se toman en cuenta los campos del checksum
        if(!(i==inicio+16)){
            checksum += trama[i] << 8 | trama[i + 1];
        }
    }

    //Se suma la seudocabecera

    //IP origen
    checksum += (trama[26]<<8|trama[27]);
    checksum += (trama[28]<<8|trama[29]);
    //IP destino
    checksum += (trama[30]<<8|trama[31]);
    checksum += (trama[32]<<8|trama[33]);

    //Proocolo
    checksum += 0x0006;

    //Tamanio TCP
    checksum += ihl;


    //(trama[26]<<8|trama[27]) + (trama[28]<<8|trama[29]) + (trama[30]<<8|trama[31]) + (trama[32]<<8|trama[33]) + 0x06 + 0x0014 +
    
    // Verificar acarreo
    if (checksum >> 16 != 0)
    {
        //Se realiza la suma del checksum + acarreo
        checksum += checksum >> 16;
        //Se elimina el acarreo con una mascara
        checksum = checksum & 0x0ffff;
    }

    checksum = ~checksum; //Complemento a uno

    checksum = checksum & 0x0000ffff; //Mascara
    
    return checksum;
}

