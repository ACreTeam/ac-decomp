extern "C" char* __copy(char* r3, char* r4, unsigned long r5) {
    if (!r3)
        return r3;
    if (!r5)
        return r3;
    char* d = (char*)r3;
    do {
        *d++ = *r4++;
    } while (--r5);
    return r3;
}
