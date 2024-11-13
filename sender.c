#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // Linux'ta uyku ve kapatma işlemleri için
#include <arpa/inet.h>      // inet_addr ve sockaddr_in için
#include <sys/socket.h>     // soket işlemleri için

int main() {
    int s;                         // UDP soket tanımlama
    struct sockaddr_in server;     // Sunucu (alıcı) adres bilgilerini saklama yapısı
    char *message = "GOOSE message\n"; // Gönderilecek mesaj

    // UDP soketi oluşturma
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { // SOCK_DGRAM parametresi, UDP soketi oluşturur
        printf("Could not create socket.\n");
        return 1;
    }

    // Sunucu (alıcı) IP adresi ve port bilgilerini ayarlama
    server.sin_addr.s_addr = inet_addr("RECEIVER_IP_ADDRESS"); // Hedef IP adresi (Linux sanal makinesinin IP'si)
    server.sin_family = AF_INET;                        // IPv4 protokolü kullanıldığını belirtir
    server.sin_port = htons(102);                       // Hedef port numarası, 102 GOOSE için yaygın olarak kullanılır

    // Sonsuz döngüde mesaj gönderme
    while (1) {
        // sendto() ile UDP paketi gönderilir
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf("Message send failed.\n");
            return 1;
        }
        printf("Message sent: %s\n", message); // Başarıyla gönderilen mesaj ekrana yazdırılır

        // Her gönderimden sonra 3 saniye bekleme
        sleep(3); // Linux'ta sleep fonksiyonu saniye cinsindendir
    }

    // Soketi kapatma
    close(s);

    return 0;
}
