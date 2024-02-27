#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <getopt.h>
bool isJsonFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    char c;
    bool isJson = true;
    bool isFirstChar = true;
    

    while (file.get(c)) {
        if (isFirstChar) {
            if (c != '{' && c != '[') {
                isJson = false;
                break;
            }
            isFirstChar = false;
        }
    }

    if (!isJson) {
        std::cerr << "File is not a Json file: " << filename << std::endl;
    }

    return isJson;

    
}

const char * const HELPTXT = {
    "Usage: ./main [OPTIONS] Json Files\n" \
    "-h --help          displays this Help Text\n"
    "  --debug          Displays Debug Logs\n"
    "-v --Version       Displays the Version of the Programm\n"
    "For more Information contact elias.fahresnchon@threemantec.de or info@threemantec.de\n"
};

const struct option longopts[] =
{
    //Mit der Nummer 1 wird das setzen des Flags gesteuert
//    {"debug",no_argument,&debug,1},
    {"help",no_argument,NULL,'h'},
    {"version",no_argument,NULL,'v'},
    {0,0,0,0}
};
static void Help()
{
    puts(HELPTXT);
    exit(0);
}

static void Version()
{
    puts("Version vom " __DATE__);
    exit(0);
}


int main(int argc, char *argv[]) {
    
    int optindex = {0};
    int c ={0};
    
    if (argc < 2) {
        std::cerr << "Please provide a Json file\n for questions -h or --help\n";
        return 1;
    }
    

    else
        while((c = getopt_long(argc,argv,"ho:v",longopts,&optindex)) >= 0)
        {
            switch(c)
            {
            case 0:
                //Keine spezifische Abarbeitung der LongOpts derzeit
                break;
            case 'h':
                Help();
                break;
            case 'o':
                printf("Option 'o' wurde mit %s aufgerufen\n",optarg);
                break;
            case 'v':
                Version();
                break;
            default:
                fprintf(stderr,"Unknown option %d", c);
                exit(1);
            }
        }
    
    
    
    if (!isJsonFile(argv[1])) {
        return 1;
    }

    // Your code to process the Json file

    return 0;
}