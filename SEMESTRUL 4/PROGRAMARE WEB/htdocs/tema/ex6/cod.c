#include <stdio.h>
#include <stdlib.h>

void print_env(const char *name, const char *label) {
    char *value = getenv(name);
    if (value)
        printf("<b>%s</b>: %s<br>\n", label, value);
    else
        printf("<b>%s</b>: (nu este setat)<br>\n", label);
}

int main() {
    printf("Content-type: text/html; charset=UTF-8\n\n");
    printf("<html><body><h2>Antete HTTP selectate</h2>\n");

    print_env("ACCEPT", "Accept");
    print_env("ACCEPT_ENCODING", "Accept-Encoding");
    print_env("ACCEPT_LANGUAGE", "Accept-Language");
    print_env("CONNECTION", "Connection");
    print_env("HOST", "Host");
    print_env("SEC_CH_UA", "Sec-CH-UA");
    print_env("SEC_CH_UA_MOBILE", "Sec-CH-UA-Mobile");
    print_env("SEC_CH_UA_PLATFORM", "Sec-CH-UA-Platform");
    print_env("SEC_FETCH_DEST", "Sec-Fetch-Dest");
    print_env("SEC_FETCH_MODE", "Sec-Fetch-Mode");
    print_env("SEC_FETCH_SITE", "Sec-Fetch-Site");
    print_env("SEC_FETCH_USER", "Sec-Fetch-User");
    print_env("UPGRADE_INSECURE_REQUESTS", "Upgrade-Insecure-Requests");
    print_env("USER_AGENT", "User-Agent");
    print_env("X_FORWARDED_FOR", "X-Forwarded-For");
    print_env("X_FORWARDED_HOST", "X-Forwarded-Host");
    print_env("X_FORWARDED_SERVER", "X-Forwarded-Server");

    printf("</body></html>\n");
    return 0;
}