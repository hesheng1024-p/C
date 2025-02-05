#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BITMAPFILEHEADERLENGTH 14  // The bmp FileHeader length is 14
#define BM 19778

using namespace std;

void bmpFileTest(FILE* fpbmp);
void bmpHeaderPartLength(FILE* fpbmp);
void BmpWidthHeight(FILE* fpbmp);
void bmpDataPart(FILE* fpbmp);
void bmpoutput(FILE *fpout);

 int OffSet = 0;
long width ;
long height ;
 char r[2000][2000],output_r[2000][2000];
 char g[2000][2000],output_g[2000][2000];
 char b[2000][2000],output_b[2000][2000];
int main(int argc, char* argv[])
{
    char *fp_temp;
     FILE *fpbmp;
     FILE *fpout;
     fpbmp= fopen("1.bmp", "rb");
     if (fpbmp == NULL)
     {
 printf("Open bmp failed!!!\n");
 return 1;
     }
     fpout= fopen("out.bmp", "wb+");
     if (fpout == NULL)
     {
 printf("Open out.bmp failed!!!\n");
 return 1;
     }
     bmpFileTest(fpbmp);
     bmpHeaderPartLength(fpbmp);
     BmpWidthHeight(fpbmp);
    fseek(fpbmp, 0L, SEEK_SET);
    fseek(fpout, 0L, SEEK_SET);
    fp_temp=malloc(OffSet);
         fread(fp_temp, 1, OffSet, fpbmp);
    fwrite(fp_temp,1,OffSet,fpout);

    bmpDataPart(fpbmp);
    bmpoutput(fpout);  //如果您想对图片进行处理，请您再这里插入处理函数
    fclose(fpbmp);
    fclose(fpout);
         return 0;
}
void bmpoutput(FILE* fpout)
{
         int i, j=0;
         int stride;
 char* pixout=NULL;

stride=(24*width+31)/8;
stride=stride/4*4;
pixout=malloc(stride);
fseek(fpout, OffSet, SEEK_SET);
for(j=0;j<height;j++)
{
   for(i=0;i<width;i++)
        {
            pixout[i*3+2]=output_r[height-1-j][i];
            pixout[i*3+1]=output_g[height-1-j][i];
            pixout[i*3]  =output_b[height-1-j][i];
        }
fwrite(pixout, 1, stride, fpout);
}
}
void bmpDataPart(FILE* fpbmp)
{
         int i, j=0;
int stride;
 char* pix=NULL;
         FILE* fpr;
         FILE* fpg;
         FILE* fpb;
     if((fpr=fopen("bmpr.txt","w+")) == NULL)
     {
    printf("Failed to construct file bmpr.txt.!!!");
exit(1);
     }
     if((fpg=fopen("bmpg.txt","w+")) == NULL)
     {
 printf("Failed to construct file bmpg.txt.!!!");
 exit(1);
     }
     if((fpb=fopen("bmpb.txt","w+")) == NULL)
     {
printf("Failed to construct file bmpb.txt.!!!");
exit(1);
     }

     fseek(fpbmp, OffSet, SEEK_SET);
stride=(24*width+31)/8;
stride=stride/4*4;
pix=malloc(stride);

for(j=0;j<height;j++)
{
fread(pix, 1, stride, fpbmp);
   for(i=0;i<width;i++)
        {
            r[height-1-j][i]   =pix[i*3+2];
            g[height-1-j][i]   =pix[i*3+1];
            b[height-1-j][i]   =pix[i*3];
            output_r[height-1-j][i]   =pix[i*3+2];
            output_g[height-1-j][i]   =pix[i*3+1];
            output_b[height-1-j][i]   =pix[i*3];
        }

}
 for(i =0; i < height; i++)
     {
for(j = 0; j < width-1; j++)
{
fprintf(fpb,"%4d",b[i][j]);
fprintf(fpg,"%4d",g[i][j]);
fprintf(fpr,"%4d",r[i][j]);
}
fprintf(fpb,"%4d\n",b[i][j]);
fprintf(fpg,"%4d\n",g[i][j]);
fprintf(fpr,"%4d\n",r[i][j]);
 }

fclose(fpr);
fclose(fpg);
fclose(fpb);

}
void bmpFileTest(FILE* fpbmp)
{
     unsigned short bfType = 0;
     fseek(fpbmp, 0L, SEEK_SET);
     fread(&bfType, sizeof(char), 2, fpbmp);
     if (BM != bfType)
     {
 printf("This file is not bmp file.!!!\n");
 exit(1);
     }
}

void bmpHeaderPartLength(FILE* fpbmp)
{
     fseek(fpbmp, 10L, SEEK_SET);
     fread(&OffSet, sizeof(char), 4, fpbmp);
     printf("The Header Part is of length %d.\n", OffSet);
}

void BmpWidthHeight(FILE* fpbmp)
{
     fseek(fpbmp, 18L, SEEK_SET);
     fread(&width, sizeof(char), 4, fpbmp);
     fseek(fpbmp, 22L, SEEK_SET);
     fread(&height, sizeof(char), 4, fpbmp);
     printf("The Width of the bmp file is %ld.\n", width);
     printf("The Height of the bmp file is %ld.\n", height);
}
