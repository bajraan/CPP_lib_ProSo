#include "pbaProSoTests.hpp"
#include "../00_pbaProSo/pbaProso.hpp"

#include <windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define TEST_PASS   SetConsoleTextAttribute(hConsole,10);std::cout<<"PASS";SetConsoleTextAttribute(hConsole,7);
#define TEST_FAIL   SetConsoleTextAttribute(hConsole,12);std::cout<<"FAIL";SetConsoleTextAttribute(hConsole,7);
#define TEST_UNKN   SetConsoleTextAttribute(hConsole,14);std::cout<<"UNKNOWN";SetConsoleTextAttribute(hConsole,7);

bool debFlag;

template <typename T>
TRes assertTrue(const T& actual, const T& expected) {
    if (actual == expected) {
        return TRes::pass;
    } else {
        return TRes::fail;
    }
}

enum Overload_Type
{
    _int_,
    _string_,
    _stringcharchar_
};

int checkDebFlag(int argc, char* argv[])
{
    char* tmp = argv[1];
    for (int i = 1; i < argc; i++) 
    {
        if (strcmp(tmp , "-deb") == 0) {
            debFlag = 1;return 1;
        }
    }
    debFlag=0;return 0;
}



void TEST__decode_cipherVigenere( void )
{
    std::cout << "----------------------------" << std::endl;
    std::cout << "TEST: decode_cipherVigenere " << std::endl;
    std::cout << "----------------------------" << std::endl;

    const int t_cnt = 1;

    struct tt
    {
        int         Test_id;
        std::string cipher;
        std::string key;
        std::string exp_output;
    };

    tt TestTab[t_cnt]
    {
    //======================================//
    // TEST TABLE                           //
    //======================================//==TEST1==
    1,
    "gwox{RgqssihYspOntqpxs}",              //cipher
    "blorpy",                               //key
    "flag{CiphersAreAwesome}"               //ex_output
    };

    for(int i=0; i<t_cnt; i++)
    {
        TRes TestResult = TRes::unknown;
        std::string out = decode_cipherVigenere(TestTab[i].cipher, TestTab[i].key);
        std::string exp = TestTab[i].exp_output;

        TestResult = assertTrue(out,exp);

        PRTRE_decode_cipherVigenere 
            (   
                TestResult,
                TestTab[i].Test_id,
                TestTab[i].cipher,
                TestTab[i].key, 
                out, 
                exp
            );
    }    
}



void TEST__decode_cipherBacon(void)
{
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "TEST: decode_cipherBacon (string,char,char)     " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    const int t_cnt = 2;

    struct tt
    {
        int           Test_id;
        Overload_Type Overload_ver;
        std::string   cipher;
        char          A;
        char          B;
        std::string   exp_output;
    };

    tt TestTab[t_cnt]
    {
    //=========================================================================================//
    // TEST TABLE                                                                              //
    //=========================================================================================//==TEST1==
    1,
    _stringcharchar_,
    "ABAAAABABAABBABBAABBAABAAAAAABAAAAAAAABAABBABABBAAAAABBABBABABBAABAABABABBAABBABBAABB",   //cipher
    'A',
    'B',
    "ilouebacondontyou",                                                                       //ex_output
    //=========================================================================================//==TEST2==
    2,
    _string_,
    "ABAAAABABAABBABBAABBAABAAAAAABAAAAAAAABAABBABABBAAAAABBABBABABBAABAABABABBAABBABBAABB",   //cipher
    'x',
    'x',
    "ilouebacondontyou"                                                                        //ex_output
    };

    for(int i=0; i<t_cnt; i++)
    {
        TRes TestResult = TRes::unknown;
        std::string out, exp;

        switch(TestTab[i].Overload_ver)
        {
            case(_stringcharchar_) : 
                out = decode_cipherBacon(TestTab[i].cipher, TestTab[i].A ,TestTab[i].B);
                break;

            case(_string_) :
                out = decode_cipherBacon(TestTab[i].cipher);
                break;

            default :
                std::cout << "error" << std::endl;
                break;
        }

        out = decode_cipherBacon(TestTab[i].cipher);

        exp = TestTab[i].exp_output;

        TestResult = assertTrue(out,exp);

        PRTRE_decode_cipherBacon 
            (   
                TestResult,
                TestTab[i].Test_id,
                TestTab[i].cipher,
                out, 
                exp
            );
    }    
}



//===========================================================
// Print Result of decode_cipherVigenere function
//===========================================================
void PRTRE_decode_cipherVigenere
(   
        TRes        TestResult,
        int         Test_id, 
        std::string inp,
        std::string key, 
        std::string out, 
        std::string exp
)
{   
    std::cout << "Test_id: " << Test_id << " ";
    switch(TestResult)
    {
        case TRes::pass:    TEST_PASS break;
        case TRes::fail:    TEST_FAIL break;
        default:            TEST_UNKN break;
    }

    if(debFlag)
        std::cout                           << std::endl
                  << "Cipher  : " << inp    << std::endl
                  << "Key     : " << key    << std::endl
                  << "out     : " << out    << std::endl
                  << "exp_out : " << exp    << std::endl;

    std::cout << std::endl;
}



//===========================================================
// Print Result of decode_cipherBacon function
//===========================================================
void PRTRE_decode_cipherBacon
(   
        TRes        TestResult,
        int         Test_id, 
        std::string inp,
        std::string out, 
        std::string exp
)
{   
    std::cout << "Test_id: " << Test_id << " ";

    switch(TestResult)
    {
        case TRes::pass:    TEST_PASS break;
        case TRes::fail:    TEST_FAIL break;
        default:            TEST_UNKN break;
    }

    if(debFlag)
        std::cout                           << std::endl
                  << "Cipher  : " << inp    << std::endl
                  << "out     : " << out    << std::endl
                  << "exp_out : " << exp    << std::endl;

    std::cout << std::endl;
}