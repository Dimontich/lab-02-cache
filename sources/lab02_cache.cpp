#include "Investigation.h"

int main()
{
    Investigation investigation;
    investigation.Begin_expirement();

    std::ofstream path_to_report("../reports/report.txt\n");
    investigation.End_expirement(path_to_report);

    return 0;
}