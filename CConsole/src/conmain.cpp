/*
    ###############################################
    conmain.cpp
    CConsole demo program
    Made by PR00F88
    EMAIL : PR0o0o0o0o0o0o0o0o0o0oF88@gmail.com
    ################################################
*/

#include "CConsole.h"

#include <stdlib.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>


#define CON_TITLE "CConsole demo program"


#pragma warning(disable:4100)  /* unreferenced formal parameter */


static void TestDefaultColors(CConsole& con)
{
    con.OLn("Simple text.");
    con.OLn("%s", "This is a string.");
    con.OLn("Signed integral value: %d", -5);
    con.OLn("Unsigned integral value: %u", 5);
    con.OLn("Floating point value: %f", 5.30215f);
    con.OLn("Boolean value: %b", false);
    con.OLn("");
}

static void TestErrorMode(CConsole& con)
{
    con.OLn("Switching to error-mode now...");
    con.EOn();

    con.OLn("Simple text.");
    con.OLn("%s", "This is a string.");
    con.OLn("Signed integral value: %d", -5);
    con.OLn("Unsigned integral value: %u", 5);
    con.OLn("Floating point value: %f", 5.30215f);
    con.OLn("Boolean value: %b", false);
    con.OLn("");

    con.OLn("Switching back to normal mode now ...");
    con.EOff();

    con.OLn("Simple text.");
    con.OLn("%s", "This is a string.");
    con.OLn("Signed integral value: %d", -5);
    con.OLn("Unsigned integral value: %u", 5);
    con.OLn("Floating point value: %f", 5.30215f);
    con.OLn("Boolean value: %b", false);
    con.OLn("");
}

static void TestCustomColors(CConsole& con)
{
    con.SetFGColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, "999999");
    con.SetIntsColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "FFFF00");
    con.SetStringsColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, "FFFFFF");
    con.SetFloatsColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "FFFF00");
    con.SetBoolsColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "00FFFF");
    con.OLn("Colors changed!");

    con.OLn("Simple text.");
    con.OLn("%s", "This is a string.");
    con.OLn("Signed integral value: %d", -5);
    con.OLn("Unsigned integral value: %u", 5);
    con.OLn("Floating point value: %f", 5.30215f);
    con.OLn("Boolean value: %b", false);
    con.OLn("");

    con.OLn("Switching to error-mode now...");
    con.EOn();

    con.OLn("Simple text.");
    con.OLn("%s", "This is a string.");
    con.OLn("Signed integral value: %d", -5);
    con.OLn("Unsigned integral value: %u", 5);
    con.OLn("Floating point value: %f", 5.30215f);
    con.OLn("Boolean value: %b", false);
    con.OLn("");

    con.OLn("Switching back to normal mode now ...");
    con.EOff();

    con.OLn("Simple text.");
    con.OLn("%s", "This is a string.");
    con.OLn("Signed integral value: %d", -5);
    con.OLn("Unsigned integral value: %u", 5);
    con.OLn("Floating point value: %f", 5.30215f);
    con.OLn("Boolean value: %b", false);
    con.OLn("");
}

static void TestOperatorStreamOut(CConsole& con)
{
    con << "Using operator<<, this is a string, and this is a boolean: " << false << ", this is an integer: " << 16 << CConsole::FormatSignal::NL;
    con << "This is already a new line";
    con << " , and this is still the same line" << CConsole::FormatSignal::NL;
    con << "This is a new line with a float: " << 4.67f << CConsole::FormatSignal::NL;
    con << CConsole::FormatSignal::E << "This is error mode " << CConsole::FormatSignal::S << "but this is success mode." << CConsole::FormatSignal::NL;
    con << CConsole::FormatSignal::N << "This is normal mode again." << CConsole::FormatSignal::NL;
    con << CConsole::FormatSignal::NL;
}

static void TestModuleLoggingSet(CConsole& con)
{
    con.SetLoggingState(CON_TITLE, false);
    con.OLn("You are not supposed to see this, line %d!", __LINE__);
    con << "You are not supposed to see this either, line " << __LINE__ << "!" << CConsole::FormatSignal::NL;

    con.SetLoggingState("4LLM0DUL3S", true);
    con.OLn("You should see this due to all debugs are turned on now, line %d", __LINE__);
    con << "You should see this too due to all debugs are turned on now, line " << __LINE__ << CConsole::FormatSignal::NL;
    con.SetLoggingState("4LLM0DUL3S", false);

    con.OLn("You are not supposed to see this at line %d!", __LINE__);
    con.EOLn("You should see this due to being in error mode, line %d", __LINE__);
    // notice that we pass NL before passing N, otherwise in reverse order no newline will be added, it will be also ignored since module logging is not enabled
    con << CConsole::FormatSignal::E << "You should also see this due to error mode, line " << __LINE__ << CConsole::FormatSignal::NL << CConsole::FormatSignal::N;

    con.OLn("You are not supposed to see this at line %d!", __LINE__);
    con.SOLn("You should not see this success log, line %d", __LINE__);
    con << CConsole::FormatSignal::S << "You should not see this success log, line " << __LINE__ << CConsole::FormatSignal::NL << CConsole::FormatSignal::N;

    con.SetLoggingState(CON_TITLE, true);
    con.SOLn("You supposed to see this success log, line %d", __LINE__);
    con << CConsole::FormatSignal::S << "You supposed to see this success log, line " << __LINE__ << CConsole::FormatSignal::NL << CConsole::FormatSignal::N;
    con.OLn("");
}

int WINAPI WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPSTR lpCmdLine, const int nCmdShow)
{
    CConsole& con = CConsole::getConsoleInstance(CON_TITLE);

    con.Initialize(CON_TITLE, true);
    con.SetLoggingState(CON_TITLE, true); // if we dont explicitly enable logging for CON_TITLE module, only errors will be visible
    con.OLn(CON_TITLE);
    con.L();
    con.OLn("");

    TestDefaultColors(con);
    TestErrorMode(con);
    TestCustomColors(con);
    TestOperatorStreamOut(con);
    TestModuleLoggingSet(con);

    system("pause");

    return 0;

} // WinMain()
