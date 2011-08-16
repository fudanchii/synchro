#include "bstrlib.h"
#include "utils.h"


bstring do_concat(int num, ...) {
    bstring lval = bfromcstr("");
    va_list arg;

    va_start(arg, num);
    while (num--) {
        bstring tstr = va_arg(arg, bstring);
        int chlen = lval->slen + tstr->slen;
        if (lval->mlen < chlen)
            balloc(lval, chlen);
        bconcat(lval, tstr);
    }
    va_end(arg);
    return lval;
}
