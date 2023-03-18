#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_CMD_LEN 256

char *urls[] = {"google.com", "amazon.com"};
int num_urls = 2;

void ping(char *url)
{
    char cmd[MAX_CMD_LEN];
    snprintf(cmd, MAX_CMD_LEN, "ping -c 1 %s > /dev/null", url);
    system(cmd);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    while (1) {
        int url_index = rand() % num_urls;
        char *url = urls[url_index];
        ping(url);

        int sleep_time = rand() % 10 + 1;
        sleep(sleep_time);
    }

    return 0;
}
