#ifndef INCLUDE_H
#define INCLUDE_H

#define DEBUG_MODE
#define PROJECT_PATH "/home/ashwin/Desktop/projectsura/"
#define NO_OF_CAMERAS 4
#define NO_OF_ACTIVITIES 3
#define NO_OF_PERSONS 20
#define MAX_ROI 10

#include<cstdlib>
using namespace std;

#ifndef DEBUG_MODE
#define PRINT(x)
#define PRINTVAL(x)
#else
#define PRINT(x) cout << x << endl;
#define PRINTVAL(x) cout << #x << ": " << x << endl;
#endif

#define ASSERT(x) if (!(x)) { cout << "ERROR! Assert " << #x << " failed" << " on line " << __LINE__  << " in file " << __FILE__ << endl; exit(1);}

#endif
