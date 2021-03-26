#include "../scripts/checkRecDigiTime.C"

void drawRecDigiTime(const char* filename)
{
  checkRecDigiTime(filename,"koalasim","KoaRecDigi","KoaFwdDigi",false,100,0,10,4000,0,400,10,25,10,25,-1,2,1000,1000,1000,1000);
}
