#include <string.h>
#include <stdarg.h>
#include <fstream>
#include "logger.hpp"

using namespace std;

unsigned int LFILE::note = 0;

LFILE::LFILE()
{
    memset(file_name, 0, sizeof(file_name));
    fhdl = NULL;
}

LFILE::LFILE(const char* name, const char* text)
{
    memset(file_name, 0, sizeof(file_name));

    fhdl = new fstream;
    fhdl->open(name, ios::binary | ios::out | ios::trunc);
    if (fhdl->fail()) {
        fhdl->close();
        delete fhdl;
        fhdl = NULL;
        return;
    }

    sprintf((char*)file_name, "%s", name);

    if (text) {
        fhdl->write((char*)text, strlen(text));
        if(fhdl->fail()) {
            fhdl->close();
            delete fhdl;
            fhdl = NULL;
        }
    }
}

LFILE::~LFILE()
{
    if (fhdl) {
        fhdl->close();
        delete fhdl;
    }
}

LFILE::LFILE(const LFILE& m)
{
    memcpy(file_name, m.file_name, sizeof(file_name));

    fhdl = new fstream;
    fhdl->open(file_name, ios::binary | ios::out | ios::trunc);

    if (fhdl->fail()) {
        fhdl->close();
        delete fhdl;
        fhdl = NULL;
    }
}

LFILE& LFILE::operator =(const LFILE& m)
{
    if (&m == this) {
        return *this;
    }

    if (fhdl) {
        fhdl->close();
        delete fhdl;
    }

    memcpy(file_name, m.file_name, sizeof(file_name));

    fhdl = new fstream;
    fhdl->open(file_name, ios::binary | ios::out | ios::trunc);

    if (fhdl->fail()) {
        fhdl->close();
        delete fhdl;
        fhdl = NULL;
    }

    return *this;
}

void LFILE::addf(const char* text, ...)
{
    va_list argptr;
    char tmp1[1024];
    char tmp2[1024];

    va_start(argptr, text);
    vsprintf(tmp1, text, argptr);
    va_end(argptr);

    sprintf(tmp2,"%s", tmp1);
    add(tmp2);
}

void LFILE::add(const char* text)
{
    char line[1024];
    char nnote[128];

    if (file_name[0] == '\0') {
        return;
    }

    if (!fhdl) {
        fhdl = new fstream;
        fhdl->open((char*)file_name, ios::binary | ios::out | ios::app);
        if(fhdl->fail()) {
            fhdl->close();
            delete fhdl;
            fhdl = NULL;
            return;
        }
    }


    memset(nnote, 0, 128);
    sprintf(nnote, " <%d> ", note);
    fhdl->write((char*)nnote, strlen(nnote));
    note++;
    memset(line, 0, 1024);
    sprintf(line, "%s", text);

    fhdl->write((char*)line, strlen(line));
    if(fhdl->fail()) {
        fhdl->close();
        delete fhdl;
        fhdl = NULL;
    }
}

void LFILE::deny()
{
    if (fhdl) {
        fhdl->close();
        delete fhdl;
    }

    memset(file_name, 0, sizeof(file_name));
    fhdl = NULL;
}

LFILE DFLOG("log.txt", "PROJECT\tDark Flame\n\n");
