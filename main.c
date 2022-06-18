#include <stdio.h>
#include <ctype.h>

#define N 5000

int main() {
    FILE *fp;
    char text[N];
    int i = 0;
    int shiftCount = 0;
    int wordCount = 0;

    int isAfterSpace = 0; // iterasyonda bakılan karakterden önce boşluk var mı
    int isFirstWord = 1; // ilk kelimeye gelene kadar true, ilk kelimeye gelindikten sonra false

    // dosya açma
    if ((fp = fopen("text.txt", "r")) == NULL) {
        printf("Dosya acma hatasi!");
        return 1;
    }
    // dosya okuma
    fgets(text, N - 1, fp);

    fclose(fp);

    //döngü metnin sonuna ulaşana kadar devam eder
    while (text[i] != '\0') {
        if (isspace(text[i])) {
            // baştaki tüm boşlukların ve art arda gelen boşlukların
            // sayısı shiftCount değişkeninde tutulur
            if (isFirstWord || isAfterSpace) {
                shiftCount++;
            } else {
                isAfterSpace = 1;
            }
        } else {
            // ilk kelime ve her boşluktan sonraki kelime
            // sayısı wordCount değişkeninde tutulur
            if (isFirstWord || isAfterSpace) {
                wordCount++;
                isAfterSpace = 0;
                isFirstWord = 0;
            }
        }

        // şu anki karakter -varsa- öncesindeki gereksiz boşlukların sayısı kadar geri ötelenir
        // ve şu anki yere NULL atanır
        if (shiftCount > 0) {
            text[i - shiftCount] = text[i];
            text[i] = '\0';
        }

        i++;
    }

    // sonda tek boşluk kaldıysa ona NULL atanır
    if (isspace(text[i - shiftCount - 1])) {
        text[i - shiftCount - 1] = '\0';
    }

    printf("Metin toplam %d adet kelime iceriyor.", wordCount);
    printf("\n");
    printf("Metnin temiz hali: <%s>", text);

    return 0;
}