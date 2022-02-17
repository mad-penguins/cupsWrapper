#include <cups/cups.h>
#include <stdio.h>

char *submitDocument(char *filepath, char* filename) {
    char *result = malloc(256);

    cups_dest_t *dest;
    cupsGetDests(&dest);
    cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, dest);

    int job_id = 0;
    int num_options = 0;
    cups_option_t *options = NULL;

    num_options = cupsAddOption(CUPS_COPIES, "1",
                                num_options, &options);
    num_options = cupsAddOption(CUPS_MEDIA, CUPS_MEDIA_A4,
                                num_options, &options);
    num_options = cupsAddOption(CUPS_SIDES,
                                CUPS_SIDES_TWO_SIDED_PORTRAIT,
                                num_options, &options);

    if (cupsCreateDestJob(CUPS_HTTP_DEFAULT, dest, info,
                          &job_id, filename, num_options,
                          options) == IPP_STATUS_OK)
        printf("Created job: %d\n", job_id);
    else {
        printf("Unable to create job: %s\n", cupsLastErrorString());
        strcpy(result, cupsLastErrorString());
    }



    FILE *fp = fopen(filepath, "rb");
    size_t bytes;
    char buffer[65536];

    if (cupsStartDestDocument(CUPS_HTTP_DEFAULT, dest, info,
                              job_id, filename, CUPS_FORMAT_PDF, num_options, options, 1
    ) == HTTP_STATUS_CONTINUE) {
        while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            if (cupsWriteRequestData(CUPS_HTTP_DEFAULT, buffer, bytes) != HTTP_STATUS_CONTINUE)
                break;
        }

        if (cupsFinishDestDocument(CUPS_HTTP_DEFAULT, dest, info) == IPP_STATUS_OK) {
            puts("Document send succeeded.");
            strcpy(result, "ok");
        }
        else {
            printf("Document send failed: %s\n", cupsLastErrorString());
            strcpy(result, cupsLastErrorString());
        }
    }

    fclose(fp);
    return result;
}
