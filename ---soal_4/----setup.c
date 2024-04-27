#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h> // Sertakan file header <time.h> untuk mengakses fungsi-fungsi waktu

#define LOG_FILE_SUFFIX ".log"

// Fungsi untuk menulis ke file log. Ini merupakan bagian dari sistem monitoring yang di rancang untuk pengawasan keamanan dalam lingkungan sistem operasi linux
void tulis_kegiatan_log(const char *user, const char *kegiatan, const char *status) {
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    char log_filename[100];
    FILE *log_file;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%d:%m:%Y-%H:%M:%S", timeinfo);

    sprintf(log_filename, "%s%s", user, LOG_FILE_SUFFIX);
    log_file = fopen(log_filename, "a");
    if (log_file != NULL) {
        fprintf(log_file, "[%s]-%s_%s\n", timestamp, kegiatan, status);
        fclose(log_file);
    } else {
        perror("Error writing to log file");
    }
}

// Fungsi untuk menampilkan proses yang sedang berjalan oleh pengguna tertentu. Ini berguna untuk pemantauan kemanan sistem dan pemecahan masalah 
void tampilkan_proses(const char *user) {
    char command[100];
    sprintf(command, "ps -u %s", user);
    system(command);
}

// Fungsi untuk mengatur pembatasan proses yang dijalankan oleh pengguna.Fitur ini mengizinkan administrator untuk mengotrol perilaku dalam lingkungan sistem oprasi linux
void atur_pembatasan_proses(const char *user, int enable) {
    char command[100];
    sprintf(command, "sudo chmod %s +x /home/%s/*", (enable ? "u-x" : "u+x"), user);
    if (system(command) == -1) {
        perror("Error running chmod command");
    }
}

int main(int argc, char *argv[]) {
    // Kode program untuk mengintegrasikan fungsi-fungsi monitoring keamanan dan pengaturan akses proses akan ditambahkah disini.

    return 0;
}
