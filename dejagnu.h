/* 
 *   Copyright (C) 2000, 2001 Free Software Foundation, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __DEJAGNU_H__
#define __DEJAGNU_H__

#include <stdio.h>

static int passed;
static int failed;
static int untest;
static int unresolve;

inline void
pass (const char *s) {
    passed++;
    printf ("\tPASSED: %s\n", s);
}

inline void
fail (const char *s) {
    failed++;
    printf ("\tFAILED: %s\n", s);
}

inline void
untested (const char *s) {
    untest++;
    printf ("\tUNTESTED: %s\n", s);
}

inline void
unresolved (const char *s) {
    unresolve++;
    printf ("\tUNRESOLVED: %s\n", s);
}

inline void
totals (void) {
    printf ("\nTotals:\n");
    printf ("\t#passed:\t\t%d\n", passed);
    printf ("\t#failed:\t\t%d\n", failed);
    if (untest)
        printf ("\t#untested:\t\t%d\n", untest);
    if (unresolve)
        printf ("\t#unresolved:\t\t%d\n", unresolved);
}

#ifdef __cplusplus

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <strstream>

char *outstate[] = {
    "FAILED: ",
    "PASSED: ",
    "UNTESTED: ",
    "UNRESOLVED: "
};

#if 0
extern ios& __iomanip_testout (ios&, int);
inline smanip<int> testout (int n) {
    return smanip<int> (__iomanip_testout, n);
}
ios & __iomanip_testout (ios& i, int x) {
    return i;
}

template<class T>
class OMANIP {
 private:
    T i;
    ostream &(*f)(ostream&, T);
 public:
    OMANIP(ostream& (*ff)(ostream&, T), T ii) : f(ff), i(ii) {
    }
    friend ostream operator<<(ostream& us, OMANIP& m) {
      return m.f(os,m.i);
    }
};

ostream&
freakout(ostream& os, int x) {
    return os << "FREAKOUT" ;
//    return x << "TESTOUT " << x ;
}

OMANIP<int> testout(int i) {
    return OMANIP<int>(&freakout,i);
}
#endif

char *testout (int x) {
    const int len = 128;
    static char buf[len];
    static ostrstream oss(buf, len, ios::out);
    oss.seekp(ios::beg);
    oss << outstate[x] << ends;
    return buf;
}

enum teststate {FAILED, PASSED,UNTESTED,UNRESOLVED} laststate;

class TestState {
 private:
    teststate laststate;
    string lastmsg;
 public:
    TestState(void) {
        passed = 0;
        failed = 0;
        untest = 0;
        unresolve = 0;
    }
    ~TestState(void) {
        totals();
    };

    void testrun (bool b, string s) {
        if (b)
            pass (s);
        else
            fail (s);
    }

    void pass (string s) {
        passed++;
        laststate = PASSED;
        lastmsg = s;
        cout << "\t" << testout(PASSED) << s << endl;
    }
    void pass (const char *c) {
        string s = c;
        pass (s);
    }

    void fail (string s) {
        failed++;
        laststate = FAILED;
        lastmsg = s;
        cout << "\t" << testout(FAILED) << s << endl;
    }
    void fail (const char *c) {
        string s = c;
        fail (s);
    }

    void untested (string s) {
        untest++;
        laststate = UNTESTED;
        lastmsg = s;
        cout << "\t" << testout(UNTESTED) << s << endl;
    }
    void untested (const char *c) {
        string s = c;
        untested (s);
    }

    void unresolved (string s) {
        unresolve++;
        laststate = UNRESOLVED;
        lastmsg = s;
        cout << "\t" << testout(UNRESOLVED) << s << endl;
    }
    void unresolved (const char *c) {
        string s = c;
        unresolved (s);
    }

    void totals (void) {
        cout << "\t#passed:\t\t" << passed << endl;
        cout << "\t#failed:\t\t" << failed << endl;
        if (untest)
            cout << "\t#untested:\t\t" << untest << endl;
        if (unresolve)
            cout << "\t#unresolved:\t\t" << unresolve << endl;
    }

    // This is so thjis class can be printed in an ostream.
    friend ostream & operator << (ostream &os, TestState& t) {
        return os << "\t" << outstate[t.laststate] << t.lastmsg ;
    }

    int GetState(void) {
        return laststate;
    }
    string GetMsg(void) {
        return lastmsg;
    }
};

#endif		// __cplusplus
#endif          // _DEJAGNU_H_


