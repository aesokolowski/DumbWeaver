// A.E. Sokolowski Jan 2022 NY, NY, USA

#include "../include/constants/templ.h"

const struct templates templ = {
    .RESP_HEAD = "HTTP/1.1 200 OK\nDate: %sServer: Apache/2.2.14 (Win32)\nLast-Modified: Sun Jan 23 2022 21:33:00\nContent-Length: %d\nContent-Type: text/html\nConnection: Closed\n\n",
    .RESP_BODY = "<html><body style=\"background-color: %s; color: %s;\"><h1 style=\"text-align: center;\">%s</h1></body></html>"
};

