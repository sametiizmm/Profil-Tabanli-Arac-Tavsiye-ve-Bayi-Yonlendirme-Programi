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
            break; // Gecerli bir giris yapildiysa döngüden cikilir
        } else {
            // Hatali giris durumunda kullanici uyarilir ve hatali giris temizlenir
            printf("Hatali giriþ! Lütfen geçerli bir tam sayi giriniz.\n");
            while (getchar() != '\n'); // Hatali girisi temizle
        }
    }

    return result;
}

// Kullanici profili girisini saglayan fonksiyon
void kullaniciProfiliGiris(struct KullaniciProfil *profil) {
    // Kullanýcidan cesitli bilgiler alinir
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
        printf("Hatali giriþ! Lütfen geçerli deðerler giriniz.\n");
        kullaniciProfiliGiris(profil); // Hatali giris durumunda tekrar giris yapilmasini iste
    }
}

// Kullanici bilgilerini yazdiran fonksiyon
void kullaniciBilgileriniYazdir(struct KullaniciProfil *profil, struct tm *tm) {
    printf("\nKullanici Bilgileri:\n");
    printf("Ad: %s\n", profil->ad);
    printf("Doðum Yýlý: %d\n", profil->yil);
    printf("Sürücü Yaþý: %d\n", profil->surucuYasi);

    int surucuTecrubeYili = tm->tm_year + 1900 - profil->ehliyetYili;
    printf("Ehliyet Alma Yýlý: %d\n", profil->ehliyetYili);
    printf("Sürücü Tecrübesi: %d\n", surucuTecrubeYili);
    printf("Guvenlik Önemi: %d\n", profil->guvenlikOnem);
}

// Arac önerilerini gösteren fonksiyon
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

// Satis ofislerini gösteren fonksiyon
void satisOfisleriGoster(struct Bayiler *satisOfisleri, int ofisSayisi) {
    printf("\nIlgi Satýþ Ofisleri:\n");
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
        printf("\nSiz yeni bir sürücüsünüz. Ýlk aracinizi secerken dikkatli olun!\n");
        aracOnerileriGoster(araclar1, aracSayisi1);
    } else if (surucuTecrubeYili >= 4) {
        printf("\nSiz deneyimli bir sürücüsünüz. Ýstediðiniz araci seçebilirsiniz.\n");
        aracOnerileriGoster(araclar1, aracSayisi1);
        aracOnerileriGoster(araclar2, aracSayisi2);
    }

    struct Bayiler satisOfisleri[] = {
        {"Borusan Oto", "Adres: Poligon Mah. Sarýyer Cad. No. 77 Sarýyer Ýstanbul"},
        {"Ford Bayisi", "Adres: Örnek Mah. Örnek Cad. No. 2 Örnek Ýstanbul"},
        {"Honda Satýþ Ofisi", "Adres: Örnek Mah. Örnek Cad. No. 3 Örnek Ýstanbul"},
        {"Mercedes-Benz Sarýyer Bayisi", "Adres: Sarýyer Mah. Mercedes Cad. No. 10 Sarýyer Ýstanbul"},
        // ... Daha fazla satýs ofisi eklenebilir
    };

    int ofisSayisi = sizeof(satisOfisleri) / sizeof(satisOfisleri[0]);
    satisOfisleriGoster(satisOfisleri, ofisSayisi);

    return 0;
}

