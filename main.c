#include <stdio.h>
#include <stdlib.h>

struct Studentt{
    int no;
    char name[30];
    int age;
    float not;
};

void AddStudent() {
    FILE *fp = fopen("student.txt", "a");
    struct Studentt s;

    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    printf("Ogrenci No: ");
    scanf("%d", &s.no);

    printf("Ogrenci Adi: ");
    scanf("%s", s.name);

    printf("Ogrenci Yasi: ");
    scanf("%d",&s.age);

    printf("Notu: ");
    scanf("%f", &s.not);

    fprintf(fp, "%d %s %d %.2f\n", s.no,s.name,s.age,s.not);
    fclose(fp);

    printf("Ogrenci eklendi.\n");
}

void ListStudent() {
    FILE *fp = fopen("student.txt", "r");
    struct Studentt s;

    if (fp == NULL) {
        printf("Kayit bulunamadi.\n");
        return;
    }

    printf("\n--- OGRENCI LISTESI ---\n");
    while (fscanf(fp, "%d %s %d %f", &s.no,s.name,&s.age,&s.not) != EOF) {
        printf("No: %d | Ad: %s | Yas: %d | Not: %.2f\n",s.no,s.name,s.age,s.not);
    }
    fclose(fp);
}

void DeleteStudent(){   // silme işlemi geçici dosya ile
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Studentt s;
    int deleteNo;
    int found = 0;
    if (fp == NULL || temp == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    printf("Silinecek ogrenci numarasi: ");
    scanf("%d", &deleteNo);

    while (fscanf(fp, "%d %s %d %f",&s.no,s.name,&s.age,&s.not) != EOF) {
        if (s.no == deleteNo) {
            found = 1;
        } else {
            fprintf(temp, "%d %s %d %.2f\n",s.no,s.name,s.age,s.not);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found) {
        printf("Ogrenci silindi.\n");
    } else {
        printf("Ogrenci bulunamadi.\n");
    }
}

void Average() {
    FILE *fp = fopen("student.txt", "r");
    struct Studentt s;
    float toplam = 0;
    int sayac = 0;

    if (fp == NULL) {
        printf("Dosya bulunamadi.\n");
        return;
    }

    while (fscanf(fp, "%d %s %d %f",&s.no,s.name,&s.age,&s.not) != EOF) {
        toplam += s.not;
        sayac++;
    }

    fclose(fp);

    if (sayac == 0) {
        printf("Kayit yok.\n");
    } else {
        printf("Not Ortalamasi: %.2f\n", toplam / sayac);
    }
}


int main()
{
    int choose;
    do{
        printf("\n--- MENU ---\n");
        printf("1- Ogrenci Ekle\n");
        printf("2- Ogrenci Listele\n");
        printf("3- Ogrenci Sil\n");
        printf("4- Ortalama Hesapla\n");
        printf("0- Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &choose);

        switch (choose) {
            case 1:
                AddStudent();
                break;
            case 2:
                ListStudent();
                break;
            case 3:
                DeleteStudent();
                break;
            case 4:
                Average();
                break;
            case 0:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Hatali secim!\n");
        }

    }while(choose != 0);

    return 0;
}
