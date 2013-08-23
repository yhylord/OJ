#include <cctype>
#include <cstdio>
#include <cstring>

const char dic[][11] = {
"a",
"i",
"an",
"as",
"am",
"if",
"or",
"to",
"is",
"he",
"it",
"in",
"of",
"on",
"my",
"we",
"so",
"do",
"go",
"us",
"me",
"be",
"was",
"can",
"our",
"her",
"his",
"him",
"did",
"are",
"she",
"you",
"sad",
"but",
"say",
"and",
"run",
"cat",
"dog",
"the",
"red",
"set",
"off",
"has",
"now",
"bad",
"out",
"far",
"fat",
"use",
"why",
"how",
"who",
"for",
"this",
"that",
"them",
"does",
"they",
"many",
"were",
"name",
"your",
"what",
"like",
"hate",
"love",
"whom",
"come",
"blue",
"when",
"easy",
"hard",
"test",
"talk",
"walk",
"take",
"case",
"good",
"into",
"have",
"last",
"here",
"will",
"file",
"whose",
"would",
"there",
"their",
"below",
"under",
"first",
"black",
"where",
"white",
"apple",
"happy",
"funny",
"sunny",
"monkey",
"around",
"please",
"config",
"sample",
"yellow",
"orange",
"purple",
"window",
"teacher",
"whether",
"weather"
};

const int MAXL = 5555;

char buf[MAXL], cur[MAXL], word[MAXL], ans[MAXL];

inline int calc() {
    int ret = 0;
    for (int i = 0; cur[i]; ) {
        int j = i, len = 0;
        for (; cur[j] && !isalpha(cur[j]) && cur[j] != '\''; ++j);
        if (!cur[j])
            break;
        bool got = false;
        for (; cur[j] && (isalpha(cur[j]) || cur[j] == '\''); ++j, ++len) {
            word[len] = isupper(cur[j]) ? cur[j] - 'A' + 'a' : cur[j];
            if (word[len] == 'a' || word[len] == 'e' || word[len] == 'i' || word[len] == 'o' || word[len] == 'u')
                got = true;
        }
        word[len] = 0;
        if (got)
            ++ret;
        got = false;
        for (int k = 0; !got && k < 111; ++k)
            if (!strcmp(word, dic[k]))
                got = true;
            else if (len > 2 && (word[len - 1] == 'd' && word[len - 2] == 'e' || word[len - 1] == 's' && word[len - 2] == '\'' || word[len - 1] == 'm' && word[len - 2] == '\'')) {
                ++ret, word[--len] = 0, word[--len] = 0;
                if (!strcmp(word, dic[k]))
                    got = true, --ret;
            }
            else if (len > 3 && word[len - 1] == 'g' && word[len - 2] == 'n' && word[len - 3] == 'i') {
                ++ret, word[--len] = 0, word[--len] = 0, word[--len] = 0;
                if (!strcmp(word, dic[k]))
                    got = true, --ret;
            }
        if (got)
            ret += 20;
        i = j;
    }
    return ret;
}

inline void work() {
    gets(buf);
    int mx = -1;
    for (int i = 0, t; i < 26; ++i) {
        int j = 0;
        for (; buf[j]; ++j)
            if (isupper(buf[j]))
                cur[j] = (buf[j] - 'A' + i) % 26 + 'A';
            else if (islower(buf[j]))
                cur[j] = (buf[j] - 'a' + i) % 26 + 'a';
            else
                cur[j] = buf[j];
        cur[j] = 0;
        if ((t = calc()) > mx) {
            mx = t;
            strcpy(ans, cur);
        }
    }
    puts(ans);
}

int main() {
    for (int i = 0; i < 10; ++i)
        work();
    return 0;
}
