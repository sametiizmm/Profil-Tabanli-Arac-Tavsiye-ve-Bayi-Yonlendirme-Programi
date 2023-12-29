#include <stdio.h>  // giris-cikis islemleri icin
#include <string.h> // dizi islemleri icin
#include <time.h>   // zaman islemleri icin kullanilirlar

// Kullanici Profili Yapisi
struct KullaniciProfil {
    char ad[50];
    int yil;
    int surucuYasi;
    int ehliyetYili;
    char meslek[50];
    int guvenlikOnem;
};

// Arac Bilgisi Yapisi
struct AracBilgisi {
    char marka[50];
    char model[50];
    int UretimYili;
    float fiyat;
    int kazaRiski;
};

// Bayi Bilgisi Yapisi
struct Bayiler {
    char bayiAdi[50];
    char bayiAdres[100];
};

// Kullanicinin dogru formatta giris yapmasini saglayan fonksiyon
int girisDenetimi() {
    int result;

    while (1) {
        // Kullanicidan tam sayi girisi istenir
        printf("Lutfen bir tam sayi giriniz: ");

        // Kullanicinin girisi scanf ile alinir
        if (scanf("%d", &result) == 1) {
            break; // Gecerli bir giris yapildiysa d�ng�den cikilir
        } else {
            // Hatali giris durumunda kullanici uyarilir ve hatali giris temizlenir
            printf("Hatali giri�! L�tfen ge�erli bir tam sayi giriniz.\n");
            while (getchar() != '\n'); // Hatali girisi temizle
        }
    }

    return result;
}

// Kullanici profili girisini saglayan fonksiyon
void kullaniciProfiliGiris(struct KullaniciProfil *profil) {
    // Kullan�cidan cesitli bilgiler alinir
    printf("Adiniz: ");
    scanf("%s", profil->ad);

    printf("Dogum yiliniz: ");
    profil->yil = girisDenetimi();

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    profil->surucuYasi = tm.tm_year + 1900 - profil->yil;

    printf("Ehliyet alma yiliniz: ");
    profil->ehliyetYili = girisDenetimi();

    // Meslek sorma islemi kaldirildi

    printf("Guvenlik sizin icin ne kadar onemli? (1-10 arasi) ");
    profil->guvenlikOnem = girisDenetimi();

    // Gecerli bir giris yapildigini kontrol et
    if (!(profil->surucuYasi > 0 && profil->ehliyetYili > 0 && profil->guvenlikOnem >= 1 && profil->guvenlikOnem <= 10)) {
        printf("Hatali giri�! L�tfen ge�erli de�erler giriniz.\n");
        kullaniciProfiliGiris(profil); // Hatali giris durumunda tekrar giris yapilmasini iste
    }
}

// Kullanici bilgilerini yazdiran fonksiyon
void kullaniciBilgileriniYazdir(struct KullaniciProfil *profil, struct tm *tm) {
    printf("\nKullanici Bilgileri:\n");
    printf("Ad: %s\n", profil->ad);
    printf("Do�um Y�l�: %d\n", profil->yil);
    printf("S�r�c� Ya��: %d\n", profil->surucuYasi);

    int surucuTecrubeYili = tm->tm_year + 1900 - profil->ehliyetYili;
    printf("Ehliyet Alma Y�l�: %d\n", profil->ehliyetYili);
    printf("S�r�c� Tecr�besi: %d\n", surucuTecrubeYili);
    printf("Guvenlik �nemi: %d\n", profil->guvenlikOnem);
}

// Arac �nerilerini g�steren fonksiyon
void aracOnerileriGoster(struct AracBilgisi *aracListesi, int aracSayisi) {
    printf("\nOnerilen Araclar:\n");
    for (int i = 0; i < aracSayisi; ++i) {
        printf("%d. Arac:\n", i + 1);
        printf("Marka: %s\n", aracListesi[i].marka);
        printf("Model: %s\n", aracListesi[i].model);
        printf("Yil: %d\n", aracListesi[i].UretimYili);
        printf("Fiyat: %.2f\n", aracListesi[i].fiyat);
        printf("Kaza Riski: %d\n", aracListesi[i].kazaRiski);
        printf("\n");
    }
}

// Satis ofislerini g�steren fonksiyon
void satisOfisleriGoster(struct Bayiler *satisOfisleri, int ofisSayisi) {
    printf("\nIlgi Sat�� Ofisleri:\n");
    for (int i = 0; i < ofisSayisi; ++i) {
        printf("%d. Ofis:\n", i + 1);
        printf("Bayi Adi: %s\n", satisOfisleri[i].bayiAdi);
        printf("%s\n", satisOfisleri[i].bayiAdres);
        printf("\n");
    }
}

// Ana program
int main() {
    struct KullaniciProfil kullanici;
    kullaniciProfiliGiris(&kullanici);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    kullaniciBilgileriniYazdir(&kullanici, &tm);

    struct AracBilgisi araclar1[] = {
        {"Toyota", "Corolla", 2023, 50000.0, 3},
        {"Honda", "Civic", 2021, 60000.0, 2},
        {"Ford", "Focus", 2020, 70000.0, 1},
        // ... Daha fazla arac eklenebilir
    };

    int aracSayisi1 = sizeof(araclar1) / sizeof(araclar1[0]);

    struct AracBilgisi araclar2[] = {
        {"Mercedes", "E-Class", 2019, 80000.0, 4},
        {"BMW", "3 Series", 2018, 90000.0, 5},
        {"Audi", "A4", 2022, 85000.0, 3},
        // ... Daha fazla arac eklenebilir
    };

    int aracSayisi2 = sizeof(araclar2) / sizeof(araclar2[0]);
    int surucuTecrubeYili = tm.tm_year + 1900 - kullanici.ehliyetYili;

    if (surucuTecrubeYili <= 3) {
        printf("\nSiz yeni bir s�r�c�s�n�z. �lk aracinizi secerken dikkatli olun!\n");
        aracOnerileriGoster(araclar1, aracSayisi1);
    } else if (surucuTecrubeYili >= 4) {
        printf("\nSiz deneyimli bir s�r�c�s�n�z. �stedi�iniz araci se�ebilirsiniz.\n");
        aracOnerileriGoster(araclar1, aracSayisi1);
        aracOnerileriGoster(araclar2, aracSayisi2);
    }

    struct Bayiler satisOfisleri[] = {
        {"Borusan Oto", "Adres: Poligon Mah. Sar�yer Cad. No. 77 Sar�yer �stanbul"},
        {"Ford Bayisi", "Adres: �rnek Mah. �rnek Cad. No. 2 �rnek �stanbul"},
        {"Honda Sat�� Ofisi", "Adres: �rnek Mah. �rnek Cad. No. 3 �rnek �stanbul"},
        {"Mercedes-Benz Sar�yer Bayisi", "Adres: Sar�yer Mah. Mercedes Cad. No. 10 Sar�yer �stanbul"},
        // ... Daha fazla sat�s ofisi eklenebilir
    };

    int ofisSayisi = sizeof(satisOfisleri) / sizeof(satisOfisleri[0]);
    satisOfisleriGoster(satisOfisleri, ofisSayisi);

    return 0;
}

