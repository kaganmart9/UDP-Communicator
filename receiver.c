#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // Linux ağ kütüphanesi
#include <arpa/inet.h>  // IP adreslerini düzenlemek için
#include <unistd.h>     // close() fonksiyonu için
#include <errno.h>      // Hata kontrolü için

int main() {
    int sock;                         // Alıcı UDP soketini temsil eden değişken
    struct sockaddr_in server, client; // Sunucu (dinleyici) ve istemci (gönderici) bilgilerini saklayan yapılar
    char buffer[1024];                // Gelen mesajları saklamak için bir tampon bellek
    socklen_t len = sizeof(client);   // İstemci adresinin boyutunu tutan değişken

    // UDP soketi oluşturma
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { // SOCK_DGRAM parametresi UDP soketi oluşturur
        printf("Socket oluşturulamadı.\n");
        return 1;
    }

    // Sunucu (dinleyici) IP adresi ve port bilgilerini ayarlama
    server.sin_family = AF_INET;            // IPv4 protokolü kullanıldığını belirtir
    server.sin_addr.s_addr = INADDR_ANY;    // Tüm IP adreslerinden gelen bağlantıları kabul eder
    server.sin_port = htons(102);           // Dinlenecek port numarası, 102 numaralı port kullanılıyor

    // Soketi IP adresi ve porta bağlama
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) { // bind() fonksiyonu soketi belirli bir adrese bağlar
        printf("Bağlanılamadı.\n");
        return 1;
    }

    printf("GOOSE mesajı bekleniyor...\n");

    // Sonsuz döngüde mesajları dinleme ve alma
    while (1) {
        // recvfrom() ile UDP paketini alma
        int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client, &len);
        
        if (n == -1) {
            // Hata durumunda hata kodunu ve açıklamasını ekrana yazdır
            printf("Mesaj alınamadı. Hata kodu: %d - %s\n", errno, strerror(errno));
            continue; // Hata durumunda döngünün başına döner
        }

        buffer[n] = '\0'; // Gelen mesajın sonuna null karakter ekleyerek C dizisi olarak sonlandırır
        printf("Mesaj alındı: %s\n", buffer); // Gelen mesajın içeriğini ekrana yazdır
        printf("Alınan mesaj uzunluğu: %d\n", n); // Mesajın uzunluğunu ekrana yazdır
    }

    // Soketi kapatma
    close(sock);

    return 0;
}
