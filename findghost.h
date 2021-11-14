#ifndef FINDGHOST_H
#define FINDGHOST_H
#include <bitset>
#include <QString>

using namespace std;

class findGhost
{
public:
    findGhost(int input1, int input2);
    int findLastEvidence(int ghostType, int evid1, int evid2);
    QString printLastGhostEvid();

private:
    int ev1;
    int ev2;
    bitset<20> comGhostsFromEvid(int evid1, int evid2);
    QString findGhostFromNum(int bitpos);
    QString numToEvidString(int num);
};

#endif // FINDGHOST_H
