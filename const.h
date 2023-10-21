#ifdef AGV_MCP
const int Magnetic_Board[30] = {3012, 2970, 2910, 2807, 2740, 2672, 2605, 2537, 2470, 2402, 2335, 2267, 2200, 2132, 2065, 1997, 1930, 1862, 1795, 1727, 1660, 1592, 1525, 1450, 1390, 1322, 1265, 1200, 1130, 1060};
#else
const int Magnetic_Board[29] = {753, 736, 719, 702, 685, 668, 651, 634, 616, 599, 582, 565, 547, 530, 514, 497, 480, 462, 445, 427, 410, 393, 376, 359, 342, 324, 307, 290, 272};
#endif
// const int Magnetic_Board[30] = {3012, 2970, 2910, 2807, 2740, 2672, 2605, 2537, 2470, 2402, 2335, 2267, 2200, 2132, 2065, 1997, 1930, 1862, 1795, 1727, 1660, 1592, 1525, 1450, 1390, 1322, 1265, 1200, 1130, 1060};
// const int Magnetic_Board[29]={753,736,719,702,685,668,651,634,616,599,582,565,547,530,514,497,480,462,445,427,410,393,376,359,342,324,307,290,272};
const int ConstAutoMaxSpeed = 2400;  // tốc độ max auto
const int ConstManualMaxSpeed = 500; // tốc độ max manual
const int ConstAutoDecelTime = 30;   // tgian giảm tốc
const int ConstAutoAccelTime = 50;   // tgian tăng tốc
const int ConstEMGDecelTime = 20;    // tgian EMG
const int ConstManualDecelTime = 50;
const int ConstManualAccelTime = 50;