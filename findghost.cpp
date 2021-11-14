#include "findghost.h"


int ev1{};
int ev2{};

findGhost::findGhost(int input1, int input2)
{
    ev1 = input1;
    ev2 = input2;
}

/*
        bitset<Num of Ghosts In Game = 20> ghostEvidDB[7] -
        *NOTE* used from: https://phasmophobia.fandom.com/wiki/Evidence Should match Table
        BIT REPRESENTION:
        *ALSO NOTE* Freezing Temperatures was accidentally selected so it is prioritised in the chart, NOTICE that continuous '1s' in evidDB[2]
        |Demon|Hantu|Jinn|Oni|Onryo|Revenant|Shade|The Twins|Banshee|Goryo|Mare|Myling|Obake|Phantom|Poltergeist|Raiju|Spirit|Wraith|Yokai|Yurei|
            Positional BIT '0': Ghost is not associated with this evidence
            Positional BIT '1': Ghost is associated with this evidence
        [0 - 6]: Type of Evidence (EX: Fingerprints, Ghost Orbs, Freezing Temperatures,...)
        EXAMPLE:
        |FINGERPRINTS| = 11100000011011110000
        |Ghost Orbs|   = 01001100110101001001

*/
bitset<20> findGhost::comGhostsFromEvid(int evid1, int evid2)
{
    bitset<20> evidDB[7] =
    {
        // 0 | Fingerprints
        0b11100000011011110000,
        // 1 |Ghost Orb
        0b01001100110101001001,
        // 2 | Freezing Temperatures
        0b11111111100000000000,
        // 3 | Spirit Box
        0b00001001000100110111,
        // 4 | EMF Level 5
        0b00110011001011001110,
        // 5 | D.O.T.S Projector
        0b00010000111000101011,
        // 6 | Ghost Writing
        0b10000110000110010100
    };
    bitset<20> FingOrb = (evidDB[evid1] & evidDB[evid2]);
    return FingOrb;
}

//Returns QString in '[Ghost Type] - [Evidence] \n' FORMAT
QString findGhost::printLastGhostEvid()
{
    QString allGhostEvid{};
    bitset<20> commonHolder = comGhostsFromEvid(ev1, ev2);
    for (int bitpos = 0; bitpos < 20; bitpos++)
    {
        //Prints all ghosts and their associated last evidence
        if (commonHolder.test(bitpos))
        {
            int lastEvid = findLastEvidence(bitpos, ev1, ev2);
            //cout << "GHOST: " << findGhostFromNum(bitpos) << " LAST EVIDENCE: " << numToEvidString(lastEvid) << "\n"; |OLD Print Code|
            allGhostEvid += findGhostFromNum(bitpos) + " - " + numToEvidString(lastEvid) + "\n";
        }

    }
    return allGhostEvid;
}

/*
    FINDS LAST EVIDENCE BY:
        Using the Ghost Type which is used to go through ghostDB to get 3 pieces of evidence
        Determines the last evidence by ignoring the other two

    Contains GHOST TYPE, EVIDENCE
    Evidence in format 0 - 6
    0 - Fingerprints
    1 - Ghost Orbs
    2 - Freezing Temperatures
    3 - Spirit Box
    4 - EMF Level 5
    5 - D.O.T.S Projector
    6 - Ghost Writing

    REFER TO evidDB for precedent

    Ghost in format of bit position:
    |Demon|Hantu|Jinn|Oni|Onryo|Revenant|Shade|The Twins|Yurei|Banshee|Goryo|Mare|Myling|Obake|Phantom|Poltergeist|Raiju|Spirit|Wraith|Yokai|
    Where Demon is ghostDB[19] & Yokai is ghostDB[0]
*/
int findGhost::findLastEvidence(int ghostType, int evid1, int evid2)
{
    int evid3{};
    for (int i = 0; i < 3; i++)
    {
        int ghostDB[20 /* GHOST TYPE */][3 /* EVIDENCE */] = {
            //Yokai
            {6, 1, 3},

            //Wraith
            {5, 4, 3},

            //Spirit
            {6, 4, 3},

            //Raiju
            {5, 4, 3},

            //Poltergeist
            {6, 0, 1},

            //Phantom
            {5, 0, 3},

            //Obake
            {4, 1, 0},

            //Myling
            {6, 4, 0},

            //Mare
            {6, 1, 3},

            //Goryo
            {5, 4, 0},

            //Banshee
            {5, 1, 0},

            //Yurei
            {5, 1, 2},

            //The Twins
            {4, 2, 3},

            //Shade
            {6, 4, 2},

            //Revenant
            {6, 1, 2},

            //Onryo
            {1, 2, 3},

            //Oni
            {5, 4, 2},

            //Jinn
            {4, 0, 2},

            //Hantu
            {1, 0, 2},

            //Demon
            {6, 0, 2}
        };

        if (ghostDB[ghostType][i] != evid1 && ghostDB[ghostType][i] != evid2)
        {
            evid3 = ghostDB[ghostType][i];
            break;
        }
    }
    return evid3;
}

//Reads the bit position and turns it into a printable string
QString findGhost::findGhostFromNum(int bitPos)
{
    switch (bitPos)
    {
    case 0:
        return "Yokai";
    case 1:
        return "Wraith";
    case 2:
        return "Spirit";
    case 3:
        return "Raiju";
    case 4:
        return "Poltergeist";
    case 5:
        return "Phantom";
    case 6:
        return "Obake";
    case 7:
        return "Myling";
    case 8:
        return "Mare";
    case 9:
        return "Goryo";
    case 10:
        return "Banshee";
    case 11:
        return "Yurei";
    case 12:
        return "The Twins";
    case 13:
        return "Shade";
    case 14:
        return "Revenant";
    case 15:
        return "Onryo";
    case 16:
        return "Oni";
    case 17:
        return "Jinn";
    case 18:
        return "Hantu";
    case 19:
        return "Demon";
    }
    return "ERROR";
}

//Number coded for Evidence into String
QString findGhost::numToEvidString(int num)
{
    switch (num)
    {
    case 0:
        return "Fingerprints";
    case 1:
        return "Ghost Orbs";
    case 2:
        return "Freezing Temperatures";
    case 3:
        return "Spirit Box";
    case 4:
        return "EMF Level 5";
    case 5:
        return "D.O.T.S Projector";
    case 6:
        return "Ghost Writing";
    }
    return "ERROR";
}
