//Bearbeitung: Leo Geiger TIM23

#include <getopt.h>
#include <iostream>
#include <cstdlib>

// Hilfetext
const char * const HELPTXT = {
    "Usage: This program can convert your Json file to ...\n" \
    "-h, --help             Display this information\n" \
    "    --debug            Enable debug mode\n" \
    "-o <file>              Named output of these programm\n" \
    "-v, --version          Display Programm Information\n" \
    "-a, --verbose          Display what is happening\n" \
    "\n" \
    "Our Team: Elias, Philipp, Leo\n" \
    "Constact: info@threemantec.de"
};

// Parameter die gesetzt werden
static int debug = 0;

const option longopts[] =
{
    // Mit der Nummer 1 wird das setzen des Flags gesteuert
    {"debug", no_argument, &debug, 1},
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {"verbose", no_argument, NULL, 'a'},
    {0, 0, 0, 0}
};

static void verbose()
{
    std::cout << "What's happening:\n";
}

static void Help()
{
    std::cout << HELPTXT << std::endl;
    exit(0);
}

static void Version()
{
    std::cout << "Version from " << __DATE__ << std::endl;
    exit(0);
}

int main(int argc, char* argv[])
{
    int optindex = 0;
    int c = 0;

    if(argc < 2)
    {
        std::cout << "See -h for options" << std::endl;
        return 0;
    }
    else
        while((c = getopt_long(argc, argv, "ho:v", longopts, &optindex)) >= 0)
        {
            switch(c)
            {
            case 0:
                // Keine spezifische Abarbeitung der LongOpts derzeit
                break;
            case 'h':
                Help();
                break;
            case 'o':
                std::cout << "Option 'o' wurde mit " << optarg << " aufgerufen" << std::endl;
                break;
            case 'v':
                Version();
                break;
            case 'a':
                verbose();
                break;
            default:
                std::cerr << "Unknown option " << c << std::endl;
                exit(1);
            }
        }

    if (optind < argc) {
        std::cout << "Nonoption arguments ";
        while (optind < argc)
            std::cout << argv[optind++] << " ";
        std::cout << std::endl;
    }

    // Ergebnisse ausgeben falls es welche gibt
    if(debug) std::cout << "DEBUG Modus eingeschalten" << std::endl;

    return 0;
}
