#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void sifir_bastir();
void sifre_olustur();
void sifre_kontrol();
void sifre_kontrol2();
void ana_menu();
void giris();
void secim_kirmizi();
void secim_yesil();
void secim_mavi();
void izleyici_ogren();
void hasilat_ogren();
void hasilat_dosyasina_degergir();
void hasilat_dosyasindan_degeral();


int secim1,secim_anamenu,secim_salon,secim_hasilat,secim_izleyici,secim_matine=0,a,b=1,c,d=1,e,f=1;
int i,j,k,l,dosya_hasilat,dosya_hasilat2,hasilat=0,koltuk_numarasi_kirmizi[250],koltuk_numarasi_yesil[250],koltuk_numarasi_mavi[250];



char kullanici_adi[25],sifre[25],kullanici_adi_girisi[25],sifre_girisi[25];
char dosya_kullanici[25],dosya_sifre[25];
FILE *Sifre;
FILE *Toplam_hasilat;


typedef struct
{
    char kirmizi[5][50];//matine, koltuk
    char yesil[5][50];
    char mavi[5][50];
}salonlar;
salonlar salon;

enum ucretler
{
    ogrenci=1,//20tl
    tam=2,//30tl
};
enum ucretler ucret;





int main()
{
    hasilat_dosyasindan_degeral();
    sifir_bastir();
    sifre_kontrol2();

}

void sifir_bastir()
{
    for(i=1;i<=5;i++)
    {
        for(j=1;j<=50;j++)
        {
            salon.kirmizi[i][j]=0;
        }
    }
    for(i=1;i<=5;i++)
    {
        for(j=1;j<=50;j++)
        {
            salon.yesil[i][j]=0;
        }
    }
    for(i=1;i<=5;i++)
    {
        for(j=1;j<=50;j++)
        {
            salon.mavi[i][j]=0;
        }
    }
}

void sifre_olustur()
{
    printf("\t\t\t\tKullanici Adi Belirleyiniz: ");
    scanf("%s",&kullanici_adi);
    printf("\t\t\t\tSifre Belirleyiniz: ");
    scanf("%s",&sifre);


    Sifre=fopen("sifre.txt","w");
    fprintf(Sifre,"%s %s",kullanici_adi,sifre);
    fclose(Sifre);

}

void sifre_kontrol()
{
    printf("\t\t\t\t\tKullanici Adini Giriniz: ");
    scanf("%s",&kullanici_adi_girisi);
    printf("\t\t\t\t\tSifreyi Giriniz: ");
    scanf("%s",&sifre_girisi);


    Sifre=fopen("sifre.txt","r");
    fscanf(Sifre,"%s %s",dosya_kullanici,dosya_sifre);
    fclose(Sifre);
    if(strcmp(dosya_kullanici,kullanici_adi_girisi) || strcmp(dosya_sifre,sifre_girisi))
     {
            printf("\n\n\t\t\t\t\tKullanici Adi veya Sifre Hatali\n");
            sifre_kontrol();
     }
     else
     {
         printf("\n\t\t\t\t\tKullanici Adi ve Sifre Dogru\n");
         ana_menu();
     }
}

void sifre_kontrol2()
{
    Sifre=fopen("sifre.txt","r");
    if(Sifre!=NULL)//Sifre dosyasi bos degilse sifre kaydedilmis demektir
        sifre_kontrol();
    else
        {
            sifre_olustur();
            sifre_kontrol();
        }
}

void ana_menu()
{
    printf("1-Bilet al\n2-Izleyicileri ogren\n3-Hasilat Ogren\nSecim yapiniz: ");
    scanf("%d",&secim_anamenu);
    switch(secim_anamenu)
    {
        case 1:
            giris();
            break;
        case 2:
            izleyici_ogren();
            break;
        case 3:
            hasilat_ogren();
            break;
        default:
            {
                printf("Hatali Secim!\n");
                ana_menu();
            }
    }
}

void giris()
{
    printf("\t\t\t\t\t1-Kirmizi\n\t\t\t\t\t2-Yesil\n\t\t\t\t\t3-Mavi\n");
    printf("\t\t\t\t\tHangi Salonu Secmek Istiyorsunuz?: ");
    scanf("%d",&secim_salon);

    switch(secim_salon)
    {
        case 1:
            secim_kirmizi();
            break;
        case 2:
            secim_yesil();
            break;
        case 3:
            secim_mavi();
            break;
        default:
          {
            printf("\n\t\t\t\t\tHatali secim\n");
            giris();
          }
    }


}

void secim_kirmizi()
{
    printf("\t\t\t\t\tKirmizi Salondan Matine Seciniz(1-5): ");
    scanf("%d",&secim_matine);
    if(secim_matine<1 || secim_matine>5)
    {
        printf("\n\t\t\t\t\tHatali secim!\n");
        secim_kirmizi();
    }
    for(i=secim_matine;i<i+1;i++)
    {
        for(j=1;j<=50;j++)
        {
            if(salon.kirmizi[i][j]==0)
            {
                salon.kirmizi[i][j]=1;
                koltuk_numarasi_kirmizi[b]=j;
                b++;
                goto a;
            }

        }
    }
    a:
    printf("1-Ogrenci\n2-Tam\nSecim yapiniz: ");
    scanf("%d",&secim_hasilat);
    if(secim_hasilat==ogrenci)
    {
        printf("\t\t\t\t\tUcret: 20TL\n");
        hasilat=hasilat+20;
        hasilat_dosyasina_degergir();
    }
    else
        if(secim_hasilat==tam)
    {
        printf("\t\t\t\t\tUcret: 30TL\n");
        hasilat=hasilat+30;
        hasilat_dosyasina_degergir();
    }
    printf("\t\t\t\t\tKirmizi Salonda %d. Matinede %d. Koltugu Aldiniz\n",secim_matine,koltuk_numarasi_kirmizi[b-1]);
    ana_menu();
}

void secim_yesil()
{
    printf("\t\t\t\t\tYesil Salondan Matine Seciniz(1-5): ");
    scanf("%d",&secim_matine);
    if(secim_matine<1 || secim_matine>5)
    {
        printf("\n\t\t\t\t\tHatali secim!\n");
        secim_yesil();
    }
    for(i=secim_matine;i<i+1;i++)
    {
        for(j=1;j<=50;j++)
        {
            if(salon.yesil[i][j]==0)
            {
                salon.yesil[i][j]=1;
                koltuk_numarasi_yesil[d]=j;
                d++;
                goto c;
            }

        }
    }
    c:
    printf("1-Ogrenci\n2-Tam\nSecim yapiniz: ");
    scanf("%d",&secim_hasilat);
    if(secim_hasilat==ogrenci)
    {
        printf("\t\t\t\t\tUcret: 20TL\n");
        hasilat=hasilat+20;
        hasilat_dosyasina_degergir();
    }
    else
        if(secim_hasilat==tam)
    {
        printf("\t\t\t\t\tUcret: 30TL\n");
        hasilat=hasilat+30;
        hasilat_dosyasina_degergir();
    }
    printf("\t\t\t\t\tYesil Salonda %d. Matinede %d. Koltugu Aldiniz\n",secim_matine,koltuk_numarasi_yesil[d-1]);
    ana_menu();
}

void secim_mavi()
{
    printf("\t\t\t\t\tMavi Salondan Matine Seciniz(1-5): ");
    scanf("%d",&secim_matine);
    if(secim_matine<1 || secim_matine>5)
    {
        printf("\n\t\t\t\t\tHatali secim!\n");
        secim_mavi();
    }
    for(i=secim_matine;i<i+1;i++)
    {
        for(j=1;j<=50;j++)
        {
            if(salon.mavi[i][j]==0)
            {
                salon.mavi[i][j]=1;
                koltuk_numarasi_mavi[f]=j;
                f++;
                goto e;
            }

        }
    }
    e:
    printf("1-Ogrenci\n2-Tam\nSecim yapiniz: ");
    scanf("%d",&secim_hasilat);
    if(secim_hasilat==ogrenci)
    {
        printf("\t\t\t\t\tUcret: 20TL\n");
        hasilat=hasilat+20;
        hasilat_dosyasina_degergir();
    }
    else
        if(secim_hasilat==tam)
    {
        printf("\t\t\t\t\tUcret: 30TL\n");
        hasilat=hasilat+30;
        hasilat_dosyasina_degergir();
    }
    printf("\t\t\t\t\tMavi Salonda %d. Matinede %d. Koltugu Aldiniz\n",secim_matine,koltuk_numarasi_mavi[f-1]);
    ana_menu();
}

void izleyici_ogren()
{
    printf("\n1-Kirmizi\n2-Yesil\n3-Mavi\nSalon Seciniz: ");
    scanf("%d",&secim_izleyici);
    switch(secim_izleyici)
     {

        case 1:
       {
        for(i=1;i<=5;i++)
        {
            for(j=1;j<=50;j++)
            {
                if(salon.kirmizi[i][j]==1)
                {
                    printf("\t\t\t\t\tKirmizi Salon %d. Matine--> %d. Koltuk Doludur\n",i,j);
                }
            }
        }
        ana_menu();
        break;
       }

        case 2:
       {
        for(i=1;i<=5;i++)
        {
            for(j=1;j<=50;j++)
            {
                if(salon.yesil[i][j]==1)
                {
                    printf("\t\t\t\t\tYesil Salon %d. Matine--> %d. Koltuk Doludur\n",i,j);
                }

            }
        }
        ana_menu();
        break;
       }


        case 3:
       {
        for(i=1;i<=5;i++)
        {
            for(j=1;j<=50;j++)
            {
                if(salon.mavi[i][j]==1)
                {
                    printf("\t\t\t\t\tMavi Salon %d. Matine--> %d. Koltuk Doludur\n",i,j);
                }
            }
        }
        ana_menu();
        break;
       }

        default:
            {
                printf("\n\t\t\t\t\tYanlis secim!!\n");
                izleyici_ogren();
            }
     }



}

void hasilat_ogren()
{
    Toplam_hasilat=fopen("hasilat.txt","r");
    fscanf(Toplam_hasilat,"%d",&dosya_hasilat);
    fclose(Toplam_hasilat);
    printf("\t\t\t\t\tToplam Hasilat: %d\n",dosya_hasilat);
    ana_menu();
}

void hasilat_dosyasina_degergir()
{
    Toplam_hasilat=fopen("hasilat.txt","w+");
    fprintf(Toplam_hasilat,"%d",hasilat);
    fclose(Toplam_hasilat);
}

void hasilat_dosyasindan_degeral()
{
    Toplam_hasilat=fopen("hasilat.txt","r");
    fscanf(Toplam_hasilat,"%d",&dosya_hasilat2);
    fclose(Toplam_hasilat);
    hasilat=hasilat+dosya_hasilat2;
}

