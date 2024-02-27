//Siehe auch https://linux.die.net/man/3/getopt_long

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

//Hilfetext
const char * const HELPTXT = {
    "Usage: options [OPTIONS] file ...\n" \
    "-h, --help             Display this information\n" \
    "    --debug            Enable debug mode\n" \
    "-o <file>              Named output of these programm\n" \
    "-v, --version          Display Programm Information\n" \
    "\n" \
    "For more information contact thomas_staudacher@yahoo.de"
};

//Parameter die gesetzt werden
static int debug = {0};

const struct option longopts[] =
{
    //Mit der Nummer 1 wird das setzen des Flags gesteuert
    {"debug",no_argument,&debug,1},
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

int main(int argc, char* argv[])
{
    int optindex = {0};
    int c = {0};

    if(argc < 2)
    {
        puts("See -h for options");
        return 0;
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

    if (optind < argc) {
        printf("Nonoption arguments ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    //Ergebnisse ausgeben falls es welche gibt
    if(debug) puts("DEBUG Modus eingeschalten");

    return 0;
}