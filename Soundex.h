#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

char getCodeForGroup1(char c) {
    if (strchr("BFPV", c)) return '1';
    if (strchr("CGJKQSXZ", c)) return '2';
    return '0';
}

char getCodeForGroup2(char c) {
    if (strchr("DT", c)) return '3';
    if (c == 'L') return '4';
    return '0';
}

char getCodeForGroup3(char c) {
    if (strchr("MN", c)) return '5';
    if (c == 'R') return '6';
    return '0';
}

char getSoundexCode(char c) {
    c = toupper(c);

    char code = getCodeForGroup1(c);
    if (code != '0') return code;

    return (code = getCodeForGroup2(c)) != '0' ? code : getCodeForGroup3(c);
}

int shouldAddCode(char code, char previousCode) {
    return code != '0' && code != previousCode;
}

void fillRemainingWithZeros(char *soundex, int *sIndex) {
    while (*sIndex < 4) {
        soundex[(*sIndex)++] = '0';
    }
    soundex[4] = '\0';
}

void addCharacterIfValid(char code, char previousCode, char *soundex, int *sIndex) {
    if (shouldAddCode(code, previousCode)) {
        soundex[(*sIndex)++] = code;
    }
}

void processCharacter(const char *name, char *soundex, int *sIndex, int len) {
    for (int i = 1; i < len && *sIndex < 4; i++) {
        char code = getSoundexCode(name[i]);
        addCharacterIfValid(code, soundex[*sIndex - 1], soundex, sIndex);
    }
}

void generateSoundex(const char *name, char *soundex) {
    soundex[0] = toupper(name[0]);
    int sIndex = 1;
    int len = strlen(name);

    // Move the loop and if statement into a helper function
    processCharacter(name, soundex, &sIndex, len);

    fillRemainingWithZeros(soundex, &sIndex);
}

#endif // SOUNDEX_H
