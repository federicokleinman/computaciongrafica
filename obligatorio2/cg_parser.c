#include "cg_parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void cg_parse_conf(char* scene_file){
    char str [512];
    FILE * pFile;

    pFile = fopen (scene_file,"r+");
    char* token;
    fgets(str,512,pFile);
    while(!feof(pFile))
    {
        token = strtok(str," \n\t");
        if(token){
            if(strcmp(token,"pos") == 0)
            {
                token = strtok(NULL," \n\t");
                float cam_pos_x = atof(token);
                token = strtok(NULL," \n\t");
                float cam_pos_y = atof(token);
                token = strtok(NULL," \n\t");
                float cam_pos_z = atof(token);
                /******************************************************/
                /*Insertar código para almacenar posición de la cámara*/
                /******************************************************/
                printf("POS: [%f %f %f]\n",cam_pos_x,cam_pos_y,cam_pos_z);
            }
            else
            {
                if(strcmp(token,"dist") == 0)
                {
                    token = strtok(NULL," \n\t");
                    float d = atof(token);
                    /*******************************************************/
                    /*Insertar código para almacenar distancia del viewport*/
                    /*******************************************************/
                    printf("DIST: %f\n",d);
                }
                else
                {
                    if(strcmp(token,"viewport") == 0)
                    {
                        token = strtok(NULL," \n\t");
                        float vw = atof(token);
                        token = strtok(NULL," \n\t");
                        float vh = atof(token);
                        /*********************************************************/
                        /*Insertar código para almacenar dimensiones del viewport*/
                        /*********************************************************/
                        printf("VIEWPORT: [%f %f]\n",vw,vh);
                    }
                    else
                    {
                        if(strcmp(token,"ambient") == 0)
                        {
                            token = strtok(NULL," \n\t");
                            float ambient = atof(token);
                            /******************************************************/
                            /*Insertar código para almacenar intensidad ambiente  */
                            /******************************************************/
                            printf("I_AMB: %f\n",ambient);
                        }
                        else
                        {
                           if(strcmp(token,"view") == 0)
                            {
                                token = strtok(NULL," \n\t");
                                float cam_view_x = atof(token);
                                token = strtok(NULL," \n\t");
                                float cam_view_y = atof(token);
                                token = strtok(NULL," \n\t");
                                float cam_view_z = atof(token);
                                /**********************************************************************/
                                /*Insertar código para almacenar vector VIEW de la cámara (OPCIONAL)  */
                                /**********************************************************************/
                                printf("VIEW: [%f %f %f]\n",cam_view_x,cam_view_y,cam_view_z);
                            }
                            else
                            {
                                if(strcmp(token,"up") == 0)
                                {
                                    token = strtok(NULL," \n\t");
                                    float cam_up_x = atof(token);
                                    token = strtok(NULL," \n\t");
                                    float cam_up_y = atof(token);
                                    token = strtok(NULL," \n\t");
                                    float cam_up_z = atof(token);
                                    /**********************************************************************/
                                    /*Insertar código para almacenar vector UP de la cámara (OPCIONAL)    */
                                    /**********************************************************************/
                                    printf("UP: [%f %f %f]\n",cam_up_x,cam_up_y,cam_up_z);
                                }
                                else
                                {
                                    if(strcmp(token,"lightP") == 0)
                                    {
                                        token = strtok(NULL," \n\t");
                                        float l_int = atof(token);
                                        token = strtok(NULL," \n\t");
                                        float l_pos_x = atof(token);
                                        token = strtok(NULL," \n\t");
                                        float l_pos_y = atof(token);
                                        token = strtok(NULL," \n\t");
                                        float l_pos_z = atof(token);
                                        /******************************************************/
                                        /*Insertar código para almacenar luz Puntual          */
                                        /******************************************************/
                                        printf("LIGHT_P: %f [%f %f %f]\n",l_int,l_pos_x,l_pos_y,l_pos_z);
                                    }
                                    else
                                    {
                                        if(strcmp(token,"lightD") == 0)
                                        {
                                            token = strtok(NULL," \n\t");
                                            float l_int = atof(token);
                                            token = strtok(NULL," \n\t");
                                            float l_dir_x = atof(token);
                                            token = strtok(NULL," \n\t");
                                            float l_dir_y = atof(token);
                                            token = strtok(NULL," \n\t");
                                            float l_dir_z = atof(token);
                                            /******************************************************/
                                            /*Insertar código para almacenar luz Direccional      */
                                            /******************************************************/
                                            printf("LIGHT_D: %f [%f %f %f]\n",l_int,l_dir_x,l_dir_y,l_dir_z);
                                        }
                                        else
                                        {
                                            if(strcmp(token,"sphere") == 0)
                                            {
                                                token = strtok(NULL," \n\t");
                                                float center_x = atof(token);
                                                token = strtok(NULL," \n\t");
                                                float center_y = atof(token);
                                                token = strtok(NULL," \n\t");
                                                float center_z = atof(token);

                                                token = strtok(NULL," \n\t");
                                                float radius = atof(token);

                                                token = strtok(NULL," \n\t");
                                                unsigned char col_dif_r = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_dif_g = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_dif_b = (unsigned char)(255*atof(token));

                                                token = strtok(NULL," \n\t");
                                                unsigned char col_spec_r = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_spec_g = (unsigned char)(255*atof(token));
                                                token = strtok(NULL," \n\t");
                                                unsigned char col_spec_b = (unsigned char)(255*atof(token));

                                                token = strtok(NULL," \n\t");
                                                float coef_spec = atof(token);

                                                token = strtok(NULL," \n\t");
                                                float coef_refl = atof(token);

                                                /******************************************************/
                                                /*Insertar código para almacenar luz Esfera           */
                                                /******************************************************/
                                                printf("SPHERE: CENTER [%f %f %f] RADIUS %f C_DIF [%d %d %d] C_SPEC [%d %d %d] CF_SPEC %f CF_REFL %f\n",center_x,center_y,center_z,radius,col_dif_r,col_dif_g,col_dif_b,col_spec_r,col_spec_g,col_spec_b,coef_spec,coef_refl);

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        fgets(str,512,pFile);
    }
    fclose (pFile);
}
