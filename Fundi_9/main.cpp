#include <iostream>
#include <sstream>
#include <vector>
#include "Logger.h"

int main(int argc, char** argv)
{
    LogBuilder builder;
    builder.addLogTarget("/home/ayttekao/CLionProjects/Fundi/Fundi_9/test.txt", FATAL);
    builder.addLogTarget("stdout");
    builder.addTargetFromJson(argv[1]);

    Logger* log = builder.createLogger();
    builder.addLogTarget("/home/ayttekao/CLionProjects/Fundi/Fundi_9/test.txt", ERROR);
    builder.addLogTarget("/home/ayttekao/CLionProjects/Fundi/Fundi_9/test.txt", WARN);
    builder.addLogTarget("/home/ayttekao/CLionProjects/Fundi/Fundi_9/test.txt", INFO);
    builder.addLogTarget("/home/ayttekao/CLionProjects/Fundi/Fundi_9/test2.txt", DEBUG);

    Logger* log2 = builder.createLogger();
    log->log("HEEEELP", FATAL);
    log->log("Nu ladno ne HELP", ERROR);
    log2->log("THIS IS ХОРОШО", FATAL);

    delete log;
    delete log2;

    return 0;
}
